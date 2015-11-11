// https://HelloACM.com

#include <iostream>
#include <time.h> 
#include <ppl.h>
#include <iomanip>

using namespace std;

int monte_carlo_count_pi(int n)
{
	int c = 0;
	for (int i = 0; i < n; i ++)
	{
		double x = (double)rand() / (RAND_MAX);
		double y = (double)rand() / (RAND_MAX);
		if (x * x + y * y <= 1.0)
		{
			c++;
		}
	}
	return c;
}

int main()
{
	srand(time(NULL));
	const int N1 = 1000;
	const int N2 = 100000;
	int n = 0;
	int c = 0;
	Concurrency::critical_section cs;
	// it is better that N1 >> N2 for better performance
	Concurrency::parallel_for(0, N1, [&](int i)
	{
		int t = monte_carlo_count_pi(N2);
		cs.lock(); // race condition
		n += N2;   // total sampling points
		c += t;    // points fall in the circle
		cs.unlock();
	});
	cout << "pi ~= " << setprecision(9) << (double)c / n * 4.0 << endl;
	return 0;
}