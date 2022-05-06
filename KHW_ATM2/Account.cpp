#include <iostream>
using namespace std;
#include "Account.h"

Account::Account() {
	nID = -1;
	nBalance = -1;
	strAccountName = "";
	strPassword = "";
}


void Account::create(int id, int money, string name, string password) {
	nID = id;
	strAccountName = name;
	strPassword = password;
	nBalance = 0;
	cout << endl;
	cout << strAccountName << "님 " << nID << "번 계좌번호가 정상적으로 개설되었습니다. 감사합니다." << endl;
}

void Account::close() {
	cout << nID << " 계좌가 해지되었습니다. 감사합니다." << endl;
	nID = -1;
	nBalance = -1;
	strAccountName = "";
	strPassword = "";
}

inline bool Account::authenticate(int id, string passwd) {
	if ((nID == id) && (strPassword == passwd)) {
		return true;
	}
	else {
		return false;
	}
}

int Account::check(int id, string password) {
	int result = authenticate(id, password);
	if (result == 1) {
		return nBalance;
	}
	else {
		return AUTHENTIFICATION_FAIL;
	}
}

int Account::deposit(int id, string password, int money) {
	int result = authenticate(id, password);
	if (result == 1) {
		nBalance += money;
		return nBalance;
	}
	else {
		return AUTHENTIFICATION_FAIL;
	}
}

int Account::widraw(int id, string password, int money) {
	int result = authenticate(id, password);
	if (result == 1) {
		if (nBalance >= money) {
			nBalance -= money;
		}
		else {
			return WIDRAW_FAIL;
		}
		return nBalance;
	}
	else {
		return AUTHENTIFICATION_FAIL;
	}
}

int Account::deposit(int id, int money) {
	if (id == nID) {
		nBalance += money;
		return nBalance;	
	}
	else
		return AUTHENTIFICATION_FAIL;
}