#include "QuadraticEquation.h"

#if MEMORY_LEAK_DEBUG == 1
#include <vld.h>
#endif

// a*X^2 + b*x + c = y
QuadraticEquation::QuadraticEquation(double a, double b, double c)
{
	parameters_ = new EquationParameter(a, b, c);
}



QuadraticEquation::QuadraticEquation(const QuadraticEquation& source)
{
	parameters_	=	new EquationParameter(*source.parameters_);
}



QuadraticEquation::~QuadraticEquation(void)
{
	delete parameters_;
}



vector<double>* QuadraticEquation::caculateLineEquation()
{
	if (parameters_->b == 0)
		return 0;
	else {
		vector<double>* solution = new vector<double>;
		solution->push_back((-parameters_->c) / parameters_->b);
		return solution;
	}
}



vector<double>* QuadraticEquation::caculateParabolEquation()
{
	double delta =	parameters_->b * parameters_->b -
					4 * parameters_->a * parameters_->c;	// b*b - 4*a*c

	if (delta < 0)
		return NULL;
	else {

		vector<double>* solution = new vector<double>;

		if (delta == 0) {
			solution->push_back((-parameters_->b) / (2 * parameters_->a));	// -b / 2*a
		}
		else {
			solution->push_back((-parameters_->b) + sqrt(delta) / (2 * parameters_->a));	// (-b + sqrt(delta)) / (2*a)
			solution->push_back((-parameters_->b) - sqrt(delta) / (2 * parameters_->a));	// (-b - sqrt(delta)) / (2*a)
		}

		return solution;
	}
}



vector<double>* QuadraticEquation::caculateSolutionForZeroY()
{
	if (parameters_->a == 0)
		return caculateLineEquation();
	else
		return caculateParabolEquation();
}



vector<double>* QuadraticEquation::getXFromY(const double& y)
{
	QuadraticEquation equationAfterReplatedY = *(*this - QuadraticEquation(0, 0, y));
	
	return equationAfterReplatedY.caculateSolutionForZeroY();
}



SmartPointer<QuadraticEquation> QuadraticEquation::operator+ (const QuadraticEquation& secondEquation)
{
	double a, b, c;
	a = parameters_->a + secondEquation.parameters_->a;
	b = parameters_->b + secondEquation.parameters_->b;
	c = parameters_->c + secondEquation.parameters_->c;

	return SmartPointer<QuadraticEquation>(new QuadraticEquation(a, b, c));
}



SmartPointer<QuadraticEquation> operator- (const QuadraticEquation& equation)
{
	return SmartPointer<QuadraticEquation>(
		new QuadraticEquation(	-equation.parameters_->a,
								-equation.parameters_->b,
								-equation.parameters_->c));
}



SmartPointer<QuadraticEquation> QuadraticEquation::operator- (const QuadraticEquation& secondEquation)
{
	return (*this + *(- secondEquation));
}