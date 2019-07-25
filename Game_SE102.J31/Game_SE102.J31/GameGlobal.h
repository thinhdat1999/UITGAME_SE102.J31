﻿#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include <WinUser.h>
#include <unordered_map>

#define SCREEN_WIDTH 360			// Chiều dài cửa sổ
#define SCREEN_HEIGHT 176	// Chiều cao cửa sổ
#define MAX_FRAME_RATE 120				// FPS
#define WIN_NAME "Captain America and The Avengers"
#define WIN_TITLE "Captain America and The Avengers"
#define KEYBOARD_BUFFER_SIZE 1024
#define DEFAULT_TPF 120
extern LPD3DXSPRITE spriteHandler; 
extern LPDIRECT3DDEVICE9 d3ddev;
extern LPDIRECT3DSURFACE9 backBuffer; // Back buffer
extern LPDIRECT3DSURFACE9 surface;
extern bool isGameRunning;
extern std::unordered_map<int, bool> keyCode;

#define mCamera Camera::GetInstance()
#define player Player::GetInstance()


// ===== Thông số cho Weapon ======
#define WEAPON_SHIELD_SPEED 0.25f
#define WEAPON_SHIELD_MAX_DISTANCEX 4.5f
#define WEAPON_SHIELD_REVERSE_ACCELERATEX 0.02f
#define WEAPON_SHIELD_WIDTH 15
#define WEAPON_SHIELD_HEIGHT 15
// ===== Thông số Captain =====
#define PLAYER_RUNNING_SPEED 0.095f
#define PLAYER_JUMPING_SPEED 0.28f
#define PLAYER_FALLING_SPEED 0.25f
#define PLAYER_WIDTH 20
#define PLAYER_STANDING_HEIGHT 26
#define PLAYER_SITTING_HEIGHT 18
#define GRAVITY_SPEED 0.014f	
// ====== ENUM của Object  ======
extern enum Tag
{
	PLAYER,
	CAPTAIN,
	ITEM,
	WEAPON,
	GROUND,
	MAP1,
	MAP2,
	MAP3,
	FONT,
	BOSS1,
	BOSS2,
	ENEMY,
	HOLDER,
	BULLET,
	MENUSCENE,
	CHANGESCENE,
	INTROSCENE,
	ENDSCENE,
};

// ====== Type Object ======
extern enum Type
{
	NONE,
	SHIELD,
	BOSS,
	EXPLODED,
};

extern enum State
{
	IDLE,
	STANDING,
	RUNNING,
	SHIELD_UP,
	SHIELD_DOWN,
	DASHING,
	JUMPING,
	SPINNING,
	FALLING,
	FLYING,
	FLYING_ATK,
	FLYING_DOWN,
	SITTING,
	ATTACKING,
	ATTACKING_JUMP,
	ATTACKING_STAND,
	ATTACKING_SIT,
	THROWING,
	CLINGING,
	ACTIVE,
	TRANSFORM,
	EXPLODE,
	DEAD,
	INJURED
};

struct Rect {
	float x, y;
	float width, height;
	Rect() {}
	Rect(float x, float y, float width, float height)
	{
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
	}
	bool isContain(Rect r)
	{
		return !((x + width < r.x) || (x > r.x + r.width) || (y < r.y - r.height) || (y - height > r.y));
	}
};
