#ifndef __MAPA_H__
#define __MAPA_H__

#include "cocos2d.h"
extern int cantcoin;
extern bool l1pass;
extern bool l2pass;
extern bool l3pass;
extern int lifemymonster;
extern int shieldmymonster;
extern int damage;
extern int cantUltimate;
extern int cantHealth;
extern int cantAttack;
extern int cantPoison;
extern int points;
class Mapa : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    bool leftPressed = false, rightPressed = false, upPressed = false, downPressed = false;

    virtual bool init();
    
    // a selector callback
    //void Exit(cocos2d::Ref* pSender);
    cocos2d::Sprite* monster;
    cocos2d::Sprite* fondoMapa;
    cocos2d::Sprite* store;
    cocos2d::Sprite* level_1;
    cocos2d::Sprite* level_2;
    cocos2d::Sprite* mountains;
    cocos2d::Sprite* totem;
    cocos2d::Sprite* coin;
    bool onKeyPressed(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event);
    bool onKeyReleased(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event);
    virtual void update(float delta) override;
    cocos2d::MenuItemImage* changestore;
    cocos2d::MenuItemImage* changelevel1;
    cocos2d::MenuItemImage* changelevel2;
    cocos2d::MenuItemImage* changetotem;
    cocos2d::Menu* menu;
    cocos2d::Label* totcoins;
    void ChangeStore(cocos2d::Ref* pSender);
    void ChangeLevel1(cocos2d::Ref* pSender);
    void ChangeLevel2(cocos2d::Ref* pSender);
    void ChangeTotem(cocos2d::Ref* pSender);
    

    // implement the "static create()" method manually
    CREATE_FUNC(Mapa);

    private:
        cocos2d::PhysicsWorld* sceneWorld;
        void SetPhysicsWorld(cocos2d::PhysicsWorld* world) { sceneWorld = world; };
        bool onContactBegin(cocos2d::PhysicsContact &contact);
        bool onContactSeparate(cocos2d::PhysicsContact& contact);
};

#endif // __MAPA_H__
