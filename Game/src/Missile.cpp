#include "Missile.h"
#include <stdlib.h>

using namespace FrameworkX;

Missile::Missile(int pId,Image* pImg, SexyVector2 pPos)
{
	mId = pId;
	mImg = pImg;
	mPos = pPos;
	mRemove = false;
	mRect = FRect(mPos.x-mImg->GetWidth()/2,mPos.y-mImg->GetHeight()/2,mImg->GetWidth(),mImg->GetHeight());
	mFrame = 0;
	mU=0;
	mR = 0;
	mIncreasing = true;
	if(mId==Missile::M_PADDLE)
		mAccel=0.1;
	else if(mId==Missile::M_BRICK)
	{
		mAccel = (0.0005*Rand())/double(RAND_MAX);
		if( mAccel>0.005)
			mAccel = 0.005;
		else if(mAccel==0)
			mAccel = 0.002;
	}


    
}

Missile::~Missile()
{
}

void Missile::Draw(Graphics* g)
{
   if(mId==Missile::M_PADDLE)
	g->DrawImageF(mImg,float(mRect.mX),float(mRect.mY));
   if(mId==Missile::M_BRICK)
   {
      g->DrawImageRotatedF(mImg,float(mRect.mX),float(mRect.mY),mU);
      g->PushState();
      g->SetColorizeImages(true);
      g->SetDrawMode(Graphics::DRAWMODE_ADDITIVE);
      g->SetColor(Color(mR,mR,mR));
      g->DrawImageRotatedF(mImg,float(mRect.mX),float(mRect.mY),mU);
      g->PopState();
   }
	

}

void Missile::Update()
{   
	if(mId==Missile::M_PADDLE)
	{
	mFrame+=0.5;
	mU=mU+mAccel*mFrame;
	mPos.y-=float(mU);
	mRect.mY=mPos.y-mImg->GetHeight()/2;
	if(mRect.mY+mRect.mHeight<=0)
		mRemove=true;
	}

	else if(mId==Missile::M_BRICK)
	{
	   mU=fmod(++mU,360.0);

		mFrame+=float(mAccel);
		mPos.y+=mFrame;
		mRect.mY=mPos.y-mImg->GetHeight()/2;
		if(mRect.mY>=600)
			mRemove = true;
		if(mIncreasing)
		{   mR+=5;
			if(mR>249)
				mIncreasing=false;
		}
		if(!mIncreasing)
		{
			mR-=5;
			if(mR<6)
				mIncreasing=true;
		}
	}
	
}

