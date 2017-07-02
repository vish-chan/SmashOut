#include "Instructions.h"
#include "Res.h"
#include "SexyAppFramework/Font.h"
#include "SexyAppFramework/SexyMatrix.h"
#include "MainMenu.h"

using namespace FrameworkX;


SexyString Roles[5] = {_S("Concept"),_S("Programmer"),_S("Designer"),_S("Special thanks to")};
SexyString Doers[5] = {_S(" Nolan Bushnell and Steve Bristow"),_S("Vishal"),_S("Vishal"),_S("Ironcode"),_S("Mini")};

Instructions::Instructions(FrameworkX::Image * pImg, MainMenu* pMM)
{
	mImg= pImg;
	mActive=false;
	mMM = pMM;
	
	Instructions::Init();
}

Instructions::~Instructions()
{

}

void Instructions::Init()
{
	mState = Instructions::I_FADEIN;
	mIA.mFrame=0;
	mIA.mSpeed=0.05F;
	mIA.mSX=0.01F;
	mIA.mSY=0.02F;
	mIA.mX = 400;
	mIA.mY = 300;
	mIA_Brick.mX=234;
	mIA_Brick.mY=473;
	mIA_Brick.mSpeed=40;
	mIA_Brick.mFrame=0;
	mBlitBrick = false;
	mIA_C.mFrame=0;
	mIA_C.mSpeed=0.2F;
	mIA_C.mX = 500;
	mIA_C.mY = 520;
	mEnableBtns = false;
	mImg = IMAGE_INSTRUCTIONS_BASE;


}

void Instructions::Activate()
{
	Instructions::Init();
	mActive = true;
	mMM->DisableMainMenu();
}


void Instructions::InitialiseCredits()
{
	mIA_C.mFrame=0;
	mIA_C.mSpeed=0.2F;
	mIA_C.mX = 450;
	mIA_C.mY = 520;
}


void Instructions::Update()
{
	if(mState==Instructions::I_FADEIN)
	{
		mIA.mSX+=mIA.mSpeed;
		if(mIA.mSX>=1)
		{
			mIA.mSX = 1;
			mIA.mSY+=mIA.mSpeed;
			if(mIA.mSY>=1)
			{
			   mIA.mSY=1;
			   mState = Instructions::I_STATIONARY;
			   mImg = IMAGE_INSTRUCTIONS_GENERAL;
	
			}
		}
	}

	if(mState==Instructions::I_STATIONARY)
	{
	   mIA.mSX = 1;
	   mIA.mSY = 1;
	   mEnableBtns=true;
	   if(mImg==IMAGE_INSTRUCTIONS_BASE)
	   {
		   mIA_C.mY-=mIA_C.mSpeed;
	   }
	   else if(mImg==IMAGE_INSTRUCTIONS_BRICKS)
	   {
	      ++mIA_Brick.mFrame;
	      if(int(mIA_Brick.mFrame)%int(mIA_Brick.mSpeed)==0)
	      {
		 mBlitBrick = !mBlitBrick;
		 mIA_Brick.mFrame=0;
	      }
	   }
		
	}

	if(mState==Instructions::I_FADEOUT)
	{
		mIA.mSY-=mIA.mSpeed;
		if(mIA.mSY<=0.005)
		{
			mActive = false;
			mMM->EnableMainMenu();
		}
	}
	
}

void Instructions::Draw(Graphics* g)
{
	Transform t;
	t.Scale(mIA.mSX,mIA.mSY);
	g->PushState();
	g->DrawImageTransformF(mImg,t,mIA.mX,mIA.mY);
	g->PopState();
	if(mImg==IMAGE_INSTRUCTIONS_BASE && mState == Instructions::I_STATIONARY)
	{
		int y=0;
		for(int i=0;i<4;i++)
		{
			y=int(mIA_C.mY)+2*i*((FONT_DEFAULT3->GetHeight()+10));
			if(y>90 && y<520)
			{
				g->SetColor(Color(60,60,60));
				g->SetFont(FONT_DEFAULT3);
				g->DrawString(Roles[i],int(mIA_C.mX-FONT_DEFAULT3->StringWidth(Roles[i])/2),y);
				g->SetColor(Color(0,0,150));
				g->DrawString(Doers[i],int(mIA_C.mX-FONT_DEFAULT3->StringWidth(Doers[i])/2),y+FONT_DEFAULT3->GetHeight()+5);
				if(i==3)
					g->DrawString(Doers[i+1],int(mIA_C.mX-FONT_DEFAULT3->StringWidth(Doers[i+1])/2),y+2*(FONT_DEFAULT3->GetHeight()+5));
			}
			
		}
		g->DrawImageF(IMAGE_CREDITS_FRAME,0,0);
	}
	else if(mImg==IMAGE_INSTRUCTIONS_BRICKS)
	{
	   if(mBlitBrick)
	      g->DrawImageF(IMAGE_BRICK_T_LOCKED,mIA_Brick.mX,mIA_Brick.mY);
	}
}


bool Instructions::IsActive()
{
	return mActive;
}


void Instructions::SetActiveScreen(Image* pImg)
{
   mImg = pImg;
}
