#include "HelloWorldScene.h"
#include "Mapa.h"
#include "Monsters.h"
#include "StoreScene.h"
#include "Scores.h"
#include "../proj.win32/Scores.h"


USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    background = Sprite::create("Background.png");
    background->setPosition(350, 300);
    this->addChild(background, 0);
    titulo = Sprite::create("MonsterBattle.png");
    titulo->setPosition(350, 465);
    this->addChild(titulo, 1);

    start = MenuItemImage::create("Start.png", "StartSelected.png", CC_CALLBACK_1(HelloWorld::Start, this));
    //exit = MenuItemImage::create("Exit.png", "ExitSelected.png", CC_CALLBACK_1(HelloWorld::Exit, this));
    monsters = MenuItemImage::create("Monsters.png", "MonstersSelected.png", CC_CALLBACK_1(HelloWorld::Monster, this));
    scores = MenuItemImage::create("Scores.png", "ScoresSelected.png", CC_CALLBACK_1(HelloWorld::ScoresButton, this));
    start->setPosition(350, 280);
    monsters->setPosition(350, 170);
    scores->setPosition(350, 60);
    //exit->setPosition(600, 50);
    auto menu = Menu::create(start, monsters, scores, nullptr);
    menu->setPosition(Vec2::ZERO);
    
    this->addChild(menu, 1);

    return true;
}

void HelloWorld::Start(Ref* pSender)
{
    auto scene = Mapa::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(1.0f, scene));
}

void HelloWorld::Exit(Ref* pSender)
{
    Director::getInstance()->end();
}

void HelloWorld::Monster(Ref* pSender)
{
    auto scene = Monsters::createScene();

    Director::getInstance()->pushScene(TransitionFade::create(1.0f, scene));
}

void HelloWorld::ScoresButton(Ref* pSender)
{
    Director::getInstance()->pushScene(Scores::createScene());
}

