#include "Player.h"
Player* Player::_instance = NULL;

Player::Player()
{
	animations[STANDING] = new Animation(PLAYER, 0);
	animations[RUNNING] = new Animation(PLAYER, 1, 4, DEFAULT_TPF);
	animations[SHIELD_UP] = new Animation(PLAYER, 5);
	animations[SITTING] = new Animation(PLAYER, 6);
	animations[JUMPING] = new Animation(PLAYER, 7);
	animations[FALLING] = new Animation(PLAYER, 7);
	animations[SPINNING] = new Animation(PLAYER, 8, 9, DEFAULT_TPF >> 1);
	animations[ATTACKING_JUMP] = new Animation(PLAYER, 10);
	animations[THROWING] = new Animation(PLAYER, 11, 12, DEFAULT_TPF );
	animations[ATTACKING_STAND] = new Animation(PLAYER, 13, 14, DEFAULT_TPF);
	animations[ATTACKING_SIT] = new Animation(PLAYER, 15, 16, DEFAULT_TPF);
	animations[DASHING] = new Animation(PLAYER, 17, 18, DEFAULT_TPF);
	animations[SHIELD_DOWN] = new Animation(PLAYER, 19);
	tag = PLAYER;
	width = PLAYER_WIDTH;
	height = PLAYER_STANDING_HEIGHT;
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
	this->_allow[ATTACKING] = false;
	this->_allow[RUNNING] = true;
	this->_allow[THROWING] = true;
	this->isHoldingShield = true;
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
	case DIK_Z:
		if (_allow[THROWING] && weaponType == SHIELD && isHoldingShield
			&& this->stateName != ATTACKING_SIT && this->stateName != ATTACKING_STAND 
			&& this->stateName != ATTACKING_JUMP) {
			_allow[THROWING] = false;
			_allow[ATTACKING] = true;
			this->isThrowing = true;
			ChangeState(new PlayerAttackingState());
		}
		else if (_allow[ATTACKING])
			{
			_allow[ATTACKING] = false;
			ChangeState(new PlayerAttackingState());
			this->isAttacking = true;
			}
		break;
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

