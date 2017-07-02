#include "Bonus.h"
#include "SexyAppFramework/SexyMatrix.h"
#include<stdlib.h>
#include<time.h>


using namespace FrameworkX;

#define PI 3.1415926535897932384626433832795028841971f

const int UPPER_LIMIT_VEL=5;
const int LOWER_LIMIT_VEL=1;
const int UPPER_LIMIT_THETA_LEFT = 60;
const int LOWER_LIMIT_THETA_LEFT = 30;
const int UPPER_LIMIT_THETA_RIGHT = 150;
const int LOWER_LIMIT_THETA_RIGHT = 120;
const int MIDDLE_LINE = 650/2;

Bonus::Bonus(BonusType pId,Image* pImg, SexyVector2 pPos,int pRows, int pCols)
{
	mId = pId;
	mImg = pImg;
	mPos = pPos;
	mRows = pRows;
	mCols = pCols;
	mRow = 0;
	mCol = 0;
	mRemove = false;
	mFrame=0;
	mDRect = FRect(mPos.x-(mImg->GetWidth()/mCols)/2,mPos.y-(mImg->GetHeight()/mRows)/2,mImg->GetWidth()/mCols,mImg->GetHeight()/mRows);
	mLives=0;
	mLaserTime=0;
	mMissiles = 0;
	mPoints = 0;
	mRot = 0;
	mScalingFactor = 1;
	mFireTime = 0;

	
	if(mId==BONUS_LIFE)
		mLives=1;
	else if(mId==BONUS_LASER)
		mLaserTime = 5;
	else if(mId==BONUS_MISSILE)
		mMissiles = 6;
	else if(mId==BONUS_RED_GEM)
		mPoints = 100;
	else if(mId==BONUS_GREEN_GEM)
		mPoints = 80;
	else if(mId==BONUS_BLUE_GEM)
		mPoints = 50;
	else if(mId==BONUS_FLAME)
		mFireTime = 5;
	else if(mId==BONUS_SIZE)
		mScalingFactor = 5;
      
	mProjectile.mVel=float(Rand()%(UPPER_LIMIT_VEL-LOWER_LIMIT_VEL)+LOWER_LIMIT_VEL);
	srand((unsigned)time(NULL));
	if(mPos.x<MIDDLE_LINE)
		mProjectile.mTheta=float(Rand()%(UPPER_LIMIT_THETA_LEFT-LOWER_LIMIT_THETA_LEFT)+LOWER_LIMIT_THETA_LEFT);
	else if(mPos.x>MIDDLE_LINE)
		mProjectile.mTheta=float(Rand()%(UPPER_LIMIT_THETA_RIGHT-LOWER_LIMIT_THETA_RIGHT)+LOWER_LIMIT_THETA_RIGHT);
	mProjectile.mTime=0;
	mProjectile.mIHeight= mPos.y;
	mProjectile.mIXPos = mPos.x;
}

Bonus::~Bonus()
{

}

void Bonus::Draw(Graphics* g)
{
	//g->DrawImageF(mImg,mDRect.mX,mDRect.mY);

	Transform t;
	t.RotateDeg(mRot);
	g->DrawImageTransformF(mImg,t,mPos.x,mPos.y);
	
}

void Bonus::Update()
{
	GetLocation();

}

void Bonus::GetLocation()
{
	const float SCALOR = 100;
	const float g = 10.0;
	float thetaradian=mProjectile.mTheta*PI/180;

	

	mPos.x =mProjectile.mIXPos+(((mProjectile.mVel*(cos(thetaradian))))*mProjectile.mTime);
	mPos.y=mProjectile.mIHeight+(((mProjectile.mVel*sin(thetaradian)*mProjectile.mTime)+0.5F*(g*mProjectile.mTime*mProjectile.mTime)))/SCALOR;


	mProjectile.mTime+=1;

	mDRect.mX = mPos.x-(mImg->GetWidth()/mCols)/2;
	mDRect.mY = mPos.y-(mImg->GetHeight()/mRows)/2;

	mRot+=5;

	if(mPos.y>600)
		mRemove=true;
	

}
