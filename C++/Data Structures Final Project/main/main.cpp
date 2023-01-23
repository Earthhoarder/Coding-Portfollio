
#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include "LinkedList.h"
using namespace std;
const int ListAmount = 1000;
Form* hashList[ListAmount] = {NULL};

//Function prototypes
void createAddressList(int x);
void createAmountRequestedList(int x);
void createNameList(int x);
void createWholeFormList();
int hash1(Form* form);
void insertHash(Form* form);
void displayHash();
void displayFlagged();


//Main
int main()
{
	//Data Generation
	//createNameList(1000);
	//createAddressList(1000);
	//createAmountRequestedList(1000);
	//createWholeFormList();
	
	//Linked List Implementation
	/*
	LinkedList list = LinkedList();
	ifstream formincoming("formlist.txt");
	ofstream time("toAddLL.txt");
	ofstream timeT("toAddAllLL.txt");
	ofstream timeR("toRet.txt");
	int count = 1;
	auto startT = chrono::high_resolution_clock::now();
	while (!formincoming.eof()) {
		Form* f1 = new Form;
		formincoming >> f1->name >> f1->address >> f1->amountRequested; //name, place, number
		f1->flagged = false;
		auto start = chrono::high_resolution_clock::now();
		list.addForm(f1);
		auto end = chrono::high_resolution_clock::now();
		auto total = end - start;
		time << chrono::duration_cast<chrono::nanoseconds>(total).count() << endl;
		count++;
	}
	auto endT = chrono::high_resolution_clock::now();
	auto totalT = endT - startT;
	timeT << chrono::duration_cast<chrono::nanoseconds>(totalT).count() << endl;

	//list.display();
	auto startR = chrono::high_resolution_clock::now();
	list.seeFlaggedForms();
	auto endR = chrono::high_resolution_clock::now();
	auto totalR = endR - startR;
	timeR << chrono::duration_cast<chrono::nanoseconds>(totalR).count() << endl;
	*/

	//Hash Table Implementation
	
	ifstream formincoming("formlist.txt");
	ofstream time("toAddH.txt");
	ofstream timeT("toAddAllH.txt");
	ofstream timeR("toRetH.txt");
	int count = 1;
	auto startT = chrono::high_resolution_clock::now();
	while (!formincoming.eof()) {
		Form* f1 = new Form;
		formincoming >> f1->name >> f1->address >> f1->amountRequested; //name, place, number
		f1->flagged = false;
		f1->child = NULL;
		f1->parent = NULL;
		auto start = chrono::high_resolution_clock::now();
		insertHash(f1);
		auto end = chrono::high_resolution_clock::now();
		auto total = end - start;
		time << chrono::duration_cast<chrono::nanoseconds>(total).count() << endl;
		count++;
	}
	auto endT = chrono::high_resolution_clock::now();
	auto totalT = endT - startT;
	timeT << chrono::duration_cast<chrono::nanoseconds>(totalT).count() << endl;
	auto startR = chrono::high_resolution_clock::now();
	displayFlagged();
	auto endR = chrono::high_resolution_clock::now();
	auto totalR = endR - startR;
	timeR << chrono::duration_cast<chrono::nanoseconds>(totalR).count() << endl;
	
}

