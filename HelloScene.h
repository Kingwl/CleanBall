#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class HelloScene : public Scene
{
public:
	HelloScene();
	~HelloScene();
	virtual bool init();
	static HelloScene* createScene();
	CREATE_FUNC(HelloScene);
	void MenuCallBackFunc(Ref *sender);
private:
	Layer *_helloLayer;
	Size size;
};

