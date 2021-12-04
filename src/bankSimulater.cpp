#pragma warning(disable : 4996)

#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include "../include/Header.h"
using namespace std;

//fuction for check number or not
bool isNumber(const string&);

//function to split string `str` using a given delimiter
vector<string> split(const string&, char);

//fuction for check ip is valid or not
bool validateIP(string);

//function for show bak info
void showBankInfo(vector<Account>& const);

//function for create account
void createAccount(vector<Account>&);

//function to check if username exist in list or not
int doesUsernameExist(string, vector<Account>& const);

//function for check the username is correct format or not
bool validateUsername(string);

//function for adding ip to a specific account
void addIP(vector<Account>&);

//check the ip is unique or not
int doesIPExist(string, vector<Account>&);

//funnction for renewal the account
void renewal(vector<Account>&);

//function for deposit money into account
void deposit(vector<Account>&, vector<Transaction>&);

//function for widthraw money from account
void widthraw(vector<Account>&, vector<Transaction>&);

//function for transfer money from account to account
void transfer(vector<Account>&, vector<Transaction>&);

//function for create a unique card number
int createCardNumber(vector<Account>& const);

//function for return the current Date in Date format class
Date getCurrentDate();

//function for check other command like username,ip,bank
void checkCommand(vector<Account>& const, string);

//function for check card number is exist or not
int doesCardExist(int, vector<Account>& const);

//function for add profit to the accounts
void addProfit(vector<Account>&);

//function for get loan
void getLoan(vector<Account>&);

//function for proccessing the loan for specefic user
void proccessLoan(int, int, vector<Account>&);

//function for pay the loan
void payLoan(vector<Account>& const);

int main()
{
    vector <Account> accounts;
    vector<Transaction>transactions;

    while (true)
    {
        string command;
        cin >> command;

        if (command == "create")
            createAccount(accounts);
        else if (command == "add_ip")
            addIP(accounts);
        else if (command == "renewal")
            renewal(accounts);
        else if (command == "widthraw")
            widthraw(accounts, transactions);
        else if (command == "transfer")
            transfer(accounts, transactions);
        else if (command == "deposit")
            deposit(accounts, transactions);
        else if (command == "bank")
            showBankInfo(accounts);
        else if (command == "add_profit")
            addProfit(accounts);
        else if (command == "get_loan")
            getLoan(accounts);
        else if (command == "pay_loan")
            payLoan(accounts);
        else if (command == "exit")
            exit(0);
        else
            checkCommand(accounts, command);
    }

}

//fuction for check number or not
bool isNumber(const string& str)
{
    return !str.empty() &&
        (str.find_first_not_of("[0123456789]") == std::string::npos);
}

//function to split string `str` using a given delimiter
vector<string> split(const string& str, char delim)
{
    auto i = 0;
    vector<string> list;

    auto pos = str.find(delim);

    while (pos != string::npos)
    {
        list.push_back(str.substr(i, pos - i));
        i = ++pos;
        pos = str.find(delim, pos);
    }

    list.push_back(str.substr(i, str.length()));

    return list;
}

//fuction for check ip is valid or not
bool validateIP(string ip)
{
    vector<string> list = split(ip, '.');

    if (list.size() != 4) {
        return false;
    }

    for (string str : list)
    {
        try
        {
            stoi(str);
        }
        catch (...)
        {
            return false;
        }

        if (!isNumber(str) || stoi(str) > 255 || stoi(str) < 0) {
            return false;
        }
    }

    return true;
}

//function for show bak info
void showBankInfo(vector<Account>& const accounts)
{
    cout << "bank total balance : " << Account::totalBalance << endl;

    int size = accounts.size();
    cout << "list of accounts:\n";
    for (int i = 0; i < size; i++)
    {
        cout << i + 1 << ".\n";

        accounts[i].printInfo();
    }
}

//function for create account
void createAccount(vector<Account>& accounts)
{
    string info;
    cin >> info;

    vector<string> extractInfo = split(info, ':');
    if (extractInfo.size() != 2)
    {
        cout << "invlaid input format!\n";
        return;
    }

    string username = extractInfo[0];
    string ip = extractInfo[1];


    if (validateUsername(username))
    {
        if (validateIP(ip))
        {
            if (doesUsernameExist(username, accounts) == -1 && doesIPExist(ip, accounts) == -1)
            {
                int cardNumber = createCardNumber(accounts);
                Date date = getCurrentDate();

                Account ac(username, ip, cardNumber, date);
                accounts.push_back(ac);

                cout << "successfully added!\n";
            }
            else
                cout << "invalid ip or username\n";
        }
        else
            cout << "invalid ip or username\n";

    }
    else
        cout << "invalid ip or username\n";

}

//function to check if username exist in list or not
int doesUsernameExist(string username, vector<Account>& const accounts)
{
    int size = accounts.size();

    if (size == 0)
        return -1;

    for (int i = 0; i < size; i++)
        if (username == accounts[i].getUsername())
            return i;

    return -1;
}

