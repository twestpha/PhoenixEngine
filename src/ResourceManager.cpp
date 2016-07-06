#include "ResourceManager.hpp"

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
    printf("[Loading] Model: %s\n", filename);
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

    char * buffer;
    size_t result;

    // size
    fseek (filePointer, 0, SEEK_END);
    long lSize = ftell (filePointer);
    rewind (filePointer);

    // allocate memory to contain the whole file:
    buffer = (char*) malloc (sizeof(char)*lSize);
    if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}

    // copy the file into the buffer:
    result = fread (buffer,1,lSize,filePointer);
    // buffer[int(lSize)] = '\0';

    for(int i(0); i < lSize; ++i){
        printf("%c", buffer[i]);
    }
    // if (result != lSize) {fputs ("Reading error",stderr); exit (3);}

    /* the whole file is now loaded in the memory buffer. */


    // free (buffer);

    fclose(filePointer);
}
