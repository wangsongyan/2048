//  
// File name: GameScene.cpp
// 9/8/2014
//
// Description：游戏场景
//
// Created by 王松雁
//
// visit http://weibo.com/wsysyj
//

#include "GameScene.h"
#include "Tile.h"
#include "GameOverScene.h"

bool GameScene::init(){
	bool ret = false;
	do{
		CC_BREAK_IF(!Layer::init());

		/*auto label = Label::create("add","Arial",25);
		auto menuItem = MenuItemLabel::create(label,CC_CALLBACK_1(GameScene::test,this));
		menuItem->setPosition(Vec2(GAME_SCRENN_WIDTH-menuItem->getContentSize().width/2,menuItem->getContentSize().height/2));
		auto menu = Menu::create(menuItem,nullptr);
		menu->setPosition(Point::ZERO);
		this->addChild(menu);*/

		auto labelName = LabelBMFont::create("2048","fonts/boundsTestFont.fnt");
		labelName->setPosition(Vec2(labelName->getContentSize().width/2,GAME_SCREEN_HEIGHT-labelName->getContentSize().height/2));
		labelName->setScale(0.8f);
		this->addChild(labelName);

		auto labelScore = LabelBMFont::create(StringUtils::format("Score:%d",0),"fonts/boundsTestFont.fnt");
		labelScore->setPosition(Vec2(GAME_SCRENN_WIDTH/2,GAME_SCREEN_HEIGHT*5/6));
		//labelScore->setScale(1.2f);
		labelScore->setTag(111);
		this->addChild(labelScore);

		initBord();
		initMap();
		addNewTile();

		auto listener1 = EventListenerTouchOneByOne::create();//创建一个触摸监听
		//listener1->setSwallowTouches(true); //设置是否想下传递触摸

		//通过 lambda 表达式 直接实现触摸事件的回掉方法
		listener1->onTouchBegan = [&](Touch* touch, Event* event){
			startMove = true;
			m_x = touch->getLocation().x;
			m_y = touch->getLocation().y;
			return true;
		};

		listener1->onTouchMoved = [&](Touch* touch, Event* event){
			//CCLOG("onTouchMoved");
			//startMove = true;
			float x = touch->getLocation().x;
			float y = touch->getLocation().y;
			if(startMove&&(abs(m_x-x)>10||abs(m_y-y)>10))
			{
				if(abs(m_x-x)>abs(m_y-y))//左右移动
				{
					if(m_x-x>0)//左滑
					{
						m_dir = Direction::LEFT;
					}
					else//右滑
					{
						m_dir = Direction::RIGHT;
					}
				}
				else//上下移动
				{
					if(m_y-y>0)//下滑
					{
						m_dir = Direction::DOWN;
					}
					else//上滑
					{
						m_dir = Direction::UP;
					}
				}

				moveAllTile(m_dir);
				startMove = false;
			}
		};

		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);

		m_score = 0;

		ret = true;
	}while(0);
	return ret;
}
//初始化网格
void GameScene::initBord()
{
	int width = GAME_TILE_WIDTH*GAME_COLS+GAME_BORDER_WIDTH*(GAME_COLS+1);
	int height = GAME_TILE_HEIGHT*GAME_ROWS+GAME_BORDER_WIDTH*(GAME_ROWS+1);

	bg = LayerColor::create(Color4B(170,170,170,255),width,height);
	//bg->setAnchorPoint(Vec2(0.5,0.5));
	bg->setPosition(Vec2(GAME_SCRENN_WIDTH/2-width/2,GAME_SCREEN_HEIGHT/2-height/2));
	this->addChild(bg);

	for(int r = 0 ; r < GAME_ROWS;r++)
	{
		for(int c = 0 ; c<GAME_COLS;c++)
		{
			auto tile = LayerColor::create(Color4B(100,100,100,255),GAME_TILE_WIDTH,GAME_TILE_HEIGHT);
			tile->setPosition(Vec2(
				c*GAME_TILE_WIDTH+(c+1)*GAME_BORDER_WIDTH,
				r*GAME_TILE_HEIGHT+(r+1)*GAME_BORDER_WIDTH));
			bg->addChild(tile);
		}
	}
}

