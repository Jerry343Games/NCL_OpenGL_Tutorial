#pragma once
#include "../nclgl/OGLRenderer.h"
class Renderer:public OGLRenderer
{
public:
    Renderer(Window& parent);
    virtual ~Renderer(void);
    virtual void RendererScene();
    void SwitchToOrthographic();

protected:

};

