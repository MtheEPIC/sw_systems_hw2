#include "myBank.h"
//#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 50
#define PREFIX 901

int virtualSize = 0;
float accounts[MAX_SIZE];
bool used[MAX_SIZE];

bool open(float amount)
{
	if (amount < 0)
	{
		printf("Invalid amount type\n");
		return false;
	}
	if (isFull())
		return false;
	int cell = emptyCell();
	if (cell == -1)
	{	
		cell = virtualSize;
		addAccount(virtualSize, true);
	}
	else
		addAccount(cell, false);
	accounts[cell] += amount;
	return true;
}
bool get(int id) 
{
	resizeID(&id);
	if (!isValid(id))
	{
		printError();
		return false;
	}
	printBalance(id);
	return true;
}
bool add(int id, float amount) //reuse code
{
	resizeID(&id);
	if (!isValid(id))
	{
		printError();
		return false;
	}
	accounts[id] += amount;
	printBalance(id);
	return true;
}
bool sub(int id, float amount)
{
	resizeID(&id);
	if (!isValid(id))
	{
		printError();
		return false;
	} //change to add?
	if (amount > accounts[id])
		return false;
	accounts[id] -= amount;
	printBalance(id);
	return true;
}
bool close(int id)
{
	resizeID(&id);
	if (!isValid(id))
	{
		printf("This account is already closed\n");
		return false;
	}
	printf("Closed account number %d\n", id+PREFIX);
	used[id] = false;
	accounts[id] = 0;
	return true;
}
void interest(float rate) //assume rate is valid, (0:)
{
	if (rate <= 0)
		return;
	for (int i=0; i<virtualSize; ++i)
	{
		if (!isValid(i))
			continue;
		accounts[i] = accounts[i] * (1+rate/100);
	}
}
void print(void)
{
	for (int i=0; i<virtualSize; ++i)
	{
		if (!isValid(i))
			continue;
		printBalance(i);
	}
}
void quit(void)
{
	for (int i=0; i<virtualSize; ++i)
	{
		if (!used[i])
			continue;
		used[i] = false;
		// accounts[i] = -1;
	}
}

bool isValid(int id)
{
	if (id < 0 || id >= virtualSize)
		return false;
	// if (!used[id])
	// 	return false;
	// return true;
	return used[id];
}
bool isFull(void)
{
	if (virtualSize > MAX_SIZE) 
		return true;
	if (virtualSize < MAX_SIZE)
		return false;
	for (int i=0; i<virtualSize; ++i)
	{
		if (!used[i])
			return false;
	}
	return true;
}
void addAccount(int id, bool resize)
{
	printf("New account number is: %d\n", id+PREFIX);
	used[id] = true;
	if (resize)
		virtualSize++;
}
int emptyCell(void)
{
	for (int i=0; i<virtualSize; ++i)
	{
		if (!used[i])
			return i;
	}
	return -1;
}
void printBalance(int id)
{ 
	printf("The balance of account number %d is: %.2f\n", id+PREFIX, accounts[id]);
}
void printError(void)
{ 
	printf("This account is closed\n");
}
void welcome(void)
{
	printf("\nPlease choose a transaction type:\n"
			 "O-Open Account\n"
			 "B-Balance Inquiry\n"
			 "D-Deposit\n"
			 "W-Withdrawal\n"
			 "C-Close Account\n"
			 "I-Interest\n"
			 "P-Print\n"
			 "E-Exit\n");
}
void resizeID(int* id)
{
	*id = *id - PREFIX;
}
