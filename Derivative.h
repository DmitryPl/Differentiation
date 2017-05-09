#ifndef DERIVATIVE_DIFFER_H
#define DERIVATIVE_DIFFER_H

#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include "System.h"

using std::string;
using std::vector;
using std::pair;
using std::vector;

class Derivative
{
private:
	string error;
	Equation* head_;
	Equation* diff_head;
	vector<double>& numbs_;
	int place_;

	Equation* Commands_One(Equation* left, Equation* right, size_t com);
	Equation* Commands_Two(Equation* left, Equation* right);
	bool Find_Var(Equation* head);

	Equation* Sum_Sub(Equation* left, Equation* right, string mode, size_t Com);
	Equation* Sum_(Equation* left, Equation* right);
	Equation* Div_(Equation* left, Equation* right);
	Equation* Mul_(Equation* left, Equation* right);
	Equation* Sub_(Equation* left, Equation* right);
	Equation* ln_(Equation* left, Equation* right);
	Equation* Sin_(Equation* left, Equation* right);
	Equation* Cos_(Equation* left, Equation* right);
	Equation* Tg_(Equation* left, Equation* right);
	Equation* Ctg_(Equation* left, Equation* right);
	Equation* Exp_(Equation* left, Equation* right);
	Equation* Deg_(Equation* left, Equation* right);

public:
	Equation* Derivative_C(Equation* head);

	explicit Derivative(Equation* head, vector<double>& numbs, int place)
		: error("Error - default\n"), numbs_(numbs), place_(place)
	{
		head_ = head;
		diff_head = new Equation(nullptr);
	}
};

Equation* Derivative::Derivative_C(Equation* head)
{
	try
	{
		char do_t = head->return_data().first;
		if (do_t == 'C')
		{
			Equation* tmp = Commands_One(head->left_l(), head->right_l(), head->return_data().second);
			if (tmp != nullptr)
			{
				return tmp;
			}
			else
			{
				error = "Error - Derivate_C 1\n";
				throw error;
			}
		}
		if (do_t == 'V')
		{
			Equation* tmp;
			if (head->return_data().second == place_)
			{
				tmp = new Equation(std::make_pair('N', 1));
			}
			else
			{
				tmp = new Equation(std::make_pair('N', 0));
			}
			return tmp;
		}
		if (do_t == 'N')
		{
			Equation* tmp = new Equation(std::make_pair('N', 0));
			return tmp;
		}
		else
		{
			error = "Error - Derivate_C 2\n";
			throw error;
		}
	}
	catch (string error)
	{
		printf("%s\n", error.c_str());
		return nullptr;
	}
}

bool Derivative::Find_Var(Equation* head)
{
	if (head->return_data().first == 'V')
	{
		if (head->return_data().second == place_)
		{
			return true;
		}
	}
	if (head->left_l() != nullptr)
	{
		if (Find_Var(head->left_l()))
		{
			return true;
		}
	}
	if (head->right_l() != nullptr)
	{
		if (Find_Var(head->right_l()))
		{
			return true;
		}
	}
	return false;
}

Equation* Derivative::Commands_One(Equation* left, Equation* right, size_t com)
{
#define DER_COMMANDS(CONST, FUNC) if (com == CONST) { return FUNC(left, right); }
	DER_COMMANDS(SUM, Sum_);
	DER_COMMANDS(DIV, Div_);
	DER_COMMANDS(MUL, Mul_);
	DER_COMMANDS(SUB, Sub_);
	DER_COMMANDS(LN, ln_);
	DER_COMMANDS(SIN, Sin_);
	DER_COMMANDS(COS, Cos_);
	DER_COMMANDS(TG, Tg_);
	DER_COMMANDS(CTG, Ctg_);
	DER_COMMANDS(EXP, Exp_);
	DER_COMMANDS(DEG, Deg_);
#undef DER_COMMANDS
	printf("It's not a command.\n");
	return nullptr;
}

Equation* Derivative::Commands_Two(Equation* left, Equation* right)
{
	return nullptr;
}

