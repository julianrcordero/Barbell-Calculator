#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <bitset>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

//bool contains(vector<double> v, double x)
//{
//	if (v.empty())
//		return false;
//	if (find(v.begin(), v.end(), x) != v.end())
//		return true;
//	else
//		return false;
//}
struct greater
{
	template<class T>
	bool operator()(T const &a, T const &b) const { return a > b; }
};

double adder()
{
	double input, sum = 45;
	for (;;)
	{
		cout << "Enter plate pair, 0 to show, or -1 to quit" << endl;
		cin >> input;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Error, please enter a number" << endl;
			continue;
		}
		if (input == -1)
			return 0;
		else if (input == 0)
			break;
		else if (input > 0)
			sum += 2 * input;
		else
			cout << "Enter a positive number" << endl;
	}
	return sum;
}

bool prompt(vector<double> &plates)
{
	double input;
	for (;;)
	{
		cout << "Enter plate pair, 0 to show, -1 to quit" << endl;
		cin >> input;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Error, please enter a number" << endl;
			continue;
		}
		if (input == -1)
			return false;
		if (input == 0)
			break;
		else if (input < 0)
		{
			cout << "Enter a positive number" << endl;
			continue;
		}
		plates.push_back(input);
	}
	return true;
}


void fillValues(vector<double> &plates, vector<pair<double, string>> &values)
{
	double size = pow(2, plates.size());
	double sum = 0;
	for (unsigned int integer = 0; integer < size; integer++)	//for each binary number in plates.size()
	{
		std::ostringstream oss;
		sum = 45;
		bitset<16> x(integer);		//each integer up to num of plates becomes binary 16 just because, I guess

		for (unsigned int i = plates.size() - 1; i >= 0; i--)
		{
			if (x[i])
			{
				sum += 2 * plates[i];
				oss << " - " << plates[i] << "pair";
			}
		}
		values.push_back(make_pair(sum, oss.str()));
	}
}


void display(vector<pair<double, string>> &values, vector<double> &plates)
{
	ofstream myfile;
	myfile.open("output.txt");
	
	for (unsigned int i = 0; i < plates.size(); i++)
	{
		unsigned int count = 1;

		unsigned int limit = plates.size() - 1;
		while (i < limit && plates[i] == plates[i + 1])
		{
			count++;
			i++;
		}
		myfile << plates[i] << "(" << count * 2 << ")\t";
		cout << plates[i] << "(" << count * 2 << ")\t";
	}
	myfile << "\n\n";
	cout << "\n\n";

	for (unsigned int i = 0; i < values.size(); i++)
	{
	nextIndexEvaluation:
		if (i + 1 < values.size())
		{
			if (values[i + 1].first != values[i].first)
			{
				myfile << values[i].first << "" << values[i].second << "\n\n";
				cout << values[i].first << "" << values[i].second << "\n" << endl;
			}

			else
			{
				if (values[i].first < 100)
					values[i].second.append("\n  ");
				else
					values[i].second.append("\n   ");

				values[i].second.append(values[i + 1].second);
				values.erase(values.begin() + i + 1);
				goto nextIndexEvaluation;
			}
		}
		else
		{
			myfile << values[i].first << "" << values[i].second << "\n\n";
			cout << values[i].first << "" << values[i].second << "\n" << endl;
		}
	}
	myfile.close();
}


int main()
{
	string choice;

	for (;;)
	{
		cout << "'adder' or 'combinationmaker'" << endl;
		cin >> choice;

		if (choice.compare("adder") == 0)
		{
			for (;;)
			{
				double sum = adder();
				if (sum == 0)
					break;

				cout << "Sum is " << sum << "lbs\n" << endl;
			}
		}

		else if (choice.compare("combinationmaker") == 0)
		{
			for (;;)
			{
				vector<double> plates;
				vector<pair<double, string>> values;

				if (!prompt(plates))
					break;
				sort(plates.begin(), plates.end(), greater());

				fillValues(plates, values);
				sort(values.begin(), values.end());

				display(values, plates);
			}
		}
	}
	return 0;
}