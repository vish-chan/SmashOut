#ifndef __BONUS_H__
#define __BONUS_H__

#include "SexyAppFramework/Graphics.h"
#include "SexyAppFramework/Image.h"
#include "SexyAppFramework/Rect.h"
#include "SexyAppFramework/SexyVector.h"



namespace FrameworkX
{
	class Graphics;

	enum BonusType
	{
		BONUS_NONE,
		BONUS_RED_GEM,
		BONUS_GREEN_GEM,
		BONUS_BLUE_GEM,
		BONUS_MISSILE,
		BONUS_FLAME,
		BONUS_SIZE,
		BONUS_LASER,
		BONUS_LIFE,
		BONUS_BLACK_SCREEN,
		BONUS_BLINKING_BALL,
		BONUS_REVERSE_MOTION
	};

	struct Projectile
	{
		float mVel;
		float mTheta;
		float mIHeight;
		float mTime;
		float mIXPos;
	};


	
	
   class Bonus
   {
   private:
	   BonusType mId;
	   Image* mImg;
	   int mRows;
	   int mCols;
	   int mRow;
	   int mCol;
	   Rect mSRect;
	   FRect mDRect;
	   int mFrame;
	   SexyVector2 mPos;
	   bool mRemove;
	   int mPoints;
	   int mMissiles;
	   int mLaserTime;
	   int mLives;
	   int mFireTime;
	   Projectile mProjectile;
	   float mRot;
	   int mScalingFactor;
	   

   public:
      Bonus(BonusType,Image*,SexyVector2, int, int );
      ~Bonus();

      void Draw(Graphics*);
	  void Update();
	  void GetLocation();

	  bool GetRemove()
	  {
		  return mRemove;
	  }
	  
     
	  int GetRow()
      {
	    return mRow;
      }

	  int GetCol()
	  {
		  return mCol;
	  }
      
	 FRect GetDRect()
		{
			return mDRect;
		}

		Image* GetImage()
		{
			return mImg;
		}
		float GetX()
		{
			return mPos.x;
		}
        float GetY()
		{
			return mPos.y;
		}
		int GetFrame()
		{
			return mFrame;
		}

		int GetLives()
		{
			return mLives;
		}
		int GetPoints()
		{
			return mPoints;
		}

		int GetNumMissiles()
		{
			return mMissiles;
		}
		int GetLaserTime()
		{
			return mLaserTime;
		}

		BonusType GetId()
		{
			return mId;
		}

		int GetFireTime()
		{
			return mFireTime;
		}

		int GetScalingFactor()
		{
			return mScalingFactor;
		}
	  


   };
}

#endif
