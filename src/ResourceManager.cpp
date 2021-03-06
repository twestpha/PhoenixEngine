#include <fstream>
#include <sys/stat.h>

#include "ResourceManager.hpp"
#include "Allocator.hpp"
#include "Assert.hpp"

const char* DATA_PATH = "data\\";

// Model Data
const int BYTES_PER_VERTEX = 32; // 4 bytes per entry, 8 entries per vertex

//
const int FILEPATH_BUFFER_SIZE = 128;
const int NO_STAT_ERROR = 0;

ResourceManager* ResourceManager::instancePointer;

ResourceManager* ResourceManager::Instance(){
    if(!instancePointer){
        instancePointer = new ResourceManager();
    }
    return instancePointer;
}

ResourceManager::ResourceManager(){

}

ResourceManager::~ResourceManager(){
    Join();
}

void ResourceManager::Join(){
    for(int i(0); i < loadingThreads.size(); ++i){
        loadingThreads[i].join();
    }
}

void ResourceManager::loadModelFromFile(const char* filename, Model* model){
    printf("[LOADING] Model: %s\n", filename);
    loadingThreads.push_back(std::thread(ResourceManager::loadModelFromFileThreaded, this, &(*filename), &(*model)));
}

unsigned long ResourceManager::GetFileSize(const char* filename){
    struct stat statBuffer;
    int result = stat(filename, &statBuffer);
    return result == NO_STAT_ERROR ? statBuffer.st_size : 0;
}

void ResourceManager::loadModelFromFileThreaded(const char* filename, Model* model){
    // I'm like 90% sure this could result in two copies in an absolute worst-case race condition
    // but... nothing's happened yet.
    // Probably __SUPER__ helpful... http://en.cppreference.com/w/cpp/thread/mutex
    if(resourceMap[filename]){
        model = (Model*) resourceMap[filename];
    } else {
        resourceMap[filename] = model; // Pre-register the pointer

        FILE* filePointer;
        char filePath[FILEPATH_BUFFER_SIZE];
        strcpy(filePath, DATA_PATH);
        strcat(filePath, filename);
        filePointer = fopen(filePath, "rb");
        Assert_(filePointer, "Error opening file.");

        void* buffer;

        unsigned long fileSize = GetFileSize(filePath);
        unsigned int vertexCount = fileSize/BYTES_PER_VERTEX;
        Assert_(fileSize == vertexCount * BYTES_PER_VERTEX, "Error ");

        buffer = Allocator::Allocate(fileSize);
        Assert_(buffer, "Error allocating model memory.");

        unsigned int result = fread(buffer, 1, fileSize, filePointer);
        Assert_(buffer, "Error reading model to buffer.");
        Assert_(result == fileSize, "Error reading model size.");

        model->SetData(buffer);
        model->vertexCount = vertexCount;

        fclose(filePointer);
    }
}
