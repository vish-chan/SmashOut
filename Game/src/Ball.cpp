#include "cGame.h"
#include "Ball.h"
#include "Res.h"
#include "cPhysics.h"
#include "SexyAppFramework/Graphics.h"
#include "SexyAppFramework/Image.h"
#include "SexyAppFramework/SexyVector.h"
#include "SexyAppFramework/SexyMatrix.h"
#include "SexyAppFramework/Rect.h"
#include <math.h>

using namespace FrameworkX;


Physics *mPhysics=new Physics;
SexyVector2 UPPERLEFT_VECTOR(-0.707106F, -0.707106F);
SexyVector2 UPPERRIGHT_VECTOR(0.707106F, -0.707106F);
SexyVector2 LOWERLEFT_VECTOR(-0.707106F, 0.707106F);
SexyVector2 LOWERRIGHT_VECTOR(0.707106F, 0.707106F);

Ball::Ball(Image* pImage, SexyVector2 pPos, FRect pRect, float pSpeed, SexyVector2 pVel,int pMass, bool pMoving, Rect pBoundary,float pMaxV,float pMinV,float pRadius,cGame* pApp)
:Sprite(pImage, pPos, pRect, pSpeed, pVel)
{
   mMass = pMass;
   mMoving = pMoving;
   mRadius = pRadius;
   mWidth = float(pRect.mWidth);
   mHeight = float(pRect.mHeight);
   mApp=pApp;
   mFactor = 1;
   mBoundary = pBoundary;
   mMaxV = pMaxV;
   mMinV = pMinV;
   mBounce[0]=mBounce[1]=mBounce[2]=true;  //0:left, 1:Up, 2:Right, 3:Down
   mBounce[3]=false;
    mElapsedBounceTime=0;
   mFRect.mX=mPos.x-mRadius;
   mFRect.mY=mPos.y-mRadius;
   mFireMode=false;
   mNormalModeRotation=0;
   Sprite::DeactivateSpecialEffect(mBlinkingBall);

}

Ball::~Ball()
{
}

void Ball::Update()
{
   CheckBoundary();
   if(mFireMode && mMoving)
	   mFireModeRotation+=30;
   
   if(!mFireMode && mMoving)
	   mNormalModeRotation+=2*mSpeed;

   if(this->mBounce[3])
   {
	   this->mElapsedBounceTime+=1;
	   if(mElapsedBounceTime>=(100*mMaxBounceTime))
		   this->SetBottomState(false);
   }

   if(mBlinkingBall.mIsActive)
   {
	   if(++mBlinkingBall.mElapsedTime%mBlinkingBall.mToggleTime==0)
		   mBlinkingBall.mToggleEffect=!mBlinkingBall.mToggleEffect;
	   if(mBlinkingBall.mElapsedTime>=mBlinkingBall.mMaxTime)
		   Sprite::DeactivateSpecialEffect(mBlinkingBall);
   }
}

void Ball::UpdateF(float pFrac)
{
   if(mMoving)
   {
      mPos+=mVel*float(mSpeed*pFrac*mFactor);
      mFRect.mX = mPos.x - mRadius;
      mFRect.mY = mPos.y - mRadius;
      mSpeed=mSpeed+((mVel.y)/fabs(mVel.y))*0.01F;
      mSpeed=min(max(mMinV,mSpeed),mMaxV);
      
   }
 
}

void Ball::FollowPaddle(Sprite* pPaddle)
{
	SetX(pPaddle->GetX());
	mFRect.mX=mPos.x-mRadius;
}


void Ball::Draw(Graphics* g)
{
	if(!mBlinkingBall.mIsActive || (mBlinkingBall.mIsActive && mBlinkingBall.mToggleEffect))
	{
	if(!mFireMode)
	{
		Transform t;
		t.RotateDeg(mNormalModeRotation);
		g->DrawImageTransformF(mImg,t,mPos.x,mPos.y);
	}
	else if(mFireMode)
	{
		Transform t;
		t.RotateDeg(float(mFireModeRotation));
		g->DrawImageTransformF(IMAGE_FIRE_BALL,t,mPos.x,mPos.y);
	}
	}

}


