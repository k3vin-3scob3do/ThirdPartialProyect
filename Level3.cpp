#include "Mapa.h"
#include "HelloWorldScene.h"
#include "Monsters.h"
#include "Title.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include <cocostudio/SimpleAudioEngine.h>

USING_NS_CC;

Scene* Level3::createScene()
{
    return Level3::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Level3::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Sounds/SunsetLover.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Sounds/SunsetLover.mp3", true);
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    background = Sprite::create("Battle2.png");
    background->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(background, 0);

    monster = Sprite::create("Monster2.png");
    monster->setPosition(510, 300);
    monster->setFlippedX(true);
    this->addChild(monster, 1);

    mycontlife = Sprite::create("H" + std::to_string(lifemymonster) + ".png");
    mycontshield = Sprite::create("S" + std::to_string(shieldmymonster) + ".png");

    if (character == 0) {
        mymonster = Sprite::create("Player1.png");
        mymonster->setPosition(180, 130);
        this->addChild(mymonster, 1);
        mycontlife->setPosition(Point(mymonster->getPositionX(), mymonster->getPositionY() + 140));
        mycontshield->setPosition(Point(mymonster->getPositionX(), mymonster->getPositionY() + 190));
    }
    else if (character == 1) {
        mymonster = Sprite::create("Player2.png");
        mymonster->setPosition(180, 110);
        this->addChild(mymonster, 1);
        mycontlife->setPosition(Point(mymonster->getPositionX(), mymonster->getPositionY() + 125));
        mycontshield->setPosition(Point(mymonster->getPositionX(), mymonster->getPositionY() + 175));
    }

    contlife = Sprite::create("H" + std::to_string(lifemonster) + ".png");
    contshield = Sprite::create("S" + std::to_string(shieldmonster) + ".png");
    contlife->setPosition(Point(monster->getPositionX(), monster->getPositionY() + 110));
    contshield->setPosition(Point(monster->getPositionX(), monster->getPositionY() + 160));
    this->addChild(contlife, 1);
    this->addChild(contshield, 1);

    this->addChild(mycontlife, 1);
    this->addChild(mycontshield, 1);

    exit = MenuItemImage::create("Exit.png", "ExitSelected.png", CC_CALLBACK_1(Level3::Exit, this));
    auto menu = Menu::create(exit, nullptr);
    exit->setPosition(600, 500);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    return true;
}

void Level3::Exit(Ref* pSender)
{
    Director::getInstance()->popScene();
}