#include "AppDelegate.h"
#include "StartScene.h"
#include "GameDefine.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("Art_Sword");
		glview->setFrameSize(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT);
        director->setOpenGLView(glview);
    }
	glview->setDesignResolutionSize(800, 480, ResolutionPolicy::SHOW_ALL);
    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = StartScene::createScene();

    // run
    director->runWithScene(scene);
	
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("linkstr.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("music_bg.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music_explode.wav");
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
