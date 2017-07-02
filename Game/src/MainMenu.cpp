#include "MainMenu.h"
#include "cGame.h"
#include "Res.h"
#include "Instructions.h"
#include "LevelSelect.h"
#include<string>
#include "SexyAppFramework/Font.h"
#include "SexyAppFramework/Graphics.h"
#include "SexyAppFramework/Image.h"
#include "SexyAppFramework/WidgetManager.h"
#include "SexyAppFramework/Rect.h"
#include "SexyAppFramework/ButtonWidget.h"
#include <fstream>

using namespace FrameworkX;



int ButtnColors[3][3] = {{210,210,210},{250,250,250},{180,180,180}};


int ButtonOverDisplayFlag=0;
std::string S;
const int ix = 57;
const int iy = 70;

const int lx = 52;
const int ly = 65;


MainMenu::MainMenu(cGame* theApp)
{
   mApp = theApp;
   mX=0;
   mY=0;
   mLevel=1;


   mWidgetFlagsMod.mAddFlags |= WIDGETFLAGS_MARK_DIRTY;  //make mainmenu dirty each frame
   
   int width = IMAGE_MM_BTN_NORMAL->GetWidth();
   int height = IMAGE_MM_BTN_NORMAL->GetHeight();
   
//*********Single player button***********
   mPlay = new ButtonWidget(1, this);
   mPlay->SetFont(FONT_DEFAULT2);
   mPlay->SetColors(ButtnColors, 3);
   mPlay->mLabel = _S("Play");

   
   mPlay->Resize(mApp->mWidth/2-width/2, 200,width, height);
   mPlay->mOverImage = IMAGE_MM_BTN_OVER;
   mPlay->mDownImage = IMAGE_MM_BTN_NORMAL;
   mPlay->mButtonImage = IMAGE_MM_BTN_NORMAL;
   AddWidget(mPlay);


   mChooseLevel = new ButtonWidget(2, this);
   mChooseLevel->SetFont(FONT_DEFAULT2);
   mChooseLevel->SetColors(ButtnColors, 3);
   mChooseLevel->mLabel = _S("Select Level");

   
   mChooseLevel->Resize(mApp->mWidth/2-width/2,  190+height+10,width, height);
   mChooseLevel->mOverImage = IMAGE_MM_BTN_OVER;
   mChooseLevel->mDownImage = IMAGE_MM_BTN_NORMAL;
   mChooseLevel->mButtonImage = IMAGE_MM_BTN_NORMAL;
   AddWidget(mChooseLevel);

  

//*********Instructions button**********
   mInstructions = new ButtonWidget(3, this);
   mInstructions->SetFont(FONT_DEFAULT2);
   mInstructions->mLabel = _S("Help");
   mInstructions->SetColors(ButtnColors, 3);

   
   mInstructions->Resize(mApp->mWidth/2-width/2,  190+2*height+10,width, height);
   mInstructions->mOverImage = IMAGE_MM_BTN_OVER;
   mInstructions->mDownImage = IMAGE_MM_BTN_NORMAL;
   mInstructions->mButtonImage = IMAGE_MM_BTN_NORMAL;
   AddWidget(mInstructions);

//********Options Button***************
   mOptions = new ButtonWidget(4, this);
   mOptions->SetFont(FONT_DEFAULT2);
   mOptions->mLabel = _S("Options");
   mOptions->SetColors(ButtnColors, 3);

   
   mOptions->Resize(mApp->mWidth/2-width/2, 190+3*height+10,width, height);
   mOptions->mOverImage = IMAGE_MM_BTN_OVER;
   mOptions->mDownImage = IMAGE_MM_BTN_NORMAL;
   mOptions->mButtonImage = IMAGE_MM_BTN_NORMAL;
   AddWidget(mOptions);

//*************Exit Button************ 
   mExit = new ButtonWidget(5, this);
   mExit->SetFont(FONT_DEFAULT2);
   mExit->mLabel = _S("Exit");
   mExit->SetColors(ButtnColors, 3);

   
   mExit->Resize(mApp->mWidth/2-width/2, 190+4*height+10,width, height);
   mExit->mOverImage = IMAGE_MM_BTN_OVER;
   mExit->mDownImage = IMAGE_MM_BTN_NORMAL;
   mExit->mButtonImage = IMAGE_MM_BTN_NORMAL;
   AddWidget(mExit);



   mI = new Instructions(IMAGE_INSTRUCTIONS_BASE,this);

   width = IMAGE_INSTRUCTIONS_BTN_NORMAL->GetWidth();
   height = IMAGE_INSTRUCTIONS_BTN_NORMAL->GetHeight();
   

   mI_General = new ButtonWidget(6, this);
   mI_General->SetFont(FONT_DEFAULT3);
   mI_General->SetColors(ButtnColors, 3);
   mI_General->mLabel = _S("Game Play");

   
   mI_General->Resize(ix,iy,width, height);
   mI_General->mOverImage = IMAGE_INSTRUCTIONS_BTN_OVER;
   mI_General->mDownImage = IMAGE_INSTRUCTIONS_BTN_NORMAL;
   mI_General->mButtonImage = IMAGE_INSTRUCTIONS_BTN_NORMAL;
   AddWidget(mI_General);

   
   mI_Bricks = new ButtonWidget(7, this);
   mI_Bricks->SetFont(FONT_DEFAULT3);
   mI_Bricks->SetColors(ButtnColors, 3);
   mI_Bricks->mLabel = _S("Bricks");

   
   mI_Bricks->Resize(ix,iy+height+10,width,height);
   mI_Bricks->mOverImage = IMAGE_INSTRUCTIONS_BTN_OVER;
   mI_Bricks->mDownImage = IMAGE_INSTRUCTIONS_BTN_NORMAL;
   mI_Bricks->mButtonImage = IMAGE_INSTRUCTIONS_BTN_NORMAL;
   AddWidget(mI_Bricks);


   mI_Bonus = new ButtonWidget(8, this);
   mI_Bonus->SetFont(FONT_DEFAULT3);
   mI_Bonus->SetColors(ButtnColors, 3);
   mI_Bonus->mLabel = _S("Bonus");

   mI_Bonus->Resize(ix,iy+2*(10+height),width, height);
   mI_Bonus->mOverImage = IMAGE_INSTRUCTIONS_BTN_OVER;
   mI_Bonus->mDownImage = IMAGE_INSTRUCTIONS_BTN_NORMAL;
   mI_Bonus->mButtonImage = IMAGE_INSTRUCTIONS_BTN_NORMAL;
   AddWidget(mI_Bonus);



   mI_Close = new ButtonWidget(9, this);
   mI_Close->SetFont(FONT_DEFAULT3);
   mI_Close->SetColors(ButtnColors, 3);
   mI_Close->mLabel = _S("Close");
   
   mI_Close->Resize(ix,iy+4*(10+height),width, height);
   mI_Close->mOverImage = IMAGE_INSTRUCTIONS_BTN_OVER;
   mI_Close->mDownImage = IMAGE_INSTRUCTIONS_BTN_NORMAL;
   mI_Close->mButtonImage = IMAGE_INSTRUCTIONS_BTN_NORMAL;
   AddWidget(mI_Close);


   mI_Credits = new ButtonWidget(10, this);
   mI_Credits->SetFont(FONT_DEFAULT3);
   mI_Credits->SetColors(ButtnColors, 3);
   mI_Credits->mLabel = _S("Credits");

   mI_Credits->Resize(ix,iy+3*(10+height),width, height);
   mI_Credits->mOverImage = IMAGE_INSTRUCTIONS_BTN_OVER;
   mI_Credits->mDownImage = IMAGE_INSTRUCTIONS_BTN_NORMAL;
   mI_Credits->mButtonImage = IMAGE_INSTRUCTIONS_BTN_NORMAL;
   AddWidget(mI_Credits);

   DisableInstructionsBtns();
   
   for(int i=0; i<30 ;i++)
    {
        mLI[i].Level=i+1;
        mLI[i].Points=0;
        mLI[i].Open=false;
    }

   ReadLevelInfo();

   mLS = new LevelSelect(IMAGE_LEVEL_SELECT_BASE, this, mLI);

   width=IMAGE_LS_1_BTN_NORMAL->GetWidth();
   height=IMAGE_LS_1_BTN_NORMAL->GetHeight();
   

   for(int i = 0;i<5;i++)
   {
	   mLS_Btns_1[i] = new ButtonWidget(11+i, this);
	   mLS_Btns_1[i]->SetFont(FONT_DEFAULT3);
	   mLS_Btns_1[i]->SetColors(ButtnColors, 3);
	   mLS_Btns_1[i]->mLabel = _S("");
	   mLS_Btns_1[i]->Resize(lx+i*(54+width),ly,width, height);
	   mLS_Btns_1[i]->mOverImage = IMAGE_LS_1_BTN_OVER;
	   mLS_Btns_1[i]->mDownImage = IMAGE_LS_1_BTN_NORMAL;
	   mLS_Btns_1[i]->mButtonImage = IMAGE_LS_1_BTN_NORMAL;
	   AddWidget(mLS_Btns_1[i]);
	   mLS_Btns_1[i]->SetDisabled(true);
	   mLS_Btns_1[i]->SetVisible(false);
   }

   for(int i = 0;i<5;i++)
   {
	   mLS_Btns_2[i] = new ButtonWidget(16+i, this);
	   mLS_Btns_2[i]->SetFont(FONT_DEFAULT3);
	   mLS_Btns_2[i]->SetColors(ButtnColors, 3);
	   mLS_Btns_2[i]->mLabel = _S("");
	   mLS_Btns_2[i]->Resize(lx+i*(54+width),ly+height+92,width, height);
	   mLS_Btns_2[i]->mOverImage = IMAGE_LS_6_BTN_OVER;
	   mLS_Btns_2[i]->mDownImage = IMAGE_LS_6_BTN_NORMAL;
	   mLS_Btns_2[i]->mButtonImage = IMAGE_LS_6_BTN_NORMAL;
	  
	   AddWidget(mLS_Btns_2[i]);
	   mLS_Btns_2[i]->SetDisabled(true);
	   mLS_Btns_2[i]->SetVisible(false);
   }

   for(int i = 0;i<5;i++)
   {
	   mLS_Btns_3[i] = new ButtonWidget(21+i, this);
	   mLS_Btns_3[i]->SetFont(FONT_DEFAULT3);
	   mLS_Btns_3[i]->SetColors(ButtnColors, 3);
	   mLS_Btns_3[i]->mLabel = _S("");
	   mLS_Btns_3[i]->Resize(lx+i*(54+width),ly+2*(height+92),width, height);
	   mLS_Btns_3[i]->mOverImage = IMAGE_LS_3_BTN_OVER;
	   mLS_Btns_3[i]->mDownImage = IMAGE_LS_3_BTN_NORMAL;
	   mLS_Btns_3[i]->mButtonImage = IMAGE_LS_3_BTN_NORMAL;
	   AddWidget(mLS_Btns_3[i]);
	   mLS_Btns_3[i]->SetDisabled(true);
	   mLS_Btns_3[i]->SetVisible(false);
   }

   width = IMAGE_LS_4_BTN_OVER->GetWidth();
   height = IMAGE_LS_4_BTN_OVER->GetHeight();

   for(int i = 0;i<5;i++)
   {
	   mLS_Btns_4[i] = new ButtonWidget(26+i, this);
	   mLS_Btns_4[i]->SetFont(FONT_DEFAULT3);
	   mLS_Btns_4[i]->SetColors(ButtnColors, 3);
	   mLS_Btns_4[i]->mLabel = _S("");
	   mLS_Btns_4[i]->Resize(lx+i*(54+width),ly,width, height);
	   mLS_Btns_4[i]->mOverImage = IMAGE_LS_5_BTN_OVER;
	   mLS_Btns_4[i]->mDownImage = IMAGE_LS_5_BTN_NORMAL;
	   mLS_Btns_4[i]->mButtonImage = IMAGE_LS_5_BTN_NORMAL;
	   AddWidget(mLS_Btns_4[i]);
	   mLS_Btns_4[i]->SetDisabled(true);
	   mLS_Btns_4[i]->SetVisible(false);
   }

   for(int i = 0;i<5;i++)
   {
	   mLS_Btns_5[i] = new ButtonWidget(31+i, this);
	   mLS_Btns_5[i]->SetFont(FONT_DEFAULT3);
	   mLS_Btns_5[i]->SetColors(ButtnColors, 3);
	   mLS_Btns_5[i]->mLabel = _S("");
	   mLS_Btns_5[i]->Resize(lx+i*(54+width),ly+height+94,width, height);
	   mLS_Btns_5[i]->mOverImage = IMAGE_LS_4_BTN_OVER;
	   mLS_Btns_5[i]->mDownImage = IMAGE_LS_4_BTN_NORMAL;
	   mLS_Btns_5[i]->mButtonImage = IMAGE_LS_4_BTN_NORMAL;
	   AddWidget(mLS_Btns_5[i]);
	   mLS_Btns_5[i]->SetDisabled(true);
	   mLS_Btns_5[i]->SetVisible(false);
   }
   for(int i = 0;i<5;i++)
   {
	   mLS_Btns_6[i] = new ButtonWidget(36+i, this);
	   mLS_Btns_6[i]->SetFont(FONT_DEFAULT3);
	   mLS_Btns_6[i]->SetColors(ButtnColors, 3);
	   mLS_Btns_6[i]->mLabel = _S("");
	   mLS_Btns_6[i]->Resize(lx+i*(54+width),ly+2*(height+92),width, height);
	   mLS_Btns_6[i]->mOverImage = IMAGE_LS_2_BTN_OVER;
	   mLS_Btns_6[i]->mDownImage = IMAGE_LS_2_BTN_NORMAL;
	   mLS_Btns_6[i]->mButtonImage = IMAGE_LS_2_BTN_NORMAL;
	   AddWidget(mLS_Btns_6[i]);
	   mLS_Btns_6[i]->SetDisabled(true);
	   mLS_Btns_6[i]->SetVisible(false);
   }

}


