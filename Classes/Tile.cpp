//  
// File name: Tile.cpp
// 9/8/2014
//
// Description:块
//
// Created by 王松雁
//
// visit http://weibo.com/wsysyj
//

#include "Tile.h"

bool Tiled::init(){
	bool ret = false;
	do{
		CC_BREAK_IF(!Node::init());
	
		int d = rand()%10;
		this->m_number = d>0?2:4;

		auto bg = LayerColor::create(Color4B(200,200,200,255),GAME_TILE_WIDTH,GAME_TILE_HEIGHT);
		bg->setTag(100);
		this->addChild(bg);

		switch(m_number)
		{
		case 2:
			bg->setColor(Color3B(230,220,210));
			break;
		case 4:
			bg->setColor(Color3B(230,210,190));
			break;
		}
		auto label = Label::create(StringUtils::format("%d",this->m_number),"Arial",40);
		label->setPosition(Vec2(GAME_TILE_WIDTH/2,GAME_TILE_HEIGHT/2));
		label->setTag(10);
		bg->addChild(label);

		ret = true;
	}while(0);
	return ret;
}

void Tiled::moveTo(int r,int c)
{
	this->r = r;
	this->c = c;
	this->setPosition(Vec2(c*GAME_TILE_WIDTH+(c+1)*GAME_BORDER_WIDTH,r*GAME_TILE_HEIGHT+(r+1)*GAME_BORDER_WIDTH));
}
void Tiled::showAt(int r,int c)
{
	moveTo(r,c);
	auto bg = this->getChildByTag(100);
	auto scale1 = ScaleTo::create(0.2f,0.5f);
	auto scale2 = ScaleTo::create(0.2f,1.2f);
	auto scale3 = ScaleTo::create(0.2f,1.0f);
	auto seq = Sequence::create(scale1,scale2,scale3,nullptr);
	bg->runAction(seq);
}
void Tiled::doubleNumber()
{
	this->m_number*=2;
	auto bg = (LayerColor*)this->getChildByTag(100);
	auto label = (Label*)bg->getChildByTag(10);
	label->setString(StringUtils::format("%d",this->m_number));
	//auto bg = this->getChildByTag(100);
	auto scale1 = ScaleTo::create(0.2f,0.5f);
	auto scale2 = ScaleTo::create(0.2f,1.2f);
	auto scale3 = ScaleTo::create(0.2f,1.0f);
	auto seq = Sequence::create(scale1,scale2,scale3,nullptr);
	bg->runAction(seq);

	switch(m_number)
	{
	case 2:
		bg->setColor(Color3B(230,220,210));
		break;
	case 4:
		bg->setColor(Color3B(230,210,190));
		break;
	case 8:
		bg->setColor(Color3B(230,150,100));
		label->setColor(Color3B(255,255,255));
		break;
	case 16:
		bg->setColor(Color3B(230,120,80));
		label->setColor(Color3B(255,255,255));
		break;
	case 32:
		bg->setColor(Color3B(230,100,90));
		label->setColor(Color3B(255,255,255));
		break;
	case 64:
		bg->setColor(Color3B(230,70,60));
		label->setColor(Color3B(255,255,255));
		break;
	case 128:
		bg->setColor(Color3B(230,190,60));
		label->setColor(Color3B(255,255,255));
		break;
	case 256:
		bg->setColor(Color3B(230,190,60));
		label->setColor(Color3B(255,255,255));
		break;
	case 512:
		bg->setColor(Color3B(230,190,60));
		label->setColor(Color3B(255,255,255));
		break;
	case 1024:
	case 2048:
		label->setScale(0.5);
		bg->setColor(Color3B(210,180,30));
		label->setColor(Color3B(255,255,255));
		break;
	}
}
