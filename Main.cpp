#include "Polynomial.h"
#include "Protocol.h"
#include "Output.h"
#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " read.txt" << std::endl;
        return 1;
    }

    // Чтение полиномов из input.txt
    std::ifstream in(argv[1]);
    if (!in.is_open()) {
        std::cerr << "Cannot open read.txt" << std::endl;
        return 1;
    }

    int m;
    in >> m;
    Polynomial** polys = new Polynomial*[m + 1000];
    int polyCount = m;
    for (int i = 0; i < m; ++i) {
        polys[i] = createPolynomial();
        readPolynomial(polys[i], in);
    }
    in.close();
    logMessage("Loaded polynomials");

    // Обработка команд из терминала
    char buffer[256];
    while (true) {
        std::cout << "> ";
        std::cin.getline(buffer, 256);
        if (std::cin.eof()) {
            logAction("exit");
            break;
        }

        // Парсинг команды
        char cmd[5] = {0};
        int p = 0, q = 0;
        int i = 0;
        while (buffer[i] && buffer[i] != ' ' && i < 4) {
            cmd[i] = buffer[i];
            i++;
        }
        if (buffer[i] == ' ') i++;
        while (buffer[i] && buffer[i] >= '0' && buffer[i] <= '9') {
            p = p * 10 + (buffer[i] - '0');
            i++;
        }
        if (buffer[i] == ' ') i++;
        while (buffer[i] && buffer[i] >= '0' && buffer[i] <= '9') {
            q = q * 10 + (buffer[i] - '0');
            i++;
        }

        if (cmd[0] == 'e' && cmd[1] == 'x' && cmd[2] == 'i') {
            logAction(buffer);
            break;
        } else if (cmd[0] == 'p' && cmd[1] == 'r' && cmd[2] == 'i') {
            if (p > 0 && p <= polyCount) {
                logAction(buffer);
                logResult(polys[p-1], nullptr);
                writeResult(polys[p-1], nullptr);
                printPolynomial(polys[p-1], std::cout);
                std::cout << "\n";
            } else {
                logMessage("Invalid polynomial number");
                std::cout << "Invalid polynomial number\n";
            }
        } else if (cmd[0] == 'a' && cmd[1] == 'd' && cmd[2] == 'd') {
            if (p > 0 && p <= polyCount && q > 0 && q <= polyCount) {
                logAction(buffer);
                polys[polyCount] = addPolynomial(polys[p-1], polys[q-1]);
                char prefix[32];
                snprintf(prefix, 32, "New polynomial %d: ", polyCount + 1);
                logResult(polys[polyCount], prefix);
                writeResult(polys[polyCount], prefix);
                std::cout << "New polynomial " << polyCount + 1 << ": ";
                printPolynomial(polys[polyCount], std::cout);
                std::cout << "\n";
                polyCount++;
            } else {
                logMessage("Invalid polynomial numbers");
                std::cout << "Invalid polynomial numbers\n";
            }
        } else if (cmd[0] == 's' && cmd[1] == 'u' && cmd[2] == 'b') {
            if (p > 0 && p <= polyCount && q > 0 && q <= polyCount) {
                logAction(buffer);
                polys[polyCount] = subtractPolynomial(polys[p-1], polys[q-1]);
                char prefix[32];
                snprintf(prefix, 32, "New polynomial %d: ", polyCount + 1);
                logResult(polys[polyCount], prefix);
                writeResult(polys[polyCount], prefix);
                std::cout << "New polynomial " << polyCount + 1 << ": ";
                printPolynomial(polys[polyCount], std::cout);
                std::cout << "\n";
                polyCount++;
            } else {
                logMessage("Invalid polynomial numbers");
                std::cout << "Invalid polynomial numbers\n";
            }
        } else if (cmd[0] == 'm' && cmd[1] == 'u' && cmd[2] == 'l') {
            if (p > 0 && p <= polyCount && q > 0 && q <= polyCount) {
                logAction(buffer);
                polys[polyCount] = multiplyPolynomial(polys[p-1], polys[q-1]);
                char prefix[32];
                snprintf(prefix, 32, "New polynomial %d: ", polyCount + 1);
                logResult(polys[polyCount], prefix);
                writeResult(polys[polyCount], prefix);
                std::cout << "New polynomial " << polyCount + 1 << ": ";
                printPolynomial(polys[polyCount], std::cout);
                std::cout << "\n";
                polyCount++;
            } else {
                logMessage("Invalid polynomial numbers");
                std::cout << "Invalid polynomial numbers\n";
            }
        } else {
            logMessage("Unknown command");
            std::cout << "Unknown command\n";
        }
    }

    // Очистка
    for (int i = 0; i < polyCount; ++i) {
        destroyPolynomial(polys[i]);
    }
    delete[] polys;

    // Финальный NULL
    std::ofstream out("Protocol.txt", std::ios::app);
    out << "[ NULL ]" << std::endl;
    out << "------------------------------------" << std::endl;
    out.close();

    return 0;
}