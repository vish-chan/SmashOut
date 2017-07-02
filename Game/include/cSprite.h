
#ifndef __CSPRITE_H__
#define __CSPRITE_H__


#include "SexyAppFramework/Graphics.h"
#include "SexyAppFramework/Image.h"
#include "SexyAppFramework/SexyVector.h"
#include "SexyAppFramework/Rect.h"



namespace FrameworkX
{
	class Image;
	class SexyVector2;
	class Graphics;
	
	struct SpecialEffects
	{
		bool mIsActive;
		bool mToggleEffect;
		int mElapsedTime;
		int mMaxTime;
		int mToggleTime;
		int mFrame;
	};
    


	class Sprite
	{
	protected:
		Image* mImg;
		SexyVector2 mPos;
		FRect mFRect;
		float mSpeed;
		SexyVector2 mVel;
		float mSFactor;   //used as RFF for paddle
		

	public:
		Sprite(Image*, SexyVector2, FRect, float, SexyVector2);
		~Sprite();
		//virtual void Update();
		virtual void UpdateF(float);
		virtual void Draw(Graphics* g);
		virtual void ActivateSpecialEffect(SpecialEffects&,int,int);
		virtual void DeactivateSpecialEffect(SpecialEffects&);

		
		void SetX(float pX)
		{
			mPos.x=pX;
			
		}
		void SetY(float pY)
		{
			mPos.y = pY;
			
		}
		void SetVX(float pVX)
		{
			mVel.x = pVX;
		}
        void SetVY(float pVY)
		{
			mVel.y=pVY;
		}
		
		void SetSpeed(float pSpeed)
		{
			mSpeed = pSpeed;
		}

		void SetRect(FRect pRect)
		{
			mFRect = pRect;
		}

		void SetImage(Image* pImg)
		{
			mImg =pImg;
		}

        float GetX()
		{
			return mPos.x;
		}
        float GetY()
		{
			return mPos.y;
		}
        float GetVX()
		{
			return mVel.x;
		}
        float GetVY()
		{
			return mVel.y;
		}
        float GetSpeed()
		{
			return mSpeed;
		}

		FRect GetRect()
		{
			return mFRect;
		}

		Image* GetImage()
		{
			return mImg;
		}
		SexyVector2 GetVel()
	  {
		  return mVel;
	  }
		float GetFactor()
		{
			return mSFactor;
		}
		void SetFactor(float pFactor)
		{
			mSFactor = pFactor;
		}
		SexyVector2 GetPos()
		{
			return mPos;
		}
	};
}



#endif