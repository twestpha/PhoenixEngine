#include <fstream>
#include <sys/stat.h>

#include "ResourceManager.hpp"
#include "Allocator.hpp"
#include "Assert.hpp"

const char* DATA_PATH = "data\\";
const int BYTES_PER_VERTEX = 32; // 4 bytes per entry, 8 entries per vertex
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
    if(resourceMap[filename]){
        model = (Model*) resourceMap[filename];
    } else {
        resourceMap[filename] = model; // Pre-register the pointer

        FILE* filePointer;
        char filePath[FILEPATH_BUFFER_SIZE];
        strcpy(filePath, DATA_PATH);
        strcat(filePath, filename);
        filePointer = fopen(filePath, "rb");
        _Assert(filePointer, "Error opening file.");

        void* buffer;

        unsigned long fileSize = GetFileSize(filePath);
        unsigned int vertexCount = fileSize/BYTES_PER_VERTEX;
        _Assert(fileSize == vertexCount * BYTES_PER_VERTEX, "Error ");

        buffer = Allocator::Allocate(fileSize);
        _Assert(buffer, "Error allocating model memory.");

        unsigned int result = fread(buffer, 1, fileSize, filePointer);
        _Assert(buffer, "Error reading model to buffer.");
        _Assert(result == fileSize, "Error reading model size.");

        model->SetData(buffer);
        model->vertexCount = vertexCount;

        fclose(filePointer);
    }
}
