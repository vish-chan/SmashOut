#include "LevelSelect.h"
#include "Res.h"
#include "SexyAppFramework/Font.h"
#include "SexyAppFramework/SexyMatrix.h"
#include "MainMenu.h"


using namespace FrameworkX;


LevelSelect::LevelSelect(FrameworkX::Image * pImg, MainMenu* pMM, LevelInfo pLI[30])
{
	mImg= pImg;
	mActive=false;
	mMM = pMM;
	for(int i=0;i<30;i++)
		mLS_LI[i] = pLI[i];

	mMaxAllowedLevel=1;
	for(int i=0;i<30;i++)
	{
		if(mLS_LI[i].Open)
			mMaxAllowedLevel = mLS_LI[i].Level;
		else if(!mLS_LI[i].Open) 
			break;
	}
	LevelSelect::Init();
}

LevelSelect::~LevelSelect()
{

}

void LevelSelect::Init()
{
	mState = LevelSelect::I_FADEIN;
	mIA.mFrame=0;
	mIA.mSpeed=0.05F;
	mIA.mSX=0.01F;
	mIA.mSY=0.02F;
	mIA.mX = 400;
	mIA.mY = 300;
	mActivePage = 0;
	mEnableBtns_1 = false;
	mEnableBtns_2 = false;
	mImg = IMAGE_LEVEL_SELECT_BASE;


}

void LevelSelect::Activate()
{
	LevelSelect::Init();
	mActive = true;
	mMM->DisableMainMenu();
}




void LevelSelect::Update()
{
	if(mState==LevelSelect::I_FADEIN)
	{
		mIA.mSX+=mIA.mSpeed;
		if(mIA.mSX>=1)
		{
			mIA.mSX = 1;
			mIA.mSY+=mIA.mSpeed;
			if(mIA.mSY>=1)
			{
			   mIA.mSY=1;
			   mState = LevelSelect::I_STATIONARY;
			   mImg = IMAGE_LEVEL_SELECT_PAGE1;
			   mActivePage=1;
			   mMM->EnableLSB_1(mMaxAllowedLevel);
	
			}
		}
	}

	if(mState==LevelSelect::I_STATIONARY)
	{
	   mIA.mSX = 1;
	   mIA.mSY = 1;
	   if(mActivePage==1 && !mEnableBtns_1)
	   {
		   mMM->EnableLSB_1(mMaxAllowedLevel);
		   mEnableBtns_1=true;
		   mEnableBtns_2=false;
	   }
	   else if(mActivePage==2 && !mEnableBtns_2)
	   {
		   mMM->EnableLSB_4(max(0,mMaxAllowedLevel-15));
		   mEnableBtns_2=true;
		   mEnableBtns_1=false;
	   }
		
	}

	if(mState==LevelSelect::I_FADEOUT)
	{
		mIA.mSY-=mIA.mSpeed;
		if(mIA.mSY<=0.005)
		{
			mActive = false;
			mMM->EnableMainMenu();
		}
	}
	

}

void LevelSelect::Draw(Graphics* g)
{
	Transform t;
	t.Scale(mIA.mSX,mIA.mSY);
	g->PushState();
	g->DrawImageTransformF(mImg,t,mIA.mX,mIA.mY);
	g->PopState();
	if(mActivePage==1)
	{
		g->SetColor(Color::White);
		g->SetFont(FONT_DEFAULT3);
		int j=0,width;
		for(int i=0;i<15;)
		{
			width = FONT_DEFAULT3->StringWidth((StrFormat(_S("%d"),mLS_LI[i].Points)));
			g->DrawString(StrFormat(_S("%d"),mLS_LI[i].Points),100+(i%5)*(150)-width/2,170+j*175);
			if(++i%5==0)
				j++;
		}
	}
	else if(mActivePage==2)
	{
		g->SetColor(Color::White);
		g->SetFont(FONT_DEFAULT3);
		int j=0,width;
		for(int i=15;i<30;)
		{
			width = FONT_DEFAULT3->StringWidth((StrFormat(_S("%d"),mLS_LI[i].Points)));
			g->DrawString(StrFormat(_S("%d"),mLS_LI[i].Points),100+(i%5)*(150)-width/2,170+j*175);
			if(++i%5==0)
				j++;
		}
	}


	
}


bool LevelSelect::IsActive()
{
	return mActive;
}


void LevelSelect::SetActiveScreen(Image* pImg,int pPage)
{
   mImg = pImg;
   mActivePage = pPage;
}
