//  
// File name: SplashScene.h
// 9/7/2014
//
// Description:开场动画
//
// Created by 王松雁
//
// visit http://weibo.com/wsysyj
//

#ifndef __H_SPLASHSCENE_H__
#define __H_SPLASHSCENE_H__

#include "GameHead.h"

class Splash :public Layer{
public:
	virtual bool init();
	CREATE_FUNC(Splash);
	SCENE_FUNC(Splash);
	void gotoGameScene(float dt);
}; 

#endif
