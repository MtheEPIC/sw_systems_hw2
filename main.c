#include "myBank.h"
#include <stdio.h>


char ans;
int id;
float amount;

bool getAns(void)
{
	printf("Please enter account number: ");
	if (scanf("%c", &ans)!=1)
	{
		printf("Failed to read the account number\n");
		return false;
	}
	return true;
}
bool getId(void)
{
	printf("Please enter account number: ");
	if (scanf("%d", &id)!=1)
	{
		printf("Failed to read the account number\n");
		return false;
	}
	if (id < 901 || id > 950)
	{
		printf("Invalid account number\n");
		return false;
	}
	return true;
}
bool getAmount(void)
{
	if (scanf("%f", &amount)!=1)
	{
		printf("Failed to read the amount\n");
		return false;
	}
	return true;
}
bool getInterest(void)
{
	if (scanf("%f", &amount)!=1)
	{
		printf("Failed to read the interest rate\n");
		return false;
	}
	if (amount < 0)
	{
		printf("Invalid interest rate\n");
		return false;
	}
	return true;
}

int main()
{
	do
	{
		welcome();
		scanf(" %c", &ans);
		switch(ans)
		{
			case 'O':
				printf("Please enter amount for deposit: ");
				if (getAmount())
					open(amount);
				break;
			case 'B':
				if (getId())
					get(id);
				break;
			case 'D':
				if (getId())
				{		
					if (!isValid(id-901))
					{
						printf("This account is closed\n");
						break;
					}
					printf("Please enter the amount to deposit: ");
					if (getAmount())
					{
						if (amount < 0)
						{
							printf("Cannot deposit a negative amount\n");
							break;
						}
						add(id, amount);
					}
				}
				break;
			case 'W':
				if (getId())
				{
					if (!isValid(id-901))
					{
						printf("This account is closed\n");
						break;
					}
					printf("Please enter the amount to withdraw: ");
					if (getAmount())
					{
						if (amount < 0)
						{
							printf("Cannot withdraw a negative amount\n");
							break;
						}
						sub(id, amount);
					}
				}
				break;
			case 'C':
				if (getId())
					close(id);
				break;
			case 'I':
				printf("Please enter interest rate: ");
				if (getInterest())
					interest(amount);
				break;
			case 'P':
				print();
				break;
			case 'E':
				quit();
				break;
			default:
				printf("Invalid transaction type\n");
		}
	} while (ans != 'E');
	return 0;
}


