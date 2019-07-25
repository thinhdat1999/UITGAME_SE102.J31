#pragma once
#include "Enemy.h"

class EnemyBlueSoldier : public Enemy
{
private :
	int bulletcount;
	int totalbullet;
public:
	EnemyBlueSoldier( float spawnX, float spawnY);
	~EnemyBlueSoldier();

	void Update(float dt);
	void Render();
};