MainMenu::~MainMenu()
{
   RemoveAllWidgets();
   delete mPlay;
   delete mInstructions;
   delete mChooseLevel;
   delete mOptions;
   delete mExit;
   delete mI;
   delete mLS;
   delete mI_General;
   delete mI_Bricks;
   delete mI_Bonus;
   delete mI_Close;
   delete mI_Credits;
   for(int i=0;i<5;i++)
	   delete mLS_Btns_1[i];
   for(int i=0;i<5;i++)
	  delete mLS_Btns_2[i];
   for(int i=0;i<5;i++)
	  delete mLS_Btns_3[i];
   for(int i=0;i<5;i++)
	   delete mLS_Btns_4[i];
   for(int i=0;i<5;i++)
	   delete mLS_Btns_5[i];
   for(int i=0;i<5;i++)
	   delete mLS_Btns_6[i];


}

void MainMenu::Update()
{
   if(!mI->IsActive() || (mI->IsActive() && mI->GetState()==Instructions::I_FADEOUT) && (!mLS->IsActive() || (mLS->IsActive() && mLS->GetState()==LevelSelect::I_FADEOUT)))
   {
	   {
		   if(++mX>=mWidth)
			   mX=0;
	   }
   }

   if(mI->IsActive())
   {
      mI->Update();
      if(mI->ActivateBtn())
	  {
		  this->EnableInstructionsBtns();
		  mI->SetBtnState(false);
      }
   }
   
   if(mLS->IsActive())
   {
	   mLS->Update();
	  
   }
}

