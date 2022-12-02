#ifndef __STORESCENE_H__
#define __STORESCENE_H__

#include "cocos2d.h"
extern bool haveUlti;
extern bool havePoison;
class StoreScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    
    cocos2d::Sprite* background;
    cocos2d::MenuItemImage* health;
    cocos2d::MenuItemImage* power;
    cocos2d::MenuItemImage* ultimate;
    cocos2d::MenuItemImage* shield;
    cocos2d::MenuItemImage* poison;
    cocos2d::MenuItemImage* goback;
    void GoBack(cocos2d::Ref* pSender);
    void Health(cocos2d::Ref* pSender);
    void Power(cocos2d::Ref* pSender);
    void Ultimate(cocos2d::Ref* pSender);
    void Shield(cocos2d::Ref* pSender);
    void Poison(cocos2d::Ref* pSender);
    //virtual void update(float delta) override;
    int costoHealth;
    int costoUltimate;
    int costoShield;
    int costoPower;
    int costoPoison;
    cocos2d::Label* totcoins;
    cocos2d::Sprite* coin;
    virtual void update(float delta) override;
    // implement the "static create()" method manually
    CREATE_FUNC(StoreScene);
};

#endif // __STORESCENE_H__
