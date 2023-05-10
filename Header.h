
#pragma once
#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <string.h>
#define N 50


typedef struct {
	char username[N];
	char password[N];
	int level;
	char fullname[N];
	struct user *next, *prev;
}user;

typedef struct {
	user *head, *tail;
}users;

typedef struct {
	int catalogNo;
	char title[N];
	char authorName[N];
	char dateOfPublication[N];
	int unitsInStock;
	int price;
	struct book *next, *prev;
}book;

typedef struct {
	book *head, *tail;
}books;

void menu(user *currworker, books *items, users *workers, FILE *FLog);
void FreeItemsWorkers(books *items, users *workers);

//......works.c.......//

user* log_in(users *workers);
void Check_files();
user* createUser();
void importData(users *workers, char *path);
char* RemoveSpaces(char* input);
void addWorker(users *workers, char* username, char* password, int level, char* fullname);
users* createUsers();
void UpdatingUsers(users *workers, FILE *FLog);
void ViewWorkers(users *workers, FILE *FLog);
void DeleteWorker(users *workers, FILE *FLog);
void InsertNewUsers(users *workers, FILE *FLog);
void WriteToFileWorkers(users *workers);


//......items.c.......//

void importDataItems(books *items, char *path);
book* createBock();
void addBock(books *items, int catalogNo, char* title, char* authorName, char* dateOfPublication, int unitsInStock, int price);
books* createBocks();
void ViewItems(books *items, FILE *FLog);
void InsertNewItems(books *items, FILE *FLog);
void UpdatingItems(books *items, FILE *FLog);
void DeleteItems(books *items, FILE *FLog);
void WriteToFileItems(books *items);
