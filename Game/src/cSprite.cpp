#include "cSprite.h"
#include "SexyAppFramework/Graphics.h"
#include "SexyAppFramework/Image.h"
#include "SexyAppFramework/SexyVector.h"
#include "SexyAppFramework/Rect.h"
#include "SexyAppFramework/XAppBase.h"


using namespace FrameworkX;

Sprite::Sprite(FrameworkX::Image *pImg, FrameworkX::SexyVector2 pPos, FrameworkX::FRect pRect, float pSpeed, FrameworkX::SexyVector2 pVel)
{
	 mImg = pImg;
	 mPos = pPos;
	 mFRect = pRect;
	 mSpeed = pSpeed;
	 mVel = pVel;
	 mSFactor = 0;
	
}

Sprite::~Sprite()
{
}


void Sprite::Draw(FrameworkX::Graphics *g)
{
	if(mImg!=NULL)
	{
		if(gSexyAppBase->Is3DAccelerated())
		   g->DrawImageF(mImg, mPos.x-mImg->GetWidth()/2, mPos.y-mImg->GetHeight()/2);
		else
		   g->DrawImage(mImg,int(mPos.x-mImg->GetWidth()/2), int(mPos.y-mImg->GetHeight()/2));
	}
}


void Sprite::UpdateF(float pFrac)
{

}

void Sprite::ActivateSpecialEffect(FrameworkX::SpecialEffects& pSE,int pMaxT,int pTTime)
{
	pSE.mElapsedTime=0;
	pSE.mFrame=0;
	pSE.mIsActive=true;
	pSE.mMaxTime=pMaxT;
	pSE.mToggleEffect=true;
	pSE.mToggleTime=pTTime;

}

void Sprite::DeactivateSpecialEffect(FrameworkX::SpecialEffects& pSE)
{
	pSE.mElapsedTime=0;
	pSE.mFrame=0;
	pSE.mIsActive=false;
	pSE.mMaxTime=0;
	pSE.mToggleEffect=false;
	pSE.mToggleTime=0;
}