void MainMenu::Draw(FrameworkX::Graphics *g)
{
   if((!mI->IsActive() || (mI->IsActive() && mI->GetState()==Instructions::I_FADEOUT)) && (!mLS->IsActive() || (mLS->IsActive() && mLS->GetState()==LevelSelect::I_FADEOUT)))
   {
      if (mApp->Is3DAccelerated())
      {
	   g->TranslateF(mX,mY);
	   g->DrawImageF(IMAGE_MM_SPACE,float(-IMAGE_MM_SPACE->GetWidth()),0);
	   g->DrawImageF(IMAGE_MM_SPACE,0,0);
	   g->DrawImageF(IMAGE_MM_SPACE,float(IMAGE_MM_SPACE->GetWidth()),0);
	   g->TranslateF(-mX,-mY);
	   g->DrawImageF(IMAGE_MAIN_MENU,0,0);
      }
      else
      {
	   g->Translate(int(mX),int(mY));
	   g->DrawImage(IMAGE_MM_SPACE,-IMAGE_MM_SPACE->GetWidth(),0);
	   g->DrawImage(IMAGE_MM_SPACE,0,0);
	   g->DrawImage(IMAGE_MM_SPACE,IMAGE_MM_SPACE->GetWidth(),0);
	   g->Translate(int(-mX),int(-mY));
	   g->DrawImage(IMAGE_MAIN_MENU,0,0);
      }
   if(ButtonOverDisplayFlag)
   {
      g->SetFont(FONT_DEFAULT3);
      g->SetColor(Color::White);
      int w=FONT_DEFAULT3->StringWidth(StringToSexyString(_S(S)));
      g->DrawString(StringToSexyString(_S(S)),mWidth/2-w/2,mHeight-FONT_NGAGE2->GetHeight());
   }
   }


   if(mI->IsActive())
      mI->Draw(g);

   if(mLS->IsActive())
      mLS->Draw(g);
   
}


