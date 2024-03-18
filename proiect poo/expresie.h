#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

class Expresie {
private:
    string expresie;
public:
    Expresie(string expr) : expresie(expr) {}
    string getExpresie() { return expresie; }
    void setExpresie(string expr) { expresie = expr; }
};