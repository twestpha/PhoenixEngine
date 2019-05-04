#ifndef MODEL_H
#define MODEL_H

#include "Resource.hpp"
#include "Math3D.hpp"

struct Vertex {
    Vector3 position;
    Vector3 normal;
    Vector2 uvcoord;
};

class Model : public Resource {
public:
    Model();
    SetData(void* data);
    Vertex* GetData();
    int vertexCount;
private:
    Vertex* vertices;
};

#endif // MODEL_H