Equation* Derivative::Sum_Sub(Equation* left, Equation* right, string mode, size_t Com)
{
	try
	{
		Equation* tmp1 = nullptr;
		Equation* tmp2 = nullptr;
		if ((left != nullptr) && (right != nullptr))
		{
			tmp1 = Derivative_C(left);
			if (tmp1 != nullptr)
			{
				doNothing();
			}
			else
			{
				error = "Error - left der";
				error = error + mode;
				throw error;
			}
			tmp2 = Derivative_C(right);
			if (tmp2 != nullptr)
			{
				doNothing();
			}
			else
			{
				error = "Error - right der";
				error = error + mode;
				throw error;
			}
			return new Equation(tmp1, tmp2, std::make_pair('C', Com));
		}
		else
		{
			error = "Error - Sum_Sub - bad tree\n";
			throw error;
		}
	}
	catch (string error)
	{
		printf("%s\n", error.c_str());
		return nullptr;
	}
}
Equation* Derivative::Sum_(Equation* left, Equation* right)
{
	try
	{
		string mode = "- Sum\n";
		Equation* tmp = nullptr;
		tmp = Sum_Sub(left, right, mode, SUM);
		if (tmp != nullptr)
		{
			return tmp;
		}
		else
		{
			error = "Error - Sum_Sub\n";
			throw error;
		}
	}
	catch (string error)
	{
		printf("%s\n", error.c_str());
		return nullptr;
	}
}
Equation* Derivative::Div_(Equation* left, Equation* right)
{
	try
	{
		if ((left != nullptr) && (right != nullptr))
		{
			Equation* tmp0 = nullptr;
			tmp0 = left->Copy(left);
			Equation* tmp1 = new Equation(tmp0, Derivative_C(right), std::make_pair('C', MUL));
			Equation* tmp2 = nullptr;
			tmp2 = right->Copy(right);
			Equation* tmp3 = new Equation(Derivative_C(left), tmp2, std::make_pair('C', MUL));
			Equation* tmp4 = new Equation(tmp1, tmp3, std::make_pair('C', SUB));
			Equation* tmp6 = nullptr;
			tmp6 = right->Copy(right);
			Equation* tmp7 = new Equation(std::make_pair('N', 2));
			Equation* tmp5 = new Equation(tmp6, tmp7, std::make_pair('C', DEG));
			return tmp5; // It's very bad... GovnoCode!
		}
		else
		{
			error = "Error - bad tree - dev - der \n";
			throw error;
		}
	}
	catch (string error)
	{
		printf("%s\n", error.c_str());
		return nullptr;
	}
}
Equation* Derivative::Mul_(Equation* left, Equation* right)
{
	try
	{
		if ((left != nullptr) && (right != nullptr))
		{
			Equation* tmp0 = nullptr;
			tmp0 = left->Copy(left);
			Equation* tmp1 = new Equation(tmp0, Derivative_C(right), std::make_pair('C', MUL));
			Equation* tmp2 = nullptr;
			tmp2 = right->Copy(right);
			Equation* tmp3 = new Equation(Derivative_C(left), tmp2, std::make_pair('C', MUL));
			Equation* tmp4 = new Equation(tmp1, tmp3, std::make_pair('C', SUM));
			return tmp4;
		}
		else
		{
			error = "Error - mul - der - bad tree \n";
			throw error;
		}
	}
	catch (string error)
	{
		printf("%s\n", error.c_str());
		return nullptr;
	}
}
Equation* Derivative::Sub_(Equation* left, Equation* right)
{
	try
	{
		string mode = "- Sub\n";
		Equation* tmp = Sum_Sub(left, right, mode, SUM);
		if (tmp != nullptr)
		{
			return tmp;
		}
		else
		{
			error = "Error - Sum_Sub\n";
			throw error;
		}
	}
	catch (string error)
	{
		printf("%s\n", error.c_str());
		return nullptr;
	}
}
Equation* Derivative::ln_(Equation* left, Equation* right)
{
	try
	{
		if ((left != nullptr) && (right == nullptr))
		{
			Equation* tmp1 = nullptr;
			tmp1 = left->Copy(left);
			Equation* tmp2 = new Equation(std::make_pair('N', 1));
			Equation* tmp0 = new Equation(tmp2, tmp1, std::make_pair('C', DIV));
			Equation* tmp3 = Derivative_C(left);
			return new Equation(tmp0, tmp3, std::make_pair('C', MUL));
		}
		else
		{
			error = "Error - ln bad tree\n";
			throw error;
		}
	}
	catch (string error)
	{
		printf("%s\n", error.c_str());
		return nullptr;
	}
}
Equation* Derivative::Sin_(Equation* left, Equation* right)
{
	try
	{
		if ((left != nullptr) && (right == nullptr))
		{
			Equation* tmp1 = nullptr;
			tmp1 = left->Copy(left);
			Equation* tmp0 = new Equation(tmp1, nullptr, std::make_pair('C', COS));
			Equation* tmp3 = Derivative_C(left);
			return new Equation(tmp0, tmp3, std::make_pair('C', MUL));
		}
		else
		{
			error = "Error - sin bad tree\n";
			throw error;
		}
	}
	catch (string error)
	{
		printf("%s\n", error.c_str());
		return nullptr;
	}
}
Equation* Derivative::Cos_(Equation* left, Equation* right)
{
	try
	{
		if ((left != nullptr) && (right == nullptr))
		{
			Equation* tmp1 = nullptr;
			tmp1 = left->Copy(left);
			Equation* tmp2 = new Equation(std::make_pair('N', -1));
			Equation* tmp0 = new Equation(tmp2, tmp1, std::make_pair('C', MUL));
			Equation* tmp3 = Derivative_C(left);
			return new Equation(tmp0, tmp3, std::make_pair('C', MUL));
		}
		else
		{
			error = "Error - cos bad tree\n";
			throw error;
		}
	}
	catch (string error)
	{
		printf("%s\n", error.c_str());
		return nullptr;
	}
}
Equation* Derivative::Tg_(Equation* left, Equation* right)
{
	try
	{
		if ((left != nullptr) && (right == nullptr))
		{
			Equation* tmp1 = nullptr;
			tmp1 = left->Copy(left);
			Equation* tmp5 = new Equation(tmp1, nullptr, std::make_pair('C', COS));
			Equation* tmp4 = new Equation(std::make_pair('N', 2));
			Equation* tmp7 = new Equation(tmp5, tmp4, std::make_pair('C', DEG));
			Equation* tmp2 = new Equation(std::make_pair('N', 1));
			Equation* tmp0 = new Equation(tmp2, tmp7, std::make_pair('C', DIV));
			Equation* tmp3 = Derivative_C(left);
			return new Equation(tmp0, tmp3, std::make_pair('C', MUL));
		}
		else
		{
			error = "Error - tg bad tree\n";
			throw error;
		}
	}
	catch (string error)
	{
		printf("%s\n", error.c_str());
		return nullptr;
	}
}
Equation* Derivative::Ctg_(Equation* left, Equation* right)
{
	try
	{
		if ((left != nullptr) && (right == nullptr))
		{
			Equation* tmp1 = nullptr;
			tmp1 = left->Copy(left);
			Equation* tmp5 = new Equation(tmp1, nullptr, std::make_pair('C', SIN));
			Equation* tmp4 = new Equation(std::make_pair('N', 2));
			Equation* tmp7 = new Equation(tmp5, tmp4, std::make_pair('C', DEG));
			Equation* tmp2 = new Equation(std::make_pair('N', -1));
			Equation* tmp0 = new Equation(tmp2, tmp7, std::make_pair('C', DIV));
			Equation* tmp3 = Derivative_C(left);
			return new Equation(tmp0, tmp3, std::make_pair('C', MUL));
		}
		else
		{
			error = "Error - ctg bad tree\n";
			throw error;
		}
	}
	catch (string error)
	{
		printf("%s\n", error.c_str());
		return nullptr;
	}
}
Equation* Derivative::Exp_(Equation* left, Equation* right)
{
	try
	{
		if ((left != nullptr) && (right == nullptr))
		{
			Equation* tmp1 = nullptr;
			tmp1 = left->Copy(left);
			Equation* tmp5 = new Equation(tmp1, nullptr, std::make_pair('C', EXP));
			Equation* tmp3 = Derivative_C(left);
			return new Equation(tmp5, tmp3, std::make_pair('C', MUL));
		}
		else
		{
			error = "Error - exp bad tree\n";
			throw error;
		}
	}
	catch (string error)
	{
		printf("%s\n", error.c_str());
		return nullptr;
	}
}
Equation* Derivative::Deg_(Equation* left, Equation* right)
{
	try
	{
		if ((left != nullptr) && (right != nullptr))
		{
			if (Find_Var(left))
			{
				if (Find_Var(right))
				{
					Equation* tmp1 = nullptr;
					tmp1 = left->Copy(left);
					Equation* tmp2 = nullptr;
					tmp2 = right->Copy(right);
					Equation* tmp7 = nullptr;
					tmp7 = right->Copy(right);
					Equation* tmp3 = new Equation(std::make_pair('N', 1));
					Equation* tmp4 = new Equation(tmp2, tmp3, std::make_pair('C', SUB));
					Equation* tmp5 = new Equation(tmp1, tmp4, std::make_pair('C', DEG));
					Equation* tmp6 = new Equation(tmp7, tmp4, std::make_pair('C', MUL));
					Equation* tmp0 = Derivative_C(right);
					return new Equation(tmp6, tmp0, std::make_pair('C', MUL));
				}
				else
				{
					Equation* tmp1 = nullptr;
					tmp1 = left->Copy(left);
					Equation* tmp2 = nullptr;
					tmp2 = right->Copy(right);
					Equation* tmp7 = nullptr;
					tmp7 = right->Copy(right);
					Equation* tmp3 = new Equation(std::make_pair('N', 1));
					Equation* tmp4 = new Equation(tmp2, tmp3, std::make_pair('C', SUB));
					Equation* tmp5 = new Equation(tmp1, tmp4, std::make_pair('C', DEG));
					return new Equation(tmp7, tmp4, std::make_pair('C', MUL));
				}
			}
			else
			{
				if (Find_Var(right))
				{
					Equation* tmp1 = nullptr;
					tmp1 = left->Copy(left);
					Equation* tmp2 = nullptr;
					tmp2 = right->Copy(right);
					Equation* tmp3 = new Equation(tmp1, tmp2, std::make_pair('C', DEG));
					Equation* tmp4 = nullptr;
					tmp4 = left->Copy(tmp4);
					Equation* tmp5 = new Equation(tmp4, nullptr, std::make_pair('C', LN));
					return new Equation(tmp3, tmp5, std::make_pair('C', MUL));
				}
				else
				{
					return new Equation(std::make_pair('N', 0));
				}
			}
		}
		else
		{
			error = "Error - deg bad tree\n";
			throw error;
		}
	}
	catch (string error)
	{
		printf("%s\n", error.c_str());
		return nullptr;
	}
}

#endif DERIVATIVE_DIFFER_H