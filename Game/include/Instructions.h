#ifndef __INSTRUCTIONS_H__
#define __INSTRUCTIONS_H__


#include "cGame.h"
#include "SexyAppFramework/Graphics.h"
#include "SexyAppFramework/Image.h"
#include "SexyAppFramework/SexyVector.h"
#include "SexyAppFramework/Rect.h"

namespace FrameworkX
{
   class MainMenu;
	

	struct InstructionsAnim
	{
		float mSX,mSY;
		float mSpeed;
		float mFrame;
		float mX,mY;
	};



	class Instructions
	{
	
	private:
		int mState;
		Image* mImg;
		InstructionsAnim mIA;
		InstructionsAnim mIA_Brick;
		InstructionsAnim mIA_C;
		bool mActive;
		bool mEnableBtns;
		bool mBlitBrick;
		MainMenu* mMM;


	public:
		enum
		{
			I_FADEIN,
			I_STATIONARY,
			I_FADEOUT,
		};

		Instructions(Image* pImg,MainMenu*);
		void Init();
		void Activate();
		~Instructions();
	
		void Draw(Graphics*);
		void Update();
		
		bool IsActive();
		void SetActiveScreen(Image*);
		void InitialiseCredits();

		void SetState(int mS)
		{
			mState = mS;
		}

		bool ActivateBtn()
		{
			return mEnableBtns;
		}


		void SetBtnState(bool pS)
		{
			mEnableBtns = pS;
		}


		void Deactivate()
		{
			mActive = false;
		}

		int GetState()
		{
			return mState;
		}

		Image* GetActiveScreen()
		{
		   return mImg;
		}

		
		


};
}

#endif