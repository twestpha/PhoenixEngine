#include <fstream>

#include "ResourceManager.hpp"
#include "Allocator.hpp"
#include "Assert.hpp"

const char* DATA_PATH = "data\\";

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

void ResourceManager::loadModelFromFileThreaded(const char* filename, Model* model){
    FILE* filePointer;

    char filePath[100];
    strcpy(filePath, DATA_PATH);
    strcat(filePath, filename);
    filePointer = fopen(filePath, "r");

    _Assert(filePointer, "Error opening file.");

    void* buffer;
    size_t result;

    fseek(filePointer, 0, SEEK_END);
    long fileSize = ftell(filePointer);
    rewind(filePointer);

    // allocate memory to contain the whole file:
    buffer = Allocator::Allocate(fileSize);

    _Assert(buffer, "Error allocating model memory.");

    fread(buffer, 1, fileSize, filePointer);

    // Debug print - remove later
    // for(int i(0); i < fileSize/sizeof(float); ++i){
    //     printf("%f ", ((float*)buffer)[i]);
    //
    //     if(i % 8 == 7){
    //         printf("\n");
    //     }
    // }

    model->SetData(buffer);
    model->vertexCount = fileSize/(sizeof(float) * 8);

    fclose(filePointer);
}
