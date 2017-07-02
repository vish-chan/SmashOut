#ifndef __BONUSMANAGER_H__
#define __BONUSMANAGER_H__

#include "Bonus.h"
#include <vector>

namespace FrameworkX
{

class BonusManager 
   { 
   private: 
       Image* mBonusImg[11];
	   std::vector<Bonus*> *mBonusAry;
   public: 
	   BonusManager(Image *pBonusImg[11]); 
       ~BonusManager(); 
       void ClearBonuss(); 
       void AddBonus(BonusType,SexyVector2, int, int); 
       void Update(); 
       void Draw(Graphics* g); 
       void DeleteBonus(int pIndex); 
       Bonus* GetBonus(int pIndex); 
	   
	   std::vector<Bonus*>* GetBonusVec()
	   {
		   return mBonusAry;
	   }

       int GetBonusCnt(); 

	   Image* GetImage(int pId)
	   {
		   return mBonusImg[pId];
	   }

	   void ClearBonusForNextLevel();
   }; 

}
#endif