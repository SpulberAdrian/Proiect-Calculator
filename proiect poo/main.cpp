#include <iostream>
#include <stdexcept>
#include "Calculator2.h"
#include <string>
#include "expresie.h"
#include "User.h"
#include <iomanip>
#include "File.h"
#include "Variable.h"

using namespace std;

int main(int argc, char* argv[]) {

    string name;
    cout << "scrie numele: ";
    getline(cin, name);

    string expression;
    string loc;

    cout << argc;

    string asd;
    if (argc == 1) {
        cout << " Specifica tipul inputului:fisier sau linie? : ";
        getline(cin, asd);
        if (asd == "fisier") {
            cout << "introdu numele fisierului: ";
            getline(cin, loc);
        }
        else if (asd != "fisier" && asd != "linie") {
            cout << "optiune invalida";
            return 0;
        }
    }

    FileHandler fileHandler(loc, "raspuns.txt");

    string out;
    cout << "Cum doresti sa fie outputul fisier / consola ?: ";
    getline(cin, out);

    Utilizator user(name);
    VariableManager varManager;

    while (true) {

        if (asd == "linie") {
            cout << "Introduceti o expresie matematica (sau tastati exit pentru a iesi): ";
            getline(cin, expression);
        }
        else if (argc > 1) {
            expression = argv[1];
        }

        if (fileHandler.isInputFileOpen()) {
            fileHandler.readFromFile(expression);
        }

        if (expression == "exit") {
            break;
        }

        Expresie expr(expression);
        try {
            double result = user.calculate(expr);
            std::cout << std::fixed << std::showpoint << std::setprecision(4);
            if (out == "consola") {
                cout << "Rezultatul espresiei   " << expr.getExpresie() << " pentru utilizatorul  " << user.getNume() << " este: " << result << endl;
            }
            else if (out == "fisier") {
                fileHandler.writeToFile("Rezultatul espresiei   " + expr.getExpresie() + " pentru utilizatorul  " + user.getNume() + " este: " + std::to_string(result));
            }
            else {
                cout << "optiune invalida";
            }

            string varName;
            cout << "Daca doriti sa salvati acest rezultat intr-o variabila, introduceti numele variabilei (sau 'nu' pentru a nu salva): ";
            getline(cin, varName);
            if (varName != "nu") {
                varManager.setVariable(varName, result);
                varManager.saveVariables("variables.bin");
            }
        }
        catch (const invalid_argument& e) {
            cout << "Eroare: " << e.what() << endl;
        }

        if (fileHandler.isEndOfFile()) {
            break;
        }
        if (argc > 1) {
            break;
        }
    }

    return 0;
}




















/*#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdexcept>
#include "Calculator2.h"
#include <string>
#include "expresie.h"
#include "User.h"
#include <iomanip>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {

    string name;
    cout << "Te rog scrieti numele: ";
    getline(cin, name);

    string expression;
    string loc;

    cout << argc;

    string asd;
    if (argc == 1) {
        cout << "ce fel de input avem prezent aicia ? fisier sau linie? : ";
        getline(cin, asd);
        if (asd == "fisier") {
            cout << "Fff: ";
            getline(cin, loc);
        }
        else if (asd != "fisier" && asd != "linie") {
            cout << "nuj ce zici, PA";
            return 0;
        }
    }
    std::ifstream myfile;
    myfile.open(loc);

    std::ofstream rezult;
    rezult.open("raspuns.txt", std::ios_base::app | std::ios_base::out);
    
    if (!rezult){
        ofstream rezult("raspuns.txt", std::ios_base::app | std::ios_base::out);
    }

    string out;
    cout << "Te rog sa imi spui foarte foarte frumos cum vrei sa fie outputul (fisier / consola): ";
    getline(cin, out);

    rezult << endl;


   Utilizator user(name);

    while (true) {

        if (asd == "linie") {
            cout << "Introduceti o expresie matematica (sau tastati exit pentru a iesi): ";
            getline(cin, expression);
        }
        else if (argc > 1) {
            expression = argv[1];
        }


        if (myfile.is_open()) { 
            myfile >> expression;
        }
 
        if (expression == "exit") {
            break;
        }
        Expresie expr(expression);
        try {
            double result = user.calculate(expr);
            std::cout << std::fixed << std::showpoint << std::setprecision(4);
            if (out == "consola") {
                cout << "Rezultatul espresiei   " << expr.getExpresie() << " pentru utilizatorul  " << user.getNume() << " este: " << result << endl;
            }
            else if (out == "fisier") {
                rezult << "Rezultatul espresiei   " << expr.getExpresie() << " pentru utilizatorul  " << user.getNume() << " este: " << result << endl;
            }
            else {
                cout << "esti bou";
            }
      
        }
        catch (const invalid_argument& e) {
            cout << "Eroare: " << e.what() << endl;
        }

        if (myfile.eof()) {
            myfile.close();
            break;
        }
        if (argc > 1) {
            break;
        }

    }

    return 0;
}
*/
  