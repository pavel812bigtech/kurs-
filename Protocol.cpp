#include "Protocol.h"
#include "Polynomial.h"
#include <fstream>

void logAction(const char* action) {
    std::ofstream out("Protocol.txt", std::ios::app);
    out << "[ " << action << " ]" << std::endl;
    out << "  \\ | /" << std::endl;
    out.close();
}

void logResult(const Polynomial* poly, const char* message) {
    std::ofstream out("Protocol.txt", std::ios::app);
    out << "[ ";
    if (message) {
        out << message;
        printPolynomial(poly, out);
    } else {
        printPolynomial(poly, out);
    }
    out << " ]" << std::endl;
    out << "  \\ | /" << std::endl;
    out << "[ NULL ]" << std::endl;
    out.close();
}

void logMessage(const char* message) {
    std::ofstream out("Protocol.txt", std::ios::app);
    out << "[ " << message << " ]" << std::endl;
    out << "  \\ | /" << std::endl;
    out << "[ NULL ]" << std::endl;
    out.close();
}