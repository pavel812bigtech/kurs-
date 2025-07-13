#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "LongInt.h"
#include <fstream>

// Член полинома
struct Monomial {
    int degree;         // Степень
    LongInt* coeff;     // Коэффициент
    Monomial* next;     // Следующий член
    Monomial* prev;     // Предыдущий член
};

// Полином
struct Polynomial {
    Monomial* head;     // Голова списка членов
};

Polynomial* createPolynomial();
void destroyPolynomial(Polynomial* poly);
void readPolynomial(Polynomial* poly, std::ifstream& in);
void printPolynomial(const Polynomial* poly, std::ostream& out);
Polynomial* addPolynomial(const Polynomial* p, const Polynomial* q);
Polynomial* subtractPolynomial(const Polynomial* p, const Polynomial* q);
Polynomial* multiplyPolynomial(const Polynomial* p, const Polynomial* q);

#endif