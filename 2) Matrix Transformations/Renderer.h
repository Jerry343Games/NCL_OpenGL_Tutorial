#pragma once
#include "../nclgl/OGLRenderer.h"
class Renderer:public OGLRenderer
{
public:
    Renderer(Window& parent);
    virtual ~Renderer(void);
    virtual void RendererScene();
    void SwitchToOrthographic();

    inline void SetScale(float scale);
    inline void SetRotation(float location);
    inline void SetPosition(Vector3 position);
protected:
    Mesh* triangle;
    Shader* shader;
    float scale;
    float rotation;
    Vector3 position;
};

