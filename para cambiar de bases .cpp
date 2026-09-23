#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int getVal(char c) {
    c = toupper(c);
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'Z') return c - 'A' + 10;
    return -1;
}

char getChar(int n) {
    return (n < 10) ? (n + '0') : (n - 10 + 'A');
}

int main() {
    string num;
    int b1, b2;
    bool valid;

    do {
        valid = true;
        cout << "Ingrese el numero: ";
        cin >> num;
        cout << "Base origen (2-36): ";
        cin >> b1;
        cout << "Base destino (2-36): ";
        cin >> b2;

        if (b1 < 2 || b1 > 36 || b2 < 2 || b2 > 36) {
            cout << "Error: Bases invalidas.\n\n";
            valid = false;
            continue;
        }

        string checkNum = (num[0] == '-') ? num.substr(1) : num;
        for (char c : checkNum) {
            if (c == '.') continue;
            int val = getVal(c);
            if (val < 0 || val >= b1) {
                cout << "Error: El digito '" << c << "' no es valido para la base " << b1 << ".\n\n";
                valid = false;
                break;
            }
        }
    } while (!valid);

    bool isNeg = (num[0] == '-');
    if (isNeg) num = num.substr(1);

    int dot = num.find('.');
    string sInt = (dot == -1) ? num : num.substr(0, dot);
    string sFrac = (dot == -1) ? "" : num.substr(dot + 1);

    long long intPart = 0;
    for (char c : sInt) {
        intPart = intPart * b1 + getVal(c);
    }

    double fracPart = 0.0;
    double div = b1;
    for (char c : sFrac) {
        fracPart += getVal(c) / div;
        div *= b1;
    }

    string resInt = (intPart == 0) ? "0" : "";
    while (intPart > 0) {
        resInt = getChar(intPart % b2) + resInt;
        intPart /= b2;
    }

    string resFrac = "";
    for (int i = 0; i < 6 && fracPart > 0.0000001; i++) {
        fracPart *= b2;
        int d = fracPart;
        resFrac += getChar(d);
        fracPart -= d;
    }

    string originalNum = (isNeg ? "-" : "") + num;
    string finalRes = (isNeg ? "-" : "") + resInt + (resFrac.empty() ? "" : "." + resFrac);

    cout << "\nEl numero " << originalNum << " que estaba en base " << b1 
         << " ahora es " << finalRes << " en base " << b2 << ".\n";

    return 0;
}