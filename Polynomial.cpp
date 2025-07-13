#include "Polynomial.h"
#include "LongInt.h"
#include <iostream>

// Создание пустого полинома
Polynomial* createPolynomial() {
    Polynomial* poly = new Polynomial;
    poly->head = nullptr;
    return poly;
}

// Уничтожение полинома
void destroyPolynomial(Polynomial* poly) {
    Monomial* current = poly->head;
    while (current) {
        Monomial* next = current->next;
        destroyLongInt(current->coeff);
        delete current;
        current = next;
    }
    delete poly;
}

// Ввод полинома из файла
void readPolynomial(Polynomial* poly, std::ifstream& in) {
    int k;
    in >> k;
    poly->head = nullptr;
    for (int i = 0; i < k; ++i) {
        Monomial* node = new Monomial;
        node->coeff = createLongInt();
        in >> node->degree;
        readLongInt(node->coeff, in);
        Monomial* current = poly->head;
        Monomial* prev = nullptr;
        while (current && current->degree > node->degree) {
            prev = current;
            current = current->next;
        }
        node->next = current;
        node->prev = prev;
        if (current) current->prev = node;
        if (prev) prev->next = node;
        else poly->head = node;
        printLongInt(node->coeff, std::cerr);
        std::cerr << std::endl;
    }
}

void printPolynomial(const Polynomial* poly, std::ostream& out) {
    if (!poly->head) {
        out << "0";
        return;
    }
    Monomial* current = poly->head;
    bool first = true;
    while (current) {
        if (current->coeff->sign == 0) {
            current = current->next;
            continue;
        }
        if (!first && current->coeff->sign > 0) {
            out << "+";
        }
        LongIntNode* digit = current->coeff->head;
        bool isOne = digit && !digit->next && digit->digit == 1 && current->coeff->sign == 1;
        bool isMinusOne = digit && !digit->next && digit->digit == 1 && current->coeff->sign == -1;
        if (!isOne && !isMinusOne) {
            printLongInt(current->coeff, out);
        } else if (isMinusOne) {
            out << "-";
        } else if (isOne && current->degree == 0) {
            out << "1";
        }
        if (current->degree > 0) {
            out << "x";
            if (current->degree > 1) {
                out << "^" << current->degree;
            }
        }
        first = false;
        current = current->next;
    }
}

// Сложение полиномов
Polynomial* addPolynomial(const Polynomial* p, const Polynomial* q) {
    Polynomial* result = createPolynomial();
    Monomial* cp = p->head;
    Monomial* cq = q->head;

    while (cp || cq) {
        Monomial* node = new Monomial;
        node->coeff = createLongInt();
        node->next = nullptr;
        node->prev = nullptr;

        if (!cq || (cp && cp->degree > cq->degree)) {
            node->degree = cp->degree;
            node->coeff = copyLongInt(cp->coeff);
            cp = cp->next;
        } else if (!cp || (cq && cq->degree > cp->degree)) {
            node->degree = cq->degree;
            node->coeff = copyLongInt(cq->coeff);
            cq = cq->next;
        } else {
            node->degree = cp->degree;
            node->coeff = addLongInt(cp->coeff, cq->coeff);
            cp = cp->next;
            cq = cq->next;
        }

        if (node->coeff->sign != 0) {
            Monomial* current = result->head;
            Monomial* prev = nullptr;
            while (current && current->degree > node->degree) {
                prev = current;
                current = current->next;
            }
            node->next = current;
            node->prev = prev;
            if (current) current->prev = node;
            if (prev) prev->next = node;
            else result->head = node;
        } else {
            destroyLongInt(node->coeff);
            delete node;
        }
    }
    return result;
}

// Вычитание полиномов
Polynomial* subtractPolynomial(const Polynomial* p, const Polynomial* q) {
    Polynomial* result = createPolynomial();
    Monomial* cp = p->head;
    Monomial* cq = q->head;

    while (cp || cq) {
        Monomial* node = new Monomial;
        node->coeff = createLongInt();
        node->next = nullptr;
        node->prev = nullptr;

        if (!cq || (cp && cp->degree > cq->degree)) {
            node->degree = cp->degree;
            node->coeff = copyLongInt(cp->coeff);
            cp = cp->next;
        } else if (!cp || (cq && cq->degree > cp->degree)) {
            node->degree = cq->degree;
            node->coeff = copyLongInt(cq->coeff);
            node->coeff->sign = -node->coeff->sign;
            cq = cq->next;
        } else {
            node->degree = cp->degree;
            node->coeff = subtractLongInt(cp->coeff, cq->coeff);
            cp = cp->next;
            cq = cq->next;
        }

        if (node->coeff->sign != 0) {
            Monomial* current = result->head;
            Monomial* prev = nullptr;
            while (current && current->degree > node->degree) {
                prev = current;
                current = current->next;
            }
            node->next = current;
            node->prev = prev;
            if (current) current->prev = node;
            if (prev) prev->next = node;
            else result->head = node;
        } else {
            destroyLongInt(node->coeff);
            delete node;
        }
    }

    return result;
}

// Умножение полиномов
Polynomial* multiplyPolynomial(const Polynomial* p, const Polynomial* q) {
    Polynomial* result = createPolynomial();
    Monomial* cp = p->head;
    while (cp) {
        Monomial* cq = q->head;
        while (cq) {
            Monomial* node = new Monomial;
            node->coeff = multiplyLongInt(cp->coeff, cq->coeff);
            node->degree = cp->degree + cq->degree;
            node->next = nullptr;
            node->prev = nullptr;
            if (node->coeff->sign != 0) {
                Monomial* current = result->head;
                Monomial* prev = nullptr;
                while (current && current->degree > node->degree) {
                    prev = current;
                    current = current->next;
                }
                if (current && current->degree == node->degree) {
                    LongInt* sum = addLongInt(current->coeff, node->coeff);
                    destroyLongInt(current->coeff);
                    current->coeff = sum;
                    destroyLongInt(node->coeff);
                    delete node;
                    if (current->coeff->sign == 0) {
                        if (prev) prev->next = current->next;
                        else result->head = current->next;
                        if (current->next) current->next->prev = prev;
                        delete current;
                    }
                } else {
                    node->next = current;
                    node->prev = prev;
                    if (current) current->prev = node;
                    if (prev) prev->next = node;
                    else result->head = node;
                }
            } else {
                destroyLongInt(node->coeff);
                delete node;
            }
            cq = cq->next;
        }
        cp = cp->next;
    }
    return result;
}