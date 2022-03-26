#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <iomanip>
#include "accountClass.h"

//PG 786 PDF

using namespace std;

const int ACCOUNT_AMOUNT = 10;
const int WINDOW_WIDTH = 90;
const int ROUTING_NUM = 100180932;

bankAccount::bankAccount() {
	balance = 0.00;
	interestRate = 0.00;
	accountHolderFName = "FIRST";
	accountHolderLName = "LAST";
	accountType = "NULL";
	accountNum = 100000000;
}

string bankAccount::getAccountHolderFName() {
	return accountHolderFName;
}
string bankAccount::getAccountHolderLName() {
	return accountHolderLName;
}
string bankAccount::getAccountType() {
	return accountType;
}
double bankAccount::getBalance() {
	return balance;
}
double bankAccount::getInterestRate() {
	return interestRate/100;
}
int bankAccount::getAccountNum() {
	return accountNum;
}
void bankAccount::setAccountHolderLName(string lName) {

	//converts string into uppercase.
	for (int i = 0; i < lName.length(); i++) {
		toupper(lName[i]);
	}
	accountHolderLName = lName;
}
void bankAccount::setAccountHolderFName(string fName) {

	//converts string into uppercase.
	for (int i = 0; i < fName.length(); i++) {
		toupper(fName[i]);
	}
	accountHolderFName = fName;
}
void bankAccount::setAccountType(string type) {
	accountType = type;
}
void bankAccount::setBalance(double bal) {
	balance = bal;
}
void bankAccount::setInterestRate(double rate) {
	interestRate = rate;
}
void bankAccount::setAccountNum(int number) {
	accountNum = number;
}
unsigned long long int bankAccount::genAccountNum() {

	//we start with our necessary temporary variables.
	int acntNum = 0;
	//this is where we define how many DIGITS we want to have.
	int maxDigits = 100000000;
	//and the temporary incrementer.
	int tempIncr = 1;

	//here we have a random number generator. This creates unique 10 digit numbers, and if they are negative, we make them positive.
	while (tempIncr < maxDigits) {
		acntNum = acntNum + (rand() * tempIncr);
		tempIncr *= 10;
	}
	if (acntNum < 0) {
		if (acntNum < maxDigits) {}
		acntNum *= -1;
	}

	return acntNum;
}

