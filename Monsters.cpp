#include "Mapa.h"
#include "HelloWorldScene.h"
#include "Monsters.h"
#include "Scores.h"
#include "Title.h"
#include <windows.h>
#include "StoreScene.h"
#include <cocostudio/SimpleAudioEngine.h>

USING_NS_CC;
extern int character = 0;
Scene* Monsters::createScene()
{
    return Monsters::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Monsters::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Sounds/sonido-para-celular-aguila.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Sounds/sonido-de-rugido-de-monstruo.mp3");

    fondo = Sprite::create("Background.png");
    fondo->setPosition(350, 300);
    this->addChild(fondo, 0);

    player1 = MenuItemImage::create("Player1.png", "Player1Selected.png", CC_CALLBACK_1(Monsters::Player1, this));
    player1->setPosition(175, 300);
    player2 = MenuItemImage::create("Player2.png", "Player2Selected.png", CC_CALLBACK_1(Monsters::Player2, this));
    player2->setPosition(525, 300);
    auto menu = Menu::create(player1, player2, nullptr);
    menu->setPosition(0, 0);
    this->addChild(menu, 2);

    return true;
}


void Monsters::Player1(Ref* pSender)
{
    character = 0;
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Sounds/sonido-para-celular-aguila.mp3");
    Director::getInstance()->popScene();
}

void Monsters::Player2(Ref* pSender)
{   
    character = 1;
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Sounds/sonido-de-rugido-de-monstruo.mp3");
    Director::getInstance()->popScene();
}

