#pragma once
#include "Object.h"
#include "Player.h"

class Enemy : public Object
{
protected :
	unordered_map<State, Animation*> animations;
public:
	Enemy();
	~Enemy();

	bool isActive;
	State stateName;
	Animation* curAnimation;
	
	void Respawn();
	void ChangeState(State newState);
	virtual void Update(float dt);
	virtual void Render(float cameraX = 0, float cameraY = 0);
};