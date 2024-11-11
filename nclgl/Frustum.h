#pragma once

#include "Plane.h"
class SceneNode;
class Matrix4;

//包含 6 个平面，分别代表视锥体的 6 个边。一个公有函数生成视锥体，并根据一个矩阵来判断一个 SceneNode 是否在视锥体内。
class Frustum {
public:
    Frustum(void) {};
    ~Frustum(void) {};

    void FromMatrix(const Matrix4& mvp);
    bool InsideFrustum(SceneNode& n);

protected:
    Plane planes[6];
};
