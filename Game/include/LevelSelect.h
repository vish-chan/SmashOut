#ifndef __LEVELSELCT_H__
#define __LEVELSELECT_H__


#include "cGame.h"
#include "MainMenu.h"
#include "SexyAppFramework/Graphics.h"
#include "SexyAppFramework/Image.h"
#include "SexyAppFramework/SexyVector.h"
#include "SexyAppFramework/Rect.h"

namespace FrameworkX
{
   class MainMenu;
	

	struct LevelSelectAnim
	{
		float mSX,mSY;
		float mSpeed;
		float mFrame;
		float mX,mY;
	};


	class LevelSelect
	{
	
	private:
		int mState;
		Image* mImg;
		LevelSelectAnim mIA;
		bool mActive;
		bool mEnableBtns_1;
		bool mEnableBtns_2;
		int mActivePage;
		int mMaxAllowedLevel;
		MainMenu* mMM;
		LevelInfo mLS_LI[30];


	public:
		enum
		{
			I_FADEIN,
			I_STATIONARY,
			I_FADEOUT,
		};

		LevelSelect(Image* pImg,MainMenu*, LevelInfo pLI[30]);
		void Init();
		void Activate();
		~LevelSelect();
	
		void Draw(Graphics*);
		void Update();
		
		bool IsActive();
		void SetActiveScreen(Image*,int);

		void SetState(int mS)
		{
			mState = mS;
		}

		bool ActivateBtnPage1()
		{
			return mEnableBtns_1;
		}

		bool ActivateBtnPage2()
		{
			return mEnableBtns_2;
		}



		void SetBtnState(bool pS,int pPage)
		{
			if(pPage==1)
				mEnableBtns_1 = pS;
			else if(pPage==2)
				mEnableBtns_2=pS;
		}


		void Deactivate()
		{
			mActive = false;
		}

		int GetState()
		{
			return mState;
		}

		int GetActivePage()
		{
			return mActivePage;
		}

		
		


};
}

#endif