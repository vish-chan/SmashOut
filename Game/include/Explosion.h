#ifndef __EXPLOSION_H__
#define __EXPLOSION_H__

#include "SexyAppFramework/Graphics.h"
#include "SexyAppFramework/Image.h"
#include "SexyAppFramework/Rect.h"
#include "SexyAppFramework/SexyVector.h"



namespace FrameworkX
{
	class Graphics;
	
	
   class Explosion
   {
   private:
	   int mId;
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

   public:
      Explosion(int,Image*,SexyVector2, int, int );
      ~Explosion();

      void Draw(Graphics*);
	  void Update();

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
	  


   };
}

#endif

     