void GameScene::initMap()
{
	for(int r = 0 ; r<GAME_ROWS;r++)
	{
		for(int c = 0;c<GAME_COLS;c++)
		{
			map[r][c] = 0;
		}
	}
}

void GameScene::addNewTile()
{

	int freeCount = 16-allTiled.size();
	log("freeCount=%d",freeCount);

	if(freeCount==0)
	{
		return ;
	}

	int num = rand()%freeCount;

	log("num=%d",num);

	//int r = rand()%GAME_ROWS;
	//int c = rand()%GAME_COLS;
	//CCLog("r = %d , c = %d",r,c);
	int r = 0;
	int c = 0;
	int count = 0;
	bool find = false;

	for(;r<GAME_ROWS;r++)
	{
		for(c=0;c<GAME_COLS;c++)
		{
			if(map[r][c]==0)
			{
				count++;
				if(count>=num)
				{
					find = true;
					break;
				}
			}	
		}

		if(find)
		{
			break;
		}
	}
	auto tile = Tiled::create();
	bg->addChild(tile);
	//tile->moveTo(r,c);
	tile->showAt(r,c);
	allTiled.pushBack(tile);
	map[r][c] = allTiled.getIndex(tile)+1;

	//////////////////////////////////////////////////////////////////////////
	if(freeCount==1)
	{
		for(int r = 0 ; r<GAME_ROWS;r++)
		{
			for(int c = 0 ;c<GAME_COLS;c++)
			{
				int num = allTiled.at(map[r][c]-1)->m_number;
				int numObj =0;
				if(r+1<GAME_ROWS)
				{
					numObj = allTiled.at(map[r+1][c]-1)->m_number;
					if(num==numObj)
					{
						return;
					}
				}

				if(r-1>=0)
				{
					numObj = allTiled.at(map[r-1][c]-1)->m_number;
					if(num==numObj)
					{
						return;
					}
				}

				if(c-1>=0)
				{
					numObj = allTiled.at(map[r][c-1]-1)->m_number;
					if(num==numObj)
					{
						return;
					}
				}

				if(c+1<GAME_COLS)
				{
					numObj = allTiled.at(map[r][c+1]-1)->m_number;
					if(num==numObj)
					{
						return;
					}
				}
			}
		}

		auto scene = GameOver::createScene();
		Director::getInstance()->replaceScene(TransitionTurnOffTiles::create(1.0f,scene));

		return;
	}
}

void GameScene::test(Ref*pSender)
{
	//addNewTile();
}

void GameScene::moveAllTile(Direction dir)
{
	switch(dir)
	{
		case Direction::UP:
			moveUp();
			break;
		case Direction::DOWN:
			moveDown();
			break;
		case Direction::LEFT:
			moveLeft();
			break;
		case Direction::RIGHT:
			moveRight();
			break;
		default:
			break;
	}

	auto labelScore = (LabelBMFont*)this->getChildByTag(111);
	labelScore->setString(StringUtils::format("Score:%d",m_score));
	//
	addNewTile();
}

void GameScene::moveUp()
{
	/*CCLog("up");*/
	for(int c = 0;c<GAME_COLS;c++)
	{
		for(int r = GAME_ROWS-1;r>=0;r-- )
		{
			if(map[r][c]==0) continue;
			for(int r1 = r ; r1<GAME_ROWS-1;r1++)
			{
				if(map[r1+1][c]==0)//上面一块为空
				{
					map[r1+1][c] = map[r1][c];
					map[r1][c]=0;
					allTiled.at(map[r1+1][c]-1)->moveTo(r1+1,c);
				}
				else
				{
					if(allTiled.at(map[r1+1][c]-1)->m_number==allTiled.at(map[r1][c]-1)->m_number)
					{
						m_score+=allTiled.at(map[r1+1][c]-1)->m_number*2;
						allTiled.at(map[r1+1][c]-1)->doubleNumber();
						allTiled.at(map[r1][c]-1)->removeFromParentAndCleanup(true);
						allTiled.eraseObject(allTiled.at(map[r1][c]-1));
						int index = map[r1][c];
						for(int i = 0;i<GAME_ROWS;i++)
						{
							for(int j = 0 ; j<GAME_COLS;j++)
							{
								if(map[i][j]>index)
								{
									map[i][j]--;
								}
							}
						}
						map[r1][c]=0;
						
					}
					break;
				}
			}
		}
	}
}

