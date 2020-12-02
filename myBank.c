#include "myBank.h"
//#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 50

int virtualSize = 0;
float accounts[MAX_SIZE] = {0};
int available[MAX_SIZE] = {0}; // 0 = true -1 = false

bool open(float balance)
{
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
	accounts[cell] += balance;
	return true;
}
bool get(int id) 
{
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
	if (!isValid(id))
	{
		printError();
		return false;
	} //change to sub?
	accounts[id] += amount;
	printBalance(id);
	return true;
}
bool sub(int id, float amount)
{
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
	if (!isValid(id))
	{
		printError();
		return false;
	}
	accounts[id] = -1;
	available[id] = 0;
	return true;
}
void interest(float rate) //assume rate is valid, (0:)
{
	if (rate <= 0)
		return;
	rate++;
	for (int i=0; i<virtualSize; ++i)
	{
		if (accounts[i] == -1)
			continue;
		accounts[i] = accounts[i] * (1+rate/100);
	}
}
void print(void)
{
	for (int i=0; i<virtualSize; ++i)
	{
		if (accounts[i] == -1)
			continue;
		printBalance(i);
	}
}
void quit(void)
{
	for (int i=0; i<virtualSize; ++i)
	{
		if (available[i] == 0)
			continue;
		available[i] = 0;
		accounts[i] = -1;
	}
	// printf("Exit");
	// exit(EXIT_FAILURE);
}

bool isValid(int id)
{
	if (id < 0 || id >= virtualSize)
		return false;
	if (available[id] == 0)
		return false;
	return true;
}
bool isFull(void)
{
	if (virtualSize >= MAX_SIZE) 
		return true;
	return false;
}
void addAccount(int id, bool resize)
{
	printf("New account number is: %d\n", id);
	available[id] = -1;
	if (resize)
		virtualSize++;
}
int emptyCell(void)
{
	for (int i=0; i<virtualSize; ++i)
	{
		if (available[i] == 0)
			return i;
	}
	return -1;
}
void printBalance(int id)
{ 
	printf("The balance of account number %d is: %.2f\n", id, accounts[id]);
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
