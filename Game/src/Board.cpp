#include "Board.h"
#include "Ball.h"
#include "Res.h"
#include "Paddle.h"
#include "Brick.h"
#include "MainMenu.h"
#include "SexyAppFramework/Font.h"
#include "SexyAppFramework/Graphics.h"
#include "SexyAppFramework/Image.h"
#include "SexyAppFramework/WidgetManager.h"
#include "SexyAppFramework/Widget.h"
#include "SexyAppFramework/Dialog.h"
#include "SexyAppFramework/SoundManager.h"
#include "SexyAppFramework/MusicInterface.h"
#include<sstream>
#include<STDLIB.h>
#include<time.h> 


using namespace FrameworkX;


#define MAX_SIZE 30
#define WIDTH 650
#define HEIGHT 600

int ButtonColors[3][3] = {{250,250,250},{255,255,255},{220,220,220}};
int LevelUpDelay = 0,GameOverDelay=0,ResetPosDelay=0;

LevelInfo S,A[30];
Dialog* mD;


Board::Board(cGame* theApp,int pLevel)
{

	mApp = theApp;
  //-------------------Code for paddle-----------------------------
	mOldMouseX=mApp->mWidgetManager->mLastMouseX; //Gets current mouse X pos 
    mOldMouseY=mApp->mWidgetManager->mLastMouseY; //Gets current mouse Y pos 
    mMouseX=mOldMouseX; 
    mMouseY=mOldMouseY; 
 //-----------------------------------------------------------------

 //--------------------Code for Brick Manager-----------------------
	Image* pImage[6];
	pImage[0]=IMAGE_BRICK_SILVER;
	pImage[1]=IMAGE_BRICK_LASER;
	pImage[2]=IMAGE_BRICK_RED;
	pImage[3] = IMAGE_BRICK_BLACK;
	pImage[4] = IMAGE_BRICK_GOLD;
	pImage[5] = IMAGE_BRICK_T_UNLOCKED;
//------------------------------------------------------------------

//-------------------Code for Explosion Manager---------------------
	Image* pExImg[4];
	pExImg[0]=IMAGE_EXPLOSION2;
	pExImg[1]=IMAGE_FIRE_EXPLOSION;
	pExImg[2]=IMAGE_WAVE_DES;
	pExImg[3] = IMAGE_EXPLOSION3;
//--------------------------------------------------------------------


//------------------Code for Bonus Manageer---------------------------
	Image* pBoImg[11];
	pBoImg[0] = IMAGE_BONUS_REDGEM; 
	pBoImg[1] = IMAGE_BONUS_GREENGEM;   
	pBoImg[2] = IMAGE_BONUS_BLUEGEM;  
	pBoImg[3] = IMAGE_BONUS_MISSILE;   
	pBoImg[4] = IMAGE_BONUS_FIRE;
	pBoImg[5] = IMAGE_BONUS_BOTTOM_BLOCK;
	pBoImg[6] = IMAGE_BONUS_LASER;
	pBoImg[7] = IMAGE_BONUS_LIFE;
	pBoImg[8] = IMAGE_BONUS_BLACK_SCREEN;
	pBoImg[9] = IMAGE_BONUS_BLINKING_BALL;
	pBoImg[10] = IMAGE_BONUS_REVERSE_MOTION;
	
//---------------------------------------------------------------------

	SpaceBodies[0]=IMAGE_PLANET_1;
	SpaceBodies[1]=IMAGE_PLANET_2;
	SpaceBodies[2]=IMAGE_PLANET_3;
	SpaceBodies[3]=IMAGE_PLANET_4;
	SpaceBodies[4]=IMAGE_PLANET_5;
	SpaceBodies[5]=IMAGE_PLANET_6;
	SpaceBodies[6]=IMAGE_GALAXY;






	mLevel = pLevel;
	mPreLevel = mLevel;
	mMaxLevels = 30;
	mBall = new Ball(IMAGE_DISC,SexyVector2(float(mApp->mWidth/2),float(mApp->mHeight-IMAGE_PLAYER->GetHeight()-IMAGE_DISC->GetHeight()/2)),FRect(0,0,34,34),10,SexyVector2(0,0),4,false, Rect(0,0,650,600),4,6,15,mApp);
	mPaddle = new Paddle(this, IMAGE_PLAYER,SexyVector2(float(mApp->mWidth/2),float(mApp->mHeight-IMAGE_PLAYER->GetHeight()/2)),FRect(mApp->mWidth/2-IMAGE_PLAYER->GetWidth()/2,mApp->mHeight-IMAGE_PLAYER->GetHeight(),IMAGE_PLAYER->GetWidth(),IMAGE_PLAYER->GetHeight()),0, SexyVector2(0,0),20, true, Rect(0,0,650,600), 20, theApp, true,mMouseX,mMouseY);
	mBM = new BrickManager(pImage);
	mEM = new ExplosionManager(pExImg);
	mBOM = new BonusManager(pBoImg);
	mSB = new ScoreBoard(0,mApp);
	mLU = new LevelUp(IMAGE_LEVELUP_SCREEN,mSB);
	mGO = new GameOver(IMAGE_END_SCREEN);
	mSpaceBody=new SpaceBody();
	mSBActive = false;
	mY=0;
	mX=0;
	mBg=IMAGE_SPACE_BG;
	mNumBalls=1;
	mBallBonus_1 = NULL;
	mBallBonus_2 = NULL;
	mBallBonus_3 = NULL;
	mWriteLevelInfoDone=false;
	mLaserSfx = mApp->mSoundManager->GetSoundInstance(SOUND_LASERSFX);


	

	mWidgetFlagsMod.mAddFlags = WIDGETFLAGS_MARK_DIRTY;

	//-------Creating btns for Levelup and Gameover Screens--------------

	int width =IMAGE_LU_BTN_NORMAL->GetWidth();
	int height =IMAGE_LU_BTN_NORMAL->GetHeight();
	
	mContinueButton = new ButtonWidget(1, this);
    mContinueButton->SetFont(FONT_DEFAULT);
    mContinueButton->mLabel = _S("Continue");
    mContinueButton->SetColors(ButtonColors, 3);
	mContinueButton->Resize(mApp->mWidth/2-width/2-5,mApp->mHeight-height-45,width, height);
    mContinueButton->mOverImage = IMAGE_LU_BTN_OVER;
    mContinueButton->mDownImage = IMAGE_LU_BTN_NORMAL;
    mContinueButton->mButtonImage = IMAGE_LU_BTN_NORMAL;
    AddWidget(mContinueButton);


	mRestartButton = new ButtonWidget(2, this);
	mRestartButton->SetFont(FONT_DEFAULT);
    mRestartButton->mLabel = _S("Restart");
    mRestartButton->SetColors(ButtonColors, 3);
	mRestartButton->Resize(mApp->mWidth/2-width/2-5, 250,width, height);
    mRestartButton->mOverImage = IMAGE_LU_BTN_OVER;
    mRestartButton->mDownImage = IMAGE_LU_BTN_NORMAL;
    mRestartButton->mButtonImage = IMAGE_LU_BTN_NORMAL;
    AddWidget(mRestartButton);

	mStartNewGameBtn = new ButtonWidget(3, this);
	mStartNewGameBtn->SetFont(FONT_DEFAULT);
    mStartNewGameBtn->mLabel = _S("New Game");
    mStartNewGameBtn->SetColors(ButtonColors, 3);
	mStartNewGameBtn->Resize(mApp->mWidth/2-width/2-5, 270+height,width, height);
    mStartNewGameBtn->mOverImage = IMAGE_LU_BTN_OVER;
    mStartNewGameBtn->mDownImage = IMAGE_LU_BTN_NORMAL;
    mStartNewGameBtn->mButtonImage = IMAGE_LU_BTN_NORMAL;
	AddWidget(mStartNewGameBtn);


	mQuitGameBtn = new ButtonWidget(4, this);
	mQuitGameBtn->SetFont(FONT_DEFAULT);
    mQuitGameBtn->mLabel = _S("QUIT");
    mQuitGameBtn->SetColors(ButtonColors, 3);
	mQuitGameBtn->Resize(mApp->mWidth/2-width/2-5, 290+2*height,width, height);
    mQuitGameBtn->mOverImage = IMAGE_LU_BTN_OVER;
    mQuitGameBtn->mDownImage = IMAGE_LU_BTN_NORMAL;
    mQuitGameBtn->mButtonImage = IMAGE_LU_BTN_NORMAL;
	AddWidget(mQuitGameBtn);

	//--------------Start new level----------

	InitiateLevel(mLevel);
	
}

