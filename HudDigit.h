#pragma once
#include "drawable.h"
#include"Texture.h"
class HudDigit :
	public Drawable
{
	int digit;
	double gaugeRadius;
public:
	HudDigit();
	HudDigit(Point center,int digit,double gaugeRadius);
	void Draw() override;
	void setDigit(int digit);
	~HudDigit(void);
};
