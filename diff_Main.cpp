#include <cstdio>
#include <cstdlib>
#include <conio.h>
#include <Windows.h>
#include "WorkSpace.h"

void Files_Main(char* buffer);

void main(int argc, char* argv[])
{
	printf("Running from %s\n", argv[0]);
	char output[MAX_PATH_SIZE] = "";
	Files_Main(output);

	WorkSpace Differentiation;
	if (Differentiation.Dialog(output))
	{
		getch();
	}
	else
	{
		printf("\nERROR DIFFER\n");
		getch();
	}
}

void Files_Main(char* buffer)
{
	printf("\nEnter \"yes\" to use standart file test.txt\n or enter way to directory like \"D:\\test.txt\"\n");
	scanf("%s", buffer);
	if (!strcmp("yes", buffer))
	{
		strcpy(buffer, "test.txt");
	}
	else
	{
		printf("\n Enter way to file\n");
		scanf("%s", buffer);
	}
}