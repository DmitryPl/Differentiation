#ifndef WORKSPACE_DIFFER_H
#define WORKSPACE_DIFFER_H

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Derivative.h"
#include "Optimization.h"
#include "Calculate.h"
#include "Tree.h"
#include "System.h"

using std::string;
using std::vector;
using std::pair;
using std::vector;

class WorkSpace
{
private:
	//Files
	std::ifstream file;
	std::ofstream file_out;

	//Trees
	Equation* head_;
	Equation* head_main = nullptr;
	Equation* diff_tree;

	//System
	string error;
	char* output_;
	Var_Names Variable;
	Var_Num Numbers;
	int place;

	bool Files(char* output);
	bool Read();
	bool Start();
	bool Write(char* output, Equation* head);
	bool Write_Tree(Equation* head);
	bool Calculate_F();
	bool Differ_F();
	bool Push_Comm(string word);
	bool Variables(int flag);
	string Return_Str(Equation* head);

public:
	explicit WorkSpace() : error("Error - default\n") { head_ = nullptr; }

	bool Dialog(char* output);
};

bool WorkSpace::Files(char* output)
{
	try
	{
		output_ = output;
		file.open(output);
		if (file.bad())
		{
			error = "bad file\n";
			throw error;
		}
		return true;
	}
	catch (string error)
	{
		printf("%s\n", error.c_str());
		return false;
	}
}

bool WorkSpace::Dialog(char* output)
{
	try
	{
		printf("\nSTARTING AKINATOR\n");
		if (Files(output))
		{
			if (Read())
			{
				head_ = head_main;
				if (Start())
				{
					Write(output_, head_main);
					file.close();
					printf("\nEND AKINATOR\n");
					return true;
				}
				else
				{
					error = "Error - Start\n";
					file.close();
					throw error;
				}
			}
			else
			{
				error = "Error - Read\n";
				file.close();
				throw error;
			}
		}
		else
		{
			error = "Error - Files\n";
			throw error;
		}
	}
	catch (string error)
	{
		printf("%s\n", error.c_str());
		return false;
	}
}

string WorkSpace::Return_Str(Equation* head)
{
	if (head->return_data().first == 'C')
	{
		int com = head->return_data().second;
#define WS_COMMANDS(CONST, STR) if (com == CONST) { return STR; }
		WS_COMMANDS(SUM, "+");
		WS_COMMANDS(DIV, "-");
		WS_COMMANDS(MUL, "*");
		WS_COMMANDS(SUB, "/");
		WS_COMMANDS(LN, "ln");
		WS_COMMANDS(SIN, "sin");
		WS_COMMANDS(COS, "cos");
		WS_COMMANDS(TG, "tg");
		WS_COMMANDS(CTG, "ctg");
		WS_COMMANDS(EXP, "exp");
		WS_COMMANDS(DEG, "^");
#undef WS_COMMANDS
	}
	if (head->return_data().first == 'N')
	{
		string buf;
		return getStrFromNumber(head->return_data().second, buf);
	}
	if (head->return_data().first == 'V')
	{
		size_t num = head->return_data().second;
		if (num < Variable.size())
		{
			return Variable[num];
		}
	}
	else
		return "False-String\n";
}

bool WorkSpace::Write_Tree(Equation* head)
{
	string word = Return_Str(head);
	if (word != "False-String\n")
	{
		file_out << word << " ";
		if (head->left_l())
		{
			file_out << " ( ";
			Write_Tree(head->left_l());
		}
		if (head->right_l())
		{
			Write_Tree(head->right_l());
			file_out << " ) ";
		}
		return true;
	}
	else
	{
		printf("%s", word.c_str());
		return false;
	}
}

bool WorkSpace::Write(char* output, Equation* head)
{
	file_out.open(output);
	head_ = head;
	file_out << " ( ";
	Write_Tree(head_);
	file_out << " ) !";
	file_out.close();
	return true;
}

bool WorkSpace::Start()
{
	try
	{
		string word;
		printf("\n\nDo you want to calculate, differentiate? Enter: cl\\df\n");
		while (true)
		{
			std::cin >> word;
			if (word == "cl")
			{
				if (Calculate_F())
				{
					return true;
				}
				else
				{
					error = "Error - Calculate\n";
					throw error;
				}
			}
			if (word == "df")
			{
				if (Differ_F())
				{
					return true;
				}
				else
				{
					error = "Error - Differ\n";
					throw error;
				}
			}
			if (word == "exit")
			{
				return true;
			}
			else
				printf("It's not a command. Try again.\n");
		}
	}
	catch (string error)
	{
		printf("%s\n", error.c_str());
		return false;
	}
}

bool WorkSpace::Push_Comm(string word)
{
	try
	{
#define Commands_Tree(STR, COM, CHAR_) if(word == STR) { head_->write(std::make_pair(CHAR_, COM)); return true; }
		Commands_Tree("+", SUM, 'C');
		Commands_Tree("-", SUB, 'C');
		Commands_Tree("*", MUL, 'C');
		Commands_Tree("/", DIV, 'C');
		Commands_Tree("ln", LN, 'C');
		Commands_Tree("sin", SIN, 'C');
		Commands_Tree("cos", COS, 'C');
		Commands_Tree("tg", TG, 'C');
		Commands_Tree("ctg", CTG, 'C');
		Commands_Tree("exp", EXP, 'C');
		Commands_Tree("^", DEG, 'C');
#undef Commands_Tree

		if (IsItNumber(word))
		{
			head_->write(std::make_pair('N', atoi(word.c_str())));
		}
		else
		{
			size_t length = Variable.size();
			for (size_t i = 0; i < length; i++)
			{
				if (Variable[i] == word)
				{
					head_->write(std::make_pair('V', i));
					return true;
				}
			}
			Variable.push_back(word);
			Numbers.push_back(NULL);
			head_->write(std::make_pair('V', length));
			return true;
		}
	}
	catch (string error)
	{
		printf("%s\n", error.c_str());
		return false;
	}
}

