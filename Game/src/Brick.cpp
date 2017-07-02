#include "Brick.h"
#include "Res.h"
#include "SexyAppFramework/XAppBase.h"



using namespace FrameworkX;




Brick::Brick(int pId,Image* pImg, SexyVector2 pPos, FRect pRect, float pSpeed, SexyVector2 pVel, bool pBreakable, int pMaxHits,Color pColor, int ir, int ic,float pBreakPoints,bool pMC, bool pCT)
:Sprite(pImg,pPos,pRect,pSpeed,pVel)
{
	mBreakable = pBreakable;
	mMaxHits = pMaxHits;
	mColor = pColor;
	mWidth = float(pRect.mWidth);
	mHeight = float(pRect.mHeight);
	mHits = 0;
	mRow = ir;
	mCol = ic;
	mId = pId;  //1 : silver 2: blue 3: red 4:black
	mBreakPoints = pBreakPoints;
	mLaserHit = false;
	mMissileLaunched = false;
	mMissileCapable = pMC;
	mCanTransform = pCT;
	mChangeFrame = 0;
	mChangeInterval = 200;

	mShake.mShouldShake=false;
	mShake.mShakeMag=0;
	mShake.mShakeDirTime=10;
	mShake.mMaxShakeTime=100;
	mShake.mElapsedShakeTime=0;
}

Brick::~Brick()
{

}
void Brick::Update()
{
   if(mId==6)
   {
      if(++mChangeFrame%mChangeInterval==0)
      {
		  if(mImg==IMAGE_BRICK_T_UNLOCKED)
		  {
	       mImg = IMAGE_BRICK_T_LOCKED;
	       mBreakable = false;
	       mChangeFrame=0;
		   mChangeInterval=400;
		  }
		  else if(mImg == IMAGE_BRICK_T_LOCKED)
		  {
	       mBreakable = true;
	       mImg = IMAGE_BRICK_T_UNLOCKED;
	       mChangeFrame=0;
		   mChangeInterval=200;
		  }
	  }
   }
   mFRect.mY=mPos.y+mShake.mShakeMag-mImg->GetHeight()/2;
   if(mShake.mShouldShake)
	   UpdateShaking();
}

void Brick::Draw(Graphics* g)
{
	if(!mShake.mShouldShake)
		Sprite::Draw(g);
	else
		g->DrawImageF(mImg,mPos.x-mImg->GetWidth()/2,mPos.y+mShake.mShakeMag-mImg->GetHeight()/2);

}

bool Brick::DestroyBrick()
{
	return (mHits>=mMaxHits);
}

void Brick::SetBonus(int pBonus)
{
	switch(pBonus)
	{
	case 0: mBonus=BONUS_NONE;
		break;
	case 1: mBonus=BONUS_RED_GEM;
		break;
	case 2: mBonus=BONUS_BLUE_GEM;
		break;
	case 3: mBonus=BONUS_GREEN_GEM;
		break;
	case 4: mBonus=BONUS_MISSILE;
		break;
	case 5: mBonus=BONUS_FLAME;
		break;
	case 6: mBonus=BONUS_SIZE;
		break;
	case 7: mBonus=BONUS_LASER;
		break;
	case 8: mBonus=BONUS_LIFE;
		break;
	case 9: mBonus=BONUS_BLACK_SCREEN;
		break;
	case 49: mBonus=BONUS_BLINKING_BALL;
		break;
	case 50: mBonus=BONUS_REVERSE_MOTION;
		break;
	default: mBonus=BONUS_NONE;
		break;
	}
}

void Brick::UpdateShaking()
{
	if(++mShake.mElapsedShakeTime%mShake.mShakeDirTime==0)
		mShake.mShakeMag=-1*mShake.mShakeMag;
	if(mShake.mElapsedShakeTime%mShake.mMaxShakeTime==0)
		ResetShake();
}


void Brick::ResetShake()
{
	mShake.mShouldShake=false;
	mShake.mShakeMag=0;
	mShake.mShakeDirTime=3;
	mShake.mMaxShakeTime=50;
	mShake.mElapsedShakeTime=0;
}

void Brick::SetShake()
{
	mShake.mShouldShake=true;
	mShake.mShakeMag=0.4F;
}

		
	
		