Board::~Board()
{
	RemoveAllWidgets();
	
	if(mBM!=NULL)
		delete mBM;
	if(mBOM!=NULL)
		delete mBOM;
	if(mEM!=NULL)
		delete mEM;
	if(mSB!=NULL)
		delete mSB;
	if(mLU!=NULL)
		delete mLU;
	if(mGO!=NULL)
		delete mGO;
	if(mPaddle!=NULL)
		delete mPaddle;
	if(mBall!=NULL)
		delete mBall;
	if(mSpaceBody!=NULL)
		delete mSpaceBody;
	mLaserSfx->Release();

	delete mContinueButton;
	delete mRestartButton;
	delete mStartNewGameBtn;
	delete mQuitGameBtn;


}


void Board::InitiateLevel(int pLevel)
{
	srand((unsigned)time(NULL));
	
	int LevelMap[10][8],BonusMap[10][8],RestartFlag;

	if(mPreLevel<mLevel)
		RestartFlag = 1;
	else if(mPreLevel==mLevel)
		RestartFlag = 2;
	else if(mPreLevel>mLevel)
		RestartFlag=3;
	
	
	mBM->ClearBrickForNextLevel();
	mSB->ClearForNextLevel(RestartFlag);
	mBOM->ClearBonusForNextLevel();
	mEM->ClearExplosionsForNextLevel();
	if(mSBActive)
	{
		if(mSpaceBody!=NULL)
			delete mSpaceBody;
		mSBActive = false;
	}
	this->DeactivateBlackScreen();
	mBall->ResetForNextLevel(float(mBall->GetBoundary().mWidth/2),float(mBall->GetBoundary().mHeight-mPaddle->GetImage()->GetHeight()-mBall->GetImage()->GetHeight()/2));
	mPaddle->ResetForNextLevel(RestartFlag,float(mPaddle->GetBoundary().mWidth/2),float(mPaddle->GetBoundary().mHeight-mPaddle->GetImage()->GetHeight()/2));

	ReadLevelFiles(LevelMap,BonusMap,pLevel);
	
	if(mLevel>=1 && mLevel<=5)
		mBg=IMAGE_SPACE_BG;
	else if(mLevel>=6 && mLevel<=10)
		mBg = IMAGE_SPACE_BG_BLUE;
	else if(mLevel>=11 && mLevel<=15)
		mBg=IMAGE_SPACE_BG_GREEN;
	else if(mLevel>=16 && mLevel<=20)
		mBg=IMAGE_NEBULA_1;
	else if(mLevel>=21 && mLevel<=25)
		mBg = IMAGE_SPACE_BG_RED;
	else if(mLevel>=25 && mLevel<=30)
		mBg=IMAGE_NEBULA_2;


	mBM->CreateLevel(LevelMap,BonusMap,10,8,2,2,1000);

	mContinueButton->SetVisible(false);
	mContinueButton->SetDisabled(true);

	mRestartButton->SetVisible(false);
	mRestartButton->SetDisabled(true);
	mStartNewGameBtn->SetVisible(false);
	mStartNewGameBtn->SetDisabled(true);
	mQuitGameBtn->SetVisible(false);
	mQuitGameBtn->SetDisabled(true);


	for(int i=0;i<MAX_SIZE;i++)
	{
		Star s;
		s.X = float(Rand()%mApp->mWidth);
		s.Y = float(Rand()% mApp->mHeight);
		int r = Rand()%3;
		switch(r)
		{
		case 0: s.R = 0; s.Increasing=true; s.Speed = 1.0F;break;
		case 1: s.R = 120; s.Increasing=true; s.Speed=1.2F; break;
		case 2: s.R = 255; s.Increasing = false;s.Speed = 1.1F; break;
		}
		s.Frame=0;
		mStarField[i]=s;
	}

	mPreLevel = mLevel;

	mApp->SetCursor(CURSOR_NONE);
}


