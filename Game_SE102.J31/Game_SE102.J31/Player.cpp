#include "Player.h"
Player* Player::_instance = NULL;

Player::Player()
{
	animations[STANDING] = new Animation(PLAYER, 0);
	animations[RUNNING] = new Animation(PLAYER, 1, 4, DEFAULT_TPF >> 1);
	animations[SHIELD_UP] = new Animation(PLAYER, 5);
	animations[SITTING] = new Animation(PLAYER, 6);
	animations[JUMPING] = new Animation(PLAYER, 7);
	animations[FALLING] = new Animation(PLAYER, 7);
	animations[SPINNING] = new Animation(PLAYER, 8, 9, DEFAULT_TPF >> 1);
	animations[THROWING] = new Animation(PLAYER, 10, 11, DEFAULT_TPF >> 1);
	animations[ATTACKING_STAND] = new Animation(PLAYER, 12, 13, DEFAULT_TPF);
	animations[ATTACKING_SIT] = new Animation(PLAYER, 14, 15, DEFAULT_TPF);
	animations[DASHING] = new Animation(PLAYER, 16, 17, DEFAULT_TPF);
	animations[SHIELD_DOWN] = new Animation(PLAYER, 18);
	tag = PLAYER;
}

// Destructor
Player::~Player()
{
	if (curAnimation) delete curAnimation;

	for (auto it = animations.begin(); it != animations.end(); ++it)
	{
		if (it->second) delete it->second;
		animations.erase(it);
	}
}

Player* Player::GetInstance()
{
	if (_instance == NULL)
		_instance = new Player();
	return _instance;
}

void Player::Respawn()
{

	this->_allow[JUMPING] = true;
	this->_allow[ATTACKING] = true;
	this->_allow[RUNNING] = true;
	this->_allow[THROWING] = true;
	this->isAttacking = false;
	this->isThrowing = false;
	this->vx = this->vy = this->dx = this->dy = 0;
	this->posX = this->spawnX;
	this->posY = this->spawnY;
	this->isDead = false;
	this->isReverse = true;
	this->weaponType = SHIELD;
	this->ChangeState(new PlayerStandingState());
}

void Player::ChangeState(PlayerState * newState)
{
	delete state;
	state = newState;
	stateName = newState->StateName;
	curAnimation = animations[stateName];
}

void Player::Update(float dt)
{
	curAnimation->Update(dt);
	state->Update(dt);
	if (player->posX < 0)
		player->posX = 0;
	if (player->posY < 0)
		player->posY = 0;
	
}

void Player::Render(float cameraX, float cameraY)
{
	screenX = this->posX - cameraX;
	screenY = cameraY - this->posY;
	curAnimation->isReverse = this->isReverse;
	curAnimation->Render(screenX, screenY);

}

void Player::OnKeyDown(int keyCode)
{
	switch (keyCode) {
	case DIK_SPACE:
		if (_allow[JUMPING])
		{
			_allow[JUMPING] = false;
			ChangeState(new PlayerJumpingState());
		}
		break;
	case DIK_UP:
		ChangeState(new PlayerShieldUpState());
		break;
	}
}

void Player::OnKeyUp(int keyCode)
{
	switch (keyCode)
	{
		// Khi thả phím DOWN: state hiện tại chuyển thành đứng
	case DIK_DOWN:
		if (stateName == SITTING)
			stateName = STANDING;
		break;
	case DIK_UP:
		if (stateName == SHIELD_UP)
			ChangeState(new PlayerStandingState());
		break;
	}
}

