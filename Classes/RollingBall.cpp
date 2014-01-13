//
//  RollingBall.cpp
//  RollingBall
//
//  Created by cocos on 14-1-13.
//
//

#include "RollingBall.h"

RollingBall::RollingBall(){}
RollingBall::~RollingBall(){}

Scene* RollingBall::createScene()
{
    auto scene = Scene::createWithPhysics();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    //choose whitch part need to draw, Joint, Shape, Contact, None or All
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    // the edge of the screen
	auto body = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
    auto edgeNode = Node::create();
    edgeNode->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	edgeNode->setPhysicsBody(body);
	scene->addChild(edgeNode);
    
    auto layer = RollingBall::create();
    layer->setPhyWorld(scene->getPhysicsWorld());
    scene->addChild(layer);
    
    //open the gravity sensor
    layer->setAccelerometerEnabled(true);
    
    return scene;
}

bool RollingBall::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    //the layout of the physics world
    demoLayout();
    //turn on or off the debug draw
    toggleOfDebugDraw();
    //collision detection
    physicsContact();
    
    return true;
}

void RollingBall::physicsContact(){
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_2(RollingBall::onContactCallBack, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

void RollingBall::toggleOfDebugDraw(){
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    auto toggleItem = MenuItemImage::create(
                                            "CloseNormal.png",
                                            "CloseSelected.png",
                                            CC_CALLBACK_1(RollingBall::btnDebugDrawCallback, this));
	toggleItem->setPosition(Point(origin.x + visibleSize.width - toggleItem->getContentSize().width/2 ,
                                  origin.y + toggleItem->getContentSize().height/2));
    
    auto menu = Menu::create(toggleItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
}

bool RollingBall::onContactCallBack(EventCustom *event, const PhysicsContact& contact)
{
    auto sp = (Sprite*)contact.getShapeA()->getBody()->getNode();
    int tag = sp->getTag();
    log("onContactBegin: %d", tag);
    return true;
}

void RollingBall::demoLayout(){
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point verts1[] = {
        Point(-146.5f, 155.1f),
        Point(-146.5f, -87.6f),
        Point(-140.9f, -88.1f),
        Point(-140.8f, 155.5f),
        Point(162.8f, 154.6f),
        Point(162.9f, -27.7f),
        Point(12.0f, -29.0f),
        Point(12.0f, -33.9f),
        Point(167.6f, -34.6f),
        Point(168.7f, 154.4f),
        Point(235.0f, 155.1f),
        Point(235.3f, -91.6f),
        Point(238.8f, -93.2f),
        Point(239.8f, -91.5f),
        Point(239.1f, 159.2f),
        Point(-238.3f, 159.0f),
        Point(-238.7f, 155.0f),
        Point(-147.4f, 154.9f)
    };
    
    Point verts2[] = {
        Point(-235.8f, 82.9f),
        Point(-235.2f, -154.1f),
        Point(-44.2f, -154.1f),
        Point(-44.3f, 98.6f),
        Point(101.1f, 99.6f),
        Point(101.1f, 95.5f),
        Point(-38.2f, 93.5f),
        Point(-38.8f, -153.6f),
        Point(161.7f, -154.2f),
        Point(161.7f, -97.9f),
        Point(12.0f, -98.3f),
        Point(12.3f, -94.0f),
        Point(167.0f, -92.2f),
        Point(167.1f, -153.8f),
        Point(239.3f, -154.7f),
        Point(239.0f, -157.8f),
        Point(-239.0f, -158.4f),
        Point(-237.6f, 81.9f)
    };
    
    auto spEdgePolygon1 = Sprite::create("bg1.png");
    spEdgePolygon1->setTag(1);
    auto borderUpper = PhysicsBody::createEdgePolygon(verts1,18);
    spEdgePolygon1->setPhysicsBody(borderUpper);
    spEdgePolygon1->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
    this->addChild(spEdgePolygon1);
    
    auto spEdgePolygon2 = Node::create();
    spEdgePolygon2->setTag(2);
    auto borderBottom = PhysicsBody::createEdgePolygon(verts2,18);
    spEdgePolygon2->setPhysicsBody(borderBottom);
    spEdgePolygon2->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
    this->addChild(spEdgePolygon2);
    
    auto spBall = Sprite::create("ball.png");
    spBall->setTag(0);
	auto body = PhysicsBody::createCircle(spBall->getContentSize().width / 2);
    spBall->setPhysicsBody(body);
    spBall->setPosition(Point(visibleSize.width/2,visibleSize.height-50));
	this->addChild(spBall);
}

void RollingBall::btnDebugDrawCallback(Object* pSender)
{
	if(_world->getDebugDrawMask() != PhysicsWorld::DEBUGDRAW_NONE) {
        _world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
	} else {
		_world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	}
}