//function for check the username is correct format or not
bool validateUsername(string username)
{
    if (isdigit(username[0]))
        return false;

    int size = username.length();
    for (int i = 0; i < size; i++)
        if (!isalpha(username[i]))
            return false;

    return true;
}

//check the ip is unique or not
int doesIPExist(string ip, vector<Account>& const accounts)
{
    int size = accounts.size();

    for (int i = 0; i < size; i++)
        if (accounts[i].haveIP(ip))
            return i;

    return -1;
}

//function for adding ip to a specific account
void addIP(vector<Account>& accounts)
{
    string info;
    cin >> info;

    vector<string>extractInfo = split(info, ':');

    if (extractInfo.size() != 2)
    {
        cout << "invlaid format!\n";
        return;
    }

    string username = extractInfo[0];
    string ip = extractInfo[1];

    int indexUser = doesUsernameExist(username, accounts);
    if (indexUser == -1)
    {
        cout << "invalid username or invalid ip\n";
        return;
    }

    if (validateIP(ip) && doesIPExist(ip, accounts) == -1)
    {
        accounts[indexUser].addIP(ip);
        cout << "added successfully!\n";
    }
    else
        cout << "invalid ip or ip already exist!\n";

}

//funnction for renewal the account
void renewal(vector<Account>& accounts)
{
    string info;
    cin >> info;

    vector<string>extractInfo = split(info, ':');

    if (extractInfo.size() != 2)
    {
        cout << "invalid format!\n";
        return;
    }

    string username = extractInfo[0];
    string ip = extractInfo[1];

    int userIndex = doesUsernameExist(username, accounts);
    if (userIndex == -1)
    {
        cout << "invalid username!\n";
        return;
    }
    if (!accounts[userIndex].haveIP(ip))
    {
        cout << "ip does not belong to user!\n";
        return;
    }

    accounts[userIndex].renewal();
}

//function for deposit money into account
void deposit(vector<Account>& accounts, vector<Transaction>& transactions)
{
    string info;
    cin >> info;

    vector<string>extractInfo = split(info, ':');
    if (extractInfo.size() != 3)
    {
        cout << "invalid synax!\n";
        return;
    }

    string username = extractInfo[0];
    string ip = extractInfo[1];
    string money = extractInfo[2];

    int userIndex = doesUsernameExist(username, accounts);
    if (userIndex == -1)
    {
        cout << "user does not exist!\n";
        return;
    }

    if (!accounts[userIndex].haveIP(ip))
    {
        cout << "ip does not belong to user!\n";
        return;
    }

    try
    {
        stoi(money);
    }
    catch (...)
    {
        cout << "invalid amount of money!\n";
        return;
    }

    int amount = stoi(money);
    if (amount < 0)
    {
        cout << "invalid amount if money!\n";
        return;
    }

    accounts[userIndex].desposit(amount);

    Transaction transaction(accounts[userIndex], accounts[userIndex], amount, "deposit");
    transactions.push_back(transaction);
    accounts[userIndex].addTransaction(transaction);

    cout << "operation done successfully!\n";
}

//function for widthraw money from account
void widthraw(vector<Account>& accounts, vector<Transaction>& transactions)
{
    string info;
    cin >> info;

    vector<string>extractInfo = split(info, ':');
    if (extractInfo.size() != 3)
    {
        cout << "invalid synax!\n";
        return;
    }

    string username = extractInfo[0];
    string ip = extractInfo[1];
    string money = extractInfo[2];

    int userIndex = doesUsernameExist(username, accounts);
    if (userIndex == -1)
    {
        cout << "user does not exist!\n";
        return;
    }

    if (!accounts[userIndex].haveIP(ip))
    {
        cout << "ip does not belong to user!\n";
        return;
    }

    try
    {
        stoi(money);
    }
    catch (...)
    {
        cout << "invalid amount of money!\n";
        return;
    }

    int amount = stoi(money);
    if (amount < 0)
    {
        cout << "invalid amount if money!\n";
        return;
    }

    accounts[userIndex].widthraw(amount);

    Transaction transaction(accounts[userIndex], accounts[userIndex], amount, "widthraw");
    transactions.push_back(transaction);
    accounts[userIndex].addTransaction(transaction);

    cout << "operation done successfully!\n";
}

//function for transfer money from account to account
void transfer(vector<Account>& accounts, vector<Transaction>& transactions)
{
    string info;
    cin >> info;

    vector<string>extractInfo = split(info, ':');
    if (extractInfo.size() != 4)
    {
        cout << "invalid synax!\n";
        return;
    }

    string senderUsername = extractInfo[0];
    string senderIP = extractInfo[1];
    string receiverUsername = extractInfo[2];
    string money = extractInfo[3];

    int senderIndex = doesUsernameExist(senderUsername, accounts);
    if (senderIndex == -1)
    {
        cout << "invalid sender username\n";
        return;
    }
    if (!accounts[senderIndex].haveIP(senderIP))
    {
        cout << "sender dont have this ip!\n";
        return;
    }

    try
    {
        stoi(money);
    }
    catch (...)
    {
        cout << "invalid amount of money!\n";
        return;
    }

    int amount = stoi(money);
    if (amount < 0)
    {
        cout << "invalid amount if money!\n";
        return;
    }

    int receiverIndex = doesUsernameExist(receiverUsername, accounts);
    if (receiverIndex == -1)
    {
        cout << "receiver username does not exist!\n";
        return;
    }

    if (accounts[senderIndex].getStock() < amount)
    {
        cout << "dont have enought money!\n";
        return;
    }

    accounts[senderIndex].widthraw(amount);
    accounts[receiverIndex].desposit(amount);

    Transaction transaction(accounts[senderIndex], accounts[receiverIndex], amount, "transfer");
    transactions.push_back(transaction);
    accounts[senderIndex].addTransaction(transaction);
    accounts[receiverIndex].addTransaction(transaction);

    cout << "operation done successfully!\n";
}

