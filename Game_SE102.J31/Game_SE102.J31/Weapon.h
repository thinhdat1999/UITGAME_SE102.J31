#pragma once
#include "Player.h"
#include <unordered_set>
#include <map>

class Weapon : public Object
{
protected:
	unordered_map<State, Animation*> animations;
	Animation *curAnimation;
	State stateName;
	bool isOut;
public:
	Weapon()
	{
		tag = WEAPON;
		if (player->isThrowing)
		{
			player->_allow[THROWING] = false;
		}
	}

	~Weapon()
	{
		if (type != SHIELD)
		{
			player->_allow[THROWING] = true;
		}
	}

	/*virtual void Update(float dt) {};*/			// Update thông số của Object sau khoảng thời gian delta-time

	virtual void Render(float cameraX = 0, float cameraY = 0)
	{
		screenX = this->posX - cameraX;
		screenY = cameraY - this->posY;
		curAnimation->isReverse = this->isReverse;
		curAnimation->Render(screenX, screenY);
	}

	virtual void UpdateDistance(float dt)
	{
		this->dx = vx * dt;
		this->dy = vy * dt;
	}

	virtual void Update(float dt)
	{
		this->UpdateDistance(dt);
		if (player->isThrowing) {
			this->posX += dx;
			this->posY += dy;
		}
		else
		{
			this->posX = player->posX;
			this->posY = player->posY;
		}
		if (!isOut) {
			switch (player->stateName) {
			case SHIELD_UP: case ATTACKING:
				stateName = SHIELD_UP;
				break;
			case SHIELD_DOWN:
				stateName = SHIELD_DOWN;
				break;
			// player->isOnGround == false -> JUMPING
			case JUMPING: case FALLING:
				stateName = JUMPING;

				break;
			default: 
				stateName = STANDING;
				if (player->stateName != SITTING)
				{
					this->posX = player->posX;
					this->posY = player->posY + 8;
				}
				else {
					this->posX = player->posX;
					this->posY = player->posY - 2;
				}
				break;
			}
		}
		else {
			stateName = SHIELD_UP;
		}
	
		
		curAnimation = animations[stateName];
		curAnimation->isReverse = player->isReverse;
		curAnimation->Update(dt);
	}
};