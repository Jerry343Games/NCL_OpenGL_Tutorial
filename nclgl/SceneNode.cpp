#include "SceneNode.h"

SceneNode::SceneNode(Mesh* mesh, Vector4 colour) {
    this->mesh = mesh;
    this->colour = colour;
    parent = NULL;
    modelScale = Vector3(1, 1, 1);
}

//不会删除Mesh变量，只是删除节点，因此可以多个SceneNode指向同的网格实例，而不必每个节点都拥有自己的 Mesh
SceneNode::~SceneNode(void) {
    for (unsigned int i = 0; i < children.size(); ++i) {
        delete children[i];
    }
}

//添加物体到子节点中，并将其父节点设为当前节点
void SceneNode::AddChild(SceneNode* s) {
    children.push_back(s);
    s->parent = this;
}

void SceneNode::Draw(const OGLRenderer& r) {
    if (mesh) { mesh->Draw(); }
}

void SceneNode::Update(float dt) {
    if (parent) {
        worldTransform = parent->worldTransform * transform;
    } else {
        worldTransform = transform;
    }

    for (auto i = children.begin(); i != children.end(); ++i) {
        (*i)->Update(dt);
    }
}
