#include <map>
#include <vector>
#include <thread>

#include "Resource.hpp"
#include "Model.hpp"

#pragma once

class ResourceManager {
public:
    static ResourceManager* Instance();
    static ResourceManager* instancePointer;

    std::vector<std::thread> loadingThreads;

    void Join();

    void loadModelFromFile(const char* filename, Model* model);
private:
    ResourceManager();
    ~ResourceManager();

    unsigned long GetFileSize(const char* filename);

    void loadModelFromFileThreaded(const char* filename, Model* model);

    std::map<const char*, Resource*> resourceMap;

};
