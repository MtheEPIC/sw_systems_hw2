#include <stdbool.h>

// main funcs
bool open(double balance); //prints account id, false if no space left
bool get(int id); //print balance, false if account does't exist
bool add(int id, double amount); //prints new balance
bool sub(int id, double amount); //prints new balance, amount <= balance
bool close(int id); //account must exist
void interest(double rate); //apply intreset to all accounts
void exit; //closes all account, exists program

//helper funcs
