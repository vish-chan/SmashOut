#include "cGame.h"
#include "Paddle.h"
#include "Board.h"
#include "Res.h"
#include "Missile.h"
#include "SexyAppFramework/Graphics.h"
#include "SexyAppFramework/Image.h"
#include "SexyAppFramework/SexyVector.h"
#include "SexyAppFramework/SexyMatrix.h"
#include "SexyAppFramework/Rect.h"
#include "SexyAppFramework/SoundInstance.h"
#include <math.h>

using namespace FrameworkX;



Paddle::Paddle(Board* pBoard,Image* pImage, SexyVector2 pPos, FRect pRect, float pSpeed, SexyVector2 pVel,int pMass, bool pMoving, Rect pBoundary,float pMaxV,cGame* pApp,bool pSolid,int pOldMX,int pOldMY)
:Sprite(pImage, pPos, pRect, pSpeed, pVel)
{
	mPBoard = pBoard;
   mMass = pMass;
   mMoving = pMoving;
   mWidth = float(pRect.mWidth);
   mHeight = float(pRect.mHeight);
   mApp=pApp;
   mBoundary = pBoundary;
   mMaxV = pMaxV;
   mSolid = pSolid;
   mOldMX=pOldMX;
   mOldMY=pOldMY;
   mMouseX=mOldMX; 
   mMouseY=mOldMY;
   mLaser.mCUImg = IMAGE_LASER_CIRCLEUNDER;
   mLaser.mCOImg = IMAGE_LASER_CIRCLEOVER;
   mLaser.mLImg = IMAGE_LASER_MAIN;
   mLaser.mLaserMode = false;
   mLaser.mNumC=0;
   mMissileFlag = false;
   mNumLasers = 0;
   mNumMissiles = 0;
   mLives = 3;
   mScalingFactor =1 ;
   mScaleTime = 0;
   mScaled = false;
   mMissileHits = 0;
   mReduceLives=false;
   mMM=new MissileManager(IMAGE_MISSILE);
   Sprite::DeactivateSpecialEffect(mReverseMotion);

}

Paddle::~Paddle()
{
	if(mMM!=NULL)
		delete mMM;
}

void Paddle::UpdatePaddle(int x,int y)
{
	mMouseX=x;
	mMouseY=y;
	
	float PaddleSpeed=float(abs(mMouseX-mOldMX));
	int PaddleDir=0; 

    if(abs(mMouseX-mOldMX)>0) 
        PaddleDir=(mMouseX-mOldMX)/abs(mMouseX-mOldMX); 
	
	SetSpeed(PaddleSpeed);
	SetVelocity(float(PaddleDir),0);

	if(!mReverseMotion.mIsActive)
		mPos.x+=(mMouseX-mOldMX)*2.0F;
	else if(mReverseMotion.mIsActive)
		mPos.x+=-1.0F*(mMouseX-mOldMX);
	
	if(mPos.x<mImg->GetWidth()/2)
		mPos.x = float(mImg->GetWidth()/2);
	else if(mPos.x>mBoundary.mX+mBoundary.mWidth-mImg->GetWidth()/2)
		mPos.x = float(mBoundary.mX+mBoundary.mWidth-mImg->GetWidth()/2);
	
	mFRect.mX = mPos.x - mFRect.mWidth/2;
	mFRect.mY = mPos.y - mFRect.mHeight/2;
	
	mOldMX=mMouseX;
	mOldMY=mMouseY;
	

	if(mLaser.mLaserMode)
		UpdateLaser();

	if(mMM->GetMissileCnt())
		mMM->Update();
	
	if((GetNumMissiles())<=0)
		SetMissileMode(false);

	if(mReverseMotion.mIsActive)
	{
		if(++mReverseMotion.mElapsedTime>=mReverseMotion.mMaxTime)
			Sprite::DeactivateSpecialEffect(mReverseMotion);
	}


}

void Paddle::UpdateLaser()
{
	if(mLaser.mLSXIncreasing)
	{
		mLaser.mLSX+=0.01F;
		if(mLaser.mLSX>1)
		{
			mLaser.mLSX=1;
			mLaser.mLSXIncreasing = false;
		}
	}
	else
	{
		mLaser.mLSX-=0.01F;
		if(mLaser.mLSX<0.5)
		{
			mLaser.mLSX=0.5;
			mLaser.mLSXIncreasing=true;
		}
	}
	
	mLaser.mCpos.x=mPos.x;
	mLaser.mCpos.y-=2;
	if(mLaser.mCpos.y==mBoundary.mY-100)
		mLaser.mCpos.y = float((mBoundary.mHeight-mImg->GetHeight()));

	
	mLaser.mFrame+=1;
	if(mLaser.mFrame%100==0)
		mLaser.mLaserOnTime+=1;
	if(mLaser.mLaserOnTime>=mLaser.mLaserMaxTime)
		RemoveLaser();
}



