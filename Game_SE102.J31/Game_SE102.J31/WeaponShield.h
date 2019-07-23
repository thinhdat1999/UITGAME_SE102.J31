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
		this->vx = 0.6f;
		type = SHIELD;
		stateName = STANDING;
		width = WEAPON_SHIELD_WIDTH;
		height = WEAPON_SHIELD_HEIGHT;
		isOut = false;
		isHolding = true;
	}
	void UpdateDistance(float dt) {
		this->dx = vx * dt;
		//this->dy = 1.5 * (player->posY - this->posY) / MAX_FRAME_RATE;
		if (this->posX > player->posX) {
			if (vx > 0)
			{
				this->dx = min(WEAPON_SHIELD_MAX_DISTANCEX, this->dx);
			}
			this->vx -= WEAPON_SHIELD_REVERSE_ACCELERATEX;
			/*		if (!this->isReverse)
					{
						this->dy -= WEAPON_SHIELD_REVERSE_DISTANCEY;
					}
					else this->dy += WEAPON_SHIELD_REVERSE_DISTANCEY;*/
		}
		else
		{
			if (this->vx < 0)
			{
				this->dx = max(-WEAPON_SHIELD_MAX_DISTANCEX, this->dx);
			}
			this->vx += WEAPON_SHIELD_REVERSE_ACCELERATEX;

			/*		if (!this->isReverse)
					{
						this->dy += WEAPON_SHIELD_REVERSE_DISTANCEY;
					}
					else this->dy -= WEAPON_SHIELD_REVERSE_DISTANCEY;*/
		}
		// Nếu player đang ném vũ khí:
		if (this->GetRect().isContain(player->GetRect()) && !player->isHoldingShield)
		{
			if (!isOut)
			{
				this->isOut = true;
				this->posX = player->posX + (player->isReverse ? player->width : -player->width);
			}
			else
			{
				this->isOut = false;
				player->isHoldingShield = true;
				this->isHolding = true;
				player->_allow[THROWING] = true;
				this->isDead = true;
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