void GameScene::moveDown()
{
	/*CCLog("down");*/
	for(int c = 0;c<GAME_COLS;c++)
	{
		for(int r = 0;r<GAME_ROWS;r++ )
		{
			if(map[r][c]==0) continue;
			for(int r1 = r ; r1>=1;r1--)
			{
				if(map[r1-1][c]==0)//下面一块为空
				{
					map[r1-1][c] = map[r1][c];
					map[r1][c]=0;
					allTiled.at(map[r1-1][c]-1)->moveTo(r1-1,c);
				}
				else
				{
					if(allTiled.at(map[r1-1][c]-1)->m_number==allTiled.at(map[r1][c]-1)->m_number)
					{
						m_score+=allTiled.at(map[r1-1][c]-1)->m_number*2;
						allTiled.at(map[r1-1][c]-1)->doubleNumber();
						allTiled.at(map[r1][c]-1)->removeFromParentAndCleanup(true);
						allTiled.eraseObject(allTiled.at(map[r1][c]-1));
						int index = map[r1][c];
						for(int i = 0;i<GAME_ROWS;i++)
						{
							for(int j = 0 ; j<GAME_COLS;j++)
							{
								if(map[i][j]>index)
								{
									map[i][j]--;
								}
							}
						}
						map[r1][c]=0;
						
					}
					break;
				}
			}
		}
	}
}

void GameScene::moveLeft()
{
	/*CCLog("left");*/

	for(int r = 0;r<GAME_ROWS;r++)
	{
		for(int c = 0;c<GAME_COLS;c++ )
		{
			if(map[r][c]==0) continue;
			for(int c1 = c ; c1>=1;c1--)
			{
				if(map[r][c1-1]==0)//下面一块为空
				{
					map[r][c1-1] = map[r][c1];
					map[r][c1]=0;
					allTiled.at(map[r][c1-1]-1)->moveTo(r,c1-1);
				}
				else
				{
					if(allTiled.at(map[r][c1-1]-1)->m_number==allTiled.at(map[r][c1]-1)->m_number)
					{
						m_score+=allTiled.at(map[r][c1-1]-1)->m_number*2;
						allTiled.at(map[r][c1-1]-1)->doubleNumber();
						allTiled.at(map[r][c1]-1)->removeFromParentAndCleanup(true);
						allTiled.eraseObject(allTiled.at(map[r][c1]-1));
						int index = map[r][c1];
						for(int i = 0;i<GAME_ROWS;i++)
						{
							for(int j = 0 ; j<GAME_COLS;j++)
							{
								if(map[i][j]>index)
								{
									map[i][j]--;
								}
							}
						}
						map[r][c1]=0;
					
					}
						break;
				}
			}
		}
	}

}

void GameScene::moveRight()
{
	/*CCLog("right");*/
	for(int r = 0;r<GAME_ROWS;r++)
	{
		for(int c = GAME_COLS-1;c>=0;c-- )
		{
			if(map[r][c]==0) continue;
			for(int c1 = c ; c1<GAME_ROWS-1;c1++)
			{
				if(map[r][c1+1]==0)//下面一块为空
				{
					map[r][c1+1] = map[r][c1];
					map[r][c1]=0;
					allTiled.at(map[r][c1+1]-1)->moveTo(r,c1+1);
				}
				else
				{
					if(allTiled.at(map[r][c1+1]-1)->m_number==allTiled.at(map[r][c1]-1)->m_number)
					{
						m_score+=allTiled.at(map[r][c1+1]-1)->m_number*2;
						allTiled.at(map[r][c1+1]-1)->doubleNumber();
						allTiled.at(map[r][c1]-1)->removeFromParentAndCleanup(true);
						allTiled.eraseObject(allTiled.at(map[r][c1]-1));
						int index = map[r][c1];
						for(int i = 0;i<GAME_ROWS;i++)
						{
							for(int j = 0 ; j<GAME_COLS;j++)
							{
								if(map[i][j]>index)
								{
									map[i][j]--;
								}
							}
						}
						map[r][c1]=0;
						
					}
					break;
				}
			}
		}
	}
}