void Board::ReadLevelFiles(int LevelMap[][8], int BonusMap[][8], int pL)
{
	int x;
	std::string LevelFilename="Maps\\LevelMaps\\level";
	std::string Filename;
	std::stringstream ss,ssb;
	ss<<LevelFilename<<pL;
	Filename = ss.str();
	Filename.append(".bin");
	ss.clear();
	char* filename = (char*)Filename.c_str();
	std::ifstream fin(filename,std::ios_base::binary);
    for(int i=0;i<10;i++)
	{
		for(int j=0;j<8;j++)
		{   
			fin.read(reinterpret_cast<char*>(&x),sizeof(x));
			LevelMap[i][j]=x;
		}
	}
	fin.close();

	int c;
	std::string BonusFilename="Maps\\BonusMaps\\bonusmap";
	ssb<<BonusFilename<<pL;
	Filename=ssb.str();
	Filename.append(".bin");
	ssb.clear();
	char* bfilename=(char*)Filename.c_str();
	
	std::ifstream bfin(bfilename);
    for(int i=0;i<10;i++)
	{
		for(int j=0;j<8;j++)
		{   
			bfin.read(reinterpret_cast<char*>(&c),sizeof(c));
			BonusMap[i][j]=c;
		}
	}
	bfin.close();
}



