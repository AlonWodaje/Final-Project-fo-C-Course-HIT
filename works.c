/*
Assigned by:
alon wodale  #311291215
Student2_Full_Name #ID
*/
#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include<stdlib.h>
#include "Header.h"

users* createUsers() {
	users* temp;
	temp = (users*)malloc(sizeof(users));
	temp->head = createUser();
	temp->tail = createUser();
	temp->head = temp->tail = NULL;
	return temp;
}

user* createUser() {
	user* temp;
	temp = (user*)malloc(sizeof(user));
	temp->next = temp->prev = NULL;
	return temp;
}

char* RemoveSpaces(char* input)
{
	int i, j;
	char* output = input;
	for (i = 0, j = 0; i < strlen(input); i++, j++)
	{
		if (input[i] != ' ')
			output[j] = input[i];
		else
			j--;
	}
	output[j] = 0;
	return output;
}

void Check_files()
{
	char user_name[N], password[N], level[N], full_namea[N];
	user worker1;
	FILE *Items, *Working, *log;
	Items = fopen("Items.dat", "r");
	log = fopen("loog.dat", "r");
	Working = fopen("Working.dat", "r");

	if (Items == NULL)
		Items = fopen("Items.dat", "w");
	if (log == NULL)
		log = fopen("loog.dat", "w");
	if (Working == NULL)
	{
		Working = fopen("Working.dat", "w");
		fprintf(Working, " username            password            level               full name");
		fprintf(Working, "\n admin      admin     3      Manager_System");
		strcpy(worker1.username, "admin");
		strcpy(worker1.password, "admin");
		worker1.level = 3;
		strcpy(worker1.fullname, "Manager_System");
	}
	fclose(Items);
	fclose(Working);
	//fclose(log);
}
user* log_in(users *workers)
{
	int i;
	FILE *log;
	user *p;
	char user_name1[N], password1[N];
	printf("\n To log in, enter a username and password  \n");
	for ( i = 0; i < 3; i++)
	{
		printf("\n username : ");
		scanf("%s", &user_name1);
		printf(" password : ");
		scanf("%s", &password1);
		p = workers->head;
		while (p != NULL)
		{
			if (!(strcmp(RemoveSpaces(user_name1), p->username)) && !(strcmp(RemoveSpaces(password1), p->password)))
			{
				return p;
			}

			p = p->next;
		}
		printf("\n Incorrect username or password");
	}
	return NULL;
}

void importData(users *workers, char *path)
{
	int level;
	char username[21], password[21], fullname[21];	
	char h1[21], h2[21], h3[21], h4[21];

	FILE *FWorking;
	fopen_s(&FWorking, path, "r");
	if (!FWorking)
	{
		printf("\n File not found!\n");
		return 0;
	}

	fscanf(FWorking, "%20s%20s%20s%20s", h1, h2, h3, h4);
	while (fscanf(FWorking, "%20s%20s%20d%20s", username, password, &level, fullname) > 0)
	{
		addWorker(workers, RemoveSpaces(username), RemoveSpaces(password), level, RemoveSpaces(fullname));
	}
	fclose(FWorking);
}


void addWorker(users *workers, char* username, char* password, int level, char* fullname) {
	user *temp, *p;
	temp = createUser();

	temp->level = level;
	strcpy(temp->fullname, fullname);
	strcpy(temp->password, password);
	strcpy(temp->username, username);

	if (workers->head == NULL) {
		workers->head = temp;
	}
	else {
		p = workers->head;
		while (p->next != NULL) {
			p = p->next;
		}
		temp->prev = p;
		p->next = temp;
	}
	workers->tail = temp;
}


void ViewWorkers(users *workers, FILE *FLog)
{
	user *p;
	printf("\n user name            password            level               full name            \n\n");
	p = workers->head;
	while (p != NULL)
	{
		printf(" %-20s %-19s %-19d %-20s\n", p->username, p->password, p->level, p->fullname);
		p = p->next;
	}
	fprintf(FLog, "the user view workers \n");
}

void InsertNewUsers(users *workers, FILE *FLog)
{
	int level;
	char username[21], password[21], fullname[21];
	fprintf(FLog, "the user insert new worker \n");
	printf("\n enter level : ");
	scanf("%d", &level);
	printf(" enter user name : ");
	scanf("%s", username);
	printf(" enter password : ");
	scanf("%s", password);
	printf(" enter full name : ");
	scanf("%s", fullname);

	addWorker(workers,  username,  password,  level,  fullname);
}
void UpdatingUsers(users *workers, FILE *FLog)
{
	user *p;
	int level;
	char username[21], fullname[21];
	printf("\n Enter a user name or full name\n");
	printf(" enter a user name : ");
	scanf("%s", username);
	printf(" enter a full name : ");
	scanf("%s", fullname);
	p = workers->head;

	while (p != NULL)
	{
		if (!(strcmp(p->username, username)) || !(strcmp(p->fullname, fullname)))
		{
			printf(" enter a level you want to change : ");
			scanf("%d", &level);
			p->level = level;
			fprintf(FLog, "the user updating worker \n");
		}
		p = p->next;
	}
}

void DeleteWorker(users *workers, FILE *FLog)
{
	user *p, *pp, *prev;
	char username[21];
	printf("\n Which user name would you like to delete. Enter the user name of the worker : ");
	scanf("%s", username);
	p = workers->head;
	pp = createUser();
	while (p != NULL)
	{
		if (!(strcmp(p->username, username)) && (p->prev == NULL)) {
			workers->head = workers->head->next;
			free(p);
			workers->head->prev = NULL;
			p = workers->head;
			fprintf(FLog, "the user delete worker \n");
		}
		else if (!(strcmp(p->username, username)) && (p->next == NULL))
		{
			pp = p->prev;
			pp->next = NULL;
			free(p);
			p = pp;
			fprintf(FLog, "the user delete worker \n");
			return;
		}
		else if (!(strcmp(p->username, username))) {
			pp = p->prev;
			pp->next = p->next;
			prev = pp;
			pp = p->next;
			pp->prev = prev;
			free(p);
			p = pp;
			fprintf(FLog, "the user delete worker \n");
		}
		p = p->next;
	}

}
void WriteToFileWorkers(users *workers)
{
	user *p;
	FILE *FWorkers;
	fopen_s(&FWorkers, "Working.dat", "w");
	p = workers->head;
	fprintf(FWorkers, " username            password            level               fullname            \n");
	while (p != NULL)
	{
		fprintf(FWorkers, " %-20s %-19s %-19d %-20s\n", p->username, p->password, p->level, p->fullname);
		p = p->next;
	}
	fclose(FWorkers);
}