#include "Output.h"
#include <fstream>

void writeResult(const Polynomial* result, const char* prefix) {
    std::ofstream out("cout.txt", std::ios::app);
    if (prefix) {
        out << prefix;
    }
    printPolynomial(result, out);
    out << "\n";
    out.close();
}