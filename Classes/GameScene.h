//  
// File name: GameScene.h
// 9/8/2014
//
// Description£∫”Œœ∑≥°æ∞
//
// Created by ÕıÀ…—„
//
// visit http://weibo.com/wsysyj
//

#ifndef __H_GAMESCENE_H__
#define __H_GAMESCENE_H__

#include "GameHead.h"
#include "Tile.h"
//#include <vector>
using namespace std;

class GameScene :public Layer{
public:
	virtual bool init();
	CREATE_FUNC(GameScene);
	SCENE_FUNC(GameScene);
	void initBord();
	void addNewTile();
	void test(Ref*pSender);
	void moveAllTile(Direction dir);
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void initMap();
private:
	LayerColor*bg;
	bool startMove;
	float m_x; 
	float m_y;
	int m_score;
	Direction m_dir;
	int map[GAME_ROWS][GAME_COLS];
	Vector<Tiled*> allTiled;
}; 

#endif