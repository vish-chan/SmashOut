#ifndef _CPHYSICS_H_
#define _CPHYSICS_H_


#include "Ball.h"
#include "SexyAppFramework/SexyVector.h"
#include "SexyAppFramework/Rect.h"


namespace FrameworkX
{
	class Ball;

	class Physics
	{
	public:
		bool point_inside_rect(SexyVector2 point,FRect rect);
		bool pointintersect_circleandrect(Ball* circle, FRect rect , int Case,float&);
		float pointintersect_circleandrect_dist(Ball* circle, SexyVector2);
		float point_linedistance(float,float,float,float,float,float);
		
	};
}

  

#endif