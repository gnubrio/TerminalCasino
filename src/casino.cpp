#include "Casino.h"
#include "GamesMenu.h"
#include "Utility.h"
#include <algorithm>
#include <iostream>
#include <string>

void mainMenu() {
  unsigned balance = 0;
  std::string userInput = "";

  screenClear();
  std::cout << "Welcome to the casino!" << std::endl;
  screenSleep();

  while (true) {
    screenClear();
    std::cout << "CASINO | Balance: $" << balance
              << "\n(1) Games\n(2) Deposit/Withdrawal\n(0) Exit\n> "
              << std::flush;
    std::getline(std::cin, userInput);

    if (userInput == "1") {
      if (balance == 0) {
        screenClear();
        std::cout << "Please deposit before playing" << std::endl;
        screenSleep();
      } else {
        gamesMenu(balance);
      }
    } else if (userInput == "2") {
      depositWithdrawalMenu(balance);
    } else if (userInput == "0") {
      while (true) {
        screenClear();
        std::cout << "Are you sure you want to exit? (Y/N)\n> " << std::flush;
        std::getline(std::cin, userInput);

        std::transform(userInput.begin(), userInput.end(), userInput.begin(),
                       [](unsigned char c) { return std::tolower(c); });

        if (userInput == "y") {
          screenClear();
          return;
        } else if (userInput == "n") {
          break;
        } else {
          screenClear();
          std::cout << "Invalid Input" << std::endl;
          screenSleep();
        }
      }
    } else {
      screenClear();
      std::cout << "Invalid Input" << std::endl;
      screenSleep();
    }
  }
}

void depositWithdrawalMenu(unsigned &balance) {
  const unsigned MAX_BALANCE = 9999999;
  const unsigned originalBalance = balance;
  std::string userInput = "";

  while (true) {
    screenClear();
    std::cout << "DEPOSIT/WITHDRAWAL | Balance: $" << balance
              << "\n(1) Deposit\n(2) Withdrawal\n(0) Exit\n> " << std::flush;
    std::getline(std::cin, userInput);

    if (userInput == "1") {
      screenClear();
      std::cout << "Deposit amount\n> " << std::flush;
      std::getline(std::cin, userInput);

      if (isStringValidInt(userInput)) {
        unsigned amount = std::stoul(userInput);

        if (balance + amount <= MAX_BALANCE) {
          balance += amount;

          screenClear();
          std::cout << "Deposited $" << amount << std::endl;
          screenSleep();
        } else {
          screenClear();
          std::cout << "Invalid amount" << std::endl;
          screenSleep();
        }
      } else {
        screenClear();
        std::cout << "Invalid amount" << std::endl;
        screenSleep();
      }
    } else if (userInput == "2") {
      screenClear();
      std::cout << "Withdrawal amount\n> " << std::flush;
      std::getline(std::cin, userInput);

      if (isStringValidInt(userInput)) {
        unsigned amount = std::stoul(userInput);

        if (balance - amount <= MAX_BALANCE) {
          balance -= amount;

          screenClear();
          std::cout << "Withdrew $" << amount << std::endl;
          screenSleep();
        } else {
          screenClear();
          std::cout << "Invalid amount" << std::endl;
          screenSleep();
        }
      } else {
        screenClear();
        std::cout << "Invalid amount" << std::endl;
        screenSleep();
      }
    } else if (userInput == "0") {
      if (balance <= MAX_BALANCE) {
        screenClear();
        std::cout << "New balance: $" << balance << std::endl;
        screenSleep();

        return;
      } else {
        balance = originalBalance;

        screenClear();
        std::cout << "Invalid amount. Resetting balance." << std::endl;
        screenSleep();
      }
    } else {
      screenClear();
      std::cout << "Invalid input" << std::endl;
      screenSleep();
    }
  }
}