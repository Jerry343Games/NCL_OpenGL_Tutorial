#include "Renderer.h"



Renderer::Renderer(Window &parent):OGLRenderer(parent)
{
    triangle =Mesh::GenerateTriangle();

    shader =new Shader("MatrixVertex.glsl","ColorFragment.glsl");
    if(!shader->LoadSuccess())
    {
        return;
    }
    init =true;

    SwitchToOrthographic();
}

Renderer::~Renderer()
{
    delete shader;
    delete triangle;
}

void Renderer::SwitchToPerspective()
{
    projMatrix = Matrix4::Perspective(1.0f,1000.0f,(float)width/(float)height,45);
}

void Renderer::SwitchToOrthographic()
{
    projMatrix = Matrix4::Orthographic(-1.0f,10000.0f,width/2.0f,-width/2.0f,height/2.0f,-height/2.0f);
}

void Renderer::RenderScene()
{
    Vector4 grey = Vector4(0.1f,0.1f,0.1f,1.0f);
    glClearColor(grey.x, grey.y, grey.z, grey.w);
    glClear(GL_COLOR_BUFFER_BIT);

    BindShader(shader);

    glUniformMatrix4fv(glGetUniformLocation(shader->GetProgram(),"projMatrix"),1,false,projMatrix.values);

    glUniformMatrix4fv(glGetUniformLocation(shader->GetProgram(),"viewMatrix"),1,false,viewMatrix.values);

    for (int i = 0;i<3;i++)
    {
        Vector3 temPos=position;
        temPos.x +=(i*500.0f);
        temPos.y +=(i*100.0f);
        temPos.z +=(i*100.0f);

        modelMatrix = Matrix4::Translation(temPos)*Matrix4::Rotation(rotation,Vector3(0,1,0))*Matrix4::Scale(Vector3(scale,scale,scale));
        glUniformMatrix4fv ( glGetUniformLocation (shader -> GetProgram () ," modelMatrix "),1,false , modelMatrix.values );
        
        triangle->Draw();
        
    }
}





