#include "Renderer.h"

Renderer::Renderer(Window& parent) : OGLRenderer(parent) {
    triangle = Mesh::GenerateTriangle();

    basicShader = new Shader("basicVertex.glsl", "colourFragment.glsl");

    if (!basicShader->LoadSuccess()) {
        std::cout << "Fail to load basicShader" << std::endl;
        return;
    }

    init = true;
}

Renderer::~Renderer(void) {
    delete triangle;
    delete basicShader;
}

void Renderer::RenderScene() {
    // ����������ɫΪ��ɫ
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // ��ȡ��ǰ���ӿڳߴ�
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    int screenWidth = viewport[2];  // �ӿڵĿ��
    int screenHeight = viewport[3]; // �ӿڵĸ߶�

    // ʹ����ɫ��
    BindShader(basicShader);

    // ��ȡ screenSize ͳһ������λ��
    GLuint screenSizeLocation = glGetUniformLocation(basicShader->GetProgram(), "screenSize");

    // �����ӿڳߴ����ɫ���е� screenSize ͳһ����
    glUniform2f(screenSizeLocation, screenWidth, screenHeight);

    // ����������
    triangle->Draw();
}
