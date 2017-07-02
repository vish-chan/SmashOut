#include "MissileManager.h"
#include "SexyAppFramework/XAppBase.h"
#include<vector>

using namespace FrameworkX;

MissileManager::MissileManager(Image *pMissileImg)
{
	mMissileImg=pMissileImg;
	mMissileAry=new std::vector<Missile*>();
	mMissileMode = false;
}

MissileManager::~MissileManager()
{
	ClearMissiles();
	mMissileAry->clear();
	delete mMissileAry;
}

void MissileManager::ClearMissiles()
{
	if(GetMissileCnt()>0)
	{
		std::vector<Missile*>::iterator i=mMissileAry->begin();
		while(i!=mMissileAry->end())
		{
			delete (*i);
			(*i)=NULL;
			i=mMissileAry->erase(i);
		}
	}
}

void MissileManager::ClearMissilesForNextLevel()
{
	ClearMissiles();
	mMissileAry->clear();
}

void MissileManager::AddMissile(int pId,SexyVector2 pPos)
{
	Missile* tMissile = new Missile(pId,mMissileImg,pPos);
	mMissileAry->push_back(tMissile);
	
}


int MissileManager::GetMissileCnt()
{
	return	int(mMissileAry->size());
}

Missile* MissileManager::GetMissile(int pIndex)
{
	if(pIndex>=0&&pIndex<GetMissileCnt())
		return (*mMissileAry)[pIndex];
	return NULL;
}

void MissileManager::DeleteMissile(int pIndex)
{
	Missile* tMissile=GetMissile(pIndex);
	mMissileAry->erase(mMissileAry->begin()+pIndex);
	delete tMissile;
}



void MissileManager::Update()
{
	
	for(int i=0;i<GetMissileCnt();i++)
	{
		Missile* tMissile=GetMissile(i);
		tMissile->Update();
		if(tMissile->GetRemove())
		{
			DeleteMissile(i);
			i--;
		}
	}
	
	
}

void MissileManager::Draw(Graphics* g)
{
	for(int i=0;i<GetMissileCnt();i++)
	{
		
		Missile* tMissile=GetMissile(i);
		tMissile->Draw(g);
	}
	
}



bool MissileManager::CheckMissileBrickCollision(FRect pRect)
{
	bool I = false;
	for(int i=0;i<GetMissileCnt();i++)
	{
		
		Missile* tMissile=GetMissile(i);
		I = pRect.Intersects(tMissile->GetRect());
		if(I)
		{
			DeleteMissile(i);
			i--;
			return I;
		}
		
		
	}
	return I;
}

	