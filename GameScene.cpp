#include "GameScene.h"


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
	state = noclicked;
	memset(map, 0, sizeof(map));
	
	ballVec = new Vector<BallSprite*>();
	mark = 0;
}
Point GameScene::getRandomPoint() const
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
	auto pan = Sprite::create("pan.png");
	pan->setPosition(ccp(0, 0));
	pan->setAnchorPoint(ccp(0, 0));
	this->addChild(pan);
	Lmark = Label::create("0", "Marker Felt",40);
	Lmark->setAnchorPoint(ccp(0, 0));
	Lmark->setColor(ccc3(0xff,0,0));
	Lmark->setPosition(ccp(0, 305));
	this->addChild(Lmark);
	auto listener = EventListenerTouchOneByOne::create();

	addBall(3);

	listener->onTouchBegan = [=](Touch *touch,Event *event){

		Point t = touch->getLocationInView();
		t = Director::sharedDirector()->convertToGL(t);
		bool flag = false;
		if (state == noclicked)
		{
			for (auto &iter : *ballVec)
			{
				auto r = Rect(iter->getPosition().x, iter->getPosition().y, iter->getContentSize().width, iter->getContentSize().height);

				if (r.containsPoint(t))
				{
					iter->flash();
					flashNow = iter;
					flag = true;
					break;
				}
			}
			if (flag){
				state = clicked;
			}
		}
		else{
			for (auto &iter : *ballVec)
			{
				auto r = Rect(iter->getPosition().x, iter->getPosition().y, iter->getContentSize().width, iter->getContentSize().height);

				if (r.containsPoint(t))
				{
					iter->flash();
					flashNow->flashStop();
					iter->flash();
					flashNow = iter;
					flag = true;
					break;
				}
			}
			if (flag){
				state = clicked;
			}
			else {
				
				flashNow->flashStop();
				int tx = (t.x - 1) / 30;
				int ty = (t.y - 1) / 30;
				bool can = is_move(flashNow->getPosX(),flashNow->getPosY(),tx ,ty);
				
				if (can)
				{
					moveBall(tx,ty,flashNow);
					getRemoveBall(tx, ty);
					addBall(3);
				}
				state = noclicked;
			}
		}
		return true;
	};
	listener->onTouchEnded = [=](Touch *touch, Event *event){
		if (unUse.size() == 0){
			//exit
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}
Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}
int GameScene::getCount() const
{
	return unUse.size();
}
void GameScene::addBall(int n)
{
	for (int i = 0; i < n; ++i)
	{
		if (getCount() > 0)
		{
			auto p = getRandomPoint();
			removePoint(p);
			auto b = BallSprite::createRandomBall();
			ballVec->pushBack(b);
			b->setPos(ccp(p.x, p.y));
			map[b->getPosX()][b->getPosY()] = b->getType();
			this->addChild(b);
		}
	}
}
bool GameScene::is_move(int fx ,int fy, int tx,int ty)
{
	memset(visit, 0, sizeof(visit));
	int tmp = map[fx][fy];
	map[fx][fy] = 0;
	bool tr = dfs(fx, fy , tx,ty);
	map[fx][fy] = tmp;
	return tr;
}
bool GameScene::dfs(int x, int y, int ex ,int ey)
{
	
	if (x < 0 || y < 0 || x >= MAX_SIZE || y >= MAX_SIZE) return false;
	if (visit[x][y] == true) return false;
	if (map[x][y] != 0) return false;
	visit[x][y] = true;
	if (x == ex && y == ey) return true;
	bool tt;
	tt = dfs(x + 1, y,ex,ey);
	if (tt){
		return true;
	}
	tt = dfs(x - 1, y,ex,ey);
	if (tt){
		return true;
	}
	tt = dfs(x, y + 1,ex,ey);
	if (tt){
		return true;
	}
	tt = dfs(x, y - 1,ex,ey);
	if (tt){
		return true;
	}
	return false;
}
void GameScene::removeBall(BallSprite *bsp)
{
	int rx = bsp->getPosX();
	int ry = bsp->getPosY();
	map[rx][ry] = 0;
	Point pp(rx, ry);
	unUse.push_back(pp);
	ballVec->eraseObject(bsp);
	bsp->removeFromParentAndCleanup(true);
}
void GameScene::getRemoveBall(int x, int y)
{
	int is_del = countBall(getBall(x, y));
	if ( is_del >= 3)
	{
		for (auto it = removelist.rbegin(); it != removelist.rend();++it)
		{
			removeBall(*it);
		}
		removelist.clear();
		mark += pow(2, is_del);
		char c[100];
		sprintf(c, "%d", mark);
		Lmark->setString(c);
	}

}
int GameScene::countBall(BallSprite* ball)
{
	removelist.clear();
	int num = 1;
	int t = ball->getType();
	int bx = ball->getPosX();
	int by = ball->getPosY();
	for (int i = bx+1; i < MAX_SIZE; ++i)
	{
		if (map[i][by] == t)
		{
			num++;
			auto bb = getBall(i, by);
			if (bb != nullptr)
				removelist.pushBack(bb);
		}
		else{
			break;
		}
	}
	for (int i = bx-1; i >= 0; --i)
	{
		if (map[i][by] == t)
		{
			num++;
			auto bb = getBall(i, by);
			if (bb != nullptr)
				removelist.pushBack(bb);
		}
		else{
			break;
		}
	}
	if (num >= 3)
	{
		removelist.pushBack(ball);
		return num;
	}
	num = 1;
	removelist.clear();
	for (int i = by+1; i < MAX_SIZE; ++i)
	{
		if (map[bx][i] == t)
		{
			num++;
			auto bb = getBall(bx, i);
			if (bb != nullptr)
				removelist.pushBack(bb);
		}
		else{
			break;
		}
	}
	for (int i = by-1; i >= 0; --i)
	{
		
		if (map[bx][i] == t)
		{
			num++;
			auto bb = getBall(bx, i);
			if (bb != nullptr)
			removelist.pushBack(bb);
		}
		else{
			break;
		}
	}
	if (num >= 3)
	{
		removelist.pushBack(ball);
		return num;
	}
	return num;
}
BallSprite* GameScene::getBall(int x, int y)
{
	for (auto &iter : *ballVec)
	{
		if (iter->getPosX() == x && iter->getPosY() == y)
		{
			return iter;
		}
	}
	return nullptr;
}
void GameScene::moveBall(int x, int y, BallSprite* bs)
{
	int tx = bs->getPosX();
	int ty = bs->getPosY();
	int t = map[tx][ty];
	Point p(tx, ty);
	unUse.push_back(p);
	p.x = x, p.y = y;
	removePoint(p);
	map[tx][ty] = 0;
	map[x][y] = t;
	bs->setPos(p);
}