void Board::Update()
{
	srand(unsigned(time(NULL)));
//------BG code------
	mY+=0.5;
	if(mY>=mBg->GetHeight())
		mY=0;
//-------------------


	Widget::Update();

	if((!mLU->IsActive() || (mLU->IsActive() && mLU->GetState()==LevelUp::LU_FADEOUT)) && (!mGO->IsActive() || (mGO->IsActive() && mGO->GetState()==GameOver::GO_FADEOUT)))
	{
		if(!mLU->IsActive() &&  mWriteLevelInfoDone)
		{
			mWriteLevelInfoDone = false;
		}


	mPaddle->UpdatePaddle(mMouseX,mMouseY);
	
	mBall->CollisionCheck((Sprite*)mPaddle);

	//------Ball collision check with bricks----------
	CollisionBallBricks();
	//-----------------------------------------------

	if(mPaddle->GetMissileManager()->GetMissileCnt())
		CollsionBrickMissile();
	//-----when ball is at rest-----------

	if(mPaddle->GetLaser().mLaserMode)
		CollisionLaserBrick();

	if(mBOM->GetBonusCnt())
		CollisionBonusPaddle();

	if(!mBall->GetMoving())
		mBall->FollowPaddle(mPaddle);

	if(mBM->GetMissileManager()->GetMissileCnt())
		CollisionBrickMissilePaddle();
	//--------------------------------------
    
	mBall->Update();
	mBM->Update();
	mEM->Update();
	mBOM->Update();

	//-------check for reset-----------------
	if(mBall->IsBallBelowBottom())
	{
		if(mPaddle->GetLives()>=0 && !ResetPosDelay)
			mPaddle->SetLives(-1);
		if(mPaddle->GetLives()<=-1 && mBM->GetBrickCnt()!=0)
		{
			if(++GameOverDelay%50==0)
			{
				mGO->Activate();
				mApp->SetCursor(CURSOR_POINTER);
				GameOverDelay = 0;
			}
		}
		else{
			if(++ResetPosDelay%40==0)
			{
				mBall->ResetPos(float(mBall->GetBoundary().mWidth/2),float(mBall->GetBoundary().mHeight-mPaddle->GetImage()->GetHeight()-mBall->GetImage()->GetHeight()/2));
				mPaddle->ResetPos(float(mPaddle->GetBoundary().mWidth/2),float(mPaddle->GetBoundary().mHeight-mPaddle->GetImage()->GetHeight()/2));
				if(mPaddle->GetLives()>=0)
					mSB->SetCurLives(mPaddle->GetLives());
				ResetPosDelay=0;
			}
		}
	}

	
	if(mBall->GetFireMode())
	   mSB->SetFireBall(true);
	else
	   mSB->SetFireBall(false);
	
	if(mBlackScreen.mIsActive)
		UpdateBlackScreen();

	if(mBM->GetBrickCnt()==0 && mBOM->GetBonusCnt()==0)
	{
		if(++LevelUpDelay%150==0)
		{
			mLU->Activate();
			mApp->SetCursor(CURSOR_POINTER);
			LevelUpDelay=0;
		}
	}
	
	}

	if(mLU->IsActive())
	{
		if(mLaserSfx->IsPlaying())
			mLaserSfx->Stop();
		mLU->Update();

		if(!mWriteLevelInfoDone)
		{
			WriteLevelInfo();
			mWriteLevelInfoDone=true;
		}
		if(mLU->ActivateContinueBtn())
		{
			mContinueButton->SetDisabled(false);
			mContinueButton->SetVisible(true);
			mLU->SetContinueBtnState(false);	
		}
		if(mLU->StartNextLevel())
		{
			
			mPreLevel = mLevel;
			this->InitiateLevel(++mLevel);
			mLU->SetNextLevelState(false);	
		}

	}

	if(mGO->IsActive())
	{
		if(mLaserSfx->IsPlaying())
			mLaserSfx->Stop();
		mGO->Update();
		if(mGO->GetButtonsState())
		{
			mRestartButton->SetDisabled(false);
			mRestartButton->SetVisible(true);
			mStartNewGameBtn->SetDisabled(false);
			mStartNewGameBtn->SetVisible(true);
			mQuitGameBtn->SetDisabled(false);
			mQuitGameBtn->SetVisible(true);
			
		}
		if(mGO->StartNewGame())
		{
			mPreLevel = mLevel;
			mLevel = 1;
			this->InitiateLevel(mLevel);
			mGO->SetNewGameState(false);
			
		}
		else if(mGO->RestartLevel())
		{
			mPreLevel = mLevel;
			this->InitiateLevel(mLevel);
			mGO->SetRestartLevelstate(false);
			
		}
		else if(mGO->QuitGame())
		{
			mGO->SetQuitGameState(false);
			
		}
	}
}


void Board::UpdateF(float theFrac)
{
	if((!mLU->IsActive() || (mLU->IsActive() && mLU->GetState()==LevelUp::LU_FADEOUT)) && (!mGO->IsActive() || (mGO->IsActive() && mGO->GetState()==GameOver::GO_FADEOUT)))
	{
		mBall->UpdateF(theFrac);
		UpdateStarField(theFrac);
		UpdateSpaceBody(theFrac);
	}
}

void Board::UpdateStarField(float pFrac)
{
	Star s;
	for(int i=0;i<MAX_SIZE;i++)
	{
		s = mStarField[i];
		s.Y+=(s.Speed*pFrac);
		if(s.Y>mApp->mHeight)
		{
			s.Y=-30;
			s.X=float(Rand()%mApp->mWidth);
		}
		s.Frame++;
		if(s.Increasing)
			s.R+=4;
		else 
			s.R-=4;
		if(s.R>=250 && s.Increasing)
			s.Increasing=false;
		else if(s.R<=4 && !s.Increasing)
			s.Increasing=true;
		mStarField[i]=s;
	}
}

void Board::UpdateSpaceBody(float pFrac)
{
	if(!mSBActive)
	{
		SRand((unsigned)time(NULL));
		SpaceBody* s=new SpaceBody;
		int r = Rand()%7;
		s->mImg = SpaceBodies[r];
		s->X = float(Rand()%(WIDTH)-s->mImg->GetWidth()/2);
		s->Y=float(0 - s->mImg->GetHeight()-(Rand()%200));
		s->Speed=Rand(0.4F)+0.2F;
		s->Frame=0;
		mSpaceBody = s;
		mSBActive = true;
	}

	else if(mSBActive)
	{
		mSpaceBody->Y+=(mSpaceBody->Speed*pFrac);
		mSpaceBody->Frame++;
		if(mSpaceBody->Y>HEIGHT)
		{
			delete mSpaceBody;
			mSpaceBody = NULL;
			mSBActive = false;
		}
	}
}

		

		
		

