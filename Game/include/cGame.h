#ifndef _CGAME_H_
#define _CGAME_H_

#include "SexyAppFramework/XAppBase.h"
#include <STDLIB.H>
#include<string>

namespace FrameworkX
{
	class LogoScreen;
	class Board;
	class LoadingScreen;
	class MainMenu;
	class OptionsDialog;

   class cGame:public SexyAppBase
   {
   private:
      Board* mBoard;
      LogoScreen* mLogo;
      LoadingScreen* mLoadingScreen;
      OptionsDialog* mOptions;
      MainMenu* mMainMenu;

	  

   public:
      bool mLogoScreen;
      
      cGame();
      ~cGame();
      virtual void Init();
      virtual void LoadingThreadProc();
      virtual void LoadingThreadCompleted();
      void InitialiseLogoScreen();
      void RemoveLogoScreen();

      void InitialiseBoard(int);
	 
      
      void LoadingScreenFinished();
      void InitialiseMainMenu();
      void InitialiseOptionsDialog();
	  //void InitialiseEndScreen();
      virtual void SwitchScreenMode(bool wantWindowed, bool is3d);
      virtual void DialogButtonDepress(int dialog_id, int button_id);
      virtual Dialog* NewDialog(Image*, Image*,int theDialogId, bool isModal, const SexyString& theDialogHeader, const SexyString& theDialogLines, const SexyString& theDialogFooter, int theButtonMode);		 
      void ExitApplication()
      {
	 exit(0);
      }
   };
}

#endif _cGAME_H_