#define PI 3.1415926

double circleS(double);

double circleLoopS(double r1, double r2)
{
	return circleS(r1>r2?r1:r2)-circleS(r1<r2?r1:r2);
}