void Board::Draw(Graphics* g)
{
	if((!mLU->IsActive() || (mLU->IsActive() && mLU->GetState()==LevelUp::LU_FADEOUT)) && (!mGO->IsActive() || (mGO->IsActive() && mGO->GetState()==GameOver::GO_FADEOUT)) )
	{
	g->TranslateF(mX,mY);
	g->DrawImageF(mBg,0,0);
	g->DrawImageF(mBg,0,float(-mBg->GetHeight()));
	g->DrawImageF(mBg,0,float(mBg->GetHeight()));
	g->TranslateF(-mX,-mY);

	DrawStarField(g);

	if(mSBActive)
		DrawSpaceBody(g);
	
	mBall->Draw(g);
	mBM->Draw(g);
	mEM->Draw(g);
	mBOM->Draw(g);
	mPaddle->Draw(g);
	
	if(mBlackScreen.mIsActive)
	{
		g->SetColor(Color::Black);
		g->FillRect(0,0,650,600);
		mBOM->Draw(g);
		mBall->Draw(g);
		mPaddle->Draw(g);
	}
	
	if(mPaddle->GetLaserMode())
		mBall->Draw(g);

	g->SetColor(Color::Black);
	g->FillRect(650,0,150,600);
	g->SetColor(Color::White);
	g->DrawLineAA(650,0,650,600);
	
	mSB->Draw(g);
	
	if(mBall->GetBottomState())
		g->DrawImageF(IMAGE_BOTTOM_SHIELD,float(mBall->GetBoundary().mX),float(mBall->GetBoundary().mY+mBall->GetBoundary().mHeight-IMAGE_BOTTOM_SHIELD->GetHeight()));

	g->SetFont(FONT_DEFAULT3);
	g->SetColor(Color::White);
	g->DrawString(StrFormat(_S("LEVEL %d"),mLevel),660,585);
	
	}
	
	if(mLU->IsActive())
	{
		mLU->Draw(g);
	}

	if(mGO->IsActive())
	{
		mGO->Draw(g);
	}
	
}

void Board::DrawStarField(FrameworkX::Graphics *g)
{
	Star s;
	g->PushState();
	g->SetColorizeImages(true);
	for(int i=0;i<MAX_SIZE;i++)
	{
		s = mStarField[i];
		g->SetColor(Color(255,255,255));
		g->DrawImageF(IMAGE_STARS,s.X,s.Y);
		g->SetDrawMode(Graphics::DRAWMODE_ADDITIVE);
		g->SetColor(Color(s.R,s.R,s.R));
		g->DrawImageF(IMAGE_STARS,s.X,s.Y);
		g->SetDrawMode(Graphics::DRAWMODE_NORMAL);
	}
	g->PopState();
}


void Board::DrawSpaceBody(Graphics* g)
{
	g->DrawImageF(mSpaceBody->mImg,mSpaceBody->X,mSpaceBody->Y);
}


void Board::CollisionBallBricks()
{
	srand((unsigned)time(NULL));
	int r1,r2,DestroyAdjBricks=0,row;
	r1 = int(mBall->GetRect().mX/(mBM->GetImage()->GetWidth()+mBM->GetHS()));
	r2 = int((mBall->GetRect().mX+mBall->GetRect().mWidth)/(mBM->GetImage()->GetWidth()+mBM->GetHS()));
	MissileManager* MM = mPaddle->GetMissileManager();

	std::vector<Brick*>::size_type i;
	for(i=0;i<mBM->GetBrickVec()->size();i++)
	{
		Brick* mBrick = mBM->GetBrick(int(i));
		if(mBrick->GetCol()==r1 || mBrick->GetCol()==r1-1|| mBrick->GetCol()==r2|| mBrick->GetCol()==r2+1 )
		{
			if(mBall->CollisionCheckBrick(mBrick))
			{
				mApp->PlaySample(SOUND_BALL_COLLISION);
				if(mBrick->GetBreakability())
				{
					if(mBall->GetFireMode())
						mBrick->SetHits(mBrick->GetMaxHits());
					else
						mBrick->SetHits(1);
					if(mBrick->DestroyBrick())
					{
					if( mBrick->GetId()==2)
					{
						mEM->AddExplosion(2,mBrick->GetPos(),1,1);
						DestroyAdjBricks=1;
						row = mBrick->GetRow();
					}
					else if((mBrick->GetId()==1 || mBrick->GetId()==3 || mBrick->GetId()==5 || mBrick->GetId()==6) && !mBall->GetFireMode())
						mEM->AddExplosion(1,mBrick->GetPos(),5,4);
					else if((mBrick->GetId()==1 || mBrick->GetId()==3 || mBrick->GetId()==5 || mBrick->GetId()==6) && mBall->GetFireMode())
						mEM->AddExplosion(0,mBrick->GetPos(),1,7);

					if(mBrick->GetBonus()!=BONUS_NONE)
						mBOM->AddBonus(mBrick->GetBonus(),mBrick->GetPos(),1,1);
					mSB->SetPoints(int(mBrick->GetBreakPoints()));
					mBM->DeleteBrick(int(i));
					i--;
					continue;
					}
					else if(!mBrick->DestroyBrick())
						mBrick->SetShake();
				}
				else if(!mBrick->GetBreakability())
					mBrick->SetShake();
			}

		}
	}

	
	
	if(DestroyAdjBricks)
	{
		for(unsigned int i=0;i<mBM->GetBrickVec()->size();i++)
		{
			Brick* tBrick = mBM->GetBrick(i);
			if(tBrick->GetRow()==row && tBrick->GetBreakability())
			{
				mEM->AddExplosion(3,tBrick->GetPos(),1,10);
				if(tBrick->GetBonus()!=BONUS_NONE)
					mBOM->AddBonus(tBrick->GetBonus(),tBrick->GetPos(),1,1);
				mSB->SetPoints(int(tBrick->GetBreakPoints()));
				mBM->DeleteBrick(i);
				i--;
		    }
	   }
	}
		
}