void bankAccount::importAccountInfo(bankAccount accounts[]) {
	string fname;
	string lname;
	string ty;
	double bal;
	double intrate;
	unsigned int num;
	fstream accountsIn("bankAccounts.txt");

	//here we go line by line for as many accounts should exist, read the data, and set the information 
	for (int i = 0; i < ACCOUNT_AMOUNT; i++) {
		accountsIn >> fname >> lname >> num >> ty >> bal >> intrate;
		accounts[i].setAccountHolderFName(fname);
		accounts[i].setAccountHolderLName(lname);
		accounts[i].setAccountNum(num);
		accounts[i].setAccountType(ty);
		accounts[i].setBalance(bal);
		accounts[i].setInterestRate(intrate);
	}	

	accountsIn.close();
}
void bankAccount::drawAccountsList(int l) {
				       //^take the relevant object as parameter^

		//combine first and last name with a comma to process as a single string
		string tempName = getAccountHolderLName() + "," + getAccountHolderFName();

		/*next three lines take the above string, if it is longer than 15 characters, 
		we add a "...". For names shorter than 15 characters, we add the "..." at the end of them then
		keep adding "."'s until they are within the bounds of our partition*/
		tempName = tempName.substr(0, 15) + "~~~";
		while (tempName.length() < 18) {
			tempName = tempName.substr(0, tempName.length()) + "~";
		}

		string adjustedBal = "";
		
		if (getBalance() > 1000000000) {
			adjustedBal = ">10B";
		}
		else {
			adjustedBal = to_string(getBalance());
			adjustedBal = adjustedBal.substr(0,adjustedBal.find('.')) + adjustedBal.substr(adjustedBal.find('.'), 3);
		}
		

		//finally we print our actual body, account order, then the holder's name, their account number and account type as well as their balance and interest rate.
		cout << "/\\" << setprecision(10) << setfill('~') << setw(2) << l + 1 << ":" << tempName << "#" << setw(12) << getAccountNum();
		cout << setw(12) << getAccountType() << setw(15) << adjustedBal << "USD"
			<< setw(10) << getInterestRate()*100 << "%" << setw(9) << "" << endl;
}
void bankAccount::drawAccountEditing(int l) {

	string tempName = getAccountHolderLName() + "," + getAccountHolderFName();
	string adjustedBal = to_string(getBalance());


		tempName = tempName.substr(0, 15) + "~~~";
		while (tempName.length() < 18) {
			tempName = tempName.substr(0, tempName.length()) + "~";
		}

		if (stoi(adjustedBal)> 1000000000) {
			adjustedBal = ">10B";
		}
		else {
			adjustedBal = adjustedBal.substr(0, adjustedBal.find('.')) + adjustedBal.substr(adjustedBal.find('.'), 3);
		}

		cout << setfill('~') << "#" << getAccountNum() << ":" << setw(21) << tempName << "" << setw(11)
			<< getAccountType() << setw(12) << adjustedBal << "USD"
			<< setw(11) << getInterestRate()*100 << "%" << setw(15) << "" << endl;

		for (int h = 1; h <= WINDOW_WIDTH; h++) {
			cout << "=";
		}
		cout << endl;
}
void bankAccount::drawHeader(string headerType) {

	if (headerType == "list") {
		cout << "[+]ACCOUNTS []editor" << endl;
		cout << " ^-_[Holder's Name]" << "<-_[Account Number]" << "[Account Type]" << "[B a l a n c e]" << "[Interest Rate]" << "-_->" << endl;
	}

	if (headerType == "editor") {
		cout << "[]accounts [+]EDITOR" << endl;
		cout << "[Account #]-^-_" << "[Holder's Name]" << "<-_[Account Type]" << "[B a l a n c e]" << "[Interest Rate]" << "-_->" << endl;

	}


	for (int h = 1; h <= WINDOW_WIDTH; h++) {
		cout << "=";
	}
	cout << endl;
}
void bankAccount::withdraw(double amnt){

	if (getBalance() < amnt) {
		cout << "[]Your balance is less than what you're trying to send...[]" << endl;
		goto end;
	}

	else if (getBalance() > 0) {
		setBalance((getBalance() - amnt));
	}


end:cout << "Amount Updated! Your Balance: " << getBalance() << endl;
	system("pause");
}
void bankAccount::withdraw() {
	double amnt = 0.0;
	system("cls");
	cout << "[Please enter how much you would like to withdraw]: ";
	cin >> amnt;
	cout << endl;
	system("cls");

	if (getBalance() < amnt) {
		cout << "[]Your balance is less than what you're trying to send...[]" << endl;
		goto end;
	}

	else if (getBalance() > 0) {
		setBalance((getBalance() - amnt));
	}


end:cout << "Amount Updated! Your Balance: " << getBalance() << endl;
	system("pause");
}
void bankAccount::deposit(double amnt) {
	setBalance(getBalance() + amnt);
	cout << "Amount Updated! Your Balance: " << getBalance() << endl;
	system("pause");
}
void bankAccount::deposit() {
	double amnt = 0.0;
	system("cls");
	cout << "[Please enter how much you would like to deposit]: ";
	cin >> amnt;
	cout << endl;
	system("cls");

	setBalance(getBalance() + amnt);

	cout << "Amount Updated! Your Balance: " << getBalance() << endl;
	system("pause");
}

void bankAccount::updateBalance(bankAccount accounts[], int l) {
		if (getAccountType() == "CHECKING") {
			accounts[l].setBalance(getBalance());
		}
		else if (getAccountType() == "SAVINGS") {
			accounts[l].setBalance(getBalance());
		}
}

