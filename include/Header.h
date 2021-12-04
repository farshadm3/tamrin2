#pragma once
#include <string>
#include <vector>
using namespace std;


class Date {
private:
	int day;
	int month;
	int year;
public:
	Date(int, int, int);
	Date() {};
	void setDate(int, int, int);
	void printDate();
	int getDay() { return day; }
	int getMonth() { return month; }
	int getYear() { return year; }

};

class Transaction;

class Account 
{
private:
	string username;
	int cardNumber;
	Date createAcc;
	Date expireAcc;
	int stock;
	vector <string> ip;
	int depth;
	vector<Transaction>accountTransactions;
public:
	static int totalBalance;

	Account() {}
	Account(string, string);
	Account(string, string, int, Date);
	void setStock(int);
	string getUsername() { return username; }
	int getCardNumber() { return cardNumber; }
	int getStock() { return stock; }
	void renewal();
	void desposit(int);
	void widthraw(int);

	bool haveIP(string);
	void addIP(string);
	void printInfo();
	void addTransaction(Transaction);
	void showAccountTransactions();
	int getDepth() { return depth; }
	void payDepth(int);
	void setDepth(int value) { depth = value; }
};

class Transaction {
private:
	Account sender;
	Account reciver;
	int value;
	string type;
public:
	Transaction(){}
	Transaction(Account, Account, int, string);
	void print();
};