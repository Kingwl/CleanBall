#include "GameScene.h"
#include "BallSprite.h"

GameScene::GameScene()
{
	srand((unsigned)time(nullptr));
	for (int i = 0; i < MAX_SIZE; ++i)
	{
		for (int j = 0; j < MAX_SIZE; ++j)
		{
			unUse.push_back(Point(i, j));
		}
	}
}
Point GameScene::getRandomPoint()
{
	int s = unUse.size();
	if (s == 0) return Point(-1, -1);
	int i = rand() % s;
	auto r = *(unUse.begin() + i);
	return r;
}

std::vector<Point>::iterator GameScene::findPoint(Point p)
{
	auto iter = unUse.begin();
	for (; iter != unUse.end(); ++iter)
	{
		if ((*iter).x == p.x && (*iter).y == p.y)
		{
			break;
		}
	}
	return iter;
}
bool GameScene::removePoint(Point p)
{
	auto t = findPoint(p);
	if (t == unUse.end()) return false;
	unUse.erase(t);
	return true;
}
GameScene::~GameScene()
{
}
bool GameScene::init()
{
	auto bk = LayerColor::create(ccc4(0xe3,0xe3,0xe3,0xe3));
	bk->setPosition(ccp(0, 0));
	this->addChild(bk);

	/*Point f = getRandomPoint();
	while (f.x != -1&&f.y != -1)
	{
		removePoint(f);
		f = getRandomPoint();
	}
	*/
	auto p = BallSprite::createBall(BallSprite::red);
	auto t = getRandomPoint();
	p->setPos(ccp(t.x, t.y));
	p->setAnchorPoint(ccp(0, 0));
	this->addChild(p);
	return true;
}
Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}