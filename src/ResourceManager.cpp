#include <fstream>
#include <sys/stat.h>

#include "ResourceManager.hpp"
#include "Allocator.hpp"
#include "Assert.hpp"

const char* DATA_PATH = "data\\";
const int BYTES_PER_VERTEX = 32; // 4 bytes per entry, 8 entries per vertex

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

    // register data with map, probably
}

// TODO make this member function
long GetFileSize(const char* filename){
    struct stat stat_buf;
    int rc = stat(filename, &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}

void ResourceManager::loadModelFromFileThreaded(const char* filename, Model* model){
    FILE* filePointer;
    char filePath[100];
    strcpy(filePath, DATA_PATH);
    strcat(filePath, filename);
    filePointer = fopen(filePath, "rb");
    _Assert(filePointer, "Error opening file.");

    void* buffer;

    unsigned int fileSize = GetFileSize(filePath);
    unsigned int vertexCount = fileSize/BYTES_PER_VERTEX;
    _Assert(fileSize == vertexCount * BYTES_PER_VERTEX, "Error ");

    buffer = Allocator::Allocate(fileSize);
    _Assert(buffer, "Error allocating model memory.");

    unsigned int result = fread(buffer, 1, fileSize, filePointer);
    _Assert(buffer, "Error reading model to buffer.");
    _Assert(result == fileSize, "Error reading model size.");

    // Debug print - remove later
    // for(int i(0); i < vertexCount; ++i){
    //     printf("[%d] ", i);
    //
    //     for(int j(0); j < 8; ++j){
    //         printf("%f ", ((float*)buffer)[i * 8 + j]);
    //     }
    //
    //     printf("\n");
    // }

    model->SetData(buffer);
    model->vertexCount = vertexCount;

    fclose(filePointer);
}
