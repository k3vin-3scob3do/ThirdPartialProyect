#ifndef __MONSTERS_H__
#define __MONSTERS_H__

#include "cocos2d.h"
extern int character;
class Monsters : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void Player1(cocos2d::Ref* pSender);
    void Player2(cocos2d::Ref* pSender);
    cocos2d::MenuItemImage* player1;
    cocos2d::MenuItemImage* player2;
    cocos2d::Sprite* fondo;
    
    
    // implement the "static create()" method manually
    CREATE_FUNC(Monsters);
};

#endif // __MONSTERS_H__
