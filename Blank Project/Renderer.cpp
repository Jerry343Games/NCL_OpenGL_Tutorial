#include "Renderer.h"


Renderer::Renderer(Window& parent) : OGLRenderer(parent) {
    triangle = Mesh::GenerateTriangle();
    cube = Mesh::LoadFromMeshFile("OffsetCubeY.msh");  // Load cube from file

    basicShader = new Shader("basicVertex.glsl", "colourFragment.glsl");

    if (!basicShader->LoadSuccess()) {
        std::cout << "Failed to load basicShader" << std::endl;
        return;
    }

    glEnable(GL_DEPTH_TEST);  // Enable depth testing for 3D rendering

    init = true;
}


Renderer::~Renderer() {
    delete triangle;
    delete cube;         // Delete the cube
    delete basicShader;
}


void Renderer::RenderScene() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    BindShader(basicShader);

    // Optional: Set up any necessary uniforms here
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    int screenWidth = viewport[2];
    int screenHeight = viewport[3];

    GLuint screenSizeLocation = glGetUniformLocation(basicShader->GetProgram(), "screenSize");
    glUniform2f(screenSizeLocation, screenWidth, screenHeight);

    // Render the triangle
    triangle->Draw();

    // Render the cube
    cube->Draw();
}
