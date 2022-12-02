#include "Mapa.h"
#include "HelloWorldScene.h"
#include "Monsters.h"
#include "Title.h"
#include "StoreScene.h"
#include <cocostudio/SimpleAudioEngine.h>



USING_NS_CC;
extern bool haveUlti = false;
extern bool havePoison = false;
Scene* StoreScene::createScene()
{
    return StoreScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool StoreScene::init()
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

    background = Sprite::create("MenuStore.png");
    background->setPosition(350, 300);
    this->addChild(background, 0);

    health = MenuItemImage::create("Health.png", "HealthSelected.png", CC_CALLBACK_1(StoreScene::Health, this));
    power = MenuItemImage::create("Power.png", "PowerSelected.png", CC_CALLBACK_1(StoreScene::Power, this));
    poison = MenuItemImage::create("Poison.png", "PoisonSelected.png", CC_CALLBACK_1(StoreScene::Poison, this));
    ultimate = MenuItemImage::create("Ultimate.png", "UltimateSelected.png", CC_CALLBACK_1(StoreScene::Ultimate, this));
    shield = MenuItemImage::create("Shield.png", "ShieldSelected.png", CC_CALLBACK_1(StoreScene::Shield, this));
    goback = MenuItemImage::create("Exit.png", "ExitSelected.png", CC_CALLBACK_1(StoreScene::GoBack, this));
    health->setPosition(140, 490);
    power->setPosition(110, 120);
    ultimate->setPosition(400, 490);
    poison->setPosition(350, 120);
    shield->setPosition(580, 110);
    goback->setPosition(580, 550);
    auto menu = Menu::create(health, power, ultimate, shield, goback, poison, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    coin = Sprite::create("Coin.png");
    coin->setPosition(600, 450);
    this->addChild(coin, 1);

    totcoins = Label::createWithTTF("x " + std::to_string(cantcoin), "fonts/Marker Felt.ttf", 45);
    totcoins->setPosition(Point(coin->getPositionX() + 60, coin->getPositionY()));
    totcoins->setTextColor(Color4B::BLACK);
    this->addChild(totcoins, 1);

    costoHealth = 5;
    costoPower = 5;
    costoUltimate = 20;
    costoShield = 3;
    costoPoison = 15;
    
    this->scheduleUpdate();
    return true;
}
void StoreScene::update(float delta) {
    totcoins->setString("x" + std::to_string(cantcoin));
    if (haveUlti) {
        ultimate->setEnabled(false);
        ultimate->setVisible(false);
    }
    else {
        ultimate->setEnabled(true);
        ultimate->setVisible(true);
    }

    if (havePoison) {
        poison->setEnabled(false);
        poison->setVisible(false);
    }
    else {
        poison->setEnabled(true);
        poison->setVisible(true);
    }
}

void StoreScene::GoBack(Ref* pSender){
    Director::getInstance()->popScene();
}

void StoreScene::Health(cocos2d::Ref* pSender) {
    if (cantcoin >= costoHealth) {
        cantcoin -= costoHealth;
        lifemymonster++;
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Sounds/sonido-de-dinero.mp3");
    }
}

void StoreScene::Power(cocos2d::Ref* pSender) {
    if (cantcoin >= costoPower) {
        cantcoin -= costoPower;
        damage++;
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Sounds/sonido-de-dinero.mp3");
    }
}

void StoreScene::Poison(cocos2d::Ref* pSender) {
    if (havePoison) {
        poison->setEnabled(false);
        poison->setVisible(false);
    }
    if (cantcoin >= costoPoison) {
        cantcoin -= costoPoison;
        havePoison = true;
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Sounds/sonido-de-dinero.mp3");
    }
}

void StoreScene::Ultimate(cocos2d::Ref* pSender) {
    if (haveUlti) {
        ultimate->setEnabled(false);
        ultimate->setVisible(false);
    }
    if (cantcoin >= costoUltimate) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Sounds/sonido-de-dinero.mp3");
        cantcoin -= costoUltimate;
        haveUlti = true;
    }
}

void StoreScene::Shield(cocos2d::Ref* pSender) {
    if (cantcoin >= costoShield) {
        cantcoin -= costoShield;
        shieldmymonster++;
    }
}

