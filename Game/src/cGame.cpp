#include "cGame.h"
#include "LogoScreen.h"
#include "LoadingScreen.h"
#include "Board.h"
#include "MainMenu.h"
#include "OptionsDialog.h"
#include "Res.h"
#include "SexyAppFramework/WidgetManager.h"
#include "SexyAppFramework/SWTri.h"

#include "SexyAppFramework/Checkbox.h"

// We will be accessing the resource manager in this demo, so include it's header
#include "SexyAppFramework/ResourceManager.h"

// Required for playing music
#include "SexyAppFramework/BassMusicInterface.h"

// Contains all the resources from the resources.xml file in our
// properties directory. See that file for more information.
#include "Res.h"
#include "SexyAppFramework/Dialog.h"


using namespace FrameworkX;

cGame::cGame()
{
   
	mProdName = "SmashOut";	
	mProductVersion = "1.0";	
	mTitle = StringToSexyStringFast("SmashOut: v" +  mProductVersion);
	mRegKey = "Games\\DreamCoders\\SmashOut";
	mWidth = 800;
	mHeight = 600;
	mAutoEnable3D = true;
	mBoard = NULL;
	mLoadingScreen = NULL;
	mMainMenu=NULL;
	SWTri_AddAllDrawTriFuncs();
	mNoSoundNeeded=false; 
	mVSyncUpdates = true;
	mWaitForVSync=true;  //Don't update the display until the screen refreshes. 
	mSoftVSyncWait=false; //We set this flag to stop shearing in windows mode  
	mLogoScreen = false;


}

cGame::~cGame()
{
   if (mBoard != NULL)
   {
	   mWidgetManager->RemoveWidget(mBoard);   
	   delete mBoard;
   }
   if (mLoadingScreen != NULL)
   {
	   mWidgetManager->RemoveWidget(mLoadingScreen);
	   delete mLoadingScreen;
   }
   if (mMainMenu != NULL)
   {
	   mWidgetManager->RemoveWidget(mMainMenu);
	   delete mMainMenu;
   }
   if(mOptions!=NULL)
   {
	   mWidgetManager->RemoveWidget(mOptions);
	   delete mOptions;
   }
   

   if(mLogo!=NULL)
   {
	   mWidgetManager->RemoveWidget(mLogo);
	   delete mLogo;
   }

   mResourceManager->DeleteResources("");
}


void cGame::Init()
{
   SexyAppBase::Init();

   mWidgetManager->mDefaultBelowModalFlagsMod.mRemoveFlags |= WIDGETFLAGS_UPDATE;

   LoadResourceManifest();
   if (!mResourceManager->LoadResources("Init"))
	{
		mLoadingFailed = true;
		ShowResourceError(true); //true if error in main thread
		return;
	}

   if (!ExtractInitResources(mResourceManager))
	{
		mLoadingFailed = true;
		ShowResourceError(true);
		return;
	}


   InitialiseLogoScreen();
   mMusicInterface->LoadMusic(2, "music/Flanging-synth-01.wav");
      
   while(mLogoScreen)
   {
	   UpdateApp(); 
   }

   RemoveLogoScreen();
   
   
   if (!mResourceManager->LoadResources("TitleScreen"))
	{
		mLoadingFailed = true;
		ShowResourceError(true);
		return;
	}
   if (!ExtractTitleScreenResources(mResourceManager))
	{
		mLoadingFailed = true;
		ShowResourceError(true);
		return;
	}

   mLoadingScreen= new LoadingScreen(this);
   mLoadingScreen->Resize(0, 0, mWidth, mHeight);
   mWidgetManager->AddWidget(mLoadingScreen);

   
 
   mMusicInterface->LoadMusic(0,"music/Eclipse.mp3");

   mMusicInterface->LoadMusic(1, "music/music 11.ogg");

	
   
   //to smoothly fadein the song
   mMusicInterface->FadeIn(0, 0, 0.002, false);
   
   //No. of resources for loading thread to display the loading bar
   mNumLoadingThreadTasks = mResourceManager->GetNumResources("Game");

}


void cGame::LoadingThreadProc()
{
   mResourceManager->StartLoadResources("Game");
   
   while(mResourceManager->LoadNextResource())
   {
      mCompletedLoadingThreadTasks++;  //tracks the no. of completed tasks and gives the percentage of loading bar
      if(mShutdown)                    //in case of error this variable is automatically set to True
		  return;

     
   }

   if (mResourceManager->HadError() || !ExtractGameResources(mResourceManager))
	{		
		ShowResourceError(false);
		mLoadingFailed = true;
		return;
	}
	
}


void cGame::LoadingThreadCompleted()
{
   SexyAppBase::LoadingThreadCompleted();
   
   if(mLoadingFailed)             //in case of error just return
      return;

   mLoadingScreen->LoadingComplete();
}

