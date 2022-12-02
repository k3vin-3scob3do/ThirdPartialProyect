#ifndef __LEVEL2_H__
#define __LEVEL2_H__

#include "cocos2d.h"

class Level2 : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void Exit(cocos2d::Ref* pSender);
    cocos2d::MenuItemImage* exit;
    cocos2d::Sprite* background;
    cocos2d::Sprite* monster;
    cocos2d::Sprite* mymonster;
    cocos2d::Sprite* contlife;
    cocos2d::Sprite* contshield;
    cocos2d::Sprite* mycontlife;
    cocos2d::Sprite* mycontshield;


    // implement the "static create()" method manually
    CREATE_FUNC(Level2);
};

#endif // __LEVEL2_H__
