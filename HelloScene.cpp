#include "HelloScene.h"
#include "GameScene.h"

HelloScene::HelloScene()
{
	_helloLayer = nullptr;
	
}


HelloScene::~HelloScene()
{
}
bool HelloScene::init()
{
	size = Director::sharedDirector()->getVisibleSize();
	CCLog("%f %f", size.height, size.width);
	_helloLayer = Layer::create();
	this->addChild(_helloLayer);


	auto bkg = Sprite::create("bkg.png");
	_helloLayer->addChild(bkg);
	bkg->setPosition(ccp(0, 0));
	bkg->setAnchorPoint(ccp(0, 0));


	auto playItem = MenuItemFont::create("Start", [&](Ref* sender)
	{
		//start game	
		CCLog("start");
		auto gamescene = GameScene::createScene();
		CCDirector::sharedDirector()->replaceScene(gamescene);
	});
	playItem->setPosition(ccp(size.width / 2, size.height*0.9));
	playItem->setFontSize(40);
	playItem->setFontName("Marker Felt");
	playItem->setColor(ccc3(255, 255, 255));
	auto aboutItem = MenuItemFont::create("About", [&](Ref* sender)
	{
		CCLog("About");
	}
	);
	aboutItem->setPosition(ccp(size.width / 2, size.height*0.6));
	aboutItem->setFontSize(40);
	aboutItem->setFontName("Marker Felt");
	aboutItem->setColor(ccc3(255, 255, 255));
	auto exitItem = MenuItemFont::create("End", [&](Ref* sender)
	{
		//exit game	
		CCLog("exit");
		Director::sharedDirector()->end();
	});
	exitItem->setPosition(ccp(size.width / 2, size.height*0.3));
	exitItem->setFontSize(40);
	exitItem->setFontName("Marker Felt");
	exitItem->setColor(ccc3(255, 255, 255));
	auto menu = Menu::create(playItem, aboutItem, exitItem, nullptr);
	menu->setPosition(ccp(0, 0));
	_helloLayer->addChild(menu);

	return true;
}
HelloScene* HelloScene::createScene()
{
	auto scene = HelloScene::create();
	return scene;
}