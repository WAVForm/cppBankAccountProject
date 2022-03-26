#pragma once

#include <string>

class bankAccount {

protected:

	std::string accountHolderFName;
	std::string accountHolderLName;
	std::string accountType;
	double balance;
	double interestRate;
	unsigned long long int accountNum;



public:
	bankAccount();

	std::string getAccountHolderFName();
	std::string getAccountHolderLName();
	std::string getAccountType();
	double getBalance();
	double getInterestRate();
	int getAccountNum();

	void setAccountHolderFName(std::string fName);
	void setAccountHolderLName(std::string lName);
	void setAccountType(std::string type);
	void setBalance(double bal);
	void setInterestRate(double rate);
	static unsigned long long int genAccountNum();
	void setAccountNum(int number);

	static void importAccountInfo(bankAccount account[]);
	static void saveFile();
	static void drawHeader(std::string headerType);
	void drawAccountsList(int l);
	void drawAccountEditing(int l);

	void withdraw(double amnt);
	void withdraw();
	void deposit(double amnt);
	void deposit();

	void updateBalance(bankAccount accounts[], int l);

};

class checkingAccount : public bankAccount {
private :
	double minBalance;
	double serviceCharge;
	int lastInterestDate;
	int interestInterval;


public : 

	checkingAccount();
	double getMinBalance();
	double getServiceCharge();

	void setAccountType();
	void setMinBalance(double num);
	void setServiceCharge(double num);
	void setInterestIntervalDays(int dateInSeconds);

	bool isBelowMinBalance();
	void postInterest();
	void writeCheck();

	void withdraw(double amnt);
	void withdraw();
	void drawAccountsList(int l);


};

class savingsAccount : public bankAccount {
private:

	int lastInterestDate;
	int interestInterval;

public:

	savingsAccount();

	void setAccountType();
	
	void postInterest();

	void drawAccountsList(int l);


};