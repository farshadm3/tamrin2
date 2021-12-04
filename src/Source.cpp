#include "../include/Header.h"
#include <iostream>
using namespace std;

Date::Date(int day, int month, int year) {
	this->day = day;
	this->month = month;
	this->year = year;
}
void Date::setDate(int day, int month, int year) {
	this->day = day;
	this->month = month;
	this->year = year;
}
void Date::printDate() {
	cout << day << '/' << month << '/' << year << endl;
}

//-----------------------------------------------------------
int Account::totalBalance = 0;

Account::Account(string username, string ip)
{
	this->username = username;
	(this->ip).push_back(ip);
}

Account::Account(string username,string ip, int cardNumber, Date createAcc) {
	this->username = username;
	(this->ip).push_back(ip);
	this->cardNumber = cardNumber;
	this->createAcc = createAcc;
	this->stock = 0;
	this->expireAcc.setDate(createAcc.getDay(), createAcc.getMonth(), createAcc.getYear() + 2);
	this->depth = 0;
}
void Account::setStock(int stock) {
	this->stock = stock;
}
void Account::renewal() {
	if (stock >= 6000)
	{
		this->stock -= 6000;//kasr 6000 toman bara tamdid
		this->expireAcc.setDate(expireAcc.getDay(), expireAcc.getMonth(), expireAcc.getYear() + 2);

		cout << "renewal successfully!\n";
		
		totalBalance += 6000;
	}
	else
		cout << "not enought money!\n";

}
void Account::desposit(int increaseValue) {
	this->stock += increaseValue;
	totalBalance += increaseValue;
}
void Account::widthraw(int decreaseValue) {
	
	if (decreaseValue > stock)
	{
		cout << "not enought money in account!\n";
		return;
	}

	this->stock -= decreaseValue;
	totalBalance -= decreaseValue;
}

bool Account::haveIP(string ip)
{
	int size = (this->ip).size();

	for (int i = 0; i < size; i++)
	{
		if (this->ip[i] == ip)
			return true;
	}

	return false;
}

void Account::addIP(string ip)
{
	(this->ip).push_back(ip);
}

void Account::printInfo()
{
	cout << "username:\t" << username << endl << "card number:\t" << cardNumber << endl;
	cout << "create account date:\t";
	createAcc.printDate();
	cout << "exprise account date:\t";
	expireAcc.printDate();

	cout << "stock:\t" << stock << endl;
	cout << "depth to bank:\t" << depth << endl;

	cout << "IP's list:\n";
	int size = ip.size();
	for (int i = 0; i < size; i++)
		cout << i + 1 << ".\n" << ip[i] << endl;
	cout << endl;

	cout << "transactions list:\n";
	size = accountTransactions.size();
	for (int i = 0; i < size; i++)
	{
		cout << i + 1 << ".\n";
		accountTransactions[i].print();
	}
	cout << endl;
}

void Account::addTransaction(Transaction transaction)
{
	accountTransactions.push_back(transaction);
}

void Account::showAccountTransactions()
{
	int size = accountTransactions.size();

	for (int i = 0; i < size; i++)
		accountTransactions[i].print();
}

void Account::payDepth(int value)
{
	if (value > stock)
	{
		cout << "not enought money!\n";
		return;
	}

	if (value > depth)
	{
		desposit(value - depth);
		depth = 0;
	}
	else
	{
		depth -= value;
		totalBalance += value;

	}
}
//-----------------------------------------------------------
Transaction::Transaction(Account sender, Account reciver, int value,string type) {
	this->sender = sender;
	this->reciver = reciver;
	this->value = value;
	this->type = type;
}

void Transaction::print()
{
	cout << "\n----------------------\n";
	cout << "sender username : " << sender.getUsername() << endl;
	cout << "receiver username : " << reciver.getUsername() << endl;
	cout << "amount : " << value << endl;
	cout << "type : " << type << endl;
	cout << "\n----------------------\n";

}