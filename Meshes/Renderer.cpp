﻿#include "Renderer.h"

#include "2) Matrix Transformations/Camera.h"

Camera camera;

Renderer::Renderer(Window& parent) : OGLRenderer(parent) {
    triangle = Mesh::GenerateTriangle();
    //路径 自动检测格式 新建一个纹理对象而不是覆盖原有的 0表示使用默认选项加载纹理，而不应用任何额外的特效或压缩
    texture =SOIL_load_OGL_texture(TEXTUREDIR"brick.tga", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,0);
    shader = new Shader("MatrixVertex.glsl", "colourFragment.glsl");

    if (!shader->LoadSuccess()) {
        return;
    }

    init = true;

    SwitchToOrthographic();
}

Renderer::~Renderer(void) {
    delete triangle;
    delete shader;

}

void Renderer::SwitchToPerspective() {
    projMatrix = Matrix4::Perspective(1.0f, 10000.0f, (float)width / (float)height, 45.0f);

}

void Renderer::SwitchToOrthographic() {
    projMatrix = Matrix4::Orthographic(-1.0f, 10000.0f, width / 2.0f, -width / 2.0f, height / 2.0f, -height / 2.0f);

}

void Renderer::RenderScene() {
    glClear(GL_COLOR_BUFFER_BIT);

    BindShader(shader);

    glUniformMatrix4fv(glGetUniformLocation(shader->GetProgram(), "projMatrix"),
        1, false, projMatrix.values);

    glUniformMatrix4fv(glGetUniformLocation(shader->GetProgram()
        , "viewMatrix"), 1, false, viewMatrix.values);

    for (int i = 0; i < 3; ++i) {
        Vector3 tempPos = position;
        tempPos.z += (i * 500.0f);
        tempPos.x -= (i * 100.0f);
        tempPos.y -= (i * 100.0f);
		
        modelMatrix = Matrix4::Translation(tempPos) *
                      Matrix4::Rotation(rotation, Vector3(0, 1, 0)) *
                      Matrix4::Scale(Vector3(scale, scale, scale));
	    
	    
        glUniformMatrix4fv(glGetUniformLocation(shader->GetProgram(), "modelMatrix"), 1, false, modelMatrix.values);
        triangle->Draw();
    }
}
void Renderer::UpdateScene(float deltaTime)
{
    camera.UpdateCamera(deltaTime);
    viewMatrix = camera.BuildViewMatrix();
}
