#ifndef __EXPLOSIONMANAGER_H__
#define __EXPLOSIONMANAGER_H__

#include "Explosion.h"
#include <vector>

namespace FrameworkX
{

class ExplosionManager 
   { 
   private: 
       Image* mExplosionImg[4];
	   std::vector<Explosion*> *mExplosionAry;
   public: 
	   ExplosionManager(Image *pExplosionImg[3]); 
       ~ExplosionManager(); 
       void ClearExplosions(); 
       void AddExplosion(int,SexyVector2, int, int); 
       void Update(); 
       void Draw(Graphics* g); 
       void DeleteExplosion(int pIndex); 
       Explosion* GetExplosion(int pIndex); 
	   
	   std::vector<Explosion*>* GetExplosionVec()
	   {
		   return mExplosionAry;
	   }

       int GetExplosionCnt(); 

	   Image* GetImage(int pId)
	   {
		   return mExplosionImg[pId];
	   }

	   void ClearExplosionsForNextLevel();
   }; 
}
#endif