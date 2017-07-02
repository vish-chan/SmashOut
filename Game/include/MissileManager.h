#ifndef __MISSILEMANAGER_H__
#define __MISSILEMANAGER_H__

#include "Missile.h"
#include <vector>

namespace FrameworkX
{

class MissileManager 
   { 
   private: 
       Image* mMissileImg;
	   std::vector<Missile*> *mMissileAry;
	   bool mMissileMode;
   public: 
	   MissileManager(Image *pMissileImg); 
       ~MissileManager(); 
       void ClearMissiles(); 
       void AddMissile(int,SexyVector2); 
       void Update(); 
       void Draw(Graphics* g); 
       void DeleteMissile(int pIndex); 
       Missile* GetMissile(int pIndex); 
	   bool CheckMissileBrickCollision(FRect);
	   
	   std::vector<Missile*>* GetMissileVec()
	   {
		   return mMissileAry;
	   }

       int GetMissileCnt(); 

	   Image* GetImage()
	   {
		   return mMissileImg;
	   }

	   void SetMM(bool pMissileMode)
	   {
		   mMissileMode = pMissileMode;
	   }

	   bool GetMM()
	   {
		   return mMissileMode;
	   }

	   void ClearMissilesForNextLevel();
   }; 
}
#endif