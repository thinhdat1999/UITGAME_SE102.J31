#pragma once
#include "Weapon.h"

class WeaponShield : public Weapon
{
public:
	WeaponShield()
	{
		animations[STANDING] = new Animation(WEAPON, 0);
		animations[JUMPING] = new Animation(WEAPON, 1);
		animations[SHIELD_UP] = new Animation(WEAPON, 2);
		animations[SHIELD_DOWN] = new Animation(WEAPON, 3);
		vx = vy = 0;
		type = SHIELD;
		stateName = STANDING;
	}
	void Update(float dt) {
		Weapon::Update(dt);
		if (!isOut) {
			switch (player->stateName) {
			case SHIELD_UP:
				
				this->posY += 15;
				this->posX += (player->isReverse ? 5 : -5);
				break;
			case JUMPING:
				this->posY += 10;
				this->posX += (player->isReverse ? -5 : 5);
				break;
			default:
				this->posX += (player->isReverse ? 9 : -9);
			}
		}
	}
	void Render(float cameraX = 0, float cameraY = 0)
	{
	/*	auto frameIndex = player->curAnimation->CurFrameIndex - 1;
		if (frameIndex != 0 && frameIndex != 1) return;*/
		auto sprite = curAnimation->GetSprite(0);
		sprite->_isFlipHorizontal = player->isReverse;

		screenX = this->posX - cameraX;
		screenY = cameraY - this->posY;
		sprite->Render(screenX, screenY);
	}
};