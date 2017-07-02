#ifndef __LOADINGSCREEN_H__
#define __LOADINGSCREEN_H__

#include "SexyAppFramework/Widget.h"
#include "SexyAppFramework/ButtonListener.h"
#include "SexyAppFramework/ButtonWidget.h"

namespace FrameworkX
{  
	class cGame;
    class Graphics;
    class WidgetManager;

   class LoadingScreen: public Widget, public ButtonListener
   {
   private:
	   cGame* mApp;
	   ButtonWidget* mContinueBtn;
	  

   public:
	   LoadingScreen(cGame*);
	   ~LoadingScreen();
	   void Draw(Graphics* g);
	   void Update();
	   virtual void ButtonDepress(int);
	   void LoadingComplete();
   };
}




#endif 