//Functions for data generation
void createAddressList(int x) { // x is the number of addresses to be created
	ofstream list("addresslist.txt");
	string l1[20];
	l1[0] = "Orange_Way";//
	l1[1] = "Plum_Drive";//
	l1[2] = "Apple_Street";//
	l1[3] = "Potato_Street";//
	l1[4] = "Lemon_Drive";
	l1[5] = "Tomato_Place";//
	l1[6] = "Park_Place";//
	l1[7] = "Spark_Drive";//
	l1[8] = "Copper_Street";//
	l1[9] = "Bronze_Ave";
	l1[10] = "Gold_Way";
	l1[11] = "McGuffin_Ave";
	l1[12] = "Honey_Place";
	l1[13] = "Kelmp_Drive";
	l1[14] = "Sad_Street";
	l1[15] = "Happy_Way";
	l1[16] = "Angry_Ave";//
	l1[17] = "Poor_Place";
	l1[18] = "Upscale_Ave";
	l1[19] = "Deter_Drive";//
	for (int i = 0; i < x; i++) {
		int a = rand() % 4000 + 1000;
		int b = rand() % 20;
		string y = to_string(a);
		string temp = y + "_" + l1[b];
		if (i == x - 1) list << temp;
		else list << temp << endl;
	}
}
void createAmountRequestedList(int x) {
	ofstream list("amountrequestedlist.txt");
	for (int i = 0; i < x; i++) {
		if (i == x - 1) list << (rand() % 5000 + 500);
		else list << (rand() % 5000 + 500) << endl;
	}
}
void createNameList(int x) {
	ofstream newlist("namelist.txt");
	ifstream seedlist("seednamelist.txt");
	string seed[500];
	for (int i = 0; i < 500; i++) {
		seedlist >> seed[i];
	}
	for (int i = 0; i < x; i++) {
		int a = rand() % 500;
		int b = rand() % 500;
		if (i == x - 1) newlist << seed[a] + "_" + seed[b];
		else newlist << seed[a] + "_" + seed[b] << endl;
	}
}
void createWholeFormList() {

	ifstream name("namelist.txt");
	ifstream address("addresslist.txt");
	ifstream money("amountrequestedlist.txt");
	ofstream total("formlist.txt");
	
	string namearry[ListAmount];
	string addressarry[ListAmount];
	string moneyarry[ListAmount];

	for (int i = 0; i < ListAmount; i++) {
		name >> namearry[i];
	}
	for (int i = 0; i < ListAmount; i++) {
		address >> addressarry[i];
	}
	for (int i = 0; i < ListAmount; i++) {
		money >> moneyarry[i];
	}

	for (int i = 0; i < ListAmount; i++) {
		total << namearry[i] << " " << addressarry[i] << " " << moneyarry[i] << endl;
	}
}
// Hash functions
int hash1(Form* form) {
	//Implement
	string temp = form->name;
	int a = 0;
	int b = 0;
	string t1 = temp.substr(0, temp.length() / 2);
	string t2 = temp.substr(temp.length() / 2, temp.length());
	for (int i = 0; i < temp.length()/2; i++) {
		a = a + (toascii(t1[i]) / 2);
		b = b + (2 * toascii(t2[i]));
	}
	return (a+b) % 100;

}
void insertHash(Form* form) {
	int a = hash1(form);
	if (hashList[a] != NULL) {
		//cout << "There is a collision with form "  << form->name << " and form " << hashList[a]->name << endl;
		hashList[a]->child = form;
	}
	else {
		hashList[a] = form;
	}
}
void displayHash() {
	for (int i = 0; i < ListAmount; i++) {
		if (hashList[i] != NULL) {

			cout << "Name: " << hashList[i]->name << ", Address: " << hashList[i]->address << ", $" << hashList[i]->amountRequested << endl;
			Form* runner = hashList[i];
			bool check = true;
			while (check == true && runner != NULL) {
				if (runner->child == NULL) {
					check = false;
				}
				else
				{
					cout << "Name: " << runner->child->name << ", Address: " << runner->child->address << ", $" << runner->child->amountRequested << endl;
					runner = runner->child;
				}

		}
		}

	}
}
void displayFlagged() {
	for (int i = 0; i < ListAmount; i++) {
		if (hashList[i] != NULL) {
			if (hashList[i]->child != NULL) {
				Form* runner = hashList[i];
				bool check = true;
				while (check) {
					cout << "Name: " << runner->name << ", Address: " << runner->address << ", $" << runner->amountRequested << endl;
					if (runner->child != NULL) runner = runner->child;
					else check = false;
				}	
			}
		}

	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
//
