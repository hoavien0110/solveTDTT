#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;

// Function to return area of intersection
double intersectionArea(double X1, double Y1, double R1, double X2, double Y2, double R2)
{
	// double M_PI = 3.14;
	double d, alpha, beta, a1, a2;
	double ans;

	d = sqrt((X2 - X1) * (X2 - X1) + (Y2 - Y1) * (Y2 - Y1));

	if (d >= R1 + R2)
		ans = 0;

	else if (d <= (R1 - R2) && R1 >= R2)
		ans = M_PI * R2 * R2;

	else if (d <= (R2 - R1) && R2 >= R1)
		ans = M_PI * R1 * R1;

	else {
		alpha = acos(1.0 * (R1 * R1 + d * d - R2 * R2)
					/ (2 * R1 * d))
				* 2;
		beta = acos(1.0 * (R2 * R2 + d * d - R1 * R1)
					/ (2 * R2 * d))
			* 2;
		a1 = 0.5 * beta * R2 * R2
			- 0.5 * R2 * R2 * sin(beta);
		a2 = 0.5 * alpha * R1 * R1
			- 0.5 * R1 * R1 * sin(alpha);
		ans = a1 + a2;
	}

	return ans;
}

double unionArea(double X1, double Y1, double R1, double X2, double Y2, double R2) {
    if (intersectionArea(X1, Y1, R1, X2, Y2, R2) == 0) {
        return M_PI * R1 * R1 + M_PI * R2 * R2;
    }

    return M_PI * R1 * R1 + M_PI * R2 * R2 - intersectionArea(X1, Y1, R1, X2, Y2, R2);

}

int main()
{
    double x1, y1, x2, y2, r;
    cin >> x1 >> y1 >> x2 >> y2 >> r;

	// Function Call
	cout << fixed << setprecision(3) << unionArea(x1, y1, r, x2, y2, r);

	return 0;
}
