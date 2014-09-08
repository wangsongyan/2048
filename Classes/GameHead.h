//  
// File name: GameHead.h
// 9/7/2014
//
// Description£º
//
// Created by ÍõËÉÑã
//
// visit http://weibo.com/wsysyj
//

#ifndef __H_GAMEHEAD_H__
#define __H_GAMEHEAD_H__

#include "cocos2d.h"
USING_NS_CC;

#define SCENE_FUNC(__TYPE__)\
	static Scene* createScene() \
{ \
	auto scene = Scene::create(); \
	auto layer = __TYPE__::create();\
	scene->addChild(layer);\
	return scene;\
}

#define  GAME_SCRENN_WIDTH 320
#define  GAME_SCREEN_HEIGHT 480
#define GAME_TILE_WIDTH 64
#define GAME_TILE_HEIGHT 64
#define GAME_BORDER_WIDTH 1
#define GAME_ROWS 4
#define GAME_COLS 4

enum class Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

#endif