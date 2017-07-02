#include "ExplosionManager.h"
#include "SexyAppFramework/XAppBase.h"
#include<vector>

using namespace FrameworkX;

ExplosionManager::ExplosionManager(Image *pExplosionImg[4])
{
	mExplosionImg[0]=pExplosionImg[0];
	mExplosionImg[1]=pExplosionImg[1];
	mExplosionImg[2]=pExplosionImg[2];
	mExplosionImg[3]=pExplosionImg[3];
	mExplosionAry=new std::vector<Explosion*>();
}

ExplosionManager::~ExplosionManager()
{
	ClearExplosions();
	mExplosionAry->clear();
	delete mExplosionAry;
}

void ExplosionManager::ClearExplosions()
{
	if(GetExplosionCnt()>0)
	{
		std::vector<Explosion*>::iterator i=mExplosionAry->begin();
		while(i!=mExplosionAry->end())
		{
			delete (*i);
			(*i)=NULL;
			i=mExplosionAry->erase(i);
		}
	}
}


void ExplosionManager::ClearExplosionsForNextLevel()
{
	ClearExplosions();
	mExplosionAry->clear();
}

void ExplosionManager::AddExplosion(int pId,SexyVector2 pPos, int pRows, int pCols)
{
	Explosion* tExplosion = new Explosion(pId,mExplosionImg[pId],pPos,pRows,pCols);
	mExplosionAry->push_back(tExplosion);
	
}


int ExplosionManager::GetExplosionCnt()
{
	return	int(mExplosionAry->size());
}

Explosion* ExplosionManager::GetExplosion(int pIndex)
{
	if(pIndex>=0&&pIndex<GetExplosionCnt())
		return (*mExplosionAry)[pIndex];
	return NULL;
}

void ExplosionManager::DeleteExplosion(int pIndex)
{
	Explosion* tExplosion=GetExplosion(pIndex);
	mExplosionAry->erase(mExplosionAry->begin()+pIndex);
	delete tExplosion;
}



void ExplosionManager::Update()
{
	
	for(int i=0;i<GetExplosionCnt();i++)
	{
		Explosion* tExplosion=GetExplosion(i);
		tExplosion->Update();
		if(tExplosion->GetRemove())
		{
			DeleteExplosion(i);
			i--;
		}
	}
	
	
}

void ExplosionManager::Draw(Graphics* g)
{
	for(int i=0;i<GetExplosionCnt();i++)
	{
		
		Explosion* tExplosion=GetExplosion(i);
		tExplosion->Draw(g);
	}
	
}