bool WorkSpace::Read()
{
	try
	{
		if (!file.eof())
		{
			string word;
			file >> word;
			if (word != "!")
			{
				printf("Read Tree has read :%s\n", word.c_str());
				if (word == "(")
				{
					if (head_ == nullptr)
					{
						head_ = new Equation(head_);
						head_main = head_;
					}
					else
						head_ = head_->push(head_);

					if (head_ != nullptr)
					{
						if (!file.eof())
						{
							file >> word;
							printf("Read Tree has read :%s\n", word.c_str());
							if (Push_Comm(word))
							{
								if (Read())
								{
									return true;
								}
								else
								{
									error = "Error - Read 1\n";
									throw error;
								}
							}
							else
							{
								error = "Error - Push Comm 1\n";
								throw error;
							}
						}
						else
						{
							error = "Error - Read Tree\n";
							throw error;
						}
					}
					else
					{
						error = "Error - Error - push 1\n";
						throw error;
					}
				}
				if (word == ")")
				{
					Equation* tmp = head_->parent_l();
					if (tmp == nullptr)
					{
						printf("End\n");
						return true;
					}
					else
					{
						head_ = head_->parent_l();
						if (Read())
							return true;
						else
						{
							error = "Error - Read Tree\n";
							throw error;
						}
					}
				}
				else
				{
					Equation* tmp = head_->parent_l();
					head_ = tmp->push(tmp);
					if (head_ != nullptr)
					{
						if (Push_Comm(word))
						{
							if (Read())
							{
								return true;
							}
							else
							{
								error = "Error - Read 2\n";
								throw error;
							}
						}
						else
						{
							error = "Error - Push Comm 2\n";
							throw error;
						}
					}
					else
					{
						error = "Error - Error - push 2\n";
						throw error;
					}
				}
			}
			else
			{
				error = "End of file - Read_Tree\n";
				throw error;
			}
		}
		else
		{
			error = "End of file - Read_Tree\n";
			throw error;
		}
	}
	catch (string error)
	{
		printf("%s\n", error.c_str());
		return false;
	}
}

bool WorkSpace::Calculate_F()
{
	try
	{
		if (!Variables(Calc))
		{
			error = "Error - Variables\n";
			throw error;
		}
		Calculate Eq2(Numbers, False);
		double answer = Eq2.Calculate_C(head_main);
		if (!IsNaN(answer))
		{
			printf("Anwser: %f \n", answer);
			return true;
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
		return true;
	}
}

bool WorkSpace::Differ_F()
{
	try
	{
		if (!Variables(Diff))
		{
			error = "Error - Variables\n";
			throw error;
		}
		Derivative Equ1(head_main, Numbers, place);
		diff_tree = Equ1.Derivative_C(head_main);
		if (diff_tree != nullptr)
		{
			Optimize Eq4(Numbers, place);
			if (!IsNaN(Eq4.Optimize_C(diff_tree)))
			{
				Write("output.txt", diff_tree);
				return true;
			}
			else
			{
				error = "Error - Optimize_C\n";
				throw error;
			}
		}
		error = "Error - Derivative_C\n";
		throw error;
	}
	catch (string error)
	{
		printf("%s\n", error.c_str());
		return true;
	}
}

bool WorkSpace::Variables(int flag)
{
	try
	{
		if (flag == Diff)
		{
			if (Variable.size() == 0)
			{
				printf("0! Because there isn't any variable!\n");
				error = "Error - 0 Variables\n";
				throw error;
			}
			char flag = 'B';
			while (flag != 'E')
			{
				printf("By what variable we will differentiate?\n");
				string answer;
				std::cin >> answer;
				if (answer == "exit")
				{
					error = "Error - exit Variables\n";
					throw error;
				}
				size_t length = Variable.size();
				for (size_t i = 0; i < length; i++)
				{
					if (answer == Variable[i])
					{
						place = i;
						flag = 'E';
					}
				}
				if (flag != 'E')
					printf("Variable not found. Try again.\n");
			}
			return true;
		}
		if (flag == Calc)
		{
			printf("Enter a values of the variables.\n");
			size_t length = Variable.size();
			for (size_t i = 0; i < length; i++)
			{
				char flag = 'B';
				while (flag != 'E')
				{
					printf("Variable: %s ", Variable[i].c_str());
					string zuy;
					std::cin >> zuy;
					if (IsItNumber(zuy))
					{
						printf("%s\n", zuy.c_str());
						Numbers[i] = stof(zuy);
						flag = 'E';
					}
					else
						printf("Try again\n");
				}
			}
			return true;
		}
		else
		{
			error = "Error - wrong flag\n";
			throw error;
		}
	}
	catch (string error)
	{
		printf("%s\n", error.c_str());
		return false;
	}
}

#endif WORKSPACE_DIFFER_H