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
    // 设置清屏颜色为灰色
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // 获取当前的视口尺寸
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    int screenWidth = viewport[2];  // 视口的宽度
    int screenHeight = viewport[3]; // 视口的高度

    // 使用着色器
    BindShader(basicShader);

    // 获取 screenSize 统一变量的位置
    GLuint screenSizeLocation = glGetUniformLocation(basicShader->GetProgram(), "screenSize");

    // 传递视口尺寸给着色器中的 screenSize 统一变量
    glUniform2f(screenSizeLocation, screenWidth, screenHeight);

    // 绘制三角形
    triangle->Draw();
}
