#ifndef __BALL_H__
#define __BALL_H__


#include "cGame.h"
#include "Paddle.h"
#include "cSprite.h"
#include "Brick.h"
#include "SexyAppFramework/Graphics.h"
#include "SexyAppFramework/Image.h"
#include "SexyAppFramework/SexyVector.h"
#include "SexyAppFramework/Rect.h"


namespace FrameworkX
{
	class Paddle;
	class Graphics;
	
	
   class Ball:public Sprite 
   {
   private:
      float mFactor;
      int mMass;
      bool mMoving;
      Rect mBoundary;
      float mMaxV;
      float mMinV;
      float mRadius;
      cGame* mApp;
      float mWidth;
      float mHeight;
	  bool mFireMode;
	  int mFireModeMaxTime;
	  int mFireModeElapsedTime;
	  int mFireModeRotation;
      bool mBounce[4];
	  int mMaxBounceTime;
	  int mElapsedBounceTime;
	  float mNormalModeRotation;
	  SpecialEffects mBlinkingBall;


   public:
      Ball(Image*, SexyVector2, FRect, float, SexyVector2,int, bool, Rect,float,float,float,cGame*);
      ~Ball();
      void CheckBoundary();
      bool CollisionCheck(Sprite*);
	  bool CollisionCheckBrick(Brick*);
      void ResetPos(float, float);
	  void FollowPaddle(Sprite*);
      
      void Update();
      virtual void UpdateF(float);

      virtual void Draw(Graphics*);
      
      void SetFactor(float pFactor)
      {
	 mFactor = pFactor;
      }

      int GetMass()
      {
	 return mMass;
      }

	  float GetRadius()
	  {
		  return mRadius;
	  }

      bool GetMoving()
      {
		  return mMoving;
      }

      void SetMoving(bool pMoving)
      {
		  mMoving = pMoving;
      }


      Rect GetBoundary()
      {
	     return mBoundary;
      }

      void SetBoundary(Rect pBoundary)
      {
		  mBoundary = pBoundary;
      }
	  void SetMaxV(float v)
	  {
		  mMaxV = v;
	  }
	  void SetMinV(float v)
	  {
		  mMinV = v;
	  }
	  float GetMaxV()
	  {
		  return mMaxV;
	  }

	  bool GetFireMode()
	  {
		  return mFireMode;
	  }

	  void SetFireMode(bool FM)
	  {
		  mFireMode =  FM;
		  mFireModeElapsedTime = 0;
		  mFireModeRotation = 0;

	  }
	  void SetFireModeMaxTime(int pFMMT)
	  {
		  mFireModeMaxTime = pFMMT;
	  }

	  void SetVelocityVec(float, float);


	  bool IsBallBelowBottom()
	  {
		  return mPos.y>(mBoundary.mY+mBoundary.mHeight+mHeight);
	  }

	  void SetBottomState(bool pBB)
	  {
		  mBounce[3]= pBB;
		  mElapsedBounceTime=0;;
	  }

	  bool GetBottomState()
	  {
		  return mBounce[3];
	  }

	  void SetBottomBlockTime(int pT)
	  {
		  mMaxBounceTime = pT;
	  }

	  void SetBlinkingBall(bool pBB)
	  {
		  if(pBB)
			  Sprite::ActivateSpecialEffect(mBlinkingBall,1000,50);
		  else
			  Sprite::DeactivateSpecialEffect(mBlinkingBall);
	  }

	  bool GetBlinkingBallState()
	  {
		  return mBlinkingBall.mIsActive;
	  }
	  void ResetForNextLevel(float,float);

   };
}

#endif

     


