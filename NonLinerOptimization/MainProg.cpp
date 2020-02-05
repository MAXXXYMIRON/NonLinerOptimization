#include<iostream>
#include<cmath>

using namespace std;

const float E = 0.001f;


float f(const float &x)
{
	return log10((2 * x * x) + x + 1) / log10(1.7f);
}


void MethSven(float &a, float &b, float x0, float d)
{
	float xL = x0 - d,
		xC = x0,
		xR = x0 + d;

	if (f(xC) > f(xL) && f(xC) > f(xR)) throw 2;
	if (f(xC) < f(xL) && f(xC) < f(xR))
	{
		a = xL;
		b = xR;
		return;
	}

	while (!(f(xC) < f(xL) && f(xC) < f(xR)))
	{
		if (f(xL) > f(xC) && f(xC) > f(xR))
		{
			xL = xC;
			xC = xR;
			xR = xR + 2 * d;
		}
		else if (f(xL) < f(xC) && f(xC) < f(xR))
		{
			xR = xC;
			xC = xL;
			xL = xL - 2 * d;
		}
		d *= 2;
	}
	a = xL;
	b = xR;
	return;
}


float PassiveSearch(const float &a, const float &b)
{
	unsigned k = 1;

	float min = f(a),
		piece = (b - a) / (((b - a) / E) + 1.0f),
		xK = a + (k * piece);

		while (f(xK) < min)
		{
			min = f(xK);
			k++;
			xK = a + (k * piece);
		}
	return xK;
}

float Dihotomy(const float &a, const float &b)
{
	float x1, x2, x3;
	x1 = (3 * a + b) / 4.0f;
	x2 = (a + b) / 2.0f;
	x3 = (a + 3 * b) / 4.0f;

	if (f(x2) < f(x1) && f(x2) < f(x3))
	{
		if ((x3 - x1) / 2.0f <= E) return (x1 + x3) / 2.0f;
		return Dihotomy(x1, x3);
	}
	else if (f(x1) > f(x2) && f(x2) > f(x3))
	{
		if ((b - x2) / 2.0f <= E) return (b + x2) / 2.0f;
		return Dihotomy(x2, b);
	}
	else
	{
		if ((x2 - a) / 2.0f <= E) return (a + x2) / 2.0f;
		return Dihotomy(a, x2);
	}
}

float GoldenRatio(const float &a, const float &b)
{
	float fi = (sqrt(5) - 1) / 2,
		x1 = fi * a + (1 - fi) * b,
		x2 = (1 - fi) * a + fi * b;

	if (f(x1) > f(x2))
	{
		if ((b - x1) / 2.0f <= E) return (x1 + b) / 2.0f;
		return GoldenRatio(x1, b);
	}
	else
	{
		if ((x2 - a) / 2.0f <= E) return (x2 + a) / 2.0f;
		return GoldenRatio(a, x2);
	}
}


void main()
{
	float a = 0,
		b = 0;
	MethSven(a, b, 0, 0.01);

	cout << a << endl;
	cout << b << endl << endl;

	cout << PassiveSearch(a, b) << endl;

	cout << Dihotomy(a, b) << endl;

	cout << GoldenRatio(a, b) << endl;

	system("pause");
}