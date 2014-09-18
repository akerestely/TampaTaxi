#pragma once
#include "Model.h"
#include "CameraSpectator.h"
class Scene
{
	Model *model;
	CCamera *cam;
public:
	Scene(Model *model,CCamera *cam=NULL);
	void Render();
	~Scene(void);
};
