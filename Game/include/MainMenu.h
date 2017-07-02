#ifndef _MAIN_MENU_H_
#define _MAIN_MENU_H_

#include "SexyAppFramework/Widget.h"
#include "SexyAppFramework/ButtonListener.h"
#include "Res.h"


namespace FrameworkX
{
   class cGame;
   class Graphics;
   class WidgetManager;
   class ButtonWidget;
   class Instructions;
   class LevelSelect;

   struct LevelInfo
   {
	   int Level;
	   int Points;
	   int Open;
   };

   class MainMenu:public Widget, public ButtonListener
   {
   protected:
      ButtonWidget* mPlay;
      ButtonWidget* mChooseLevel;
      ButtonWidget* mInstructions;
      ButtonWidget* mOptions;
      ButtonWidget* mExit;
      cGame* mApp;
      float mX,mY;
      int mLevel;

      Instructions* mI;
      ButtonWidget* mI_General;
      ButtonWidget* mI_Bricks;
      ButtonWidget* mI_Bonus;
      ButtonWidget* mI_Close;
      ButtonWidget* mI_Credits;

      LevelSelect* mLS;
      ButtonWidget* mLS_Btns_1[5];
      ButtonWidget* mLS_Btns_2[5];
      ButtonWidget* mLS_Btns_3[5];
      ButtonWidget* mLS_Btns_4[5];
      ButtonWidget* mLS_Btns_5[5];
      ButtonWidget* mLS_Btns_6[5];

      LevelInfo mLI[30];


   
   public:
      MainMenu(cGame*);
      ~MainMenu();
      void Update();
      void Draw(Graphics* g);
      virtual void ButtonDepress(int theId);
      virtual void KeyUp(KeyCode theKey);

      void DisableMainMenu();
      void EnableMainMenu();

      void EnableInstructionsBtns();
      void DisableInstructionsBtns();

      void EnableLSB_1(int);
      void EnableLSB_2(int);
      void EnableLSB_3(int);
      void EnableLSB_4(int);
      void EnableLSB_5(int);
      void EnableLSB_6(int);
      void DisableLSB_1(int);
      void DisableLSB_2(int);
      void DisableLSB_3(int);
      void DisableLSB_4(int);
      void DisableLSB_5(int);
      void DisableLSB_6(int);

      void ReadLevelInfo();
      
      virtual void ButtonMouseEnter(int);
      virtual void ButtonMouseLeave(int);
   };
}

#endif