void MainMenu::ButtonDepress(int theId)
{
   if(theId==1)
   {
      mApp->mWidgetManager->RemoveWidget(this);
      mApp->SafeDeleteWidget(this);
      mApp->InitialiseBoard(mLevel);
	  mApp->PlaySample(SOUND_BOARDMOUSEDOWN);
   }
   if(theId==2)
   {
	   mLS->Activate();
	   this->DisableMainMenu();
   }
      
   else if(theId==3)
   {
      mI->Activate();
      this->DisableMainMenu();
   }
   else if(theId==4)
   {
      mApp->InitialiseOptionsDialog();
   }
   else if(theId==5)
   {
      mApp->mWidgetManager->RemoveWidget(this);
      mApp->SafeDeleteWidget(this);
      mApp->ExitApplication();
   }
   else if(theId==6)
   {
      mI->SetActiveScreen(IMAGE_INSTRUCTIONS_GENERAL);
   }
   else if(theId==7)
   {
       mI->SetActiveScreen(IMAGE_INSTRUCTIONS_BRICKS);
   }
   else if(theId==8)
   {
       mI->SetActiveScreen(IMAGE_INSTRUCTIONS_BONUS);
   }
   else if(theId==9)
   {
      mI->SetState(Instructions::I_FADEOUT);
      mI->SetActiveScreen(IMAGE_INSTRUCTIONS_BASE);
      this->DisableInstructionsBtns();
   }
   else if(theId==10)
   {
       mI->SetActiveScreen(IMAGE_INSTRUCTIONS_BASE);
       mI->InitialiseCredits();
   }

   else if(theId>=11 && theId<=40)
   {
	   mLevel = theId-10;
	   mLS->SetState(LevelSelect::I_FADEOUT);
	   mLS->SetActiveScreen(IMAGE_LEVEL_SELECT_BASE,0);
	   this->DisableLSB_1(5);
	   this->DisableLSB_4(5);
   }

   if(theId>=2)
	   mApp->PlaySample(SOUND_LSMOUSEDOWN);
}


