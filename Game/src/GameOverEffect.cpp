#include "GameOverEffect.h"
#include "Res.h"
#include "SexyAppFramework/Font.h"
#include "SexyAppFramework/SexyMatrix.h"
#include "SexyAppFramework/XAppBase.h"
#include "SexyAppFramework/MusicInterface.h"

using namespace FrameworkX;


const int xpos = 315;
const int xpos2 = 450;

GameOver::GameOver(FrameworkX::Image * pImg)
{
	mImg= pImg;
	mRestartLevel=false;
	mStartNewGame = false;
	mQuitGame = false;
	mActive=false;
	GameOver::Init();
}

GameOver::~GameOver()
{
}

void GameOver::Init()
{
	mState = GameOver::GO_FADEIN;
	mGOA.mFrame=0;
	mGOA.mSpeed=10;
	mGOA.x=0;
	mGOA.y=0-mImg->GetHeight()*1.0F;
	mDone = false;
	mEnableBtns = false;

}

void GameOver::Activate()
{
	GameOver::Init();
	mActive = true;
	gSexyAppBase->PlaySample(SOUND_PLAYMOUSEDOWN);
	gSexyAppBase->mMusicInterface->FadeOut(1,true,0.01);
}

void GameOver::Update()
{
	if(mState==GameOver::GO_FADEIN)
	{
		mGOA.y+=mGOA.mSpeed;
		if(mGOA.y>=0)
		{
			mGOA.y = 0;
			mState=GameOver::GO_STATIONARY;
		}
	}

	if(mState==GameOver::GO_STATIONARY)
	{
		mEnableBtns=true;
		
	}

	if(mState==GameOver::GO_FADEOUT)
	{
		mGOA.y+=mGOA.mSpeed;
		if(mGOA.y>=600)
		{
			mActive = false;
			mDone = true;
		}
	}
	

}

void GameOver::Draw(Graphics* g)
{
	Transform t;
	g->PushState();
	g->SetColor(Color::White);
	g->SetFont(FONT_NGAGE2);
	g->TranslateF(mGOA.x,mGOA.y);
	g->DrawImageF(mImg,0,0);
	g->TranslateF(-mGOA.x,-mGOA.y);
	g->PopState();

}


bool GameOver::IsActive()
{
	return mActive;
}
