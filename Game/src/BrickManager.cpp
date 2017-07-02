#include "BrickManager.h"
#include "Res.h"
#include <stdlib.h>
#include<time.h>
#include<vector>

using namespace FrameworkX;


BrickManager::BrickManager(Image *pBrickImg[6])
{
	mBrickImg[0]=pBrickImg[0];
	mBrickImg[1]=pBrickImg[1];
	mBrickImg[2]=pBrickImg[2];
	mBrickImg[3]=pBrickImg[3];
	mBrickImg[4]=pBrickImg[4];
	mBrickImg[5]=pBrickImg[5];
	mBrickAry=new std::vector<Brick*>();
	mBMM= new MissileManager(IMAGE_BRICK_MISSILE);
	mMissileTime=0;
}

BrickManager::~BrickManager()
{
	ClearLevel();
	mBrickAry->clear();
	delete mBrickAry;
	if(mBMM!=NULL)
		delete mBMM;
}

void BrickManager::ClearLevel()
{
	if(GetBrickCnt()>0)
	{
		std::vector<Brick*>::iterator i=mBrickAry->begin();
		while(i!=mBrickAry->end())
		{
			delete (*i);
			(*i)=NULL;
			i=mBrickAry->erase(i);
		}
	}
}

void BrickManager::AddRow(int pY,int pRow[],int pRowBonus[],int ir)
{
	
	float x,y;
	for(int ic=0;ic<mCols;ic++)
	{
		if(pRow[ic])
		{
			switch(pRow[ic])
			{
				Brick* tBrick;
			case 1:
				x = float(ic*(mBrickImg[0]->GetWidth()+mHorzSpacing)+mBrickImg[0]->GetWidth()/2);
				y = float(pY+mBrickImg[0]->GetHeight()/2);
				tBrick=new Brick(1,mBrickImg[0],SexyVector2(x,y),FRect(ic*(mBrickImg[0]->GetWidth()+mHorzSpacing),pY,mBrickImg[0]->GetWidth(),mBrickImg[0]->GetHeight()),0,SexyVector2(0,0),true,1,Color(255,255,255),ir,ic,10,false,false);
				tBrick->SetBonus(pRowBonus[ic]);
				mBrickAry->push_back(tBrick);
				break;
			case 2:
				x = float(ic*(mBrickImg[1]->GetWidth()+mHorzSpacing)+mBrickImg[0]->GetWidth()/2);
				y = float(pY+mBrickImg[1]->GetHeight()/2);
				tBrick=new Brick(2,mBrickImg[1],SexyVector2(x,y),FRect(ic*(mBrickImg[1]->GetWidth()+mHorzSpacing),pY,mBrickImg[1]->GetWidth(),mBrickImg[1]->GetHeight()),0,SexyVector2(0,0),true,5,Color(255,255,255),ir,ic,50,false,false);
				tBrick->SetBonus(pRowBonus[ic]);
				mBrickAry->push_back(tBrick);
				break;
			case 3:
				x = float(ic*(mBrickImg[2]->GetWidth()+mHorzSpacing)+mBrickImg[0]->GetWidth()/2);
				y = float(pY+mBrickImg[2]->GetHeight()/2);
				tBrick=new Brick(3,mBrickImg[2],SexyVector2(x,y),FRect(ic*(mBrickImg[2]->GetWidth()+mHorzSpacing),pY,mBrickImg[2]->GetWidth(),mBrickImg[2]->GetHeight()),0,SexyVector2(0,0),true,4,Color(255,255,255),ir,ic,20,false,false);
				tBrick->SetBonus(pRowBonus[ic]);
				mBrickAry->push_back(tBrick);
				break;
			case 4:
				x = float(ic*(mBrickImg[2]->GetWidth()+mHorzSpacing)+mBrickImg[0]->GetWidth()/2);
				y = float(pY+mBrickImg[2]->GetHeight()/2);
				tBrick=new Brick(4,mBrickImg[3],SexyVector2(x,y),FRect(ic*(mBrickImg[3]->GetWidth()+mHorzSpacing),pY,mBrickImg[3]->GetWidth(),mBrickImg[3]->GetHeight()),0,SexyVector2(0,0),false,1,Color(255,255,255),ir,ic,100,false,false);
				tBrick->SetBonus(pRowBonus[ic]);
				mBrickAry->push_back(tBrick);
				break;
			case 5:
				x = float(ic*(mBrickImg[2]->GetWidth()+mHorzSpacing)+mBrickImg[0]->GetWidth()/2);
				y = float(pY+mBrickImg[2]->GetHeight()/2);
				tBrick=new Brick(5,mBrickImg[4],SexyVector2(x,y),FRect(ic*(mBrickImg[4]->GetWidth()+mHorzSpacing),pY,mBrickImg[4]->GetWidth(),mBrickImg[4]->GetHeight()),0,SexyVector2(0,0),true,10,Color(255,255,255),ir,ic,200,true,false);
				tBrick->SetBonus(pRowBonus[ic]);
				mBrickAry->push_back(tBrick);
				break;
			case 6:
				x = float(ic*(mBrickImg[2]->GetWidth()+mHorzSpacing)+mBrickImg[0]->GetWidth()/2);
				y = float(pY+mBrickImg[2]->GetHeight()/2);
				tBrick=new Brick(6,mBrickImg[5],SexyVector2(x,y),FRect(ic*(mBrickImg[3]->GetWidth()+mHorzSpacing),pY,mBrickImg[3]->GetWidth(),mBrickImg[3]->GetHeight()),0,SexyVector2(0,0),true,1,Color(255,255,255),ir,ic,300,false,true);
				tBrick->SetBonus(pRowBonus[ic]);
				mBrickAry->push_back(tBrick);
				break;
			}
			
		}
	}
}

