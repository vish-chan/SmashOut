#include "LoadingScreen.h"
#include "cGame.h"
#include "Res.h"
#include "SexyAppFramework/Font.h"
#include "SexyAppFramework/Graphics.h"
#include "SexyAppFramework/Image.h"
#include "SexyAppFramework/WidgetManager.h"
#include "SexyAppFramework/Rect.h"
#include "SexyAppFramework/SexyMatrix.h"


using namespace FrameworkX;


int color_alt=50,alt_factor=1;
int BtnColors[3][3] = {{250,250,250},{255,255,255},{220,220,220}};

LoadingScreen::LoadingScreen(cGame *theApp)
{
   mApp=theApp;
   mWidgetFlagsMod.mAddFlags = WIDGETFLAGS_MARK_DIRTY;
   
   
   //adding Button widget to titlescreen childwidget list
   int width =IMAGE_LU_BTN_NORMAL->GetWidth();
   int height =IMAGE_LU_BTN_NORMAL->GetHeight();

   mContinueBtn = new ButtonWidget(1, this);
   mContinueBtn->SetFont(FONT_DEFAULT);
   mContinueBtn->mLabel = _S("START");
   mContinueBtn->SetColors(BtnColors, 3);
   mContinueBtn->Resize(mApp->mWidth / 2 - width / 2, mApp->mHeight - height - 80, width, height);
   mContinueBtn->mOverImage = IMAGE_LU_BTN_OVER;
   mContinueBtn->mDownImage = IMAGE_LU_BTN_NORMAL;
   mContinueBtn->mButtonImage = IMAGE_LU_BTN_NORMAL;
   mContinueBtn->SetVisible(false);
   mContinueBtn->SetDisabled(true);
   AddWidget(mContinueBtn);
   
}

LoadingScreen::~LoadingScreen()
{
   RemoveAllWidgets();
   delete mContinueBtn;
}



void LoadingScreen::Draw(Graphics *g)
{
	Transform t;

	// for black/white,use Color::Black and Color::White.
   g->DrawImageF(IMAGE_TITLE_SCREEN,0,0);
   int loaderBarWidth = IMAGE_LOADER_BAR->GetWidth();
   float ScaleX = float((mApp->GetLoadingThreadProgress()));
   float DrawWidth = ScaleX*loaderBarWidth;
   t.Scale(ScaleX,1);
   g->DrawImageF(IMAGE_LOADER_BAR_BASE, float(mWidth / 2 - loaderBarWidth / 2),400.0F);
	if (DrawWidth > 0)
	{
		g->DrawImageTransformF(IMAGE_LOADER_BAR,t,float(mWidth / 2 - loaderBarWidth / 2 + DrawWidth/2),400.0F+(IMAGE_LOADER_BAR->GetHeight()*1.0F)/2); 
	}

	// If our button widget is false, let's instead draw some
	// "Loading" text (er, actually in this case it's an image) where
	// it is located.
	if (mContinueBtn->mVisible == false)
	{
		g->PushState();
		g->SetColorizeImages(true);
		g->SetColor(Color(color_alt,color_alt,color_alt));
		g->DrawImage(IMAGE_LOADER_LOADINGTXT, mWidth/2-IMAGE_LOADER_LOADINGTXT->GetWidth()/2 , mContinueBtn->mY-40 );
		g->PopState();
	}


}

void LoadingScreen::Update()
{
   color_alt=(alt_factor+color_alt)%221;
   if(color_alt==220 && alt_factor)
	   alt_factor = -1;
   else if(color_alt==50 && alt_factor==-1)
	   alt_factor=1;
}
 

   

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void LoadingScreen::LoadingComplete()
{
	mContinueBtn->SetVisible(true);
	mContinueBtn->SetDisabled(false);
}

void LoadingScreen::ButtonDepress(int theId)
{
	if (theId == 1)
	{
		mApp->mWidgetManager->RemoveWidget(this);
		mApp->SafeDeleteWidget(this);
		
		// Now let's tell the game app that it's ok to add the board widget:
		mApp->LoadingScreenFinished();
		mApp->PlaySample(SOUND_CONTINUE);
	}
}