void Board::CollsionBrickMissile()
{
	srand((unsigned)time(NULL));
	int DestroyAdjBricks=0,row;
	MissileManager* MM = mPaddle->GetMissileManager();
	std::vector<Brick*>::size_type i;
		for(i=0;i<mBM->GetBrickVec()->size();i++)
		{
			Brick* mBrick = mBM->GetBrick(int(i));
			
				if(MM->CheckMissileBrickCollision(mBrick->GetRect()))
				{
					mApp->PlaySample(SOUND_BALL_COLLISION);
					if(mBrick->GetBreakability())
					{
						mBrick->SetHits(1);
						if(mBrick->DestroyBrick())
						{
							if( mBrick->GetId()==2)
							{
								mEM->AddExplosion(2,mBrick->GetPos(),1,1);
						        DestroyAdjBricks=1;
						        row = mBrick->GetRow();
							}
						
							else if(mBrick->GetId()==1 || mBrick->GetId()==3|| mBrick->GetId()==5 || mBrick->GetId()==6)
						        mEM->AddExplosion(1,mBrick->GetPos(),5,4);
							if(mBrick->GetBonus()!=BONUS_NONE)
								mBOM->AddBonus(mBrick->GetBonus(),mBrick->GetPos(),1,1);
							mSB->SetPoints(int(mBrick->GetBreakPoints()));
							mBM->DeleteBrick(int(i));
					        i--;
						}
						else if(!mBrick->DestroyBrick())
							mBrick->SetShake();
					}
					else if(!mBrick->GetBreakability())
						mBrick->SetShake();
				}
		}


		if(DestroyAdjBricks)
		{
			for(unsigned int i=0;i<mBM->GetBrickVec()->size();i++)
			{
				Brick* tBrick = mBM->GetBrick(i);
				if(tBrick->GetRow()==row &&  tBrick->GetBreakability())
				{
					mEM->AddExplosion(3,tBrick->GetPos(),1,10);
					if(tBrick->GetBonus()!=BONUS_NONE)
						mBOM->AddBonus(tBrick->GetBonus(),tBrick->GetPos(),1,1);
					mSB->SetPoints(int(tBrick->GetBreakPoints()));
					mBM->DeleteBrick(int(i));
				    i--;
				}
			}
		}
}



void Board::CollisionLaserBrick()
{
	srand((unsigned)time(NULL));
	int c1,c2;
	Laser LASER = mPaddle->GetLaser();
	
	c1 = int((mPaddle->GetPos().x-LASER.mLImg->GetWidth()/2+20)/(mBM->GetImage()->GetWidth()+mBM->GetHS()));
	c2 = int((mPaddle->GetPos().x+LASER.mLImg->GetWidth()/2-20)/(mBM->GetImage()->GetWidth()+mBM->GetHS()));
	
	std::vector<Brick*>::size_type i;
	for(i=0;i<mBM->GetBrickVec()->size();i++)
	{
		Brick* mBrick = mBM->GetBrick(int(i));
		if(mBrick->GetCol()==c1 || mBrick->GetCol()==c2)
		{
			if(mBrick->GetId()!=4)
			{
				if(!mBrick->GetLaserHit())
				{
					if(mBrick->GetBonus()!=BONUS_NONE)
						mBOM->AddBonus(mBrick->GetBonus(),mBrick->GetPos(),1,1);
					mBrick->SetLaserHit(true);

				
				}
				mBrick->SetShake();
			}
			else if(mBrick->GetId()==4)
			{
				mEM->AddExplosion(3,mBrick->GetPos(),1,10);
				if(mBrick->GetBonus()!=BONUS_NONE)
					mBOM->AddBonus(mBrick->GetBonus(),mBrick->GetPos(),1,1);
				mSB->SetPoints(int(mBrick->GetBreakPoints()));
				mBM->DeleteBrick(int(i));
				i--;
			}
		}
	}
}

void Board::CollisionBonusPaddle()
{
	bool t=false;
	for(int i=0;i<mBOM->GetBonusVec()->size();i++)
	{
		t=false;
		Bonus* tBonus=mBOM->GetBonus(i);
		t=tBonus->GetDRect().Intersects(mPaddle->GetRect());
		if(t)
		{
			AssignPaddlePowers(tBonus);
			if(tBonus->GetId()==BONUS_LIFE)
				mApp->PlaySample(SOUND_ONEUPSFX);
			else if(tBonus->GetId()==BONUS_LASER)
				mApp->PlaySample(SOUND_BONUS_LASERSFX);
			else
				mApp->PlaySample(SOUND_BONUSSFX);
			mBOM->DeleteBonus(i);
			i--;
		}
	}
}


