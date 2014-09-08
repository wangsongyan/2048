//  
// File name: Tile.h
// 9/8/2014
//
// Description£º¿é
//
// Created by ÍõËÉÑã
//
// visit http://weibo.com/wsysyj
//

#ifndef __H_TILE_H__
#define __H_TILE_H__

#include "GameHead.h"

class Tiled :public Node{
public:
	virtual bool init();
	CREATE_FUNC(Tiled);
	void moveTo(int r,int c);
	void showAt(int r,int c);
	void doubleNumber();
	int m_number;
private:
	int r;
	int c;
	
}; 

#endif