#ifndef _LOGOSCREEN_H_
#define _LOGOSCREEN_H_

#include "SexyAppFramework/Widget.h"


namespace FrameworkX
{
   class cGame;
   class Graphics;
   class WidgetManager;
   class HyperlinkWidget;

   class LogoScreen: public Widget
   {
      private:
		  cGame* mApp;
		  float mX1,mY1,mFrame;
		  int mR;
		  bool mFadeIn,mFadeOut,mStationary;;
	

      public:
	 LogoScreen(cGame*);
	 ~LogoScreen();
	 void Draw(Graphics* g);
	 void UpdateF(float);
	 void CheckRectMotion(int&,int&,int&);
	 virtual void KeyDown(KeyCode theKey);
	
   };
}




#endif 