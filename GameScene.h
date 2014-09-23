#pragma once
#include <cocos2d.h>
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
	CREATE_FUNC(GameScene);
private:
	std::vector<Point> unUse ;
	Point getRandomPoint();
	std::vector<Point>::iterator findPoint(Point p);
	int map[MAX_SIZE][MAX_SIZE];
};