void cGame::InitialiseBoard(int pLevel)
{
	//stop the intro song
   mMusicInterface->FadeOut(0,true,0.002);
   
   //fade in the game music

   mMusicInterface->FadeIn(1, -1, 0.002, false);
   mMainMenu = NULL;
   mBoard = new Board(this,pLevel);
   mBoard->Resize(0,0,mWidth,mHeight);
   mWidgetManager->AddWidget(mBoard);
   mWidgetManager->SetFocus(mBoard);
}


void cGame::InitialiseLogoScreen()
{
   mLogo=new LogoScreen(this);
   mLogo->Resize(0,0,mWidth,mHeight);
   mWidgetManager->AddWidget(mLogo);
   mWidgetManager->SetFocus(mLogo);
   mLogoScreen=true;
   mMusicInterface->PlayMusic(2,0);
   SetCursor(CURSOR_NONE);
}


void cGame::RemoveLogoScreen()
{
   mWidgetManager->RemoveWidget(mLogo);
   SafeDeleteWidget(mLogo);
   mLogo=NULL;
   mMusicInterface->StopMusic(2);
   SetCursor(CURSOR_POINTER);
  
}




void cGame::LoadingScreenFinished()
{  
   //remove LoadingScreen
   mLoadingScreen = NULL;
   mResourceManager->DeleteResources("LoadingScreen");
   
   //add mainmenu
   InitialiseMainMenu();

}
//
void cGame::SwitchScreenMode(bool wantWindowed, bool is3d)
{
	// Let the app handle the actual details of this call...
	SexyAppBase::SwitchScreenMode(wantWindowed, is3d);

	// We can see if the options dialog is up with a call to
	// GetDialog. You pass GetDialog the unique ID of the dialog box,
	// and if it exists it is returned to you, otherwise NULL is returned.
	OptionsDialog* d = (OptionsDialog*) GetDialog(OptionsDialog::DIALOG_ID);

	// Set the checkbox state to our windowed state
	if ((d != NULL) && (d->mFSCheckbox != NULL))      //in case user uses ALT+Return to switch screen mode
		d->mFSCheckbox->SetChecked(!wantWindowed);

}


void cGame::DialogButtonDepress(int dialog_id, int button_id)
{
   if(dialog_id==OptionsDialog::MESSAGE_BOX_ID)
      if(button_id == Dialog::ID_OK)
		  SexyAppBase::KillDialog(dialog_id);

   if(dialog_id==OptionsDialog::DIALOG_ID)
      if(button_id==Dialog::ID_FOOTER)
      {
		  SwitchScreenMode(!mOptions->mFSCheckbox->mChecked, mOptions->m3DCheckbox->mChecked);
		  SexyAppBase::KillDialog(dialog_id);
      }

  if(dialog_id==2)
  {
	  if(button_id==Dialog::ID_OK)
	  {
		  mWidgetManager->RemoveWidget(mBoard);
		  SafeDeleteWidget(mBoard);
		  InitialiseMainMenu();
		  PlaySample(SOUND_BOARDMOUSEDOWN);
		  KillDialog(dialog_id);

	  }

	  else if(button_id==Dialog::ID_CANCEL)
	  {
		  KillDialog(dialog_id);
		  SetCursor(CURSOR_NONE);
	  }
  
  }
}
//
//
void cGame::InitialiseMainMenu()
{
	//stop the intro song
	if(mMusicInterface->IsPlaying(1))
		mMusicInterface->FadeOut(1);
   
   //fade in the game music

   mMusicInterface->FadeIn(0,-1, 0.004, false);
   
   mMainMenu = new MainMenu(this);
   mMainMenu->Resize(0,0,mWidth,mHeight);
   mWidgetManager->AddWidget(mMainMenu);
   mWidgetManager->SetFocus(mMainMenu);
   mBoard = NULL;
}

//
//
void cGame::InitialiseOptionsDialog()
{
   mOptions = new OptionsDialog("Options"," ");
   mOptions->Resize(250,150,300,400);
   AddDialog(OptionsDialog::DIALOG_ID,mOptions);

}
//
//
Dialog* cGame::NewDialog(Image* theDialogImage, Image* theButtonImage,int theDialogId, bool isModal, const SexyString& theDialogHeader, const SexyString& theDialogLines, const SexyString& theDialogFooter, int theButtonMode)
{
	Dialog* aDialog =new Dialog(theDialogImage,theButtonImage, theDialogId, isModal,theDialogHeader,theDialogLines,theDialogFooter,theButtonMode); 
	AddDialog(theDialogId, aDialog);
	aDialog->SetColor(theDialogId, Color::White);
	aDialog->SetHeaderFont(FONT_DEFAULT3);
	aDialog->SetLinesFont(FONT_DEFAULT3);
	aDialog->SetButtonFont(FONT_DEFAULT3);
	return aDialog;
}


//

