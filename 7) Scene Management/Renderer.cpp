#include "Renderer.h"
#include "nclgl/CubeRobot.h"
#include "../nclgl/Camera.h"
#include <algorithm> // 用于 std::sort

Renderer::Renderer(Window& parent) : OGLRenderer(parent) {
    camera = new Camera(0.0f, 0.0f, Vector3(0, 100, 750.0f));
    quad = Mesh::GenerateQuad();
    cube = Mesh::LoadFromMeshFile("OffsetCubeY.msh");

    shader = new Shader("SceneVertex.glsl", "SceneFragment.glsl");

    texture = SOIL_load_OGL_texture(TEXTUREDIR "stainedglass.tga",
                                    SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 0);

    if (!shader->LoadSuccess() || !texture) {
        return;
    }

    root = new SceneNode();

    for (int i = 0; i < 5; ++i) {
        SceneNode* s = new SceneNode();
        s->SetColour(Vector4(1.0f, 1.0f, 1.0f, 0.5f));
        s->SetTransform(Matrix4::Translation(Vector3(0, 100.0f, -300.0f + 100.0f + 100 * i)));
        s->SetModelScale(Vector3(100.0f, 100.0f, 100.0f));
        s->SetBoundingRadius(100.0f);
        s->SetMesh(quad);
        s->SetTexture(texture);
        root->AddChild(s);
    }

    root->AddChild(new CubeRobot(cube));

    projMatrix = Matrix4::Perspective(1.0f, 10000.0f, (float)width / (float)height, 45.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    init = true;
}

Renderer::~Renderer(void) {
    delete root;
    delete quad;
    delete camera;
    delete cube;
    delete shader;
    glDeleteTextures(1, &texture);
}

void Renderer::UpdateScene(float dt) {
    camera->UpdateCamera(dt);
    viewMatrix = camera->BuildViewMatrix();
    frameFrustum.FromMatrix(projMatrix * viewMatrix);
    root->Update(dt);
}

//构建不透明和透明的 SceneNode 列表。通过递归函数 BuildNodeLists 从场景图的根节点开始。对于每个节点，
//首先检查它是否在视锥体内，如果是的话，计算它与摄像机的距离，并将其放入正确的 vector 中。然后，每个节点
//的子节点依次调用 BuildNodeLists，构建两个包含所有可见节点的完整 vector。
void Renderer::BuildNodeLists(SceneNode* from) {
    if (frameFrustum.InsideFrustum(*from)) {
        Vector3 dir = from->GetWorldTransform().GetPositionVector() - camera->GetPosition();
        from->SetCameraDistance(Vector3::Dot(dir, dir));  // 使用距离平方

        if (from->GetColour().w < 1.0f) {  // alpha 值小于 1 的节点认为是透明的
            transparentNodeList.push_back(from);
        } else {
            nodeList.push_back(from);
        }
    }

    for (vector<SceneNode*>::const_iterator i = from->GetChildIteratorStart(); i != from->GetChildIteratorEnd(); ++i) {
        BuildNodeLists((*i));
    }
}

//通过函数指针 CompareByCameraDistance 对节点按距离进行排序。
void Renderer::SortNodeLists() {
    std::sort(transparentNodeList.rbegin(), transparentNodeList.rend(), SceneNode::CompareByCameraDistance);
    std::sort(nodeList.begin(), nodeList.end(), SceneNode::CompareByCameraDistance);
}

//绘制场景图，分为两个循环，首先绘制不透明节点，然后绘制透明节点。
void Renderer::DrawNodes() {
    for (const auto& i : nodeList) {
        DrawNode(i);
    }
    for (const auto& i : transparentNodeList) {
        DrawNode(i);
    }
}

void Renderer::DrawNode(SceneNode* n) {
    if (n->GetMesh()) {
        Matrix4 model = n->GetWorldTransform() * Matrix4::Scale(n->GetModelScale());
        glUniformMatrix4fv(glGetUniformLocation(shader->GetProgram(), "modelMatrix"), 1, false, model.values);

        glUniform4fv(glGetUniformLocation(shader->GetProgram(), "nodeColour"), 1, (float*)&n->GetColour());

        texture = n->GetTexture();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        glUniform1i(glGetUniformLocation(shader->GetProgram(), "useTexture"), texture);

        n->Draw(*this);
    }
}

//调用 DrawNodes 来绘制两个节点列表。绘制完后清空 SceneNode 的 vector，避免每帧重复添加节点。
void Renderer::RenderScene() {
    BuildNodeLists(root);
    SortNodeLists();

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    BindShader(shader);
    UpdateShaderMatrices();

    glUniform1i(glGetUniformLocation(shader->GetProgram(), "diffuseTex"), 0);
    DrawNodes();

    ClearNodeLists();
}

void Renderer::ClearNodeLists() {
    transparentNodeList.clear();
    nodeList.clear();
}








