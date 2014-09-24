#pragma once
#include <cocos2d.h>
#include "BallSprite.h"
#define MAX_SIZE 10
using namespace cocos2d;
class GameScene : public Layer
{
public:
	GameScene();
	~GameScene();
	virtual bool init();
	static Scene* createScene();
	bool removePoint(Point p);
	Point getRandomPoint() const;
	int getCount() const;
	Vector<BallSprite*> *ballVec;
	BallSprite *flashNow;
	void addBall(int n);
	CREATE_FUNC(GameScene);
	bool is_move(int fx, int fy, int tx, int ty);
	bool dfs(int x, int y, int ex, int ey);
	void removeBall(BallSprite *bsp);
	void getRemoveBall(int x, int y);
	int countBall(BallSprite* ball);
	BallSprite* getBall(int x, int y);
	void moveBall(int x, int y, BallSprite* bs);
private:
	static const int noclicked = 0;
	static const int clicked = 1;
	int state;
	std::vector<Point> unUse;
	std::vector<Point>::iterator findPoint(Point p);
	int map[MAX_SIZE][MAX_SIZE];
	bool visit[MAX_SIZE][MAX_SIZE];
	Vector<BallSprite*>removelist;
	int mark;
	Label *Lmark;
};

