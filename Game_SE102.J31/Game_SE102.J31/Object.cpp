#include "Object.h"

void Object::Update(float dt)
{
	dx = vx * dt;
	dy = vy * dt;
	posX += dx;
	posY += dy;
}
Rect Object::GetRect()
{
	Rect rect;
	rect.x = posX - (width >> 1);
	rect.y = posY + (height >> 1);
	rect.width = this->width;
	rect.height = this->height;
	return rect;
}
bool Object::IsCollide(Rect r)
{
	return this->GetRect().isContain(r);
}