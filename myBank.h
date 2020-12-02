#include <stdbool.h>

//main funcs
bool open(float balance); //prints account id, false if no space left
bool get(int id); //print balance, false if account does't exist
bool add(int id, float amount); //prints new balance
bool sub(int id, float amount); //prints new balance, amount <= balance
bool close(int id); //account must exist
void interest(float rate); //apply intreset to all accounts rate=(0:)
void print(void); //prints balance in all open accounts
void quit(void); //closes all account, exists program

//helper funcs
bool isValid(int id); //check if the given id is valid
bool isFull(void); //check if there is no space for a new account
int emptyCell(void); //get id of an empty cell, -1 if null
void addAccount(int id, bool resize); //register a new account
void printBalance(int id);
void printError(void);
void welcome(void);
