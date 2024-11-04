#include "Camera.h"
#include<algorithm>

#include "nclgl/Window.h"

void Camera::UpdateCamera(float deltaTime)
{
    rotationHorizontal += Window::GetMouse()->GetRelativePosition().x;
    rotationVertical -= Window::GetMouse()->GetRelativePosition().y;

    rotationHorizontal=std::min(rotationHorizontal,90.0f);
    rotationHorizontal=std::max(rotationHorizontal,-90.0f);

    if(rotationHorizontal>360.0f)
    {
        rotationHorizontal=0;
    }
    if(rotationVertical<0)
    {
        rotationVertical=360;
    }

    Matrix4 rotation = Matrix4::Rotation(rotationHorizontal, Vector3(0,1,0));

    Vector3 forward = rotation * Vector3(0, 0, -1);

    Vector3 right = rotation * Vector3(1, 0, 0);

    float speed = 30.0f*deltaTime;

    if(Window::GetKeyboard()->KeyDown(KEYBOARD_W))
    {
        position += forward * speed;
    }
    if(Window::GetKeyboard()->KeyDown(KEYBOARD_S))
    {
        position -= forward * speed;
    }
    if(Window::GetKeyboard()->KeyDown(KEYBOARD_A))
    {
        position -= right * speed;
    }
    if(Window::GetKeyboard()->KeyDown(KEYBOARD_D))
    {
        position += right * speed;
    }

    if(Window::GetKeyboard()->KeyDown(KEYBOARD_SHIFT))
    {
        position.y += speed;
    }
    if(Window::GetKeyboard()->KeyDown(KEYBOARD_CONTROL))
    {
        position.y -= speed;
    }
}

Matrix4 Camera::BuildViewMatrix()
{
    return Matrix4 ::Rotation(-rotationVertical, Vector3(1, 0, 0))*Matrix4::Rotation(rotationHorizontal,Vector3(0,1,0))*Matrix4::Translation(-position);
}

Camera::~Camera()
{
    
}





