#include "LinkedList.h"
using namespace std;


LinkedList::LinkedList() {
	head = NULL;
	tail = NULL;
	count = 0;
}
void LinkedList::flagged(Form* form) {
	form->flagged = true;
	flaggedForms[count] = form;
	count++;
}
void LinkedList::addForm(Form* newForm) {
	if (head == NULL) {
		head = newForm;
		tail = newForm;
	}
	else {
		newForm->child = head;
		newForm->parent = NULL;
		head->parent = newForm;
		head = newForm;
	}
	if (newForm->amountRequested >= 5000) flagged(newForm);
		scanMatch(newForm);
}
void LinkedList::delForm(Form* form) {
	form->parent->child = form->child;
	form->child->parent = form->parent;
}
void LinkedList::scanMatch(Form* newForm) {
	if (head != tail) {
		Form* runner = head->child;
		while (runner != tail && newForm->name != runner->name && newForm->address != runner->address && newForm->amountRequested != runner->amountRequested)
		{
			runner = runner->child;
		}
		if (runner != tail) {
			if (runner->flagged == false) flagged(runner);
			if (newForm->flagged == false) flagged(newForm);
		}
	}
}
void LinkedList::display() {
	Form* runner = head;
	while (runner != tail) {
		cout << "Name: " << runner->name << ", Address: " << runner->address << ", $" << runner->amountRequested << endl;
		runner = runner->child;
	}
	cout << "Name: " << runner->name << ", Address: " << runner->address << ", $" << runner->amountRequested << endl;
}
void LinkedList::seeFlaggedForms() {
	for (int i = 0; i < count; i++) {
		cout << "Name: " << flaggedForms[i]->name << ", Address: " << flaggedForms[i]->address << ", $" << flaggedForms[i]->amountRequested << endl;
	}
}

// 