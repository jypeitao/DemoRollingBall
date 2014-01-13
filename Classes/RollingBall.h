//
//  RollingBall.h
//  RollingBall
//
//  Created by cocos on 14-1-13.
//
//

#ifndef __RollingBall__RollingBall__
#define __RollingBall__RollingBall__

#include "cocos2d.h"
USING_NS_CC;

class RollingBall : public cocos2d::Layer
{
public:
    RollingBall();
    ~RollingBall();
    static cocos2d::Scene* createScene();
    virtual bool init();
    void btnDebugDrawCallback(Object* pSender);
    CREATE_FUNC(RollingBall);
    
    void setPhyWorld(PhysicsWorld* world){_world = world;}
    void demoLayout();
    void toggleOfDebugDraw();
    void physicsContact();
private:
    PhysicsWorld* _world;
    bool onContactCallBack(EventCustom* event, const PhysicsContact& contact);
};

#endif /* defined(__RollingBall__RollingBall__) */
