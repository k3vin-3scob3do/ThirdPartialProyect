#ifndef __TITLE_H__
#define __TITLE_H__

#include "cocos2d.h"

class Title : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void Exit(cocos2d::Ref* pSender);
    bool onKeyPressed(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event);
    cocos2d::Sprite* fondo;
    cocos2d::Sprite* background;
    
    
    // implement the "static create()" method manually
    CREATE_FUNC(Title);
};

#endif // __TITLE_H__
