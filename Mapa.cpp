#include "Mapa.h"
#include "HelloWorldScene.h"
#include "Monsters.h"
#include "Title.h"
#include "Level1.h"
#include "StoreScene.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "../proj.win32/Level1.h"
#include <AudioEngine.h>
#include <cocostudio/SimpleAudioEngine.h>

USING_NS_CC;
extern int cantcoin = 40;
extern bool l1pass = false;
extern bool l2pass = false;
extern bool l3pass = false;
extern int lifemymonster = 5;
extern int shieldmymonster = 0;
extern int damage = 2;
extern int cantUltimate = 1;
extern int cantHealth = 5;
extern int cantAttack = 7;
extern int cantPoison = 2;
extern int points = 0;
Scene* Mapa::createScene()
{
    auto scene = Scene::createWithPhysics();
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(Vec2(0,0));
    auto layer = Mapa::create();
    layer->SetPhysicsWorld(scene->getPhysicsWorld());
    scene->addChild(layer);
    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Mapa::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    AudioEngine::stopAll();
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Sounds/sonido-puerta-abierta-y-cerrada.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Sounds/abriendo-la-puerta-del-castillo-efecto-de-sonido.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Sounds/Strength of the Titans.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Sounds/Strength of the Titans.mp3", true);
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.4);
 
    
    fondoMapa = Sprite::create("Fondo.png");
    fondoMapa->setPosition(350, 300);
    this->addChild(fondoMapa, 0);

    mountains = Sprite::create("Mountains.png");
    mountains->setPosition(350, 300);
    this->addChild(mountains, 3);

    if (character == 0) {
        monster = Sprite::create("Player1Min.png");
        monster->setPosition(0, 300);
        auto skullBody = PhysicsBody::createCircle(monster->getContentSize().width / 2, PhysicsMaterial(0, 1, 0));
        skullBody->setCollisionBitmask(1);
        skullBody->setContactTestBitmask(true);
        monster->setPhysicsBody(skullBody);
        this->addChild(monster, 2);
    }else if (character == 1) {
        monster = Sprite::create("Player2Min.png");
        monster->setPosition(0, 300);
        auto skullBody = PhysicsBody::createCircle(monster->getContentSize().width / 2, PhysicsMaterial(0, 1, 0));
        skullBody->setCollisionBitmask(1);
        skullBody->setContactTestBitmask(true);
        monster->setPhysicsBody(skullBody);
        this->addChild(monster, 2);
    }
    

    store = Sprite::create("Store.png");
    store->setPosition(135, 480);
    auto storeBody = PhysicsBody::createCircle(store->getContentSize().width / 2, PhysicsMaterial(0, 1, 0));
    storeBody->setCollisionBitmask(2);
    storeBody->setContactTestBitmask(true);
    storeBody->setDynamic(false);
    store->setPhysicsBody(storeBody);
    this->addChild(store, 1);

    level_1 = Sprite::create("Level1.png");
    level_1->setPosition(400, 460);
    auto level1Body = PhysicsBody::createCircle(level_1->getContentSize().width / 2, PhysicsMaterial(0, 1, 0));
    level1Body->setCollisionBitmask(3);
    level1Body->setContactTestBitmask(true);
    level1Body->setDynamic(false);
    level_1->setPhysicsBody(level1Body);
    this->addChild(level_1, 1);

    level_2 = Sprite::create("Level2.png");
    level_2->setPosition(210, 130);
    auto level2Body = PhysicsBody::createCircle(level_2->getContentSize().width / 2, PhysicsMaterial(0, 1, 0));
    level2Body->setCollisionBitmask(4);
    level2Body->setContactTestBitmask(true);
    level2Body->setDynamic(false);
    level_2->setPhysicsBody(level2Body);
    this->addChild(level_2, 1);

    totem = Sprite::create("Totem.png");
    totem->setPosition(600, 250);
    auto totemBody = PhysicsBody::createCircle(totem->getContentSize().width / 2, PhysicsMaterial(0, 1, 0));
    totemBody->setCollisionBitmask(5);
    totemBody->setContactTestBitmask(true);
    totemBody->setDynamic(false);
    totem->setPhysicsBody(totemBody);
    this->addChild(totem, 1);


    changestore = MenuItemImage::create("Enter.png", "EnterSelected.png", CC_CALLBACK_1(Mapa::ChangeStore, this));
    changelevel1 = MenuItemImage::create("Enter.png", "EnterSelected.png", CC_CALLBACK_1(Mapa::ChangeLevel1, this));
    changelevel2 = MenuItemImage::create("Enter.png", "EnterSelected.png", CC_CALLBACK_1(Mapa::ChangeLevel2, this));
    changetotem = MenuItemImage::create("Enter.png", "EnterSelected.png", CC_CALLBACK_1(Mapa::ChangeTotem, this));
    menu = Menu::create(changestore, changelevel1, changelevel2, changetotem, nullptr);
    menu->setPosition(Vec2::ZERO);
    changestore->setPosition(Point(store->getPositionX(), store->getPositionY() + 85));
    changelevel1->setPosition(Point(level_1->getPositionX(), level_1->getPositionY() + 85));
    changelevel2->setPosition(Point(level_2->getPositionX(), level_2->getPositionY() + 85));
    changetotem->setPosition(Point(totem->getPositionX(), totem->getPositionY() + 165));
    menu->setVisible(false);
    menu->setEnabled(false);
    this->addChild(menu, 1);

    coin = Sprite::create("Coin.png");
    coin->setPosition(590, 560);
    this->addChild(coin, 1);

    totcoins = Label::createWithTTF("x " + std::to_string(cantcoin), "fonts/Marker Felt.ttf", 45);
    totcoins->setPosition(Point(coin->getPositionX() + 60, coin->getPositionY()));
    totcoins->setTextColor(Color4B::BLACK);
    this->addChild(totcoins, 1);

    auto contactlistener = EventListenerPhysicsContact::create();
    contactlistener->onContactBegin = CC_CALLBACK_1(Mapa::onContactBegin, this);
    contactlistener->onContactSeparate = CC_CALLBACK_1(Mapa::onContactSeparate, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactlistener, this);

    auto listenerKeyboard = EventListenerKeyboard().create();
    listenerKeyboard->onKeyPressed = CC_CALLBACK_2(Mapa::onKeyPressed, this);
    listenerKeyboard->onKeyReleased = CC_CALLBACK_2(Mapa::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeyboard, this);

    

    this->scheduleUpdate();
    return true;
}

