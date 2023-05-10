/*
Assigned by:
alon wodale  #311291215
Student2_Full_Name #ID
*/
#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include<stdlib.h>
#include "Header.h"

books* createBocks() {
	books* temp;
	temp = (books*)malloc(sizeof(books));
	temp->head = createBock();
	temp->tail = createBock();
	temp->head = temp->tail = NULL;
	return temp;
}

book* createBock() {
	book* temp;
	temp = (book*)malloc(sizeof(book));
	temp->next = temp->prev = NULL;
	return temp;
}

void importDataItems(books *items , char *path)
{
	int catalogNo, unitsInStock, price;
	char title[21], authorName[21], dateOfPublication[21];
	char h1[21], h2[21], h3[21], h4[21], h5[21], h6[21];

	FILE *FItems;
	fopen_s(&FItems, path, "r");
	if (!FItems)
	{
		printf("\n File not found!\n");
		return 0;
	}

	fscanf(FItems, "%20s%20s%20s%20s%20s%20s", h1, h2, h3, h4, h5, h6);
	//fscanf_s(FItems, " %%20d%20s%20s%20s%20d%20d", &catalogNo, title, authorName, dateOfPublication, &unitsInStock, &price);
	while (fscanf(FItems, "%20d%20s%20s%20s%20d%20d", &catalogNo, title, authorName, dateOfPublication, &unitsInStock, &price) > 0)
	{
		addBock(items, catalogNo, RemoveSpaces(title), RemoveSpaces(authorName), RemoveSpaces(dateOfPublication), unitsInStock, price);
	}
	fclose(FItems);
}


void addBock(books *items, int catalogNo, char* title, char* authorName, char* dateOfPublication, int unitsInStock, int price) {
	book *temp, *p;
	temp = createBock();

	temp->catalogNo = catalogNo;
	strcpy(temp->title, title);
	strcpy(temp->authorName, authorName);
	strcpy(temp->dateOfPublication, dateOfPublication);
	temp->unitsInStock = unitsInStock;
	temp->price = price;

	if (items->head == NULL) {
		items->head = temp;
	}
	else {
		p = items->head;
		while (p->next != NULL) {
			p = p->next;
		}
		temp->prev = p;
		p->next = temp;
	}
	items->tail = temp;

}

void ViewItems(books *items, FILE *FLog)
{
	book *p;
	printf("\n Catalog No            Title            Author Name            Date Of Publication            Unitsv InStock            Price\n\n");
	p = items->head;
	while (p!=NULL)
	{
		printf(" %-21d %-16s %-22s %-30s %-25d %d\n",p->catalogNo, p->title, p->authorName, p->dateOfPublication, p->unitsInStock, p->price);
		p = p->next;
	}
	fprintf(FLog, "the user view items \n");
}

void InsertNewItems(books *items, FILE *FLog)
{
	int catalogNo, unitsInStock, price;
	char title[21], authorName[21], dateOfPublication[21];
	printf("\n enter catalog No : ");
	scanf("%d", &catalogNo);
	printf(" enter title : ");
	scanf("%s", title);
	printf(" enter author Name : ");
	scanf("%s", authorName);
	printf(" enter date Of Publication : ");
	scanf("%s", dateOfPublication);
	printf(" enter units In Stock : ");
	scanf("%d", &unitsInStock);
	printf(" enter price : ");
	scanf("%d", &price);
	addBock(items, catalogNo, RemoveSpaces(title), RemoveSpaces(authorName), RemoveSpaces(dateOfPublication), unitsInStock, price);
	fprintf(FLog, "the user insert new items \n");
}
void UpdatingItems(books *items, FILE *FLog)
{
	book *p;
	int unitsInStock, i, Price;
	char title[21], authorName[21];
	printf("\n Enter a book name or author name \n");
	printf(" enter a book name : ");
	scanf("%s", title);
	printf(" enter a author name : ");
	scanf("%s", authorName);
	p = items->head;
	while (p!=NULL)
	{
		if (!( strcmp(p->title, title)) || !(strcmp(p->authorName, authorName)))
		{
			printf(" to change Price Click 1, to change units In Stock Click 2  :  ");
			scanf("%d", &i);
			if (i==1)
			{
				printf(" enter Price : ");
				scanf("%d", &Price);
				p->price = Price;
				fprintf(FLog, "the user updating items \n");
			}
			else if (i == 2)
			{
				printf(" enter units In Stock : ");
				scanf("%d", &unitsInStock);
				p->unitsInStock = unitsInStock;
				fprintf(FLog, "the user updating items \n");
			}
			else
			{
				printf(" You typed the wrong number");
				UpdatingItems(items, FLog);
				fprintf(FLog, "the user updating items \n");
			}
		}
		p = p->next;
	}
}

void DeleteItems(books *items, FILE *FLog)
{
	book *p, *pp, *prev;
	char title[21];
	printf("\n Which book would you like to delete. Enter the name of the book : ");
	scanf("%s", title);
	p = items->head;
	pp = createBock();
	while (p != NULL)
	{
		if (!(strcmp(p->title, title)) && (p->prev == NULL)) {
			items->head = items->head->next;
			free(p);
			items->head->prev = NULL;
			p = items->head;
			fprintf(FLog, "the user delete items \n");
		}
		else if (!(strcmp(p->title, title)) && (p->next == NULL))
		{
			pp = p->prev;
			pp->next = NULL;
			free(p);
			p = pp;
			fprintf(FLog, "the user delete items \n");
			return ;
		}
		else if(!(strcmp(p->title, title))){
			pp = p->prev;
			pp->next = p->next;
			prev = pp;
			pp = p->next;
			pp->prev = prev;
			free(p);
			p = pp;
			fprintf(FLog, "the user delete items \n");
		}
		p = p->next;
	}
	
}
void WriteToFileItems(books *items)
{
	book *p;
	FILE *FItems;
	fopen_s(&FItems, "items.dat", "w");
	p = items->head;
	fprintf(FItems, " Catalog No            Title            Author Name            Date Of Publication            Unitsv In Stock            Price\n");
	while (p!=NULL)
	{
		fprintf(FItems, " %-21d %-16s %-22s %-30s %-26d %d\n",p->catalogNo, p->title, p->authorName, p->dateOfPublication, p->unitsInStock, p->price );
		p = p->next;
	}
	fclose(FItems);
}