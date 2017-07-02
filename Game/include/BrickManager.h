#ifndef __BRICKMANAGER_H__
#define __BRICKMANAGER_H__

#include "Brick.h"
#include "MissileManager.h"
#include <vector>

namespace FrameworkX
{

class BrickManager 
   { 
   private: 
       Image* mBrickImg[6];
	   std::vector<Brick*> *mBrickAry;
	   MissileManager* mBMM;
	   int mMissileTime;

       int mCurTime,mMaxTime,mLevelMap[10][8],mBonusMap[10][8],mRows,mCols,mHorzSpacing,mVertSpacing; 
   public: 
	   BrickManager(Image *pBrickImg[6]); 
       ~BrickManager(); 
       void CreateLevel(int pLevelMap[][8],int pBonusMap[][8],int,int, int pHorzSpacing, int pVertSpacing,int pMaxTime); 
       void ClearLevel(); 
       void AddRow(int pY, int pRow[],int pRowBonus[],int); 
       void MoveDown(int pAmt); 
       void Update(); 
       void Draw(Graphics* g); 
       void DeleteBrick(int pIndex); 
       int TestCollision(Sprite *pSpr); 
       Brick* GetBrick(int pIndex); 
	   
	   std::vector<Brick*>* GetBrickVec()
	   {
		   return mBrickAry;
	   }

       int GetBrickCnt(); 
	   int GetHS()
	   {
		   return mHorzSpacing;
	   }
	   int GetVS()
	   {
		   return mVertSpacing;
	   }

	   Image* GetImage()
	   {
		   return mBrickImg[0];
	   }

	   void ClearBrickForNextLevel();

	   MissileManager* GetMissileManager()
	  {
		  return mBMM;
	  }

   }; 
}
#endif