#pragma once
#include "../nclgl/OGLRenderer.h"

class Renderer : public OGLRenderer {
public:
	Renderer(Window& parent);
	virtual ~Renderer(void);

	virtual void RenderScene();
	void SwitchToPerspective();
	void SwitchToOrthographic();

	inline void SetScale(float s) { scale = s; }
	inline void SetRotation(float r) { rotation = r; }
	inline void SetPosition(Vector3 p) { position = p; }

    inline void SetCamPos(Vector3 inputDir)
	{
	    camPos+=inputDir;
	}

protected:
	Mesh* triangle;
	Shader* shader;
	float scale;
	float rotation;
	Vector3 position;

    Vector3 camPos;
};