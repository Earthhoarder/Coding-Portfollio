#pragma once
#include <iostream>
#include <string>
using namespace std;
const int MAX = 1000;

struct Form {
	Form* parent;
	Form* child;
	string name; //name of the form's submitter
	string address; //address of the form's submitter
	int amountRequested; //amount of money requested by the form
	bool flagged; //true for amountRequested values greater than 5,000, and other situations for flagged entries
};

class LinkedList {
private:
	Form* head;
	Form* tail;
	Form* flaggedForms[MAX];
	void flagged(Form* form);
	int count;
public:
	LinkedList();
	void addForm(Form* newForm);
	void delForm(Form* form);
	void scanMatch(Form* newForm);
	void display();
	void seeFlaggedForms();
};

