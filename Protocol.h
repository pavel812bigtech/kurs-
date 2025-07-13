#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "Polynomial.h"

struct Polynomial;

void logAction(const char* action);
void logResult(const Polynomial* poly, const char* message);
void logMessage(const char* message);

#endif