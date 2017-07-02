#include "BonusManager.h"
#include "SexyAppFramework/XAppBase.h"
#include<vector>

using namespace FrameworkX;

BonusManager::BonusManager(Image *pBonusImg[11])
{
	mBonusImg[0] = pBonusImg[0];
	mBonusImg[1] = pBonusImg[1];
	mBonusImg[2] = pBonusImg[2];
	mBonusImg[3] = pBonusImg[3];
	mBonusImg[4] = pBonusImg[4];
	mBonusImg[5] = pBonusImg[5];
	mBonusImg[6] = pBonusImg[6];
	mBonusImg[7] = pBonusImg[7];
	mBonusImg[8] = pBonusImg[8];
	mBonusImg[9] = pBonusImg[9];
	mBonusImg[10] = pBonusImg[10];
	mBonusAry=new std::vector<Bonus*>();
}

BonusManager::~BonusManager()
{
	ClearBonuss();
	mBonusAry->clear();
	delete mBonusAry;
}

void BonusManager::ClearBonuss()
{
	if(GetBonusCnt()>0)
	{
		std::vector<Bonus*>::iterator i=mBonusAry->begin();
		while(i!=mBonusAry->end())
		{
			delete (*i);
			(*i)=NULL;
			i=mBonusAry->erase(i);
		}
	}
}

void BonusManager::ClearBonusForNextLevel()
{
	ClearBonuss();
	mBonusAry->clear();
}


void BonusManager::AddBonus(BonusType pId,SexyVector2 pPos, int pRows, int pCols)
{
	Image* BonusImg(mBonusImg[0]);
	if(pId==BONUS_RED_GEM)
		BonusImg=mBonusImg[0];
	else if(pId==BONUS_GREEN_GEM)
		BonusImg=mBonusImg[1];
	else if(pId==BONUS_BLUE_GEM)
		BonusImg=mBonusImg[2];
	else if(pId==BONUS_MISSILE)
		BonusImg=mBonusImg[3];
	else if(pId==BONUS_FLAME)
		BonusImg=mBonusImg[4];
	else if(pId==BONUS_SIZE)
		BonusImg=mBonusImg[5];
	else if(pId==BONUS_LASER)
		BonusImg=mBonusImg[6];
	else if(pId==BONUS_LIFE)
		BonusImg=mBonusImg[7];
	else if(pId==BONUS_BLACK_SCREEN)
		BonusImg=mBonusImg[8];
	else if(pId==BONUS_BLINKING_BALL)
		BonusImg=mBonusImg[9];
	else if(pId==BONUS_REVERSE_MOTION)
		BonusImg=mBonusImg[10];


	Bonus* tBonus = new Bonus(pId,BonusImg,pPos,pRows,pCols);
	mBonusAry->push_back(tBonus);
	
}


int BonusManager::GetBonusCnt()
{
	return	int(mBonusAry->size());
}

Bonus* BonusManager::GetBonus(int pIndex)
{
	if(pIndex>=0&&pIndex<GetBonusCnt())
		return (*mBonusAry)[pIndex];
	return NULL;
}

void BonusManager::DeleteBonus(int pIndex)
{
	Bonus* tBonus=GetBonus(pIndex);
	mBonusAry->erase(mBonusAry->begin()+pIndex);
	delete tBonus;
}



void BonusManager::Update()
{
	
	for(int i=0;i<GetBonusCnt();i++)
	{
		Bonus* tBonus=GetBonus(i);
		tBonus->Update();
		if(tBonus->GetRemove())
		{
			DeleteBonus(i);
			i--;
		}
	}
	
	
}

void BonusManager::Draw(Graphics* g)
{
	for(int i=0;i<GetBonusCnt();i++)
	{
		
		Bonus* tBonus=GetBonus(i);
		tBonus->Draw(g);
	}
	
}