void BrickManager::CreateLevel(int pLevelMap[][8],int pBonusMap[][8],int pRows, int pCols, int pHorzSpacing, int pVertSpacing, int pMaxTime)
{
	srand((unsigned)time(NULL));

	int* RowBricks,*RowBonus;
	RowBricks = new int[pCols];
	RowBonus = new int[pCols];
	
	mRows=pRows;
	mCols=pCols;
	for(int i=0;i<mRows;i++)
		for(int j=0;j<mCols;j++)
		{
			mLevelMap[i][j] = pLevelMap[i][j];
			mBonusMap[i][j] = pBonusMap[i][j];
		}

	mHorzSpacing=pHorzSpacing;
	mVertSpacing=pVertSpacing;
	mMaxTime=pMaxTime;
	
	ClearLevel();
	
	for(int ir=0;ir<mRows;ir++)
	{
		for(int j=0;j<mCols;j++)
		{
			RowBricks[j]=mLevelMap[ir][j];
			RowBonus[j]=mBonusMap[ir][j];
		}
		AddRow(ir*(mBrickImg[0]->GetHeight()+mVertSpacing),RowBricks,RowBonus,ir);
	}
}

int BrickManager::GetBrickCnt()
{
	return	int(mBrickAry->size());
}

Brick* BrickManager::GetBrick(int pIndex)
{
	if(pIndex>=0&&pIndex<GetBrickCnt())
		return (*mBrickAry)[pIndex];
	return NULL;
}

void BrickManager::DeleteBrick(int pIndex)
{
	Brick* tBrick=GetBrick(pIndex);
	mBrickAry->erase(mBrickAry->begin()+pIndex);
	delete tBrick;
}

int BrickManager::TestCollision(Sprite * pSpr)
{
	return 10;
}

void BrickManager::MoveDown(int pAmt)
{
	for(int i=0;i<GetBrickCnt();i++)
	{
		Brick* tBrick=GetBrick(i);
		tBrick->SetY(tBrick->GetY()+(mBrickImg[0]->GetHeight()+mVertSpacing)*pAmt);
	}
}

void BrickManager::Update()
{
	mMissileTime++;
	for(int i=0;i<GetBrickCnt();i++)
	{
		Brick* tBrick=GetBrick(i);
		tBrick->Update();
		if(tBrick->GetMissileCap())
		{
			if(!tBrick->GetMissileLaunched() && (mBMM->GetMissileCnt()<2) && (mMissileTime%200)==0)
			{
				mBMM->AddMissile(Missile::M_BRICK,SexyVector2(tBrick->GetX(),tBrick->GetY()+tBrick->GetImage()->GetHeight()/2));
				tBrick->SetMissileLaunched(true);
				mMissileTime = 100;
			}
			else if(mBMM->GetMissileCnt()==0 && tBrick->GetMissileLaunched() )
				tBrick->SetMissileLaunched(false);
		}

	}

	if(mBMM->GetMissileCnt())
		mBMM->Update();
	if(mBMM->GetMissileCnt()>=2)
		mMissileTime = 160;
}

void BrickManager::Draw(Graphics* g)
{
	for(int i=0;i<GetBrickCnt();i++)
	{
		Brick* tBrick=GetBrick(i);
		tBrick->Draw(g);
	}

	if(mBMM->GetMissileCnt())
	   mBMM->Draw(g);
	
}

void BrickManager::ClearBrickForNextLevel()
{
	ClearLevel();
	mBrickAry->clear();
	mBMM->ClearMissiles();
	mBMM->GetMissileVec()->clear();
	mMissileTime=0;
}