void MainMenu::EnableMainMenu()
{
   mPlay->SetVisible(true);
   mChooseLevel->SetVisible(true);
   mInstructions->SetVisible(true);
   mOptions->SetVisible(true);
   mExit->SetVisible(true);
   mPlay->SetDisabled(false);
   mChooseLevel->SetDisabled(false);
   mInstructions->SetDisabled(false);
   mOptions->SetDisabled(false);
   mExit->SetDisabled(false);
}

void MainMenu::DisableMainMenu()
{
   mPlay->SetVisible(false);
   mChooseLevel->SetVisible(false);
   mInstructions->SetVisible(false);
   mOptions->SetVisible(false);
   mExit->SetVisible(false);
   mPlay->SetDisabled(true);
   mChooseLevel->SetDisabled(true);
   mInstructions->SetDisabled(true);
   mOptions->SetDisabled(true);
   mExit->SetDisabled(true);
}

void MainMenu::DisableInstructionsBtns()
{
   mI_General->SetVisible(false);
   mI_Bricks->SetVisible(false);
   mI_Bonus->SetVisible(false);
   mI_Close->SetVisible(false);
   mI_Credits->SetVisible(false);
   mI_General->SetDisabled(true);
   mI_Bricks->SetDisabled(true);
   mI_Bonus->SetDisabled(true);
   mI_Close->SetDisabled(true);
   mI_Credits->SetDisabled(true);

}

