#include <stdio.h>
#include <math.h>


double integrate(double (*f)(double x), double a, double b, int n)
{
	double h;		/* height of rectangle */
	double w;		/* width of rectangle */
	double area = 0.0;	/* area of rectangle */
	double x;		/* the domain value */
	int i;
      

	w = (b - a) / n;

	for (i = 1, x = a; i <= n; i++) {
		x += w;
		h = (*f)(x);
		area += (w * h);
	}

	return area;		/* area under the curve */

}


int main(void)
{
	double area;
	int n = 10;
	/* integrate with sin, cos, exp */
	area = integrate(exp, 0.0, M_PI/2, n);
	printf("area = %lf\n", area);
	return 0;
}
