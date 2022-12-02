


#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void Start(cocos2d::Ref* pSender);
    void ScoresButton(cocos2d::Ref* pSender);
    void Monster(cocos2d::Ref* pSender);
    void Exit(cocos2d::Ref* pSender);

    cocos2d::Sprite* titulo;
    cocos2d::Sprite* background;
    cocos2d::MenuItemImage* start;
    cocos2d::MenuItemImage* monsters;
    cocos2d::MenuItemImage* scores;
    cocos2d::MenuItemImage* exit;
    
    
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
