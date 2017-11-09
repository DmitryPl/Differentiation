#ifndef SYSTEM_DIFFER_H
#define SYSTEM_DIFFER_H

#include <cstdlib>
#include <string>
#include <exception>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "Tree.h"

using std::string;
using std::vector;
using std::pair;
using std::vector;

typedef pair<char, int> data;
typedef vector<string> Var_Names;
typedef vector<double> Var_Num;
typedef Tree<data> Equation;

enum Commands
{ SUM = 10, DIV, MUL, SUB, LN, SIN, COS, TG, CTG, EXP, DEG };

enum Sys
{
	Calc = 1, Diff, True = 5, False = -5, SUCCESS = 42, MAX_PATH_SIZE = 32
};

int doNothing()
{
	return SUCCESS;
}

bool IsNaN(double num)
{
	return num != num;
}

bool IsItNumber(string word)
{
	size_t i = 0;
	if (word[0] == '-')
	{
		i++;
	}
	while (word[i] != '\0')
	{
		if (!isdigit(word[i++]))
			return false;
	}
	return true;
}

string getStrFromNumber(float num, string buf)
{
	float mod = 0;
	float y = 0;
	if (num > 0)
	{
		y = log10(num);
	}
	else if (num == 0)
	{
		return "0";
	}
	else 
	{
		num = num * -1;
		y = log10(num);
	}
	modf(y, &mod);
	int x = mod;
	char* res = (char*)malloc(x + 15);
	sprintf(res, "%g", num);
	buf = res;
	return buf;
}

#endif SYSTEM_DIFFER_H