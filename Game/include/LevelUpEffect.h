#ifndef __LEVELUPEFFECT_H__
#define __LEVELUPEFFECT_H__


#include "cGame.h"
#include "SexyAppFramework/Graphics.h"
#include "SexyAppFramework/Image.h"
#include "SexyAppFramework/SexyVector.h"
#include "SexyAppFramework/Rect.h"
#include "SexyAppFramework/ButtonListener.h"
#include "ScoreBoard.h"

namespace FrameworkX
{
	

	struct LevelUpAnim
	{
		float x,y;
		float mSpeed;
		float mFrame;
	};

	class LevelUp
	{
	
	private:
		int mState;
		Image* mImg;
		ScoreBoard* mLUSB;
		LevelUpAnim mLUA;
		bool mActive;
		bool mDone;
		bool mStartNextLevel;
		bool mVisible[6];
		bool mEnableContinueButton;
		bool mIsHighScore;
		bool mPlayHSSfx;


	public:
		enum
		{
			LU_FADEIN,
			LU_STATIONARY,
			LU_FADEOUT,
		};

		LevelUp(Image*, ScoreBoard*);
		void Init();
		void Activate();
		~LevelUp();
	
		void Draw(Graphics*);
		void Update();
		

		bool StartNextLevel()
		{
			return mStartNextLevel;
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

		bool ActivateContinueBtn()
		{
			return mEnableContinueButton;
		}

		void SetNextLevelState(bool pS)
		{
			mStartNextLevel = pS;
		}

		void SetContinueBtnState(bool pS)
		{
			mEnableContinueButton = pS;
		}


		void Deactivate()
		{
			mActive = false;
		}

		int GetState()
		{
			return mState;
		}

		bool GetIsHighScore()
		{
			return mIsHighScore;
		}

		void SetIsHighScore(bool pHS)
		{
			mIsHighScore = pHS;
			mPlayHSSfx = pHS;
		}


		
		


};
}

#endif