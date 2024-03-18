#pragma once
#include <iostream>
#include <string>
#include "Calculator2.h"
#include "expresie.h"
#include <map>
using namespace std;

class Utilizator {
private:
    string nume;
    Calculator calculator;
public:
    Utilizator(string userNume) : nume(userNume) {}
    string getNume() { return nume; }
    double calculate(Expresie expr) {
        return calculator.evaluate(expr.getExpresie());
    }
};