void MainMenu::EnableInstructionsBtns()
{
   mI_General->SetVisible(true);
   mI_Bricks->SetVisible(true);
   mI_Bonus->SetVisible(true);
   mI_Close->SetVisible(true);
   mI_Credits->SetVisible(true);
   mI_General->SetDisabled(false);
   mI_Bricks->SetDisabled(false);
   mI_Bonus->SetDisabled(false);
   mI_Close->SetDisabled(false);
   mI_Credits->SetDisabled(false);
}


void MainMenu::EnableLSB_1(int pI)
{
	int pIdx=0,j;
	if(pI>5)
		pIdx=5;
	else pIdx = pI;
	j=pI/5;
	for(int i=0;i<pIdx;i++)
	{
		mLS_Btns_1[i]->SetDisabled(false);
		mLS_Btns_1[i]->SetVisible(true);
	}
	if(pI>5)
	{
		EnableLSB_2((j-1)*5+pI%5);
	}

}

void MainMenu::EnableLSB_2(int pI)
{
	int pIdx=0,j;
	if(pI>5)
		pIdx=5;
	else pIdx = pI;
	j=pI/5;
	for(int i=0;i<pIdx;i++)
	{
		mLS_Btns_2[i]->SetDisabled(false);
		mLS_Btns_2[i]->SetVisible(true);
	}
	if(pI>5)
	{
		EnableLSB_3((j-1)*5+pI%5);
	}
}

void MainMenu::EnableLSB_3(int pI)
{
	int pIdx=0,j;
	if(pI>5)
		pIdx=5;
	else pIdx = pI;
	j=pI/5;
	for(int i=0;i<pIdx;i++)
	{
		mLS_Btns_3[i]->SetDisabled(false);
		mLS_Btns_3[i]->SetVisible(true);
	}

}

void MainMenu::EnableLSB_4(int pI)
{
	int pIdx=0,j;
	if(pI>5)
		pIdx=5;
	else pIdx = pI;
	j=pI/5;
	for(int i=0;i<pIdx;i++)
	{
		mLS_Btns_4[i]->SetDisabled(false);
		mLS_Btns_4[i]->SetVisible(true);
	}
	if(pI>5)
	{
		EnableLSB_5((j-1)*5+pI%5);
	}
}

void MainMenu::EnableLSB_5(int pI)
{
	int pIdx=0,j;
	if(pI>5)
		pIdx=5;
	else pIdx = pI;
	j=pI/5;
	for(int i=0;i<pIdx;i++)
	{
		mLS_Btns_5[i]->SetDisabled(false);
		mLS_Btns_5[i]->SetVisible(true);
	}
	if(pI>5)
	{
		EnableLSB_6((j-1)*5+pI%5);
	}
}


void MainMenu::EnableLSB_6(int pI)
{
	int pIdx=0,j;
	if(pI>5)
		pIdx=5;
	else pIdx = pI;
	j=pI/5;
	for(int i=0;i<pIdx;i++)
	{
		mLS_Btns_6[i]->SetDisabled(false);
		mLS_Btns_6[i]->SetVisible(true);
	}

}


