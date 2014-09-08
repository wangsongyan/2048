//  
// File name: GameOverScene.cpp
// 9/8/2014
//
// Description£ºÓÎÏ·½áÊø
//
// Created by ÍõËÉÑã
//
// visit http://weibo.com/wsysyj
//

#include "GameOverScene.h"
#include "GameScene.h"

bool GameOver::init(){
	bool ret = false;
	do{
		CC_BREAK_IF(!Layer::init());

		auto labelGameOver =  LabelBMFont::create("GameOver!","fonts/boundsTestFont.fnt");
		labelGameOver->setPosition(Vec2(GAME_SCRENN_WIDTH/2,GAME_SCREEN_HEIGHT/2));
		this->addChild(labelGameOver);

		auto labelRestart =  LabelBMFont::create("restart","fonts/boundsTestFont.fnt");
		auto menuItem = MenuItemLabel::create(labelRestart,CC_CALLBACK_1(GameOver::restartCallback,this));
		menuItem->setPosition(Vec2(GAME_SCRENN_WIDTH/2,GAME_SCREEN_HEIGHT/2-50));
		
		auto menu = Menu::create(menuItem,nullptr);
		menu->setPosition(Point::ZERO);
		this->addChild(menu);
		ret = true;
	}while(0);
	return ret;
}

void GameOver::restartCallback(Ref*pSender)
{
	Scene *scene = GameScene::createScene();
	Director::getInstance()->replaceScene(scene);
	//Director::getInstance()->replaceScene(TransitionTurnOffTiles::create(1.0f,scene));
}