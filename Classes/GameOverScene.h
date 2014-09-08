//  
// File name: GameOverScene.h
// 9/8/2014
//
// Description:游戏结束场景
//
// Created by 王松雁
//
// visit http://weibo.com/wsysyj
//

#ifndef __H_GAMEOVERSCENE_H__
#define __H_GAMEOVERSCENE_H__

#include "GameHead.h"

class GameOver :public Layer{
public:
	virtual bool init();
	CREATE_FUNC(GameOver);
	SCENE_FUNC(GameOver);
	void restartCallback(Ref*pSender);
}; 

#endif
