#include "HelloWorldScene.h"
#include "StateManager.h"
#include <random>

#define ACH_COCOS2DX_ACHIEVEMENT_01 "CgkIme7H5v4XEAIQCA"
#define ACH_COCOS2DX_ACHIEVEMENT_02 "CgkIme7H5v4XEAIQCQ"
#define LEAD_COCOS2DX_LEADERBOARD "CgkIme7H5v4XEAIQBw"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto close_menu = Menu::create(closeItem, NULL);
    close_menu->setPosition(Point::ZERO);
    this->addChild(close_menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    std::string status = "Status:GPGS signed in";
    
    if(!StateManager::IsSignedIn())
    {
        status = "Status:GPGS not signed in";
    }
    
    label = LabelTTF::create(status.c_str(), "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Point(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    //SignIn and Sign Out.
    std::string strSign = "Sign In";
    if (StateManager::IsSignedIn()) {
        strSign = "Sign Out";
    }
    auto signin_label = Label::createWithSystemFont(strSign, "Arial", 20);
    auto signin_menuitem = MenuItemLabel::create(signin_label,
                                                 [signin_label](Ref* ref){
                                                     if (StateManager::IsSignedIn()) {
                                                         log("The Status of now is SignedIn");
                                                         signin_label->setString("Sign Out");
                                                         StateManager::SignOut();
                                                     } else {
                                                         log("The Status of now is not SignedIn");
                                                         StateManager::BeginUserInitiatedSignIn();
                                                     }

                                                 });
    signin_menuitem->setPosition(Point(visibleSize.width/2-100, visibleSize.height/2+50));
    
    //Show LeaderBoards
    auto leaderboard_label = Label::createWithSystemFont("LeaderBoard", "Arial", 20);
    auto leaderboard_menuitem = MenuItemLabel::create(leaderboard_label,
                                                      [](Ref* ref){
                                                          if (StateManager::IsSignedIn()) {
                                                              log("Show LeaderBoard");
                                                              StateManager::ShowLeaderboard(LEAD_COCOS2DX_LEADERBOARD);
                                                          }
                                                          else{
                                                              log("Failed to show LeaderBoard, Not Signed in");
                                                          }
                                                      });
    leaderboard_menuitem->setPosition(Point(visibleSize.width/2+100, visibleSize.height/2+50));
    
    //Show Achievements
    auto achievement_label = Label::createWithSystemFont("Achievement", "Arial", 20);
    auto achievement_menuitem = MenuItemLabel::create(achievement_label,
                                                      [](Ref* ref){
                                                          if (StateManager::IsSignedIn()) {
                                                              log("Show Achievements");
                                                              StateManager::ShowAchievements();
                                                          }
                                                          else{
                                                              log("Failed to show Achievements, Not Signed in");
                                                          }
                                                      });
    achievement_menuitem->setPosition(Point(visibleSize.width/2-100, visibleSize.height/2));
    
    //Submit Score
    std::uniform_int_distribution<unsigned> u(0,10000);
    std::default_random_engine e;
    e.seed((unsigned)time(NULL));
    auto rand_score =  u(e);
    auto submitscore_label = Label::createWithSystemFont("SubmitScore", "Arial", 20);
    auto submitscore_menuitem = MenuItemLabel::create(submitscore_label,
                                                      [rand_score](Ref* ref){
                                                          if (StateManager::IsSignedIn()) {
                                                              log("Submit Score %d", rand_score);
                                                              StateManager::SubmitHighScore(LEAD_COCOS2DX_LEADERBOARD, rand_score);
                                                          }
                                                          else{
                                                              log("Failed to submit score, Not Signed in");
                                                          }
                                                      });
    submitscore_menuitem->setPosition(Point(visibleSize.width/2+100, visibleSize.height/2));
    
    //Unlock Achievement
    auto unlockachievement_label = Label::createWithSystemFont("UnlockAchievement", "Arial", 20);
    auto unlockachievement_menuitem = MenuItemLabel::create(unlockachievement_label,
                                                      [](Ref* ref){
                                                          if (StateManager::IsSignedIn()) {
                                                              log("Unlock Achievement %s", ACH_COCOS2DX_ACHIEVEMENT_01);
                                                              StateManager::UnlockAchievement(ACH_COCOS2DX_ACHIEVEMENT_01);
                                                          }
                                                          else{
                                                              log("Failed to unlock Achievements, Not Signed in");
                                                          }
                                                      });
    unlockachievement_menuitem->setPosition(Point(visibleSize.width/2-100, visibleSize.height/2-50));
    
    //Increase Achievement
    auto increaseachievement_label = Label::createWithSystemFont("IncreaseAchievement", "Arial", 20);
    auto increaseachievement_menuitem = MenuItemLabel::create(increaseachievement_label,
                                                            [](Ref* ref){
                                                                if (StateManager::IsSignedIn()) {
                                                                    log("Increase Achievement %s", ACH_COCOS2DX_ACHIEVEMENT_02);
                                                                    StateManager::IncrementAchievement(ACH_COCOS2DX_ACHIEVEMENT_02);
                                                                }
                                                                else{
                                                                    log("Failed to increase Achievements, Not Signed in");
                                                                }
                                                            });
    increaseachievement_menuitem->setPosition(Point(visibleSize.width/2+100, visibleSize.height/2-50));
    
    auto menu = Menu::create(signin_menuitem, leaderboard_menuitem, achievement_menuitem,
                             submitscore_menuitem, unlockachievement_menuitem, increaseachievement_menuitem, nullptr);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);
    
    this->scheduleUpdate();
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::update(float dt)
{
    std::string status = "Status:GPGS signed in";
    
    if(!StateManager::IsSignedIn())
    {
        status = "Status:GPGS not signed in";
    }
    
    label->setString(status);
}