void Board::CollisionBrickMissilePaddle()
{
	bool t = false;
	for(int i=0;i<mBM->GetMissileManager()->GetMissileVec()->size();i++)
	{
		Missile* tMissile=mBM->GetMissileManager()->GetMissile(i);
		t=tMissile->GetRect().Intersects(mPaddle->GetRect());
		if(t)
		{
			mApp->PlaySample(SOUND_GAMEOVERSFX);
			
			mBM->GetMissileManager()->DeleteMissile(i);
			i--;
			mPaddle->SetMHits(1);
			if(mPaddle->GetReduceLives())
			{
				mPaddle->SetLives(-1);
				if(mPaddle->GetLives()<=-1 && mBM->GetBrickCnt()!=0)
				{
					mGO->Activate();
					mApp->SetCursor(CURSOR_POINTER);
					
				}
				if(mPaddle->GetLives()>-1)
					mSB->SetCurLives(mPaddle->GetLives());
				mPaddle->SetReduceLives(false);
			}

		}
	}
}



void Board::AssignPaddlePowers(Bonus* pBonus)
{
	BonusType pId = pBonus->GetId();
	switch(pId)
	{
	case BONUS_RED_GEM: mSB->SetRedGems(1);
		mSB->SetPoints(pBonus->GetPoints());
		if(mSB->GetRedGems()>=10)
		{
		   mPaddle->SetLives(1);
		   mSB->SetCurLives(mPaddle->GetLives());
		   mSB->SetRedGems(-10);
			
		}
		break;
	case BONUS_GREEN_GEM: mSB->SetGreenGems(1);
		mSB->SetPoints(pBonus->GetPoints());
		if(mSB->GetGreenGems()>=10)
		{
		   mSB->SetLasers(1);
		   mPaddle->SetNumLasers(1);
		   mSB->SetCurLasers(mPaddle->GetNumLasers());
		   mPaddle->SetLaserMaxTime(3);
		   mSB->SetGreenGems(-10);

		}
		break;
	case BONUS_BLUE_GEM: mSB->SetBlueGems(1);
		mSB->SetPoints(pBonus->GetPoints());
		if(mSB->GetBlueGems()>=10)
		{
		   mPaddle->SetMissileMode(true);
		   mPaddle->SetNumMissiles(4);
		   mSB->SetCurMissiles(mPaddle->GetNumMissiles());
		   mSB->SetBlueGems(-10);
		}
		break;
	case BONUS_MISSILE: mSB->SetMissiles(pBonus->GetNumMissiles());
		mPaddle->SetMissileMode(true);
		mPaddle->SetNumMissiles(pBonus->GetNumMissiles());
		mSB->SetCurMissiles(mPaddle->GetNumMissiles());
		break;
	case BONUS_FLAME: mBall->SetFireMode(true); 
		break;
	case BONUS_SIZE:  mBall->SetBottomBlockTime(pBonus->GetScalingFactor());
		mBall->SetBottomState(true);
		break;
	case BONUS_LASER: mSB->SetLasers(1);
		                         mPaddle->SetNumLasers(1);
								 mSB->SetCurLasers(mPaddle->GetNumLasers());
								 mPaddle->SetLaserMaxTime(pBonus->GetLaserTime());
		                         break;
	case BONUS_LIFE: mPaddle->SetLives(pBonus->GetLives());
		mSB->SetCurLives(mPaddle->GetLives());
		break;

	case BONUS_BLINKING_BALL: mBall->SetBlinkingBall(true);
		break;

	case BONUS_BLACK_SCREEN: ActivateBlackScreen();
		break;
	case BONUS_REVERSE_MOTION: mPaddle->ActivateReverseMotion();
		break;


	}
}
void Board::UpdateBlackScreen()
{
	SpecialEffects& pSE=mBlackScreen;
	if(++pSE.mElapsedTime>=pSE.mMaxTime)
		DeactivateBlackScreen();
}
	

void Board::ActivateBlackScreen()
{
	SpecialEffects& pSE = mBlackScreen;
	pSE.mElapsedTime=0;
	pSE.mFrame=0;
	pSE.mIsActive=true;
	pSE.mMaxTime=800;
	pSE.mToggleEffect=false;
	pSE.mToggleTime=0;
}

void Board::DeactivateBlackScreen()
{
	SpecialEffects& pSE = mBlackScreen;
	pSE.mElapsedTime=0;
	pSE.mFrame=0;
	pSE.mIsActive=false;
	pSE.mMaxTime=0;
	pSE.mToggleEffect=false;
	pSE.mToggleTime=0;

}


void Board::WriteLevelInfo()
{
	std::ifstream f1;
	f1.open("LevelsInfo\\levelsinfo.bin",std::ios_base::binary);
	if(!f1)
	{
		MessageBox(mApp->mHWnd,"Level info not found","Error",NULL);
		mApp->ExitApplication();
	}
	S.Level=mLevel;
	S.Points=mSB->GetPoints();
	S.Open = 1;
	
	f1.read(reinterpret_cast<char*>(&A[0]),sizeof(A[0]));
	for(int i=1;i<30;i++)
		f1.read(reinterpret_cast<char*>(&A[i]),sizeof(A[i]));

	f1.close();

	for(int i=0;i<30;i++)
	{
		if(A[i].Level==S.Level && A[i].Points<S.Points)
		{
			A[i].Level=S.Level;
			A[i].Open=S.Open;
			A[i].Points = S.Points;
			mLU->SetIsHighScore(true);
		}
		if(A[i].Level==S.Level)
		{
			A[i+1].Open=1;
		}
	}

	std::ofstream f2;

	f2.open("LevelsInfo\\levelsinfo.bin",std::ios_base::binary);

	f2.write(reinterpret_cast<char*>(&A[0]),sizeof(A[0]));
	for(int i=1;i<30;i++)
	{
		f2.write(reinterpret_cast<char*>(&A[i]),sizeof(A[i]));
	}

	f2.close();

}

		