checkingAccount::checkingAccount() {
	balance = 0.00;
	interestRate = 0.00;
	accountHolderFName = "";
	accountHolderLName = "";
	accountType = "";
	accountNum = 0;
	minBalance = 0.00;
	serviceCharge = 0.00;
	lastInterestDate = time(NULL);
	interestInterval = 5;
}

void checkingAccount::setMinBalance(double num) {
	minBalance = num;
}
void checkingAccount::setServiceCharge(double num) {
	serviceCharge = num;
}
double checkingAccount::getMinBalance() {
	return minBalance;
}
double checkingAccount::getServiceCharge() {
	return serviceCharge;
}
void checkingAccount::setAccountType() {
	accountType = "CHECKING";
}
bool checkingAccount::isBelowMinBalance(){
	if (getBalance() < getMinBalance()) {
		return true;
	}
	else if (getBalance() >= getMinBalance()) {
		return false;
	}
}
void checkingAccount::setInterestIntervalDays(int days) {
	int dateInSeconds = (days * 86400);

	interestInterval = dateInSeconds;
}
void checkingAccount::postInterest() {
	if (getAccountType() == "CHECKING") {
		int timeNow = time(NULL);
		//while (timeNow - lastInterestDate >= interestInterval) { cout << lastInterestDate << timeNow << endl; }
		if (timeNow - lastInterestDate >= interestInterval) {
			double temp = getBalance();	
			setBalance(temp /(1+getInterestRate()));
			lastInterestDate = timeNow;
			if (isBelowMinBalance() == true) {
				double temp = getBalance();
				setBalance(temp - getServiceCharge());
			}
		}
	}
}
void checkingAccount::writeCheck() {

	string fname;
	string lname;
	double amount;
	string amountPlain;
	string selection;
	double beforeBal = getBalance();

start:system("cls");
	for (int h = 1; h <= WINDOW_WIDTH; h++) {
		cout << "=";
	}
	cout << endl;
	cout << "Please enter the reciever's first and last name: ";
	cin >> fname >> lname;
	cout << endl;
	cout << "Please enter the numerical value of money you wish to send: ";
	cin >> amount;
	cout << endl;
	cout << "Please enter " << amount << " in plain-text english (with cents and/or dollars at the end): ";
	cin.ignore();
	getline(cin , amountPlain);
	cout << "You wish to send: \" " << fname << " " << lname << " \" " << amountPlain << " ... or $" << amount << "? :";
	cin >> selection;
	
	if (toupper(selection[0]) == 'Y') {
		system("cls");

		withdraw(amount);

		if (getBalance() == beforeBal - amount) {
			system("cls");
			for (int h = 1; h <= WINDOW_WIDTH; h++) {
				cout << "=";
			}
			
			cout << endl << "[]Long Beach Municipal Bank[]" << endl << endl;
			cout << "Pay to the order of: " << fname << " " << lname << " |$" << amount << "|" << endl;

			cout << "____________" << amountPlain << endl;
			cout << "|: " << ROUTING_NUM << " |: " << getAccountNum() << endl;

			for (int h = 1; h <= WINDOW_WIDTH; h++) {
				cout << "=";
			}
			cout << endl;
			system("pause");
		}
		else {
			cout << beforeBal << " " << getBalance() << endl;
		}
	}
	else {
		goto start;
	}
}
void checkingAccount::withdraw() {
	
	double amnt = 0.0;
	system("cls");
	cout << "[Please enter how much you would like to withdraw]: ";
	cin >> amnt;
	cout << endl;
	system("cls");

	string s = "";

	if (getBalance() < amnt) {
		cout << "[]Your balance is less than what you're trying to send...[]" << endl;
		goto end;
	}

	if (!isBelowMinBalance()) {
		setBalance(getBalance() - amnt);
	}
	else if (getBalance() > 0) {
		cout << getAccountHolderFName() << " it looks like you are below your minimum balance and will need to pay fees. Would you like to proceed?";
		cin >> s;
		if (toupper(s[0]) == 'Y') {
			setBalance((getBalance() - amnt));
		}
	}
end:cout << "Amount Updated! Your Balance: " << getBalance() << endl;
	system("pause");
}
void checkingAccount::withdraw( double amnt) {
	string s= "";

	if (getBalance() < amnt) {
		cout << "[]Your balance is less than what you're trying to send...[]" << endl;
		goto end;
	}

	if (!isBelowMinBalance()) {
		setBalance(getBalance() - amnt);
	}else if (getBalance() > 0) {
		cout << getAccountHolderFName() << " it looks like you are below your minimum balance and will need to pay fees. Would you like to proceed?";
		cin >> s;
		if (toupper(s[0]) == 'Y') {
			setBalance((getBalance() - amnt));
		}
	}
	end:cout << "Amount Updated! Your Balance: " << getBalance() << endl;
	system("pause");
}
void checkingAccount::drawAccountsList(int l) {
	//^take the relevant object as parameter^

	if (getAccountType() == "CHECKING") {
		bankAccount::drawAccountsList(l);
	}
}

