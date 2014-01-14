// ProjFunc.h
// Funktionsdeklarationer till programmet för att hantera en personlista
// Thomas Nordenmark 2014-01-14
// Ver 0.1
//------------------------------------------------------------------------------
#ifndef PROJFUNC_H
#define PROJFUNC_H
#include "ProjStruct.h"
using namespace std;

void showMenu();
int menuChoice();
void invalidChoice();
void invalidSortChoice();
void addPerson(Person p, vector<Person> &v);
bool isUnique(string f, string l, double &h, vector<Person> v);
void printList(vector<Person> &v);
bool findSign(string k, vector<Person> &v);
void findPerson(vector<Person> &v);
void delPerson(vector<Person> &v);
void sortList(int s, vector<Person> &v);
bool compareStr(Person a, Person b);
bool compareSign(const Person &a, const Person &b);
bool compareHeight(const Person &a, const Person &b);
void randList(vector<Person> &v);
void saveFile(vector<Person> &v);
void readFile(Person &p, vector<Person> &v);

#endif // PROJFUNC_H
