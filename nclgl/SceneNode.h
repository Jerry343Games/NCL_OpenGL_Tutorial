﻿#pragma once
#include "Matrix4.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Mesh.h"
#include <vector>

class SceneNode
{
public:
    SceneNode(Mesh* mesh=NULL, Vector4 colour=Vector4(1,1,1,1));

    //析构销毁所有子节点
    ~SceneNode();

    //位置
    void SetTransform(const Matrix4& matrix) { transform = matrix; }
    const Matrix4& GetTransform() const { return transform; }
    Matrix4 GetWorldTransform() const { return worldTransform; }

    //颜色
    Vector4 GetColour() const { return colour; }
    void SetColour(Vector4 c) { colour = c; }

    //缩放
    Vector3 GetModelScale() const { return modelScale; }
    void SetModelScale(Vector3 s) { modelScale = s; }

    //模型
    Mesh* GetMesh() const { return mesh; }
    void SetMesh(Mesh* m) { mesh = m; }

    //添加子物体 绘制
    void AddChild(SceneNode* s);
    virtual void Update(float dt);
    virtual void Draw(const OGLRenderer& r);

    //遍历子物体的迭代器
    std::vector<SceneNode*>::const_iterator GetChildIteratorStart() { return children.begin(); }
    std::vector<SceneNode*>::const_iterator GetChildIteratorEnd() { return children.end(); }

protected:
    SceneNode* parent;
    Mesh* mesh;
    Matrix4 worldTransform;
    Matrix4 transform;
    Vector3 modelScale;
    Vector4 colour;
    std::vector<SceneNode*> children;

};
