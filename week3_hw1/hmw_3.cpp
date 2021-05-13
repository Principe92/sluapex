#include <iostream>
#include <math.h>

using namespace std;

float speed_up(int p, int n);
float efficiency(float s, int p);

int main() {

	for (int i = 0; i < 8; i++) {
		for (int j = 1; j <= 32; j++) {
			int n = 10 * j;
			int p = pow(2, i); 
			float r = speed_up(p, n);
			float e = efficiency(r, p);
			printf("For p = %d and n = %d, speed up: %.2f efficiency: %.2f\n", p, n, r, e);
		}
	}
}

float speed_up(int p, int n)
{
	float ts = n * n;
	float tp = (ts/p) + log2(p);

	return ts/tp;
}

float efficiency(float s, int p) {

	return s/p;
}
