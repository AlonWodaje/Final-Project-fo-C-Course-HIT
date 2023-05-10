/*
Assigned by:
alon wodale #311291215
Student2_Full_Name #ID
*/
#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include<stdlib.h>
#include "Header.h"


void main()
{
	int i;
	user *currworker;
	users *workers;
	books *items;
	FILE *FLog;
	fopen_s(&FLog, "loog.dat", "a");	
	workers = createUsers();
	items = createBocks();
	Check_files();
	importData(workers, "Working.dat");
	importDataItems(items, "Items.dat");
	currworker = log_in(workers);
	if (currworker == NULL)
		return;
	currworker = workers->head;
	fprintf(FLog, "the user %s log in\n", currworker->fullname);
	menu(currworker, items, workers, FLog);
	fprintf(FLog, "the user %s log out\n", currworker->fullname);
	WriteToFileItems(items);
	WriteToFileWorkers(workers);
	FreeItemsWorkers(items, workers);
}


void menu(user *currworker, books *items, users *workers, FILE *FLog)
{
	int i;
	switch (currworker->level)
	{
	case 1:
		printf(" to view for a items click   1\n to add items click          2");
		scanf("%d", &i);
		if (i == 1)
			ViewItems(items, FLog);
		else if (i == 2)
			InsertNewItems(items, FLog);
		else
			printf("You typed the wrong number");
	case 2:
		printf(" to view for a items click   1\n to add items click          2\n to updating items click     3\n to delete items click       4");
		scanf("%d", &i);
		if (i == 1)
			ViewItems(items, FLog);
		else if (i == 2)
			InsertNewItems(items, FLog);
		else if (i == 3)
			UpdatingItems(items, FLog);
		else if (i == 4)
			DeleteItems(items, FLog);
		else
			printf(" You typed the wrong number");
	case 3:
		printf("\n to view for a items click    1\n to add items click           2\n to updating items click      3\n to delete items click        4");
		printf("\n to view for a worker click   5\n to add worker click          6\n to updating worker click     7\n to delete worker click       8\n\n the numbe : ");
		scanf("%d", &i); 
		if (i == 1)
			ViewItems(items, FLog);
		else if (i == 2)
			InsertNewItems(items, FLog);
		else if (i == 3)
			UpdatingItems(items, FLog);
		else if (i == 4)
			DeleteItems(items, FLog);
		else if (i == 5) 
			ViewWorkers(workers, FLog);
		else if (i == 6)
			InsertNewUsers(workers, FLog);
		else if (i == 7)
			UpdatingUsers(workers, FLog);
		else if (i == 8)
			DeleteWorker(workers, FLog);
		else
			printf(" You typed the wrong number");
	}
	printf("\n Return to the main menu Press  1 else the program will end\n\n click the number : ");
	scanf("%d", &i);
	if (i == 1)
		menu(currworker, items, workers, FLog);
}

void FreeItemsWorkers(books *items, users *workers)
{
	book *it;
	user *wor;
	it = items->head;
	wor = workers->head;
	while (workers->head !=NULL)
	{
		workers->head = workers->head->next;
		free(wor);
		wor = workers->head;
	}
	while (items->head != NULL)
	{
		items->head = items->head->next;
		free(it);
		it = items->head;
	}
}