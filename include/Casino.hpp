#pragma once

#include "Pocket.hpp"

void mainMenu();
void cashiersCage(unsigned int &balance, Pocket &pocket);
void buyChips(unsigned int &balance, Pocket &pocket);
void tradeInChips(unsigned int &balance, Pocket &pocket);
void cardroomMenu(Pocket &pocket);
template <typename T>
void displayGameMenu(T &game, const char *&location,
                     const char *&information, Pocket &pocket);