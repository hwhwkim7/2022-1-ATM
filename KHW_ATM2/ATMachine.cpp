#include <iostream>
#include "ATMachine.h"
#include "Account.h"
#include "Statistics.h"
using namespace std;

ATMachine::ATMachine(int size, int balance, string password) {
	nMachineBalance = balance;
	nMaxAccountNum = size;
	strManagerPassword = password;
	nCurrentAccountNum = 0;

	pAcctArray = new Account[nMaxAccountNum];
}

ATMachine::~ATMachine() {
	delete[]pAcctArray;
}

void ATMachine::displayMenu() {
	cout << endl;
	cout << "----------------------" << endl;
	cout << "-    TUKOREA BANK    -" << endl;
	cout << "----------------------" << endl;
	cout << " 1. 계좌 개설" << endl;
	cout << " 2. 계좌 조회" << endl;
	cout << " 3. 계좌 입금" << endl;
	cout << " 4. 계좌 출금" << endl;
	cout << " 5. 계좌 이체" << endl;
	cout << " 6. 계좌 해지" << endl;
	cout << " 7. 고객 관리" << endl;
	cout << " 9. 업무 종료" << endl;
	cout << endl;
}
void ATMachine::createAccount() {
	int id;
	string name;
	string password;
	int money = 0;

	cout << " ----- 개설 ----- " << endl;
	cout << "이름 입력 : ";
	cin >> name;
	cout << "암호 입력 : ";
	cin >> password;
	cout << endl;

	id = rand() % 1001;
	if (id < 100) {
		id = id + BASE_ACCOUNT_ID;
	}

	nCurrentAccountNum++;

	for (int i = 0; i < nCurrentAccountNum; i++) {
		if ((pAcctArray + i)->getAcctID() == -1) {
			(pAcctArray + i)->create(id, money, name, password);
			break;
		}
	}
}

void ATMachine::closeAccount() {
	int id;
	string password;
	int i;
	int temp;

	cout << " ----- 조회 ----- " << endl;
	cout << "계좌번호 입력 : ";
	cin >> id;
	cout << "비밀번호 입력 : ";
	cin >> password;
	cout << endl;

	for (i = 0; i < nCurrentAccountNum; i++) {
		temp = (pAcctArray + i)->check(id, password);
		if (temp != -1) {
			break;
		}
	}

	if (temp == 0) {
		(pAcctArray + i)->close();
		//nCurrentAccountNum--;
	}
	else if (temp == -1) {
		cout << "계정 인증에 실패하였습니다." << endl;
	}
	else {
		cout << "계좌에 잔액이 남아있어 해지가 불가능합니다." << endl;
	}
}
void ATMachine::checkMoney() {
	int id;
	string password;
	int temp;

	cout << " ----- 조회 ----- " << endl;
	cout << "계좌번호 입력 : ";
	cin >> id;
	cout << "비밀번호 입력 : ";
	cin >> password;
	cout << endl;

	for (int i = 0; i < nCurrentAccountNum; i++) {
		temp = (pAcctArray + i)->check(id, password);
		if (temp != -1) {
			break;
		}
	}

	if (temp == -1) {
		cout << "계정 인증에 실패하였습니다." << endl;
	}
	else {
		cout << "현재 잔액 : " << temp << endl;
	}
}

void ATMachine::depositMoney() {
	int id;
	string password;
	int money;
	int temp;

	cout << " ----- 입금 ----- " << endl;
	cout << "계좌번호 입력 : ";
	cin >> id;
	cout << "비밀번호 입력 : ";
	cin >> password;
	cout << "임금액 입력 : ";
	cin >> money;
	cout << endl;

	for (int i = 0; i < nCurrentAccountNum; i++) {
		temp = (pAcctArray + i)->deposit(id, password, money);
		if (temp != -1) {
			break;
		}
	}

	if (temp == -1) {
		cout << "계정 인증에 실패하였습니다." << endl;
	}
	else {
		cout << "현재 잔액 : " << temp << endl;
		cout << "입금 완료" << endl;
	}
}