bool Mapa::onKeyPressed(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event) {
    switch (key) {
    case EventKeyboard::KeyCode::KEY_A: case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        leftPressed = true;
        break;
    case EventKeyboard::KeyCode::KEY_D: case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        rightPressed = true;
        break;
    case EventKeyboard::KeyCode::KEY_W: case EventKeyboard::KeyCode::KEY_UP_ARROW:
        upPressed = true;
        break;
    case EventKeyboard::KeyCode::KEY_S: case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        downPressed = true;
        break;
    }

    return true;
}

bool Mapa::onKeyReleased(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event) {
    leftPressed = false;
    rightPressed = false;
    upPressed = false;
    downPressed = false;
    return true;
}

void Mapa::update(float delta) {
    Vec2 pos = monster->getPosition();

    if (pos.x <= 0) leftPressed = false;
    if (leftPressed) {
        monster->setPositionX(pos.x - 100 * delta);
        monster->setFlippedX(true);
    }
    if (pos.x >= 700) rightPressed = false;
    if (rightPressed) {
        monster->setPositionX(pos.x + 100 * delta);
        monster->setFlippedX(false);
    }
    if (pos.y >= 600) upPressed = false;
    if (upPressed) {
        monster->setPositionY(pos.y + 100 * delta);
    }
    if (pos.y <= 0) downPressed = false;
    if (downPressed) {
        monster->setPositionY(pos.y - 100 * delta);
    }

    totcoins->setString("x" + std::to_string(cantcoin));

}

bool Mapa::onContactBegin(cocos2d::PhysicsContact& contact) {
    PhysicsBody* a = contact.getShapeA()->getBody();
    PhysicsBody* b = contact.getShapeB()->getBody();
    menu->setVisible(true);
    menu->setEnabled(true);
    if ((1 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask()) || (2 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask())) {
        changestore->setVisible(true);
        changestore->setEnabled(true);
        changelevel1->setVisible(false);
        changelevel1->setEnabled(false);
        changelevel2->setVisible(false);
        changelevel2->setEnabled(false);
        changetotem->setVisible(false);
        changetotem->setEnabled(false);
    }else if ((1 == a->getCollisionBitmask() && 3 == b->getCollisionBitmask()) || (3 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask())) {
        changestore->setVisible(false);
        changestore->setEnabled(false);
        changelevel1->setVisible(true);
        changelevel1->setEnabled(true);
        changelevel2->setVisible(false);
        changelevel2->setEnabled(false);
        changetotem->setVisible(false);
        changetotem->setEnabled(false);
    }else if ((1 == a->getCollisionBitmask() && 4 == b->getCollisionBitmask()) || (4 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask())) {
        changestore->setVisible(false);
        changestore->setEnabled(false);
        changelevel1->setVisible(false);
        changelevel1->setEnabled(false);
        changelevel2->setVisible(true);
        changelevel2->setEnabled(true);
        changetotem->setVisible(false);
        changetotem->setEnabled(false);
    }else if ((1 == a->getCollisionBitmask() && 5 == b->getCollisionBitmask()) || (5 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask())) {
        if (!l1pass || !l2pass) {
            changestore->setVisible(false);
            changestore->setEnabled(false);
            changelevel1->setVisible(false);
            changelevel1->setEnabled(false);
            changelevel2->setVisible(false);
            changelevel2->setEnabled(false);
            changetotem->setVisible(false);
            changetotem->setEnabled(false);
        }else{
            changestore->setVisible(false);
            changestore->setEnabled(false);
            changelevel1->setVisible(false);
            changelevel1->setEnabled(false);
            changelevel2->setVisible(false);
            changelevel2->setEnabled(false);
            changetotem->setVisible(true);
            changetotem->setEnabled(true);
        }
      
    }
    
    return true;
}

bool Mapa::onContactSeparate(cocos2d::PhysicsContact& contact) {
    menu->setVisible(false);
    menu->setEnabled(false);
    return true;
}


void Mapa::ChangeStore(Ref* pSende) {
    auto scene = StoreScene::createScene();
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Sounds/sonido-puerta-abierta-y-cerrada.mp3");
    Director::getInstance()->pushScene(TransitionCrossFade::create(1.0f, scene));
}

void Mapa::ChangeLevel1(Ref* pSende) {
    auto scene = Level1::createScene();
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Sounds/sonido-puerta-abierta-y-cerrada.mp3");
    Director::getInstance()->pushScene(TransitionCrossFade::create(1.0f, scene));
}

void Mapa::ChangeLevel2(Ref* pSende) {
    auto scene = Level2::createScene();
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Sounds/sonido-puerta-abierta-y-cerrada.mp3");
    Director::getInstance()->pushScene(TransitionCrossFade::create(1.0f, scene));
}

void Mapa::ChangeTotem(Ref* pSende) {
    auto scene = Level3::createScene();
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Sounds/sonido-puerta-abierta-y-cerrada.mp3");
    Director::getInstance()->pushScene(TransitionCrossFade::create(1.0f, scene));
}
