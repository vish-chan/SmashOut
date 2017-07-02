#include "Explosion.h"
#include "SexyAppFramework/XAppBase.h"


using namespace FrameworkX;

Explosion::Explosion(int pId,Image* pImg, SexyVector2 pPos,int pRows, int pCols)
{
	mId = pId;
	mImg = pImg;
	mPos = pPos;
	mRows = pRows;
	mCols = pCols;
	mRow = 0;
	mCol = 0;
	mRemove = false;
	mFrame=0;
	mDRect = FRect(mPos.x-(mImg->GetWidth()/mCols)/2,mPos.y-(mImg->GetHeight()/mRows)/2,mImg->GetWidth()/mCols,mImg->GetHeight()/mRows);
    
}

Explosion::~Explosion()
{
}

void Explosion::Draw(Graphics* g)
{
	if(mId==0 || mId==1 || mId==3)
	{
		mSRect = Rect(int(mCol*mDRect.mWidth),int(mRow*mDRect.mHeight),int(mDRect.mWidth),int(mDRect.mHeight));
		g->DrawImageF(mImg,float(mDRect.mX),float(mDRect.mY),mSRect);
	}
	if(mId==2)
	{
		g->DrawImageF(mImg,mPos.x-mSRect.mWidth/2,mPos.y-mImg->GetHeight()/2,mSRect);
	}
}

void Explosion::Update()
{
	if(mId==0 || mId==3)
	{
		if((++mFrame)%5==0)
		   mCol=++mCol%mCols;
		if(mRow==mRows-1 && mCol==mCols-1)
		   mRemove=true;
	}
	else if(mId==1)
	{
		if(++mFrame%5==0)
		   mCol=++mCol%mCols;
		if(mCol==mCols-1)
		   mRow=++mRow%mRows;
		if(mRow==mRows-1 && mCol==mCols-1)
		   mRemove=true;
	}
	else if(mId==2)
	{
		mFrame+=15;
		mRow = (mImg->GetWidth()/2)-(mFrame);      //x
		mCol=mImg->GetHeight();        
		mSRect=Rect(mRow,0,abs(2*((mImg->GetWidth()/2)-mRow)),mCol);
		if(mRow<=0)
		   mRemove=true;
	}

}


