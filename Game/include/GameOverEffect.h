#ifndef __GAMEOVEREFFECT_H__
#define __GAMEOVEREFFECT_H__


#include "cGame.h"
#include "SexyAppFramework/Graphics.h"
#include "SexyAppFramework/Image.h"
#include "SexyAppFramework/SexyVector.h"
#include "SexyAppFramework/Rect.h"
#include "SexyAppFramework/ButtonListener.h"
#include "ScoreBoard.h"

namespace FrameworkX
{
	

	struct GameOverAnim
	{
		float x,y;
		float mSpeed;
		float mFrame;
	};

	class GameOver
	{
	
	private:
		int mState;
		Image* mImg;
		GameOverAnim mGOA;
		bool mActive;
		bool mDone;
		bool mRestartLevel;
		bool mStartNewGame;
		bool mQuitGame;
		bool mEnableBtns;


	public:
		enum
		{
			GO_FADEIN,
			GO_STATIONARY,
			GO_FADEOUT,
		};

		GameOver(Image*);
		void Init();
		void Activate();
		~GameOver();
	
		void Draw(Graphics*);
		void Update();
		

		bool RestartLevel()
		{
			return mRestartLevel;
		}

		bool StartNewGame()
		{
			return mStartNewGame;
		}
		bool QuitGame()
		{
			return mQuitGame;
		}

		bool IsDone()
		{
			return mDone;
		}
		bool IsActive();

		void SetState(int mS)
		{
			mState = mS;
		}

		bool GetButtonsState()
		{
			return mEnableBtns;
		}

		void SetRestartLevelstate(bool pS)
		{
			mRestartLevel = pS;
		}
		void SetNewGameState(bool pS)
		{
			mStartNewGame = pS;
		}

		void SetQuitGameState(bool pS)
		{
			mQuitGame = pS;
		}

		void SetButtonsState(bool pS)
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

		
		


};
}

#endif