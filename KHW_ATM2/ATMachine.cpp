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
	cout << " 1. ���� ����" << endl;
	cout << " 2. ���� ��ȸ" << endl;
	cout << " 3. ���� �Ա�" << endl;
	cout << " 4. ���� ���" << endl;
	cout << " 5. ���� ��ü" << endl;
	cout << " 6. ���� ����" << endl;
	cout << " 7. �� ����" << endl;
	cout << " 9. ���� ����" << endl;
	cout << endl;
}
void ATMachine::createAccount() {
	int id;
	string name;
	string password;
	int money = 0;

	cout << " ----- ���� ----- " << endl;
	cout << "�̸� �Է� : ";
	cin >> name;
	cout << "��ȣ �Է� : ";
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

	cout << " ----- ��ȸ ----- " << endl;
	cout << "���¹�ȣ �Է� : ";
	cin >> id;
	cout << "��й�ȣ �Է� : ";
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
		cout << "���� ������ �����Ͽ����ϴ�." << endl;
	}
	else {
		cout << "���¿� �ܾ��� �����־� ������ �Ұ����մϴ�." << endl;
	}
}
void ATMachine::checkMoney() {
	int id;
	string password;
	int temp;

	cout << " ----- ��ȸ ----- " << endl;
	cout << "���¹�ȣ �Է� : ";
	cin >> id;
	cout << "��й�ȣ �Է� : ";
	cin >> password;
	cout << endl;

	for (int i = 0; i < nCurrentAccountNum; i++) {
		temp = (pAcctArray + i)->check(id, password);
		if (temp != -1) {
			break;
		}
	}

	if (temp == -1) {
		cout << "���� ������ �����Ͽ����ϴ�." << endl;
	}
	else {
		cout << "���� �ܾ� : " << temp << endl;
	}
}

void ATMachine::depositMoney() {
	int id;
	string password;
	int money;
	int temp;

	cout << " ----- �Ա� ----- " << endl;
	cout << "���¹�ȣ �Է� : ";
	cin >> id;
	cout << "��й�ȣ �Է� : ";
	cin >> password;
	cout << "�ӱݾ� �Է� : ";
	cin >> money;
	cout << endl;

	for (int i = 0; i < nCurrentAccountNum; i++) {
		temp = (pAcctArray + i)->deposit(id, password, money);
		if (temp != -1) {
			break;
		}
	}

	if (temp == -1) {
		cout << "���� ������ �����Ͽ����ϴ�." << endl;
	}
	else {
		cout << "���� �ܾ� : " << temp << endl;
		cout << "�Ա� �Ϸ�" << endl;
	}
}

void ATMachine::widrawMoney() {
	int id;
	string password;
	int money;
	int temp;

	cout << " ----- ��� ----- " << endl;
	cout << "���¹�ȣ �Է� : ";
	cin >> id;
	cout << "��й�ȣ �Է� : ";
	cin >> password;
	cout << "��ݾ� �Է� : ";
	cin >> money;
	cout << endl;

	for (int i = 0; i < nCurrentAccountNum; i++) {
		temp = (pAcctArray + i)->widraw(id, password, money);
		if (temp != -1) {
			break;
		}
	}

	if (temp == -1) {
		cout << "���� ������ �����Ͽ����ϴ�." << endl;
	}
	else if (temp == -2) {
		cout << "�ܾ��� �����մϴ�." << endl;
	}
	else {
		cout << "���� �ܾ� : " << temp << endl;
		cout << "��� �Ϸ�" << endl;
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

	cout << " ----- ��ü ----- " << endl;
	cout << "���¹�ȣ �Է� : ";
	cin >> id;						//���� ���� ��ȣ
	cout << "��й�ȣ �Է� : ";
	cin >> password;				//���� ��� ��ȣ
	cout << "��ü���� �Է� : ";
	cin >> transId;					//������ü�� ���� ��ȣ
	cout << "��ü�ݾ� �Է� : ";
	cin >> money;					//��ü�� �ݾ�
	cout << endl;

	for (i = 0; i < nCurrentAccountNum; i++) {
		temp = (pAcctArray + i)->widraw(id, password, money);
		if (temp != -1) {
			break;
		}
	}

	if (temp == -1) {
		cout << "���� ������ �����Ͽ����ϴ�." << endl;
	}
	else if (temp == -2) {
		cout << "�ܾ��� �����մϴ�." << endl;
	}
	else {
		for (int j = 0; j < nCurrentAccountNum; j++) {
			result = (pAcctArray + j)->deposit(transId, money);
			if (result != -1) {
				break;
			}
		}

		if (result == -1) {
			cout << "�ش� ���°� �����ϴ�." << endl;
				temp = (pAcctArray + i)->deposit(id, password, money);
		}
		else {
			cout << "���� �ܾ� : " << temp << endl;
			cout << "��ü �Ϸ�" << endl;
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
	cout << "ATM  ���� �ܰ�: " << "       " << nMachineBalance + Statistics::sum(pAcctArray, nCurrentAccountNum) << "��" << endl;
	cout << "�� �ܰ� �Ѿ�: " << "       " << Statistics::sum(pAcctArray, nCurrentAccountNum) << "��(��" << Statistics::pnum << "��)" << endl;
	cout << "�� �ܰ� ���: " << "       " << Statistics::average(pAcctArray, nCurrentAccountNum)<< "��" << endl;
	cout << "�� �ܰ� �ְ�: " << "       " << Statistics::max(pAcctArray, nCurrentAccountNum) << "��" << endl;
}

void ATMachine::managerMode() {
	string password;
	int temp;
	//int num = 1;

	cout << " ----- ���� ----- " << endl;
	cout << "������ ��й�ȣ �Է� : ";
	cin >> password;
	cout << endl;

	temp = isManager(password);

	if (temp) {
		cout << "������ �Դϴ�." << endl;
		cout << "----------------------" << endl;
		displayReport();
		cout << "----------------------" << endl;
		cout << " - �� ���� ��� - " << endl;
		cout << "----------------------" << endl;

		Statistics::sort(pAcctArray, nCurrentAccountNum);
	}
	else {
		cout << "��й�ȣ�� ���� �ʽ��ϴ�." << endl;
	}
}