void Paddle::UpdateF(float pFrac)
{
   
 
}


void Paddle::Draw(Graphics* g)
{
   Sprite::Draw(g);
   if(mSFactor)
	   g->DrawImageF(IMAGE_RFF,mPos.x-mImg->GetWidth()/2,mPos.y-mImg->GetHeight()/2);


   if(mLaser.mLaserMode)
	   DrawLaser(g);
   
   if(mMM->GetMissileCnt())
	   mMM->Draw(g);
   
   if(mNumLasers>0 || mMM->GetMM() || mLaser.mLaserMode)
	   g->DrawImageF(IMAGE_LASER_PAD,mPos.x-IMAGE_LASER_PAD->GetWidth()/2,float(mBoundary.mY));
   
}

void Paddle::DrawLaser(Graphics* g)
{  
	int j=1 ;

	for(int i=0;i<mLaser.mNumC;i++)
	{
		g->DrawImageF(mLaser.mCUImg,mLaser.mCpos.x-mLaser.mCUImg->GetWidth()/2,mLaser.mCpos.y+mLaser.mCUImg->GetHeight()*j);
		j=j*-1;
	}

	Transform t;
	t.Scale(mLaser.mLSX,1);
	g->DrawImageTransformF(mLaser.mLImg,t,mPos.x,float((mBoundary.mHeight-mImg->mHeight))/2);
	
	j=1;
	
	for(int i=0;i<mLaser.mNumC;i++)
	{
		g->DrawImageF(mLaser.mCOImg,mLaser.mCpos.x-mLaser.mCOImg->GetWidth()/2,mLaser.mCpos.y+mLaser.mCOImg->GetHeight()*j);
		j=j*-1;
	}
	
}


void Paddle::AddMissile()
{
	mMM->AddMissile(Missile::M_PADDLE,SexyVector2(mPos.x-IMAGE_LASER_PAD->GetWidth()/2+25,mPos.y-mImg->GetHeight()/2-50));
	mMM->AddMissile(Missile::M_PADDLE,SexyVector2(mPos.x+IMAGE_LASER_PAD->GetWidth()/2-25,mPos.y-mImg->GetHeight()/2-50));
}



void Paddle::ResetPos(float x, float y)
{
   mPos.x = x;
   mPos.y = y;
   mFRect.mX = x - mWidth/2;
   mFRect.mY = y - mHeight/2;
   mSpeed = 0;
   mVel.x = 0;
   mVel.y = 0;
   mMoving = false;
   RemoveLaser();
   
}

void Paddle::ResetForNextLevel(int pRF,float x,float y)
{
	ResetPos(x,y);
	Sprite::DeactivateSpecialEffect(mReverseMotion);
	mMissileHits = 0;
	mReduceLives = false;

	if(pRF==1)
		return;
	else if(pRF==2 || pRF==3)
	{
		mLives = 3;
		this->mNumLasers = 0;
		this->mNumMissiles = 0;
	}
	
}


void Paddle::InitialiseLaser()
{
	mLaser.mLPos=mPos;
	mLaser.mLSX=0.5;
	mLaser.mFrame=0;
	mLaser.mCpos.x=mPos.x;
	mLaser.mCpos.y=float((mBoundary.mHeight-mImg->GetHeight()))/2;
	mLaser.mLSXIncreasing = true;
	mLaser.mLaserMode=true;
	mLaser.mNumC=5;
	mLaser.mLaserOnTime=0;

}


void Paddle::RemoveLaser()
{
	mLaser.mLaserMode=false;
	if(mPBoard->mLaserSfx->IsPlaying())
		mPBoard->mLaserSfx->Stop();
}

void Paddle::SetMissileMode(bool pMM)
{
	mMM->SetMM(pMM);
}

bool Paddle::GetMissileMode()
{
	return mMM->GetMM();
}

void Paddle::ActivateReverseMotion()
{
	Sprite::ActivateSpecialEffect(mReverseMotion,500,0);
	  
}