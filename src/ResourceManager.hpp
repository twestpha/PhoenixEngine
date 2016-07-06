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

    void loadModelFromFileThreaded(const char* filename, Model* model);

    std::map<char*, Resource*> resourceMap;

};
