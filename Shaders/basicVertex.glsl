#version 330 core

layout(location = 0) in vec3 position;  // 顶点位置输入
layout(location = 1) in vec4 colour;    // 顶点颜色输入

out Vertex{
    vec4 colour;    // 传递颜色到片段着色器
} OUT;

void main(void) {
    // 设置顶点位置 (标准化设备坐标 NDC)
    gl_Position = vec4(position, 1.0);

    // 传递颜色
    OUT.colour = colour;
}