void ATMachine::widrawMoney() {
	int id;
	string password;
	int money;
	int temp;

	cout << " ----- 출금 ----- " << endl;
	cout << "계좌번호 입력 : ";
	cin >> id;
	cout << "비밀번호 입력 : ";
	cin >> password;
	cout << "출금액 입력 : ";
	cin >> money;
	cout << endl;

	for (int i = 0; i < nCurrentAccountNum; i++) {
		temp = (pAcctArray + i)->widraw(id, password, money);
		if (temp != -1) {
			break;
		}
	}

	if (temp == -1) {
		cout << "계정 인증에 실패하였습니다." << endl;
	}
	else if (temp == -2) {
		cout << "잔액이 부족합니다." << endl;
	}
	else {
		cout << "현재 잔액 : " << temp << endl;
		cout << "출금 완료" << endl;
	}
}

void ATMachine::transfer() {
	int id;
	int transId;
	string password;
	int money;
	int temp;
	int result = 0;
	int i;

	cout << " ----- 이체 ----- " << endl;
	cout << "계좌번호 입력 : ";
	cin >> id;						//본인 계좌 번호
	cout << "비밀번호 입력 : ";
	cin >> password;				//본인 비밀 번호
	cout << "이체계좌 입력 : ";
	cin >> transId;					//계좌이체할 계좌 번호
	cout << "이체금액 입력 : ";
	cin >> money;					//이체할 금액
	cout << endl;

	for (i = 0; i < nCurrentAccountNum; i++) {
		temp = (pAcctArray + i)->widraw(id, password, money);
		if (temp != -1) {
			break;
		}
	}

	if (temp == -1) {
		cout << "계정 인증에 실패하였습니다." << endl;
	}
	else if (temp == -2) {
		cout << "잔액이 부족합니다." << endl;
	}
	else {
		for (int j = 0; j < nCurrentAccountNum; j++) {
			result = (pAcctArray + j)->deposit(transId, money);
			if (result != -1) {
				break;
			}
		}

		if (result == -1) {
			cout << "해당 계좌가 없습니다." << endl;
				temp = (pAcctArray + i)->deposit(id, password, money);
		}
		else {
			cout << "현재 잔액 : " << temp << endl;
			cout << "이체 완료" << endl;
		}
	}

	
}

bool ATMachine::isManager(string password) {
	if (password == strManagerPassword) {
		return true;
	}
	else {
		return false;
	}
		
}

void ATMachine::displayReport() {
	cout << "ATM  현재 잔고: " << "       " << nMachineBalance + Statistics::sum(pAcctArray, nCurrentAccountNum) << "원" << endl;
	cout << "고객 잔고 총액: " << "       " << Statistics::sum(pAcctArray, nCurrentAccountNum) << "원(총" << Statistics::pnum << "명)" << endl;
	cout << "고객 잔고 평균: " << "       " << Statistics::average(pAcctArray, nCurrentAccountNum)<< "원" << endl;
	cout << "고객 잔고 최고: " << "       " << Statistics::max(pAcctArray, nCurrentAccountNum) << "원" << endl;
}

void ATMachine::managerMode() {
	string password;
	int temp;
	//int num = 1;

	cout << " ----- 관리 ----- " << endl;
	cout << "관리자 비밀번호 입력 : ";
	cin >> password;
	cout << endl;

	temp = isManager(password);

	if (temp) {
		cout << "관리자 입니다." << endl;
		cout << "----------------------" << endl;
		displayReport();
		cout << "----------------------" << endl;
		cout << " - 고객 계좌 목록 - " << endl;
		cout << "----------------------" << endl;

		Statistics::sort(pAcctArray, nCurrentAccountNum);
	}
	else {
		cout << "비밀번호가 맞지 않습니다." << endl;
	}
}