void MainMenu::DisableLSB_1(int pI)
{
	for(int i=0;i<pI;i++)
	{
		mLS_Btns_1[i]->SetDisabled(true);
		mLS_Btns_1[i]->SetVisible(false);
	}
	DisableLSB_2(5);
}

void MainMenu::DisableLSB_2(int pI)
{
	for(int i=0;i<pI;i++)
	{
		mLS_Btns_2[i]->SetDisabled(true);
		mLS_Btns_2[i]->SetVisible(false);
	}
	DisableLSB_3(5);
}

void MainMenu::DisableLSB_3(int pI)
{
	for(int i=0;i<pI;i++)
	{
		mLS_Btns_3[i]->SetDisabled(true);
		mLS_Btns_3[i]->SetVisible(false);
	}
}

void MainMenu::DisableLSB_4(int pI)
{
	for(int i=0;i<pI;i++)
	{
		mLS_Btns_4[i]->SetDisabled(true);
		mLS_Btns_4[i]->SetVisible(false);
	}
	DisableLSB_5(5);
}

void MainMenu::DisableLSB_5(int pI)
{
	for(int i=0;i<pI;i++)
	{
		mLS_Btns_5[i]->SetDisabled(true);
		mLS_Btns_5[i]->SetVisible(false);
	}
	DisableLSB_6(5);
}

void MainMenu::DisableLSB_6(int pI)
{
	for(int i=0;i<pI;i++)
	{
		mLS_Btns_6[i]->SetDisabled(true);
		mLS_Btns_6[i]->SetVisible(false);
	}
}


void MainMenu::ReadLevelInfo()
{
	std::fstream f;
	f.open("LevelsInfo\\levelsinfo.bin",std::ios_base::in|std::ios_base::binary);
	if(!f)
	{
		MessageBox(mApp->mHWnd,"Level info not found","Error",NULL);
		mApp->ExitApplication();
	}
	f.read(reinterpret_cast<char*>(&mLI[0]),sizeof(mLI[0]));
	for(int i=1;i<30;i++)
		f.read(reinterpret_cast<char*>(&mLI[i]),sizeof(mLI[i]));

	f.close();
}




void MainMenu::ButtonMouseEnter(int theId)
{
   if(theId==1)
      S = "Test your skills";
    if(theId==2)
      S = "Choose an unlocked level";
   else if(theId==3)
      S = "Know about game play, bonuses and more";
   else if(theId==4)
      S = "Change Settings";
   else if(theId==5)
      S = "Go and Study";

   if(theId>=1 && theId<=5)
   {
      ButtonOverDisplayFlag = theId;	  
   }
    if(theId>=1 && theId<=10)
   {
      mApp->PlaySample(SOUND_MMOUSEOVER); 
   }
	if(theId>=11 && theId<=40)
   {
      mApp->PlaySample(SOUND_LSMOUSEOVER); 
   }
   
}

void MainMenu::ButtonMouseLeave(int theId)
{
   if(theId>=1 && theId<=5)
      ButtonOverDisplayFlag = 0;
      
}


void MainMenu::KeyUp(KeyCode theKey)
{
	if(theKey==KEYCODE_UP)
	{
		if(mLS->IsActive() && mLS->GetActivePage()==2)
		{
			mLS->SetActiveScreen(IMAGE_LEVEL_SELECT_PAGE1,1);
			this->DisableLSB_4(5);
		}
		else if(mI->IsActive() && mI->GetActiveScreen()==IMAGE_INSTRUCTIONS_BONUS_2)
		{
		   mI->SetActiveScreen(IMAGE_INSTRUCTIONS_BONUS);
		}
	}
	else if(theKey==KEYCODE_DOWN)
	{
		if(mLS->IsActive() && mLS->GetActivePage()==1)
		{
			mLS->SetActiveScreen(IMAGE_LEVEL_SELECT_PAGE2,2);
			this->DisableLSB_1(5);
		}
		else if(mI->IsActive() && mI->GetActiveScreen()==IMAGE_INSTRUCTIONS_BONUS)
		{
		   mI->SetActiveScreen(IMAGE_INSTRUCTIONS_BONUS_2);
		}
	}
}




   
  