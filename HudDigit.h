#pragma once
#include "Texture.h"
#include "Object3d.h"
#include "Drawable.h"

class HudDigit : public Object3d, public Drawable
{
	int digit;
	double gaugeRadius;
public:
	HudDigit(Point center,int digit,double gaugeRadius);
	void Draw() override;
	void setDigit(int digit);
	~HudDigit(void);
};
