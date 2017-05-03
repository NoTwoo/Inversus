#pragma once

#include <Windows.h>
#include <vector>
#include <iostream>
#include <string>
#include <memory>

#include "CGameManager.h"
#include "CCharacter.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CPanel.h"
#include "CPlainPanel.h"
#include "CActivePanel.h"
#include "CMap.h"
#include "CText.h"
#include "CBullet.h"
#include "CRotatingBullet.h"

using namespace std;

#define WINDOWS_SIZE_X 1000
#define WINDOWS_SIZE_Y 800

#define MAP_X 19
#define MAP_Y 13

#define GAMEMANAGER CGameManager::GetInstance()

#define TITLE_WIDTH 70
#define SMALL_TEXT_WIDTH 30

#define BSIZE 30
#define PIE 3.141592
#define DR (PIE/180)

#define MAX_STR 5

#define OBJECT_SIZE 47
#define CHARACTER_SIZE 37

#define INTERVAL 2

#define MAX_BULLET 5

#define SMALL_BULLET_SIZE 3