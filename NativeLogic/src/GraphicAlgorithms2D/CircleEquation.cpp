#include "CircleEquation.h"

#if MEMORY_LEAK_DEBUG == 1
#include <vld.h>
#endif

CircleEquation::CircleEquation(T6Vec3 center, T6Vec3 aPointOnCircle)
{
	parameters_ = new EquationParameter(
						center.x,
						center.y,
						sqrt(
							pow(center.x - aPointOnCircle.x, 2) +
							pow(center.y - aPointOnCircle.y, 2)));
}



CircleEquation::CircleEquation(double x, double y, double r)
{
	parameters_ = new EquationParameter(x, y, r);
}



CircleEquation::CircleEquation(const CircleEquation& source)
{
	parameters_	=	new EquationParameter(*source.parameters_);
}

CircleEquation::CircleEquation(T6Vec3 center, double radius)
{
	parameters_ = new EquationParameter(center.x, center.y, radius);
}



CircleEquation::~CircleEquation(void)
{
	delete parameters_;
}



T6Vec3 CircleEquation::getCoodirateFromDegree(const double& t)
{
	return 
		T6Vec3((float)(parameters_->x + parameters_->r * Default::cos(DEGREE_TO_RADIAN(t))),
					(float)(parameters_->y + parameters_->r * Default::sin(DEGREE_TO_RADIAN(t))),
				DEFAULT_DEPTH);
}



double CircleEquation::getDegreeFromCoodirate(T6Vec3 point)
{
	double variable;
	variable = (point.x - parameters_->a) / parameters_->r;
	return (Default::acos(variable) * GET_SIGN(((int)(point.y - this->getCenter().y))));
}



void CircleEquation::increaseR(double difference)
{
	parameters_->r += difference;
}



void CircleEquation::setCenter(double x, double y)
{
	parameters_->x = x;
	parameters_->y = y;
}


EquationParameter CircleEquation::getParameter()
{
	return *parameters_;
}


T6Vec3	CircleEquation::getCenter()
{
	return T6Vec3((float)parameters_->x, (float)parameters_->y, DEFAULT_DEPTH);
}


void CircleEquation::setR(double r)
{
	parameters_->r = r;
}