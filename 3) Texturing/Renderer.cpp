#include "Renderer.h"

#include "2) Matrix Transformations/Camera.h"

Camera camera;

Renderer::Renderer(Window& parent) : OGLRenderer(parent) {
    triangle = Mesh::GenerateTriangle();
    texture = SOIL_load_OGL_texture(TEXTUREDIR"brick.tga",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,0);
    
    shader = new Shader("DefaultTextureVertex.glsl", "DefaultTextureFrag.glsl");

    if (!shader->LoadSuccess()) {
        return;
    }

    filtering=true;
    repeating=false;
    init = true;
    
    SwitchToOrthographic();
}

Renderer::~Renderer(void) {
    delete triangle;
    delete shader;
    glDeleteTextures(1,&texture);
}

void Renderer::SwitchToPerspective() {
    projMatrix = Matrix4::Perspective(1.0f, 10000.0f, (float)width / (float)height, 45.0f);

}

void Renderer::SwitchToOrthographic() {
    projMatrix = Matrix4::Orthographic(-1.0f, 10000.0f, width / 2.0f, -width / 2.0f, height / 2.0f, -height / 2.0f);

}

void Renderer::RenderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    BindShader(shader);
    UpdateShaderMatrices();
    glUniform1i(glGetUniformLocation(shader->GetProgram(), "diffuseTex"), 0); // 最后一个参数
    glActiveTexture(GL_TEXTURE0); // 应匹配此编号
    glBindTexture(GL_TEXTURE_2D, texture);

    //glUniformMatrix4fv(glGetUniformLocation(shader->GetProgram(), "projMatrix"),1, false, projMatrix.values);

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
