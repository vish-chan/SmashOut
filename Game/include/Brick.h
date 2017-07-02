#ifndef __BRICK_H__
#define __BRICK_H__

#include "cSprite.h"
#include "Bonus.h"
#include "SexyAppFramework/Graphics.h"
#include "SexyAppFramework/Image.h"
#include "SexyAppFramework/SexyVector.h"
#include "SexyAppFramework/Rect.h"
#include "SexyAppFramework/Color.h"


namespace FrameworkX
{
	class Graphics;

	struct Shake
	{
		bool mShouldShake;
		int mMaxShakeTime;
		int mElapsedShakeTime;
		float mShakeMag;
		int mShakeDirTime;
	};

	
	
   class Brick:public Sprite 
   {
   private:
      int mId;
      float mWidth;
      float mHeight;
      bool mBreakable;
      int mMaxHits;
      int mHits;
      int mRow;
      int mCol;
      Color mColor;
      BonusType mBonus;
      bool mLaserHit;
      float mBreakPoints;
      bool mMissileCapable;
      bool mMissileLaunched;

      //-----for tranformer brick---------//
      bool mCanTransform;
      int mChangeInterval;
      int mChangeFrame;
	  
	  Shake mShake;
	  

   public:
      Brick(int,Image*, SexyVector2, FRect, float, SexyVector2, bool, int,Color, int ,int, float,bool,bool);
      ~Brick();

      virtual void Draw(Graphics*);
      void SetBonus(int);
      void Update();
	  void ResetShake();
	  void SetShake();
	  void UpdateShaking();
      BonusType GetBonus()
      {
	 return mBonus;
      }
     
	  int GetRow()
      {
	 return mRow;
      }

	  int GetCol()
	  {
		  return mCol;
	  }

	  bool GetBreakability()
	  {
		  return mBreakable;
	  }
	  int GetHits()
	  {
		  return mHits;
	  }
	  int GetMaxHits()
	  {
		  return mMaxHits;
	  }
	  Color GetColor()
	  {
		  return mColor;
	  }
	  void SetHits(int pHit)
	  {
		  mHits+=pHit;
	  }

	  bool DestroyBrick();

	  int GetId()
	  {
		  return mId;
	  }

	  void SetLaserHit(bool pHit)
	  {
		  mLaserHit = pHit;
	  }

	  bool GetLaserHit()
	  {
		  return mLaserHit;
	  }

	  float GetBreakPoints()
	  {
		  return mBreakPoints;
	  }

	  bool GetMissileCap()
	  {
		  return mMissileCapable;
	  }

	  bool GetMissileLaunched()
	  {
		  return mMissileLaunched;
	  }

	  void SetMissileLaunched(bool pML)
	  {
		  mMissileLaunched = pML;
	  }

	  bool GetCanTransform()
	  {
	     return mCanTransform;
	  }


};
}

#endif

     


