﻿#include "Renderer.h"

#include "Camera.h"

Camera camera;

Renderer::Renderer(Window& parent) : OGLRenderer(parent) {
    triangle = Mesh::GenerateTriangle();
    texture = SOIL_load_OGL_texture(TEXTUREDIR"brick.tga",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,0);
    
    shader = new Shader("DefaultTextureVertex.glsl", "DefaultTextureFrag.glsl");

    if (!shader->LoadSuccess()) {
        return;
    }

    camera = Camera(0.0f,0.0f,Vector3(0,0,0.0f));

    filtering=true;
    repeating=false;
    init = true;
    
}

Renderer::~Renderer(void) {
    delete triangle;
    delete shader;
    glDeleteTextures(1,&texture);
}

void Renderer::UpdateScene(float deltaTime)
{
    camera.UpdateCamera(deltaTime);
    viewMatrix = camera.BuildViewMatrix();
}

void Renderer::RenderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    BindShader(shader);

    glUniformMatrix4fv(glGetUniformLocation(shader->GetProgram(), "viewMatrix"),
                       1, false, viewMatrix.values);

    UpdateShaderMatrices();
    glUniform1i(glGetUniformLocation(shader->GetProgram(), "diffuseTex"), 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    triangle->Draw();

}

void Renderer::UpdateTextureMatrix(float value)
{
    Matrix4 push =Matrix4::Translation(Vector3(-0.5,0.5,0));
    Matrix4 pop = Matrix4::Translation(Vector3(0.5f,0.5f,0));
    Matrix4 rotation =Matrix4::Rotation(value, Vector3(0,0,1));
    textureMatrix =pop*rotation*push;
}

void Renderer::ToggleFiltering()
{
    filtering = ! filtering ;
    glBindTexture ( GL_TEXTURE_2D , texture );
    glTexParameteri ( GL_TEXTURE_2D , GL_TEXTURE_MIN_FILTER ,
    filtering ? GL_LINEAR : GL_NEAREST );
    glTexParameteri ( GL_TEXTURE_2D , GL_TEXTURE_MAG_FILTER ,
    filtering ? GL_LINEAR : GL_NEAREST );
    glBindTexture ( GL_TEXTURE_2D , 0);

}

void Renderer::ToggleRepeating()
{
    repeating = ! repeating ;
    SetTextureRepeating ( texture , repeating );
}



