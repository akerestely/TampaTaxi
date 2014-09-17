#pragma once
#include "Movable.h"

class Animable : public Movable
{
public:
	Animable(Point center);
	virtual bool MoveWith(double speed, double angle) override;
	virtual void Animate()=0;
};
