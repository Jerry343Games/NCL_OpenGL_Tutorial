#pragma once
#include "Matrix4.h"
#include "Vector3.h"
/*
*首先要有构造和注销函数
*第二要有刷新相机方法
*第三要有获取和设置相机各个参数的方法
*/

class Camera
{
public:
    //相机无参构造函数
    Camera(void)
    {
        rotationHorizontal =0.0f;
        rotationVertical = 0.0f;
    }

    //相机含参构造函数
    Camera(float rHorizental, float rVertical, Vector3 position)
    {
        rotationHorizontal = rHorizental;
        rotationVertical = rVertical;
        this->position = position;
    }

    //注销相机方法
    ~Camera(void);

    //相机刷新方法
    void UpdateCamera(float deltaTime=1.0f);

    Matrix4 BuildViewMatrix();

    //获取相机位置
    Vector3 GetPosition() const
    {
        return position;
    }
    //设置相机位置
    void SetPosition(Vector3 position)
    {
        this->position = position; 
    }
    //获取水平旋转
    float GetRotationHorizontal() const
    {
        return rotationHorizontal;
    }
    //设置水平旋转
    void SetRotationHorizontal(float rHorizontal)
    {
        rotationHorizontal = rHorizontal;
    }
    //获取竖直旋转
    float GetRotationVertical() const
    {
        return rotationVertical;
    }
    //设置竖直旋转
    void SetRotationVertical(float rVertical)
    {
        rotationVertical = rVertical;
    }
    
protected:
    float rotationHorizontal;
    float rotationVertical;
    Vector3 position;
};