//function for create a unique card number
int createCardNumber(vector<Account>& const accounts)
{
    srand(time(0));

    while (true)
    {
        int cardnumber = 1000 + (rand() % (9999 - 1000 + 1));

        if (doesCardExist(cardnumber, accounts) == -1)
            return cardnumber;
    }
}

//function for return the current Date in Date format class
Date getCurrentDate()
{
    time_t now = time(0);
    tm* ltm = localtime(&now);

    int year = 1900 + ltm->tm_year;
    int month = 1 + ltm->tm_mon;
    int day = ltm->tm_mday;

    Date date(day, month, year);

    return date;
}

//function for check other command like username,ip,bank
void checkCommand(vector<Account>& const accounts, string command)
{
    int userIndex = doesIPExist(command, accounts);
    if (userIndex == -1)
    {
        try
        {
            stoi(command);
        }
        catch (...)
        {
            cout << "invalid command!\n";
            return;
        }

        userIndex = doesCardExist(stoi(command), accounts);
    }

    if (userIndex == -1)
        cout << "invalid command!\n";
    else
        accounts[userIndex].printInfo();
}

//function for check card number is exist or not
int doesCardExist(int cardnumber, vector<Account>& const accounts)
{
    int size = accounts.size();

    for (int i = 0; i < size; i++)
        if (cardnumber == accounts[i].getCardNumber())
            return i;

    return -1;
}

//function for add profit to the accounts
void addProfit(vector<Account>& accounts)
{
    string username;
    cin >> username;

    int userIndex = doesUsernameExist(username, accounts);
    if (userIndex == -1)
    {
        cout << "invalid username!\n";
        return;
    }

    if (accounts[userIndex].getDepth() != 0)
    {
        cout << "cannot gain profit cause dont pay the loan compelete!\n";
        return;
    }

    int profit = 0.1 * accounts[userIndex].getStock();
    accounts[userIndex].desposit(profit);

    cout << "profit gain successfully!\n";
}

//function for get loan
void getLoan(vector<Account>& accounts)
{
    string info;
    cin >> info;

    vector<string>extractInfo = split(info, ':');
    if (extractInfo.size() != 3)
    {
        cout << "invalid synax!\n";
        return;
    }

    string username = extractInfo[0];
    string ip = extractInfo[1];
    string money = extractInfo[2];

    int userIndex = doesUsernameExist(username, accounts);
    if (userIndex == -1)
    {
        cout << "user does not exist!\n";
        return;
    }

    if (!accounts[userIndex].haveIP(ip))
    {
        cout << "ip does not belong to user!\n";
        return;
    }

    try
    {
        stoi(money);
    }
    catch (...)
    {
        cout << "invalid amount of money!\n";
        return;
    }

    int amount = stoi(money);
    if (amount < 0)
    {
        cout << "invalid amount if money!\n";
        return;

    }

    proccessLoan(userIndex, amount, accounts);
}

//function for proccessing the loan for specefic user
void proccessLoan(int userIndex, int amount, vector<Account>& accounts)
{

    if (accounts[userIndex].getStock() >= 0.75 * amount && accounts[userIndex].getDepth() == 0)
    {
        accounts[userIndex].desposit(amount);
        accounts[userIndex].setDepth(amount);
        Account::totalBalance -= amount;

        cout << "loan added successfully!\n";
    }
    else
        cout << "dont have the requirment!(3/4 of amount in stock and dont have any depth)\n";

}

//function for pay the loan
void payLoan(vector<Account>& const accounts)
{
    string info;
    cin >> info;

    vector<string>extractInfo = split(info, ':');
    if (extractInfo.size() != 2)
    {
        cout << "invalid synax!\n";
        return;
    }

    string username = extractInfo[0];
    string money = extractInfo[1];

    int userIndex = doesUsernameExist(username, accounts);
    if (userIndex == -1)
    {
        cout << "user does not exist!\n";
        return;
    }

    try
    {
        stoi(money);
    }
    catch (...)
    {
        cout << "invalid amount of money!\n";
        return;
    }

    int amount = stoi(money);
    if (amount < 0)
    {
        cout << "invalid amount if money!\n";
        return;
    }

    accounts[userIndex].payDepth(amount);

    cout << "paid successfully!\n";
}