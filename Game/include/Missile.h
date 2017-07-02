#ifndef __MISSILE_H__
#define __MISSILE_H__

#include "SexyAppFramework/Graphics.h"
#include "SexyAppFramework/Image.h"
#include "SexyAppFramework/Rect.h"
#include "SexyAppFramework/SexyVector.h"

namespace FrameworkX
{
	class Graphics;
	
	class Missile
   {
   private:
	   int mId;
	   Image* mImg;
	   FRect mRect;
	   SexyVector2 mPos;
	   bool mRemove;
	   float mFrame;
	   double mU;
	   double mAccel;
	   int mR;
	   bool mIncreasing;

   public:
	   enum
	   {
		   M_PADDLE,
		   M_BRICK,
	   };
      Missile(int,Image*,SexyVector2);
      ~Missile();

      void Draw(Graphics*);
	  void Update();

	  bool GetRemove()
	  {
		  return mRemove;
	  }
	  
	 FRect GetRect()
		{
			return mRect;
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
	};
}

#endif

     
