#ifndef __PADDLE_H__
#define __PADDLE_H__


#include "cGame.h"
#include "cSprite.h"
#include "SexyAppFramework/Graphics.h"
#include "SexyAppFramework/Image.h"
#include "SexyAppFramework/SexyVector.h"
#include "SexyAppFramework/Rect.h"
#include <vector>
#include "MissileManager.h"


namespace FrameworkX
{
	class Board;
	struct Laser
	{
		Image* mLImg;
		Image* mCUImg;
		Image* mCOImg;
		int mFrame;
		float mLSX;
		bool mLSXIncreasing;
		SexyVector2 mLPos;
		SexyVector2 mCpos;
		bool mLaserMode;
		float mLaserOnTime;
		float mLaserMaxTime;
		int mNumC;
		int mLives;
	};
	
	class Paddle:public Sprite 
	{
	private:
		int mMass;
		bool mMoving;
        Rect mBoundary;
        float mMaxV;
	    cGame* mApp;
		Board* mPBoard;
        float mWidth;
        float mHeight;
        bool mSolid;
		int mMouseX,mMouseY,mOldMX,mOldMY;
		Laser mLaser;
		int mNumLasers;
		int mNumMissiles;
		MissileManager* mMM;
		bool mMissileFlag;
		float mScalingFactor;
		float mScaleTime;
		bool mScaled;
		int mLives;
		int mMissileHits;
		bool mReduceLives;
		SpecialEffects mReverseMotion;

		
		

   public:
      Paddle(Board*, Image*, SexyVector2, FRect, float, SexyVector2,int, bool, Rect,float,cGame*,bool,int,int);
      ~Paddle();
      
      void ResetPos(float, float);
	  void ResetForNextLevel(int,float,float);
      
      void UpdatePaddle(int,int);
      void UpdateF(float);
	  void UpdateLaser();
	  void DrawLaser(Graphics*);
	  void AddMissile();

      void Draw(Graphics*);
	  void InitialiseLaser();
	  void RemoveLaser();

	  void ActivateReverseMotion();
	  

	  void SetLaserMaxTime(int pMT)
	  {
		  mLaser.mLaserMaxTime=float(pMT);
	  }

	  void SetLives(int pL)
	  {
		  mLives+=pL;
	  }

	  int GetLives()
	  {
		  return mLives;
	  }

	  int GetMHits()
	  {
		  return mMissileHits;
	  }

	  bool GetReduceLives()
	  {
		 return mReduceLives;
	  }
	  void SetReduceLives(bool pRL)
	  {
		  mReduceLives = pRL;
	  }

	  void SetMHits(int pMH)
	  {
		  mMissileHits+=pMH;
		  if(mMissileHits>=3)
		  {
			  mMissileHits = 0;
			  mReduceLives = true;
		  }
	  }


	  void SetScaledPaddle(float pS)
	  {
		  mScaleTime = 0;
		  mScalingFactor = pS;
		  mScaled = true;
	  }

	  bool GetLaserMode()
	  {
		  return mLaser.mLaserMode;
	  }

      int GetMass()
      {
	 return mMass;
      }

      float GetMoving()
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

	  inline void SetVelocity(float vX, float vY)
	  {
		  mVel = SexyVector2(vX,vY);
		  mVel = mVel.Normalize();
	  }

	  SexyVector2 GetVel()
	  {
		  return mVel;
	  }

	  bool GetMF()
	  {
		  return mMissileFlag;
	  }

	  void SetMF(bool pMF)
	  {
		  mMissileFlag = pMF;
	  }

	  void SetMissileMode(bool);
	  bool GetMissileMode();

	  MissileManager* GetMissileManager()
	  {
		  return mMM;
	  }
	  
	  Laser GetLaser()
	  {
		  return mLaser;
	  }

	  int GetNumLasers()
	  {
		  return mNumLasers;
	  }
	  int GetNumMissiles()
	  {
		  return mNumMissiles;
	  }

	  void SetNumLasers(int pL)
	  {
		  mNumLasers+=pL;
	  }

	  void SetNumMissiles(int pM)
	  {
		  mNumMissiles+=pM;
	  }
	  
   };
}

#endif
