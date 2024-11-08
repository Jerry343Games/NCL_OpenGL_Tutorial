#include "Renderer.h"

Renderer::Renderer(Window& parent):OGLRenderer(parent)
{
    meshes[0] = Mesh::GenerateTriangle();
    meshes[1] = Mesh::GenerateQuad();

    texture[0] = SOIL_load_OGL_texture(TEXTUREDIR"brick.tga", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 0);
    texture[1] = SOIL_load_OGL_texture(TEXTUREDIR"star.png",SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 0);

    if (!texture[0]||!texture[1])
    {
        return;
    }

    SetTextureRepeating(texture[0], true);
    SetTextureRepeating(texture[1], true);

    shader = new Shader("DefaultTextureVertex.glsl", "StencilFragment.glsl");
    if (!shader->LoadSuccess()) {
        return;
    }
    usingScissor = false;
    usingStencil = false;
    init = true;

    BindShader(shader);

    textureMatrix = Matrix4::Scale(Vector3(1, 1, 1));
    UpdateShaderMatrices();

    glUniform1i(glGetUniformLocation(shader->GetProgram(), "diffuseTex"), 0);

    if (usingStencil) {
        glEnable(GL_STENCIL_TEST);

        glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
        glStencilFunc(GL_ALWAYS, 2, ~0);
        glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);

        glBindTexture(GL_TEXTURE_2D, texture[1]);
        meshes[1]->Draw();

        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
        glStencilFunc(GL_EQUAL, 2, ~0);
        glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
    }

    glBindTexture(GL_TEXTURE_2D, texture[0]);
    meshes[0]->Draw();

    glDisable(GL_SCISSOR_TEST);
    glDisable(GL_STENCIL_TEST);
}


//析构函数
Renderer::~Renderer()
{
    delete meshes[0];
    delete meshes[1];
    glDeleteTextures(2, texture);
    delete shader;
}

//开启区域裁剪
void Renderer::ToggleScissor() {
    usingScissor = !usingScissor;
}

//开启模板测试
void Renderer::ToggleStencil() {
    usingStencil = !usingStencil;
}

void Renderer::RenderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    if (usingScissor) {
        glEnable(GL_SCISSOR_TEST);
        glScissor((float)width / 2.5f, (float)height / 2.5f, (float)width / 5.0f, (float)height / 5.0f);
    }
}


