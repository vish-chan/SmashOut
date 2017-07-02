#include "ScoreBoard.h"
#include "Res.h"


using namespace FrameworkX;


const int GDpos = 170;
const int RDpos = 212 ;
const int BDpos = 252;
const int Lpos = 330;
const int Mpos = 375;
const int Lifepos = 550;
const int Ballpos = 440;

const int xpos = 720;

ScoreBoard::ScoreBoard(int pPoints,cGame* pApp)
{
	mPoints = pPoints;
	mGreenGems = 0;
	mRedGems = 0;
	mBlueGems = 0;
	mMissiles = 0;
	mLasers = 0;
	mExtraBonuses = 0;
	mApp = pApp;
	mScoreBoardBG = 0;
	mCurMissiles = 0;
	mCurLasers = 0;
	mCurLives = 3;
	mFireBall = false;
}

ScoreBoard::~ScoreBoard()
{
}


void ScoreBoard::Draw(Graphics* g)
{
	g->DrawImageF(IMAGE_SCORE_BOARD,650,0);
	g->PushState();
	g->SetColor(Color::White);
	g->SetFont(FONT_DEFAULT);
	g->DrawString(StrFormat(_S("%d"),mPoints),665,52);
	g->SetFont(FONT_NGAGE2);
	g->DrawString(StrFormat(_S("%d"),mGreenGems),xpos,GDpos);
	g->DrawString(StrFormat(_S("%d"),mRedGems),xpos,RDpos);
	g->DrawString(StrFormat(_S("%d"),mBlueGems),xpos,BDpos);
	g->DrawString(StrFormat(_S("%d"),mCurLasers),xpos,Lpos);
	g->DrawString(StrFormat(_S("%d"),mCurMissiles),xpos,Mpos);
	g->DrawString(StrFormat(_S("%d"),mCurLives),xpos-10,Lifepos);
	
	g->SetColorizeImages(true);
	if(mCurLasers)
		g->SetColor(Color::White);
	else
		(g->SetColor(Color(100,100,100)));
	g->DrawImageF(IMAGE_BONUS_LASER,xpos-60,Lpos-25);
	if(mCurMissiles)
		g->SetColor(Color::White);
	else
		(g->SetColor(Color(100,100,100)));
	g->DrawImageF(IMAGE_BONUS_MISSILE,xpos-55,Mpos-20);

	g->PopState();
	if(mFireBall)
		g->DrawImageF(IMAGE_FIRE_BALL,xpos-55,425);
}


void ScoreBoard::Update()
{
}


void ScoreBoard::ClearForNextLevel(int pRestartFlag)
{
	mGreenGems = 0;
	mRedGems = 0;
	mBlueGems = 0;
	mPoints = 0;
	mLasers=0;
	mMissiles = 0;
	if(pRestartFlag==2 || pRestartFlag==3)
	{
		mCurLasers=0;
		mCurMissiles = 0;
		mCurLives = 3;
	}
	mFireBall = false;
}


