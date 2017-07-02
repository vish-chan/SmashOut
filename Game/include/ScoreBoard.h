#ifndef __SCOREBOARD_H__
#define __SCOREBOARD_H__


#include "SexyAppFramework/Graphics.h"
#include "SexyAppFramework/Image.h"
#include "SexyAppFramework/Rect.h"
#include "SexyAppFramework/Color.h"
#include "cGame.h"


namespace FrameworkX
{
	class Graphics;

	class ScoreBoard
	{
	private:
		int mPoints;
		int mGreenGems;
		int mRedGems;
		int mBlueGems;
		int mMissiles;
		int mLasers;
		int mCurMissiles;
		int mCurLasers;
		int mCurLives;
		int mExtraBonuses;
		cGame* mApp;
		Image* mScoreBoardBG;
		bool mFireBall;
	public:
		ScoreBoard(int,cGame*);
		~ScoreBoard();
		void Draw(Graphics*);
		void Update();

		int GetGreenGems()
		{
			return mGreenGems;
		}
		int GetRedGems()
		{
			return mRedGems;
		}
		int GetBlueGems()
		{
			return mBlueGems;
		}
		int GetMissiles()
		{
			return mMissiles;
		}
		int GetLasers()
		{
			return mLasers;
		}
		int GetPoints()
		{
			return mPoints;
		}

		void SetGreenGems(int pGG)
		{
			mGreenGems+=pGG;
		}

		void SetRedGems(int pRG)
		{
			mRedGems += pRG;
		}
		void SetBlueGems(int pBG)
		{
			mBlueGems += pBG;
		}

		void SetMissiles(int pM)
		{
			mMissiles +=pM;
		}

		void SetLasers(int pL)
		{
			mLasers+=pL;
		}

		void SetPoints(int pP)
		{
			mPoints+=pP;
		}

		void SetCurMissiles(int pM)
		{
			mCurMissiles=pM;
		}
		void SetCurLasers(int pL)
		{
			mCurLasers=pL;
		}
		void SetCurLives(int pL)
		{
			mCurLives=pL;
		}
		void SetFireBall(bool pFM)
		{
			mFireBall = pFM;
		}

		void ClearForNextLevel(int RestartFlag);

	};
}
#endif


	