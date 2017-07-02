#ifndef __BOARD_H__
#define __BOARD_H__

#include "SexyAppFramework/Widget.h"
#include "SexyAppFramework/Image.h"
#include "ScoreBoard.h"
#include "cGame.h"
#include "cSprite.h"
#include "Ball.h"
#include "Paddle.h"
#include "BrickManager.h"
#include "ExplosionManager.h"
#include "BonusManager.h"
#include "LevelUpEffect.h"
#include "GameOverEffect.h"
#include "SexyAppFramework/ButtonWidget.h"
#include "SexyAppFramework/SoundInstance.h"

#include <fstream>

namespace FrameworkX
{
   class Graphics;
   class cGame;
   class Ball;
   class Image;
   class Paddle;

   struct Star
   {
	   float X,Y;
	   float Speed;
	   float Frame;
	   int R;
	   bool Increasing;
   };

   struct SpaceBody
   {
	   Image* mImg;
	   float X,Y;
	   float Speed;
	   float Frame;
   };


class Board : public Widget,ButtonListener
{

	private:

		cGame*	mApp;
		Ball* mBall;
		Paddle* mPaddle;
		BrickManager* mBM;
		ExplosionManager* mEM;
		BonusManager* mBOM;
		ScoreBoard* mSB;
		LevelUp* mLU;
		GameOver* mGO;
		Star mStarField[30];
		SpaceBody* mSpaceBody;
		bool mSBActive;
		Image* SpaceBodies[7];
		int mLevel;
		int mPreLevel;
		int mMaxLevels;
		Ball* mBallBonus_1;
		Ball* mBallBonus_2;
		Ball* mBallBonus_3;
		int mNumBalls;
		float mX,mY;
		Image* mBg;
		int mOldMouseX;
		int mOldMouseY;
		int mMouseY;
		int mMouseX;
		bool mWriteLevelInfoDone;
		ButtonWidget* mContinueButton;
		ButtonWidget* mRestartButton;
		ButtonWidget* mStartNewGameBtn;
		ButtonWidget* mQuitGameBtn;
		SpecialEffects mBlackScreen;
		

public:
	    
        SoundInstance* mLaserSfx;

		Board(cGame* theApp,int);

		virtual ~Board();

		virtual void Draw(Graphics* g);

		virtual void UpdateF(float theFrac);
		virtual void Update();
		void CollisionBallBricks();
		void CollsionBrickMissile();
		void CollisionLaserBrick();
		void CollisionBonusPaddle();
		void CollisionBrickMissilePaddle();
		void AssignPaddlePowers(Bonus*);
		void InitiateLevel(int pL);
		void ReadLevelFiles(int LevelMap[][8],int BonusMap[][8],int);
		void UpdateStarField(float pFrac);
		void UpdateSpaceBody(float pFrac);
		void DrawStarField(Graphics*);
		void DrawSpaceBody(Graphics*);
		void WriteLevelInfo();
		void UpdateBlackScreen();
		void ActivateBlackScreen();
		void DeactivateBlackScreen();
		virtual void MouseMove(int, int);
		virtual void MouseDown(int,int,int,int);
		virtual void MouseDrag(int,int);
		virtual void MouseUp(int,int,int,int);
		virtual void KeyDown(KeyCode theKey);
		virtual void ButtonDepress(int pBtnId);
		virtual void ButtonMouseEnter(int);
		SoundInstance* GetLaserSFX();
		//virtual void KeyUp(KeyCode theKey);

};


}

#endif // __BOARD_H__