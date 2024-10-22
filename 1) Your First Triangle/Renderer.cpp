#include "Renderer.h"

Renderer::Renderer(Window& parent) : OGLRenderer(parent) {
    // 定义三角形的顶点数据，包含位置和颜色
    GLfloat vertices[] = {
        // 位置           // 颜色
         0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // 顶部 红色
         0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // 右下 绿色
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f  // 左下 蓝色
    };

    // 生成 VAO 和 VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // 绑定 VAO
    glBindVertexArray(VAO);

    // 绑定并填充 VBO 数据
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 位置属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // 颜色属性
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // 解绑 VAO
    glBindVertexArray(0);

    // 初始化着色器
    basicShader = new Shader("basicVertex.glsl", "colourFragment.glsl");


    if (!basicShader->LoadSuccess()) {
        return;
    }

    init = true;
}

/// <summary>
/// Clear buffer
/// </summary>
/// <param name=""></param>
Renderer::~Renderer(void) {
    glDeleteVertexArrays(1, &VAO);  // 删除 VAO
    glDeleteBuffers(1, &VBO);  // 删除 VBO
    delete basicShader;  // 删除着色器
}

/// <summary>
/// Actual rendering process
/// </summary>
void Renderer::RenderScene() {
    glClearColor(0.5, 0.5, 0.5, 1.0f);  // 设置清屏颜色为灰色
    glClear(GL_COLOR_BUFFER_BIT);  // 清除颜色缓冲区

    // 使用着色器
    BindShader(basicShader);

    // 绘制三角形
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);  // 绘制3个顶点的三角形
    glBindVertexArray(0);
}

