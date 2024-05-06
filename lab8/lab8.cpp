#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <cfloat>
#define accuracy_float_mode 1.192092896e-07F
#define accuracy_double_mode 2.2204460492503131e-15
#define maxLoopIteration 100
#define PI 3.14159265358979323846
#define DATA_SIZE 10
using namespace std;
template<typename T> inline T f(T x)
{
	return sin(x);
}
template<typename T> inline T df(T x)
{
	return cos(x);
}
template <typename T> inline T progressiveDifference_2pkt(T x, T h)
{
	return (f(x + h) - f(x)) / h;
}
template <typename T> inline T centralDifference_2pkt(T x, T h)
{
	return (f(x + h) - f(x - h)) / (2.0 * h);
}
template <typename T> inline T backwardDifference_2pkt(T x, T h)
{
	return (f(x) - f(x - h)) / h;
}
template <typename T> inline T progressiveDifference_3pkt(T x, T h)
{
	return (-3.0 / 2.0 * f(x) + 2.0 * f(x + h) - 1.0 / 2.0 * f(x + h + h))
		/ (h);
}
template <typename T> inline T backwardDifference_3pkt(T x, T h)
{
	return (3.0 / 2.0 * f(x) - 2.0 * f(x - h) + 1.0 / 2.0 * f(x - h - h)) /
		(h);
}
template <typename T> inline void createDF_Absolute(T data[maxLoopIteration][DATA_SIZE], T absolute[maxLoopIteration][DATA_SIZE], T h, T accuracy_mode)
{
	T start = 0.0;
	T end = PI / 2.0;
	T middle = (start + end) / 2.0;
	for (int i = 0; i < maxLoopIteration; i++)
	{
		if (h < accuracy_mode) break;
		data[i][0] = progressiveDifference_2pkt(start, h);
		absolute[i][0] = fabs(data[i][0] - df(start));
		data[i][1] = centralDifference_2pkt(middle, h);
		absolute[i][1] = fabs(data[i][1] - df(middle));
		data[i][2] = backwardDifference_2pkt(end, h);
		absolute[i][2] = fabs(data[i][2] - df(end));
		data[i][3] = progressiveDifference_3pkt(start, h);
		absolute[i][3] = fabs(data[i][3] - df(start));
		data[i][4] = progressiveDifference_3pkt(middle, h);
		absolute[i][4] = fabs(data[i][4] - df(middle));
		data[i][5] = backwardDifference_3pkt(middle, h);
		absolute[i][5] = fabs(data[i][5] - df(middle));
		data[i][6] = backwardDifference_3pkt(end, h);
		absolute[i][6] = fabs(data[i][6] - df(end));
		data[i][7] = progressiveDifference_2pkt(middle, h);
		absolute[i][7] = fabs(data[i][7] - df(middle));
		data[i][8] = backwardDifference_2pkt(middle, h);
		absolute[i][8] = fabs(data[i][8] - df(middle));
		absolute[i][9] = h;
		h = h / 1.2;
	}
	cout << endl << "Rzedy dokladnosci: " << endl;
	for (int i = 0; i < 9; i++) {
		cout << i + 1 << ". " << (log10(absolute[1][i]) - log10(absolute[2][i]))
			/ (log10(absolute[1][9]) - log10(absolute[2][9])) << endl;
	}
}
template <typename T> inline void writeToFile(T
	absolute[maxLoopIteration][DATA_SIZE], T h, T accuracy_mode)
{
	fstream progressive_2pkt_start, central_2pkt_middle, backward_2pkt_end, progressive_3pkt_start, progressive_3pkt_middle, backward_3pkt_middle, backward_3pkt_end, backward_2pkt_middle, progressive_2pkt_middle;
	progressive_2pkt_start.open("progressive_2pkt_start.txt", ios::out);
	progressive_3pkt_start.open("progressive_3pkt_start.txt", ios::out);
	progressive_3pkt_middle.open("progressive_3pkt_middle.txt", ios::out);
	central_2pkt_middle.open("central_2pkt_middle.txt", ios::out);
	backward_3pkt_middle.open("backward_3pkt_middle.txt", ios::out);
	backward_2pkt_end.open("backward_2pkt_end.txt", ios::out);
	backward_3pkt_end.open("backward_3pkt_end.txt", ios::out);
	progressive_2pkt_middle.open("progressive_2pkt_middle.txt", ios::out);
	backward_2pkt_middle.open("backward_2pkt_middle.txt", ios::out);
	if (!progressive_2pkt_start.good())
	{
		cout << "Blad otwarcia pliku progressive_2pkt_start" << endl;
		return;
	}
	if (!central_2pkt_middle.good())
	{
		cout << "Blad otwarcia pliku central_2pkt_middle" << endl;
		return;
	}
	if (!backward_2pkt_end.good())
	{
		cout << "Blad otwarcia pliku backward_2pkt_end" << endl;
		return;
	}
	if (!progressive_3pkt_start.good())
	{
		cout << "Blad otwarcia pliku progressive_3pkt_start" << endl;
		return;
	}
	if (!progressive_3pkt_middle.good())
	{
		cout << "Blad otwarcia pliku progressive_3pkt_middle" << endl;
		return;
	}
	if (!backward_3pkt_middle.good())
	{
		cout << "Blad otwarcia pliku backward_3pkt_middle" << endl;
		return;
	}
	if (!backward_3pkt_end.good())
	{
		cout << "Blad otwarcia pliku backward_3pkt_end" << endl;
		return;
	}
	if (!backward_2pkt_middle.good())
	{
		cout << "Blad otwarcia pliku backward_2pkt_middle" << endl;
		return;
	}
	if (!progressive_2pkt_middle.good())
	{
		cout << "Blad otwarcia pliku progressive_2pkt_middle" << endl;
		return;
	}
	for (int i = 0; i < maxLoopIteration; i++)
	{
		if (h < accuracy_mode) break;
		progressive_2pkt_start << log10(h) << " ";
		central_2pkt_middle << log10(h) << " ";
		backward_2pkt_end << log10(h) << " ";
		progressive_3pkt_start << log10(h) << " ";
		progressive_3pkt_middle << log10(h) << " ";
		backward_3pkt_middle << log10(h) << " ";
		backward_3pkt_end << log10(h) << " ";
		backward_2pkt_middle << log10(h) << " ";
		progressive_2pkt_middle << log10(h) << " ";
		for (int j = 0; j < 9; j++)
		{
			switch (j) {
			case 0:
				progressive_2pkt_start << log10(absolute[i][j]) << " ";
				break;
			case 1:
				central_2pkt_middle << log10(absolute[i][j]) << " ";
				break;
			case 2:
				backward_2pkt_end << log10(absolute[i][j]) << " ";
				break;
			case 3:
				progressive_3pkt_start << log10(absolute[i][j]) << " ";
				break;
			case 4:
				progressive_3pkt_middle << log10(absolute[i][j]) << "";
					break;
			case 5:
				backward_3pkt_middle << log10(absolute[i][j]) << " ";
				break;
			case 6:
				backward_3pkt_end << log10(absolute[i][j]) << " ";
				break;
			case 7:
				progressive_2pkt_middle << log10(absolute[i][j]) << "";
					break;
			case 8:
				backward_2pkt_middle << log10(absolute[i][j]) << " ";
				break;
			default:
				break;
			}
		}
		progressive_2pkt_start << endl;
		central_2pkt_middle << endl;
		backward_2pkt_end << endl;
		progressive_3pkt_start << endl;
		progressive_3pkt_middle << endl;
		backward_3pkt_middle << endl;
		backward_3pkt_end << endl;
		progressive_2pkt_middle << endl;
		backward_2pkt_middle << endl;
		h = h / 1.2;
	}
	progressive_2pkt_start.close();
	central_2pkt_middle.close();
	backward_2pkt_end.close();
	progressive_3pkt_start.close();
	progressive_3pkt_middle.close();
	backward_3pkt_middle.close();
	backward_3pkt_end.close();
	backward_2pkt_middle.close();
	progressive_2pkt_middle.close();
}
int main()
{
	cout << scientific;
	cout.precision(10);
	float h = 0.2;
	float data[maxLoopIteration][DATA_SIZE];
	float absolute[maxLoopIteration][DATA_SIZE];
	createDF_Absolute(data, absolute, h, accuracy_float_mode);
	writeToFile(absolute, h, accuracy_float_mode);
}