void Ball::CheckBoundary()
{
   double mX,mY;
   float mVX,mVY;
   mX = mFRect.mX;
   mY = mFRect.mY;
   mVX = mVel.x;
   mVY = mVel.y;


   if(mImg!=NULL) //make sure image set 
 {
    if(mBounce[0])
    {
     if(mX+mVX<mBoundary.mX) //Check left 
     { 
         mVX=fabs(mVX); //Move right
		 if(mVY>0)
			 mVY+=0.2F;
		 else mVY-=0.2F;
         mX=double(mBoundary.mX-mVX); //Reposition X inside boundry

     } 
    }
    if(mBounce[2])
    {
       if(mX+mVX+mImg->GetWidth()>mBoundary.mX+mBoundary.mWidth) //Check right 
    { 
         mVX=fabs(mVX)*-1; //Move left 
		 if(mVY>0)
			 mVY+=0.2F;
		 else mVY-=0.2F;
         mX=double(mBoundary.mX+mBoundary.mWidth-mImg->GetWidth()-mVX); //Reposition X inside boundry 
    }  
    }
    if(mBounce[1])
    {
    if(mY+mVY<mBoundary.mY) //Check top 
    { 
         mVY=fabs(mVY); //Move down 
		 if(mVX>0)
			 mVX+=0.2F;
		 else mVX-=0.2F;
         mY=double(mBoundary.mY-mVY); //reposition Y inside boundry 
    }  
    }

    if(mBounce[3])
    {
    if(mY+mVY+mImg->GetHeight()>mBoundary.mY+mBoundary.mHeight) //Check bottom 
    { 
         mVY=fabs(mVY)*-1; //Move up 
         mY=double(mBoundary.mY+mBoundary.mHeight-mImg->GetHeight()-mVY); //reposition y inside boundry 
    } 
    }
 }
   SetVelocityVec(mVX,mVY);
   Sprite::SetX(float(mX+mRadius));
   Sprite::SetY(float(mY+mRadius));
   SetRect(FRect(mX,mY,mWidth,mHeight));
    
}


bool Ball::CollisionCheck(Sprite* pSprite)
{
	FRect pRect = pSprite->GetRect();
	float dist=0;
	float x0,y0,x1,y1,w,h;

	x0=mPos.x;
	y0=mPos.y;
	x1=float(pRect.mX);
	y1=float(pRect.mY);
	w=float(pRect.mWidth);
	h=float(pRect.mHeight);

	if(fabs(mPos.x-(pRect.mX+pRect.mWidth/2))>mRadius+pRect.mWidth/2)
		return false;
	if(fabs(mPos.y-(pRect.mY+pRect.mHeight/2))>mRadius+pRect.mHeight/2)
		return false;
	if(mPhysics->pointintersect_circleandrect(this,pRect,0,dist))
	{
		mVel = -mVel + LOWERRIGHT_VECTOR;
	
	}

	else if(mPhysics->pointintersect_circleandrect(this,pRect,1,dist))
	{
		mVel = -mVel + UPPERRIGHT_VECTOR;
	
	}
	else if(mPhysics->pointintersect_circleandrect(this,pRect,2,dist))
	{
		mVel = -mVel + LOWERLEFT_VECTOR;

	}
	else if(mPhysics->pointintersect_circleandrect(this,pRect,3,dist))
	{
		mVel = -mVel + UPPERLEFT_VECTOR;
	
	}

	
	else if((mPhysics->point_linedistance(x0,y0,x1,y1+h,x1+w,y1+h)<=mRadius) && mVel.y<0)
	{
		SetY(float(pRect.mY+pRect.mHeight+mRadius));
		SetVY(1*abs(mVel.y));
		mVel+=pSprite->GetVel();
		mSpeed+=pSprite->GetSpeed();
		
		
	}
	else if((mPhysics->point_linedistance(x0,y0,x1+w,y1,x1+w,y1+h)<=mRadius) && mVel.x<0)
	{
		SetX(float(pRect.mX+pRect.mWidth+mRadius));
		SetVX(1*abs(mVel.x));
		mVel+=pSprite->GetVel();
		mSpeed+=pSprite->GetSpeed();

	}
	else if((mPhysics->point_linedistance(x0,y0,x1,y1,x1+w,y1)<=mRadius) && mVel.y>0)
	{
		SetY(float(pRect.mY-mRadius));
		SetVY(-1*abs(mVel.y));
		mVel+=pSprite->GetVel();
		mSpeed+=pSprite->GetSpeed();
		
	}
	else if((mPhysics->point_linedistance(x0,y0,x1,y1,x1,y1+h)<=mRadius) && mVel.x>0)
	{
		SetX(float(pRect.mY-mRadius));
		SetVX(-1*abs(mVel.x));
		mVel+=pSprite->GetVel();
		mSpeed+=pSprite->GetSpeed();
		
	}
	else 
		return false;
	
	if(pSprite->GetFactor()==1)  //for paddle's RFF
	{
		mMaxV=7;
		mMinV=5;
		
	}
	else
	{
		mMaxV=4;
		mMinV=3;
		
	}
	mSpeed=min(max(mMinV,mSpeed),mMaxV);
	
	SetVelocityVec(mVel.x,mVel.y);

	return true;

}


