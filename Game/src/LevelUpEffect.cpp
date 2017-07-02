#include "LevelUpEffect.h"
#include "Res.h"
#include "SexyAppFramework/Font.h"
#include "SexyAppFramework/SexyMatrix.h"
#include "SexyAppFramework/XAppBase.h"
#include "SexyAppFramework/MusicInterface.h"

using namespace FrameworkX;


const float xpos = 315;
const float xpos2 = 450;

LevelUp::LevelUp(FrameworkX::Image * pImg, FrameworkX::ScoreBoard *pSB)
{
	mImg= pImg;
	mLUSB = pSB;
	mStartNextLevel=false;
	mActive=false;
	
	LevelUp::Init();
}

LevelUp::~LevelUp()
{

}

void LevelUp::Init()
{
	mState = LevelUp::LU_FADEIN;
	mLUA.mFrame=0;
	mLUA.mSpeed=10;
	mLUA.x=0-mImg->GetWidth()*1.0F;
	mLUA.y=0;
	mDone = false;
	mIsHighScore = false;
	mPlayHSSfx = false;
	mEnableContinueButton = false;
	for(int i=0;i<6;i++)
		mVisible[i]=false;

}

void LevelUp::Activate()
{
	LevelUp::Init();
	gSexyAppBase->PlaySample(SOUND_PLAYMOUSEDOWN);
	gSexyAppBase->mMusicInterface->FadeOut(1,true,0.01);
	mActive = true;
}

void LevelUp::Update()
{
	if(mState==LevelUp::LU_FADEIN)
	{
		mLUA.x+=mLUA.mSpeed;
		if(mLUA.x>=0)
		{
			mLUA.x = 0;
			mState=LevelUp::LU_STATIONARY;
		}
	}

	if(mState==LevelUp::LU_STATIONARY)
	{
		++(mLUA.mFrame);
		float mF=mLUA.mFrame;

		if(mF==1)
		{
			mVisible[0]=true;
			gSexyAppBase->PlaySample(SOUND_LEVELUPSFX);
		}
		if(mF==50)
		{
			mVisible[1] = true;
			gSexyAppBase->PlaySample(SOUND_LEVELUPSFX);
		}
		if(mF==100)
		{
			mVisible[2] = true;
			gSexyAppBase->PlaySample(SOUND_LEVELUPSFX);
		}
		if(mF==150)
		{
			mVisible[3] = true;
			gSexyAppBase->PlaySample(SOUND_LEVELUPSFX);
		}
		if(mF==200)
			{
			mVisible[4] = true;
			gSexyAppBase->PlaySample(SOUND_LEVELUPSFX);
		}
		if(mF==250)
		{
			mVisible[5] = true;
			gSexyAppBase->PlaySample(SOUND_LEVELUPSFX);
			mEnableContinueButton=true;
		}
	}

	if(mState==LevelUp::LU_FADEOUT)
	{
		mLUA.x+=mLUA.mSpeed;
		if(mLUA.x>=800)
		{
			mActive = false;
			mDone = true;
		}
	}
	

}

void LevelUp::Draw(Graphics* g)
{
	int w=0;
	Transform t;
	t.RotateDeg(-mLUA.mFrame);
	g->PushState();
	g->SetColor(Color::White);
	g->SetFont(FONT_NGAGE2);
	g->TranslateF(mLUA.x,mLUA.y);
	g->DrawImageF(mImg,0,0);
	g->DrawImageTransform(IMAGE_ROTATING_EFFECTS,t,260,133);

	if(mVisible[0])
	{
		g->DrawImageF(IMAGE_BONUS_GREENGEM,xpos,223.0);
		g->DrawString(StrFormat(_S("%d"),mLUSB->GetGreenGems()),int(xpos2),240);
	}
	if(mVisible[1])
	{
		g->DrawImageF(IMAGE_BONUS_REDGEM,xpos,263);
		g->DrawString(StrFormat(_S("%d"),mLUSB->GetRedGems()),int(xpos2),280);
	}
	if(mVisible[2])
	{
		g->DrawImageF(IMAGE_BONUS_BLUEGEM,xpos,303);
		g->DrawString(StrFormat(_S("%d"),mLUSB->GetBlueGems()),int(xpos2),320);
	}
	if(mVisible[3])
	{
		g->DrawImageF(IMAGE_BONUS_LASER,xpos,343);
		g->DrawString(StrFormat(_S("%d"),mLUSB->GetLasers()),int(xpos2),365);
	}
	if(mVisible[4])
	{
		g->DrawImageF(IMAGE_BONUS_MISSILE,xpos+2,394);
		g->DrawString(StrFormat(_S("%d"),mLUSB->GetMissiles()),int(xpos2),412);
	}
	if(mVisible[5])
	{
		g->SetFont(FONT_DEFAULT1);
		w = FONT_DEFAULT1->StringWidth((StrFormat(_S("%d"),mLUSB->GetPoints())));
		g->SetDrawMode(Graphics::DRAWMODE_ADDITIVE);
		g->DrawString(StrFormat(_S("%d"),mLUSB->GetPoints()),400-w/2,475);
		g->SetDrawMode(Graphics::DRAWMODE_NORMAL);
		if(mIsHighScore)
		{
			if(mPlayHSSfx)
			{
				gSexyAppBase->PlaySample(SOUND_BOARDMOUSEDOWN);
				mPlayHSSfx = false;
			}
			g->DrawImageF(IMAGE_HIGH_SCORE,420,395);

		}

	}
	

	g->TranslateF(-mLUA.x,-mLUA.y);
	g->PopState();

	
}


bool LevelUp::IsActive()
{
	return mActive;
}

	

