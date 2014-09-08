//  
// File name: SplashScene.cpp
// 9/7/2014
//
// Description：开场动画界面
//
// Created by 王松雁
//
// visit http://weibo.com/wsysyj
//

#include "SplashScene.h"
#include "GameScene.h"

bool Splash::init(){
	bool ret = false;
	do{
		CC_BREAK_IF(!Layer::init());

		//auto labelName = Label::create();
		//labelName->setString("2048");
		//labelName->setPosition(Vec2(GAME_SCRENN_WIDTH/2,GAME_SCREEN_HEIGHT/2));
		//this->addChild(labelName);
		//游戏名字
		auto labelName = LabelBMFont::create("2048","fonts/boundsTestFont.fnt");
		labelName->setPosition(Vec2(0,GAME_SCREEN_HEIGHT));
		labelName->setScale(1.2f);
		this->addChild(labelName);

		//游戏作者
		auto labelAuthor = LabelBMFont::create("wsy 2014-9-8","fonts/boundsTestFont.fnt");
		labelAuthor->setPosition(Vec2(GAME_SCRENN_WIDTH/2,GAME_SCREEN_HEIGHT*1/4));
		this->addChild(labelAuthor);

		auto rotate = RotateBy::create(0.5f,720.0f);
		auto move = MoveTo::create(0.5f,Vec2(GAME_SCRENN_WIDTH/2,GAME_SCREEN_HEIGHT*3/4));
		auto spwan = Spawn::createWithTwoActions(rotate,move);

		labelName->runAction(spwan);

		auto scale1 = ScaleTo::create(0.2f,0.5f);
		auto scale2 = ScaleTo::create(0.3f,1.2f);
		auto scale3 = ScaleTo::create(0.2f,1.0f);
		auto seq = Sequence::create(scale1,scale2,scale3,NULL);
		labelAuthor->runAction(seq);

		this->scheduleOnce(schedule_selector(Splash::gotoGameScene),2.0f);

		ret = true;
	}while(0);
	return ret;
}

void Splash::gotoGameScene(float dt)
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionJumpZoom::create(1.0f,scene));
}