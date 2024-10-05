#include "GamesMenu.h"
#include "Utility.h"
#include "Casino.h"

int main(void) {
  mainMenu();
  return 0;
}

void mainMenu() {
  unsigned balance = 0;
  std::string userInput = "";

  screenClear();
  std::cout << "Welcome to the casino!\n";
  screenSleep();

  while (true) {
    screenClear();
    std::cout << "CASINO | Balance: $" << balance
              << "\n(1) Games\n(2) Deposit/Withdrawal\n(0) Exit\n> ";
    std::getline(std::cin, userInput);

    if (userInput == "1") {
      if (balance == 0) {
        screenClear();
        std::cout << "Please deposit before playing\n";
        screenSleep();
      } else {
        gamesMenu(balance);
      }
    } else if (userInput == "2") {
      depositWithdrawalMenu(balance);
    } else if (userInput == "0") {
      while (true) {
        screenClear();
        std::cout << "Are you sure you want to exit? (Y/N)\n> ";
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
          std::cout << "Invalid Input\n";
          screenSleep();
        }
      }
    } else {
      screenClear();
      std::cout << "Invalid Input\n";
      screenSleep();
    }
  }
}

void depositWithdrawalMenu(unsigned &balance) {
  const int MAX_BALANCE = 9999999;
  const int MIN_BALANCE = 0;
  const unsigned originalBalance = balance;
  std::string userInput = "";

  while (true) {
    screenClear();
    std::cout << "DEPOSIT/WITHDRAWAL | Balance: $" << balance
              << "\n(1) Deposit\n(2) Withdrawal\n(0) Exit\n> ";
    std::getline(std::cin, userInput);

    if (userInput == "1") {
      screenClear();
      std::cout << "Deposit amount\n> ";
      std::getline(std::cin, userInput);

      if (isStringValidInt(userInput)) {
        unsigned amount = std::stoul(userInput);

        if (balance + amount >= MIN_BALANCE &&
            balance + amount <= MAX_BALANCE) {
          balance += amount;

          screenClear();
          std::cout << "Deposited $" << amount << "\n";
          screenSleep();
        } else {
          screenClear();
          std::cout << "Invalid amount\n";
          screenSleep();
        }
      } else {
        screenClear();
        std::cout << "Invalid amount\n";
        screenSleep();
      }
    } else if (userInput == "2") {
      screenClear();
      std::cout << "Withdrawal amount\n> ";
      std::getline(std::cin, userInput);

      if (isStringValidInt(userInput)) {
        unsigned amount = std::stoul(userInput);

        if (balance - amount >= MIN_BALANCE &&
            balance - amount <= MAX_BALANCE) {
          balance -= amount;

          screenClear();
          std::cout << "Withdrew $" << amount << "\n";
          screenSleep();
        } else {
          screenClear();
          std::cout << "Invalid amount\n";
          screenSleep();
        }
      } else {
        screenClear();
        std::cout << "Invalid amount\n";
        screenSleep();
      }
    } else if (userInput == "0") {
      if (balance >= MIN_BALANCE && balance <= MAX_BALANCE) {
        screenClear();
        std::cout << "New balance: $" << balance << "\n";
        screenSleep();

        return;
      } else {
        balance = originalBalance;

        screenClear();
        std::cout << "Invalid amount. Resetting balance.\n";
        screenSleep();
      }
    } else {
      screenClear();
      std::cout << "Invalid input\n";
      screenSleep();
    }
  }
}