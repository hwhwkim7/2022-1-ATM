#include <iostream>
#include "Statistics.h"
using namespace std;

int Statistics::pnum = 0;

int Statistics::sum(Account* pArray, int size) {
	int temp;
	int sum = 0;
	Statistics::pnum = 0;

	for (int i = 0; i < size; i++) {
		temp = (pArray + i)->getBalance();
		if (temp != -1) {
			sum += temp;
			pnum++;
		}
	}
	
	return sum;
}

int Statistics::average(Account* pArray, int size) {
	int avg;
	int total = sum(pArray, size);

	avg = total / pnum;

	return avg;
}

int Statistics::max(Account* pArray, int size) {
	int max = 0;
	int temp;

	for (int i = 0; i < size; i++) {
		temp = (pArray + i)->getBalance();
		if (temp != -1) {
			if (max < temp) {
				max = temp;
			}
		}
	}

	return max;
}

int Statistics::sort(Account* pArray, int size) {
	int* arrayBal = new int[size];
	int* arrayId = new int[size];
	int n = 1;
	int temp;

	for (int i = 0; i < size; i++) {
		arrayBal[i] = (pArray + i)->getBalance();		//잔액만 저장한 배열
		arrayId[i] = (pArray + i)->getAcctID();			//ID만 저장한 배열
	}

	for (int i = 0; i < size - 1; i++) {
		for (int j = i + 1; j < size; j++) {
			if (arrayBal[i] < arrayBal[j]) {
				temp = arrayBal[i];
				arrayBal[i] = arrayBal[j];
				arrayBal[j] = temp;

				temp = arrayId[i];
				arrayId[i] = arrayId[j];
				arrayId[j] = temp;
			}
		}
	}

	for (int i = 0; i < size; i++) {
		if (arrayId[i] != -1) {
			for (int j = 0; j < size; j++) {
				if (arrayId[i] == (pArray + j)->getAcctID()) {
					cout << n << ". " << (pArray + j)->getAccountName() << "       " << (pArray + j)->getAcctID() << "     " << (pArray + j)->getBalance() << "원" << endl;
					n++;
				}
			}
		}
		else {
			break;
		}
	}

	return 0;
}