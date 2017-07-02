#include "cPhysics.h"
#include "SexyAppFramework/SexyVector.h"
#include "SexyAppFramework/Rect.h"
#include <vector>


using namespace FrameworkX;



bool Physics::pointintersect_circleandrect(Ball* circle, FRect rect , int Case, float& dist)
   {
      double xc,yc,x,y;
      xc = circle->GetX();
      yc = circle->GetY();
      double r = pow(circle->GetRadius(),2);
      
      if(Case==0)
      {
		  x = rect.mX+rect.mWidth;
		  y = rect.mY+rect.mHeight;
		  dist = pow(xc-x,2)+pow(yc-y,2);
		  if(dist<=r)
		     return true;
		  
		return false;
      }

      if(Case==1)
	  {
		  x = rect.mX+rect.mWidth;
		  y = rect.mY;
		  dist = pow(xc-x,2)+pow(yc-y,2);
		  if(dist<=r)
			  return true;
		  
			  return false;
      }

      if(Case==2)
      {
		  x = rect.mX;
		  y = rect.mY+rect.mHeight;
		  dist = pow(xc-x,2)+pow(yc-y,2);
		  if(dist<=r)
			  return true;
		  
			  return false;
      }

      if(Case==3)
      {
		  x = rect.mX;
		  y = rect.mY;
		  dist = pow(xc-x,2)+pow(yc-y,2);
		  if(dist<=r)
			  return true;
		 
			  return false;
      }
	  return false;
   }


float Physics::pointintersect_circleandrect_dist(Ball* circle, SexyVector2 pPoint)
{
   float xc,yc,x,y;
   xc = circle->GetX();
   yc = circle->GetY();
   float dist;
   x = pPoint.x;
   y = pPoint.y;
   dist = pow(xc-x,2)+pow(yc-y,2);
   return dist;
}


   

bool Physics::point_inside_rect(SexyVector2 point,FRect rect)
   {

		if (point.x>=rect.mX && point.x<=(rect.mX+rect.mWidth))
		{
			if (point.y>=rect.mY && point.y<=(rect.mY+rect.mHeight))
				return true;
		}
		return false;
   }


float Physics::point_linedistance(float x0, float y0, float x1, float y1, float x2, float y2)
{
	float Distance = sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
	float Num = fabs((x2-x1)*(y1-y0)-(x1-x0)*(y2-y1));
	return (Num/Distance)-2;
}