void Board::MouseMove(int x, int y)
{
	if(!mLU->IsActive() && !mGO->IsActive())
	{
		mMouseX=x; 
		mMouseY=y; 
	}
	
}
void Board::MouseDrag(int x,int y)
{ if(!mLU->IsActive() && !mGO->IsActive())
{ 
	mMouseX=x; 
    mMouseY=y;
	mPaddle->SetFactor(1);
}
}


void Board::MouseDown(int x, int y, int theBtnNum, int theClickCount)
{
	if(!mLU->IsActive() && !mGO->IsActive())
	{
	Widget::MouseDown(x, y, theBtnNum, theClickCount);

	if (theClickCount > 0)
	{
		switch(theBtnNum)
		{
			case 0:
				if(!mBall->GetMoving())
				{
					mBall->SetMoving(true);
					mBall->SetVelocityVec(0,-1);
					mBall->SetSpeed(mBall->GetMaxV());
				}
				mPaddle->SetFactor(1);
				break;
			case 1:
				if(mPaddle->GetMissileMode() && !mPaddle->GetMF() && mBall->GetMoving())
				{
					mPaddle->AddMissile();
					mPaddle->SetMF(true);
					mPaddle->SetNumMissiles(-2);
					mSB->SetCurMissiles(mPaddle->GetNumMissiles());
					mApp->PlaySample(SOUND_MISSILESFX);
				}
				mPaddle->SetFactor(0);
				break;
				
		}
	}

	}
}

void Board::MouseUp(int x,int y,int theBtnNum, int theClickCount)
{
	Widget::MouseDown(x, y, theBtnNum, theClickCount);
   if(!mLU->IsActive() && !mGO->IsActive())
   {
	if (theClickCount > 0)
	{
		switch(theBtnNum)
		{
			case 0: // left
				mPaddle->SetFactor(0);
				break;
			case 1:
				mPaddle->SetMF(false);
				mPaddle->SetFactor(0);
				break;
		}
	}
   }
	
}


void Board::KeyDown(KeyCode theKey)
{if(!mLU->IsActive() && !mGO->IsActive())
{
	if(theKey==KEYCODE_SPACE)
	{
		if(!mPaddle->GetLaserMode() && mPaddle->GetNumLasers() && mBall->GetMoving())
		{
			mPaddle->InitialiseLaser();
			mPaddle->SetNumLasers(-1);
			mSB->SetCurLasers(mPaddle->GetNumLasers());
			mLaserSfx->Play(true,false);
		}
	}
	else if(theKey==KEYCODE_ESCAPE)
	{
		mD = mApp->NewDialog(IMAGE_DIALOG_BOX, IMAGE_DIALOG_BUTTON,2, true, StringToSexyString(_S("Paused")), StringToSexyString(_S("")),StringToSexyString(_S("Do u really wanna quit?")),Dialog::BUTTONS_YES_NO);
		mApp->SetCursor(CURSOR_POINTER);
	}
}

}



void Board::ButtonDepress(int pBtnId)
{
	if(pBtnId==1)
	{
		mLU->SetNextLevelState(true);
		mLU->SetContinueBtnState(false);
		mLU->SetState(LevelUp::LU_FADEOUT);
		mApp->PlaySample(SOUND_PLAYMOUSEDOWN);
		mApp->mMusicInterface->FadeIn(1,-1,0.001,false);
	}
	else if(pBtnId==2)
	{
		mGO->SetRestartLevelstate(true);
		mGO->SetButtonsState(false);
		mGO->SetState(GameOver::GO_FADEOUT);
		mApp->PlaySample(SOUND_PLAYMOUSEDOWN);
		mApp->mMusicInterface->FadeIn(1,-1,0.001,false);
	}

	else if(pBtnId==3)
	{
		mGO->SetNewGameState(true);
		mGO->SetButtonsState(false);
		mGO->SetState(GameOver::GO_FADEOUT);
		mApp->PlaySample(SOUND_PLAYMOUSEDOWN);
		mApp->mMusicInterface->FadeIn(1,-1,0.001,false);
	}

	else if(pBtnId==4)
	{
		//mGO->SetQuitGameState(true);
		//mGO->SetButtonsState(false);
		mApp->mWidgetManager->RemoveWidget(this);
		mApp->SafeDeleteWidget(this);
		mApp->InitialiseMainMenu();
		mApp->PlaySample(SOUND_BOARDMOUSEDOWN);
		
	}

}


void Board::ButtonMouseEnter(int theId)
{
	mApp->PlaySample(SOUND_MMOUSEOVER); 
}
