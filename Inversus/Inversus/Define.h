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

#define MAX_STR 5

#define OBJECT_SIZE 47