bool Ball::CollisionCheckBrick(Brick *mBrick)
{

	
	FRect pRect = mBrick->GetRect();
	int ID = mBrick->GetId();
	float x0,y0,x1,y1,w,h;

	x0=mPos.x;
	y0=mPos.y;
	x1=float(pRect.mX);
	y1=float(pRect.mY);
	w=float(pRect.mWidth);
	h=float(pRect.mHeight);
	

	if(fabs(mPos.x-(pRect.mX+pRect.mWidth/2))>mRadius+2+pRect.mWidth/2)
		return false;
	if(fabs(mPos.y-(pRect.mY+pRect.mHeight/2))>mRadius+2+pRect.mHeight/2)
		return false;

	float dist=0,diff;


	if(mBrick->GetBreakability())
	{
	if(mPhysics->pointintersect_circleandrect(this,pRect,0,dist) && !mFireMode)
	{
	   if(dist<pow(mRadius,2))
	   {
	      diff = mRadius+1-sqrt(dist);
	      mPos+=(mVel*-1.0)*diff;
	      mFRect.mX = mPos.x - mRadius;
	      mFRect.mY = mPos.y - mRadius;
	   }
	      mVel = -mVel + LOWERRIGHT_VECTOR;
	
	}
	else if(mPhysics->pointintersect_circleandrect(this,pRect,1,dist) && !mFireMode)
	{
	   if(dist<pow(mRadius,2))
	   {
	      diff = mRadius+1-sqrt(dist);
	      mPos+=(mVel*-1.0)*diff;
	      mFRect.mX = mPos.x - mRadius;
	      mFRect.mY = mPos.y - mRadius;
	   }
	   mVel = -mVel + UPPERRIGHT_VECTOR;
	
	}
	else if(mPhysics->pointintersect_circleandrect(this,pRect,2,dist) && !mFireMode)
	{
	   if(dist<pow(mRadius,2))
	   {
	      diff = mRadius+1-sqrt(dist);
	      mPos+=(mVel*-1.0)*diff;
	      mFRect.mX = mPos.x - mRadius;
	      mFRect.mY = mPos.y - mRadius;
	   }
	   mVel = -mVel + LOWERLEFT_VECTOR;

	}
	else if(mPhysics->pointintersect_circleandrect(this,pRect,3,dist) && !mFireMode)
	{
	   if(dist<pow(mRadius,2))
	   {
	      diff = mRadius+1-sqrt(dist);
	      mPos+=(mVel*-1.0)*diff;
	      mFRect.mX = mPos.x - mRadius;
	      mFRect.mY = mPos.y - mRadius;
	   }
	   mVel = -mVel + UPPERLEFT_VECTOR;
	
	}

	if((mPhysics->point_linedistance(x0,y0,x1,y1+h,x1+w,y1+h)<=mRadius) && mVel.y<0 && !mFireMode)
	{
		SetY(float(pRect.mY+pRect.mHeight+mRadius));
		SetVY(1*abs(mVel.y));
		if(mVel.x>0)
		   mVel.x+=0.2F;
		else mVel.x-=0.2F;
		
	}
	else if((mPhysics->point_linedistance(x0,y0,x1+w,y1,x1+w,y1+h)<=mRadius) && mVel.x<0 && !mFireMode)
	{
		SetX(float(pRect.mX+pRect.mWidth+mRadius));
		SetVX(1*abs(mVel.x));
		if(mVel.y>0)
		   mVel.y+=0.2F;
		else mVel.y-=0.2F;
		
	}
	else if((mPhysics->point_linedistance(x0,y0,x1,y1,x1+w,y1)<=mRadius) && mVel.y>0 && !mFireMode)
	{
		SetY(float(pRect.mY-mRadius));
		SetVY(-1*abs(mVel.y));
		if(mVel.x>0)
		   mVel.x+=0.2F;
		else mVel.x-=0.2F;

	}
	else if((mPhysics->point_linedistance(x0,y0,x1,y1,x1,y1+h)<=mRadius) && mVel.x>0 && !mFireMode)
	{
		SetX(float(pRect.mY-mRadius));
		SetVX(-1*abs(mVel.x));
		if(mVel.y>0)
		   mVel.y+=0.2F;
		else mVel.y-=0.2F;
		
	}
	else 
	   return true;
	}


	else if(!mBrick->GetBreakability())
	{
	if(mPhysics->pointintersect_circleandrect(this,pRect,0,dist))
	{
	   if(dist<pow(mRadius,2))
	   {
	      diff = mRadius+1-sqrt(dist);
	      mPos+=(mVel*-1.0)*diff;
	      mFRect.mX = mPos.x - mRadius;
	      mFRect.mY = mPos.y - mRadius;
	    
	   }
		mVel = -mVel + LOWERRIGHT_VECTOR;
	
	}
	else if(mPhysics->pointintersect_circleandrect(this,pRect,1,dist) )
	{
	   if(dist<pow(mRadius,2))
	   {
	      diff = mRadius+1-sqrt(dist);
	      mPos+=(mVel*-1.0)*diff;
	      mFRect.mX = mPos.x - mRadius;
	      mFRect.mY = mPos.y - mRadius;
	  
	   }
		mVel = -mVel + UPPERRIGHT_VECTOR;
	
	}
	else if(mPhysics->pointintersect_circleandrect(this,pRect,2,dist))
	{
	   if(dist<pow(mRadius,2))
	   {
	      diff = mRadius+1-sqrt(dist);
	      mPos+=(mVel*-1.0)*diff;
	      mFRect.mX = mPos.x - mRadius;
	      mFRect.mY = mPos.y - mRadius;
	     
	   }
		mVel = -mVel + LOWERLEFT_VECTOR;

	}
	else if(mPhysics->pointintersect_circleandrect(this,pRect,3,dist))
	{
	   if(dist<pow(mRadius,2))
	   {
	      diff = mRadius+1-sqrt(dist);
	      mPos+=(mVel*-1.0)*diff;
	      mFRect.mX = mPos.x - mRadius;
	      mFRect.mY = mPos.y - mRadius;
	      
	   }
		mVel = -mVel + UPPERLEFT_VECTOR;
	
	}

	if((mPhysics->point_linedistance(x0,y0,x1,y1+h,x1+w,y1+h)<=mRadius) && mVel.y<0)
	{
		SetY(float(pRect.mY+pRect.mHeight+mRadius));
		SetVY(1*fabs(mVel.y));
		if(mVel.x>0)
		   mVel.x+=0.2F;
		else mVel.x-=0.2F;
		
		
	}
	else if((mPhysics->point_linedistance(x0,y0,x1+w,y1,x1+w,y1+h)<=mRadius) && mVel.x<0)
	{
		SetX(float(pRect.mX+pRect.mWidth+mRadius));
		SetVX(1*fabs(mVel.x));
		if(mVel.y>0)
		   mVel.y+=0.2F;
		else mVel.y-=0.2F;
		
	}
	else if((mPhysics->point_linedistance(x0,y0,x1,y1,x1+w,y1)<=mRadius) && mVel.y>0)
	{
		SetY(float(pRect.mY-mRadius));
		SetVY(-1*fabs(mVel.y));
		if(mVel.x>0)
		   mVel.x+=0.2F;
		else mVel.x-=0.2F;
	}
	else if((mPhysics->point_linedistance(x0,y0,x1,y1,x1,y1+h)<=mRadius) && mVel.x>0 )
	{
		SetX(float(pRect.mY-mRadius));
		SetVX(-1*fabs(mVel.x));
		if(mVel.y>0)
		   mVel.y+=0.2F;
		else mVel.y-=0.2F;
		
	}
	else 
		return true;
	}
	
	SetVelocityVec(mVel.x,mVel.y);
	return true;
}

	


void Ball::ResetPos(float x, float y)
{
   mPos.x = x;
   mPos.y = y;
   mFRect.mX = x - mRadius*1.0;
   mFRect.mY = y - mRadius*1.0;
   mSpeed = 0;
   mVel.x = 0;
   mVel.y = 0;
   mMoving = false;
   SetFireMode(false);
   SetBottomState(false);
   Sprite::DeactivateSpecialEffect(mBlinkingBall);
}

void Ball::ResetForNextLevel(float x,float y)
{
	ResetPos(x,y);
}




void Ball::SetVelocityVec(float pVX, float pVY)
{
	mVel.x = pVX;
	mVel.y = pVY;
	mVel = mVel.Normalize();
}


