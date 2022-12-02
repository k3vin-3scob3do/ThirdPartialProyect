#include "Mapa.h"
#include "HelloWorldScene.h"
#include "Monsters.h"
#include "Title.h"
#include <cocostudio/SimpleAudioEngine.h>

USING_NS_CC;

Scene* Title::createScene()
{
    return Title::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Title::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }


    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Sounds/Mountain Emperor.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Sounds/Mountain Emperor.mp3");

    auto listenerKeyboard = EventListenerKeyboard().create();
    listenerKeyboard->onKeyPressed = CC_CALLBACK_2(Title::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeyboard, this);

    background = Sprite::create("Background.png");
    background->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(background, 0);

    fondo = Sprite::create("Title.png");
    fondo->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(fondo, 1);
    
    return true;
}

bool Title::onKeyPressed(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event) {
    auto scene = HelloWorld::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(1.0f, scene));
    return true;
}

void Title::Exit(Ref* pSender)
{
    Director::getInstance()->end();
}