savingsAccount::savingsAccount() {
	balance = 0.00;
	interestRate = 0.00;
	accountHolderFName = "";
	accountHolderLName = "";
	accountType = "";
	accountNum = 0;
	lastInterestDate = time(NULL);
	interestInterval = 5;
}

void savingsAccount::setAccountType() {
	accountType = "SAVINGS";
}
void savingsAccount::postInterest() {
	if (getAccountType() == "SAVINGS") {
		int timeNow = time(NULL);
		//while (timeNow - lastInterestDate >= interestInterval) { cout << lastInterestDate << timeNow << endl; }
		if (timeNow - lastInterestDate >= interestInterval) {
			double temp = getBalance();
			setBalance(temp * (1 + getInterestRate()));
			lastInterestDate = timeNow;
		}
	}
}
void savingsAccount::drawAccountsList(int l){
	if (getAccountType() == "SAVINGS") {
		bankAccount::drawAccountsList(l);
	}
}


int main() {
	srand(time(NULL));

	bankAccount clients[ACCOUNT_AMOUNT];

	bankAccount::importAccountInfo(clients);

	checkingAccount checkingClients[ACCOUNT_AMOUNT];
	savingsAccount savingsClients[ACCOUNT_AMOUNT];

	for (int i = 0; i < ACCOUNT_AMOUNT; i++) {
		if (clients[i].getAccountType() == "CHECKING") {
			checkingClients[i].setAccountHolderFName(clients[i].getAccountHolderFName());
			checkingClients[i].setAccountHolderLName(clients[i].getAccountHolderLName());
			checkingClients[i].setAccountNum(clients[i].getAccountNum());
			checkingClients[i].setAccountType();
			checkingClients[i].setBalance(clients[i].getBalance());
			//checkingClients[i].setInterestIntervalDays((1/17280)); //five seconds
			checkingClients[i].setInterestRate(clients[i].getInterestRate() * 100);
			checkingClients[i].setMinBalance(50.00);//minimum balance is 50 dollars
			checkingClients[i].setServiceCharge(5.00);//charge 5 dollars every interest interval if account is at minimum
		}
		else if (clients[i].getAccountType() == "SAVINGS") {
			savingsClients[i].setAccountHolderFName(clients[i].getAccountHolderFName());
			savingsClients[i].setAccountHolderLName(clients[i].getAccountHolderLName());
			savingsClients[i].setAccountNum(clients[i].getAccountNum());
			savingsClients[i].setAccountType();
			savingsClients[i].setBalance(clients[i].getBalance());
			//savingsClients[i].setInterestIntervalDays((1/17280)); //five seconds
			savingsClients[i].setInterestRate(clients[i].getInterestRate() * 100);
		}
	}

home:system("cls");
	string selection = "";
	for (int l = 0; l < ACCOUNT_AMOUNT; l++) {
		checkingClients[l].postInterest();
		savingsClients[l].postInterest();
		checkingClients[l].updateBalance(clients, l);
		savingsClients[l].updateBalance(clients, l);
	}
	cout << "]Welcome to Long Beach Municipal Bank Home Page: ADMIN, select an option[" << endl;
	cout << "^-_[1] Checking Accounts " << "^-_[2] Savings Accounts " << "^-_[3] ALL Accounts " << "^-_[4] Edit Account Information " << endl << "Selection: ";
	cin >> selection;

	if (selection == "1") {
		for (int l = 0; l < ACCOUNT_AMOUNT; l++) {
			checkingClients[l].postInterest();
			savingsClients[l].postInterest();
			checkingClients[l].updateBalance(clients, l);
			savingsClients[l].updateBalance(clients, l);
		}
		selection = "";
		//draw the Accounts Screen
		system("cls");//clears console
		bankAccount::drawHeader("list");//draws the header

		for (int l = 0; l < ACCOUNT_AMOUNT; l++) {
			checkingClients[l].drawAccountsList(l);
		}
		system("pause");
		goto home;
	}

	else if (selection == "2") {
		for (int l = 0; l < ACCOUNT_AMOUNT; l++) {
			checkingClients[l].postInterest();
			savingsClients[l].postInterest();
			checkingClients[l].updateBalance(clients, l);
			savingsClients[l].updateBalance(clients, l);
		}
		selection = "";
		//draw the Accounts Screen
		system("cls");//clears console
		bankAccount::drawHeader("list");//draws the header

		for (int l = 0; l < ACCOUNT_AMOUNT; l++) {
			savingsClients[l].drawAccountsList(l);
		}
		system("pause");
		goto home;
	}

	else if (selection == "3") {
		for (int l = 0; l < ACCOUNT_AMOUNT; l++) {
			checkingClients[l].postInterest();
			savingsClients[l].postInterest();
			checkingClients[l].updateBalance(clients, l);
			savingsClients[l].updateBalance(clients, l);
		}
		selection = "";
		//draw the Accounts Screen
		system("cls");//clears console
		bankAccount::drawHeader("list");//draws the header

		for (int l = 0; l < ACCOUNT_AMOUNT; l++) {
			clients[l].drawAccountsList(l);
		}
		system("pause");
		goto home;
	}

	else if (selection == "4") {

	edit:system("cls");
		for (int l = 0; l < ACCOUNT_AMOUNT; l++) {
			checkingClients[l].postInterest();
			savingsClients[l].postInterest();
			checkingClients[l].updateBalance(clients, l);
			savingsClients[l].updateBalance(clients, l);
		}
		selection = "";
		int l = 0;
		cout << "Enter The Row Number Of The Account: ";
		cin >> l;
		system("cls");
		bankAccount::drawHeader("editor"); // draws the header

		clients[l - 1].drawAccountEditing(l);

		if (clients[l - 1].getAccountType() == "CHECKING") {
			int sl = 0;
			cout << "  ^-_[1]Withdraw" << "  ^-_[2]Write a Check" << "  ^-_[3]Deposit" << "  ^-_[0] Return to Homepage";
			cout << endl << "Selection: ";
			cin >> sl;
			if (sl == 1) {
				checkingClients[l - 1].withdraw();
				goto edit;
			}
			else if (sl == 2) {
				checkingClients[l - 1].writeCheck();
				goto edit;
			}
			else if (sl == 3) {
				checkingClients[l - 1].deposit();
			}
			else if (sl == 0) {
				goto home;
			}
		}
		else if (clients[l - 1].getAccountType() == "SAVINGS") {
			int sl = 0;
			cout << "  ^-_[1]Withdraw" << "  ^-_[2]Deposit" << "  ^-_[0] Return to Homepage";
			cout << endl << "Selection: ";
			cin >> sl;
			if (sl == 1) {
				savingsClients[l - 1].withdraw();
				goto edit;
			}
			else if (sl == 2) {
				savingsClients[l - 1].deposit();
				goto edit;
			}
			else if (sl == 0) {
				goto home;
			}

			goto edit;
		}





	}
}