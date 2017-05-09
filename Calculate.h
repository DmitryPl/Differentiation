#ifndef CALCULATE_DIFFER_H
#define CALCULATE_DIFFER_H

#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <math.h>
#include "System.h"

using std::string;
using std::vector;
using std::pair;
using std::vector;

class Calculate
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
	double Calculate_C(Equation* head);

	explicit Calculate(vector<double>& numbs, int place)
		: error("Error - default\n"), numbs_(numbs) {  }
};

double Calculate::Calculate_C(Equation* head)
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

double Calculate::Commands_One(Equation* left, Equation* right, size_t com)
{
	try
	{
		double lefter;
		double righter;
		if (left != nullptr)
		{
			lefter = Calculate_C(left);
			if (lefter == NAN)
			{
				error = "Error - left\n";
				throw error;
			}
		}
		else
			lefter = NAN;
		if (right != nullptr)
		{
			righter = Calculate_C(right);
			if (righter == NAN)
			{
				error = "Error - left\n";
				throw error;
			}
		}
		else
			righter = NAN;
		lefter = Commands_Two(lefter, righter, com);
		if (lefter != NAN)
		{
			return lefter;
		}
		else
		{
			error = "Error - Commanders_Two\n";
			throw error;
		}
	}
	catch (string error)
	{
		printf("%s\n", error.c_str());
		return NAN;
	}
}

double Calculate::Commands_Two(double left, double right, size_t com)
{
#define CALC_COMMANDS(CONST, FUNC) if (com == CONST) { return FUNC(left, right); }
	CALC_COMMANDS(SUM, Sum_);
	CALC_COMMANDS(DIV, Div_);
	CALC_COMMANDS(MUL, Mul_);
	CALC_COMMANDS(SUB, Sub_);
	CALC_COMMANDS(LN, ln_);
	CALC_COMMANDS(SIN, Sin_);
	CALC_COMMANDS(COS, Cos_);
	CALC_COMMANDS(TG, Tg_);
	CALC_COMMANDS(CTG, Ctg_);
	CALC_COMMANDS(EXP, Exp_);
	CALC_COMMANDS(DEG, Deg_);
#undef CALC_COMMANDS
	printf("It's not a command.\n");
	return NAN;
}

double Calculate::Sum_(double left, double right)
{
	if ((left != NAN) && (right != NAN))
	{
		return left + right;
	}
	else
	{
		printf("Error - Bad - Numbers - Sum\n");
		return NAN;
	}
}
double Calculate::Div_(double left, double right)
{
	if ((left != NAN) && (right != NAN) && (right != NULL))
	{
		return left / right;
	}
	else
	{
		if (right == NULL)
		{
			printf("Error - right - NULL - Div\n");
			return NAN;
		}
		else
		{
			printf("Error - Bad Numbers - Div\n");
			return NAN;
		}
	}
}
double Calculate::Mul_(double left, double right)
{
	if ((left != NAN) && (right != NAN))
	{
		return left * right;
	}
	else
	{
		printf("Error - Bad - Numbers - Mul\n");
		return NAN;
	}
}
double Calculate::Sub_(double left, double right)
{
	if ((left != NAN) && (right != NAN))
	{
		return left - right;
	}
	else
	{
		printf("Error - Bad - Numbers - Sub\n");
		return NAN;
	}
}
double Calculate::ln_(double left, double right)
{
	if (right == NAN)
	{
		if (left != NAN)
		{
			return log(left);
		}
		else
		{
			printf("Error - Bad - Numbers - ln\n");
			return NAN;
		}
	}
	else
	{
		printf("Error - Bad - Tree - ln\n");
		return NAN;
	}
}
double Calculate::Sin_(double left, double right)
{
	if (right == NAN)
	{
		if (left != NAN)
		{
			return sin(left);
		}
		else
		{
			printf("Error - Bad - Numbers - Sin\n");
			return NAN;
		}
	}
	else
	{
		printf("Error - Bad - Tree - Sin\n");
		return NAN;
	}
}
double Calculate::Cos_(double left, double right)
{
	if (right == NAN)
	{
		if (left != NAN)
		{
			return cos(left);
		}
		else
		{
			printf("Error - Bad - Numbers - cos\n");
			return NAN;
		}
	}
	else
	{
		printf("Error - Bad - Tree - cos\n");
		return NAN;
	}
}
double Calculate::Tg_(double left, double right)
{
	if (right == NAN)
	{
		if (left != NAN)
		{
			return tan(left);
		}
		else
		{
			printf("Error - Bad - Numbers - tg\n");
			return NAN;
		}
	}
	else
	{
		printf("Error - Bad - Tree - tg\n");
		return NAN;
	}
}
double Calculate::Ctg_(double left, double right)
{
	if (right == NAN)
	{
		if (left != NAN)
		{
			return 1/tan(left);
		}
		else
		{
			printf("Error - Bad - Numbers - ctg\n");
			return NAN;
		}
	}
	else
	{
		printf("Error - Bad - Tree - ctg\n");
		return NAN;
	}
}
double Calculate::Exp_(double left, double right)
{
	if (right == NAN)
	{
		if (left != NAN)
		{
			return exp(left);
		}
		else
		{
			printf("Error - Bad - Numbers - exp\n");
			return NAN;
		}
	}
	else
	{
		printf("Error - Bad - Tree - exp\n");
		return NAN;
	}
}
double Calculate::Deg_(double left, double right)
{
	if ((left != NAN) && (right != NAN))
	{
		return pow(left, right);
	}
	else
	{
		printf("Error - Bad - Numbers - Deg\n");
		return NAN;
	}
}

#endif CALCULATE_DIFFER_H