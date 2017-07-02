#include "LogoScreen.h"
#include "cGame.h"
#include "Res.h"
#include "SexyAppFramework/Font.h"
#include "SexyAppFramework/Graphics.h"
#include "SexyAppFramework/Image.h"
#include "SexyAppFramework/WidgetManager.h"
#include "SexyAppFramework/Rect.h"
#include "SexyAppFramework/HyperlinkWidget.h"
#include "SexyAppFramework/SexyMatrix.h"



using namespace FrameworkX;


LogoScreen::LogoScreen(cGame *theApp)
{
   mApp=theApp;
   mWidth=800;
   mHeight=600;
   mFadeIn=true;
   mFadeOut=false;
   mStationary = false;
   mX1 = 0;
   mY1 = 0;
   mR=0;
   mFrame = 0;
   
   mWidgetFlagsMod.mAddFlags = WIDGETFLAGS_MARK_DIRTY;
}

LogoScreen::~LogoScreen()
{
	
}



void LogoScreen::Draw(Graphics *g)
{
	
	g->PushState();
	
	g->SetColorizeImages(true);
	g->SetColor(Color(mR,mR,mR));
	
	
	g->DrawImageF(IMAGE_LOGO,0,0);
	
	
	g->PopState();

}

void LogoScreen::UpdateF(float theFrac)
{
	if(mFadeIn)
	{
		if(mR++>254)
		{
			mR=255;
			mFadeIn=false;
			mStationary=true;
			mFrame = 0;
		}
	}
	else if(mStationary)
	{
		mFrame++;
		if(mFrame>=50)
		{
			mStationary=false;
			mFadeOut = true;
		}

	}
	else if(mFadeOut)
	{
		if(mR--<3)
		{
			mFadeOut=false;
			mApp->mLogoScreen=false;
		}
	}
}
			

 

   
void LogoScreen::KeyDown(FrameworkX::KeyCode theKey)
{
	if(theKey==KEYCODE_RETURN)
		mApp->mLogoScreen=false;

}



   