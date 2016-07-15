#include "Model.hpp"

Model::Model(){
}

Model::SetData(void* data){
    vertices = (Vertex**) data;
}

Vertex** Model::GetData(){
    return vertices;
}
