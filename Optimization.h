#ifndef OPTIMIZATION_DIFFER_H
#define OPTIMIZATION_DIFFER_H

#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include "System.h"

using std::string;
using std::vector;
using std::pair;
using std::vector;

class Optimize
{
private:
	string error;
	vector<double>& numbs_;
	int place_;

	double Commands_One(Equation* left, Equation* right, size_t com);
	double Commands_Two(double left, double right, size_t com);

	double Sum_(double left, double right);
	double Div_(double left, double right);
	double Mul_(double left, double right);
	double Sub_(double left, double right);
	double ln_(double left, double right);
	double Sin_(double left, double right);
	double Cos_(double left, double right);
	double Tg_(double left, double right);
	double Ctg_(double left, double right);
	double Exp_(double left, double right);
	double Deg_(double left, double right);

public:
	double Optimize_C(Equation* head);

	explicit Optimize(vector<double>& numbs, int place)
		: error("Error - default\n"), numbs_(numbs) {  }
};

double Optimize::Optimize_C(Equation* head)
{
	try
	{
		char do_t = head->return_data().first;
		if (do_t == 'C')
		{
			double res = Commands_One(head->left_l(), head->right_l(), head->return_data().second);
			if (res != NAN)
			{
				return res;
			}
			else
			{
				error = "Error - Commanders_One\n";
				throw error;
			}
		}
		if (do_t == 'V')
		{
			size_t do_f = head->return_data().second;
			size_t length = numbs_.size();
			if (do_f < numbs_.size())
			{
				if ((head->left_l() == nullptr) && (head->right_l() == nullptr))
				{
					return numbs_[do_f];
				}
				else
				{
					error = "Error - Tree wrong 1\n";
					throw error;
				}
			}
			else
			{
				error = "Error - Find Var\n";
				throw error;
			}
		}
		if (do_t == 'N')
		{
			if ((head->left_l() == nullptr) && (head->right_l() == nullptr))
			{
				return head->return_data().second;
			}
			else
			{
				error = "Error - Tree wrong 2\n";
				throw error;
			}
		}
		else
		{
			error = "Error - Calculate_C\n";
			throw error;
		}
	}
	catch (string error)
	{
		printf("%s\n", error.c_str());
		return NAN;
	}
}


double Optimize::Sum_(double left, double right)
{
	return true;
}
double Optimize::Div_(double left, double right)
{
	return true;
}
double Optimize::Mul_(double left, double right)
{
	return true;
}
double Optimize::Sub_(double left, double right)
{
	return true;
}
double Optimize::ln_(double left, double right)
{
	return true;
}
double Optimize::Sin_(double left, double right)
{
	return true;
}
double Optimize::Cos_(double left, double right)
{
	return true;
}
double Optimize::Tg_(double left, double right)
{
	return true;
}
double Optimize::Ctg_(double left, double right)
{
	return true;
}
double Optimize::Exp_(double left, double right)
{
	return true;
}


#endif OPTIMIZATION_DIFFER_H