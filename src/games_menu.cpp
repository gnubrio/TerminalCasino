#include "Blackjack.h"
#include "GamesMenu.h"
#include "SlotMachine.h"
#include "Utility.h"

void gamesMenu(unsigned &balance) {
  std::string userInput = "";

  while (true) {
    screenClear();
    std::cout << "GAMES | Balance: $" << balance
              << "\n(1) Slots\n(2) Blackjack\n(0) Exit\n> ";
    std::getline(std::cin, userInput);

    if (userInput == "1") {
      SlotMachine SlotMachine;

      while (true) {
        screenClear();
        std::cout << "SLOTS | Balance: $" << balance
                  << "\n(Enter) Play\n(1) Information\n(0) Exit\n> ";
        std::getline(std::cin, userInput);

        if (userInput.empty()) {
          unsigned bet = getBet(balance);

          if (bet != 0) {
            SlotMachine.play(balance, bet);
          }
        } else if (userInput == "1") {
          while (true) {
            screenClear();
            std::cout
                << "SLOTS | Information\nSymbol Values:\n| C | 6x bet\n| O | "
                   "10x bet\n| B | 20x bet\n| G | 50x bet\n| 7 | 100x bet\n(0) "
                   "Exit\n> ";
            std::getline(std::cin, userInput);
            if (userInput == "0") {
              break;
            } else {
              screenClear();
              std::cout << "Invalid Input\n";
              screenSleep();
            }
          }
        } else if (userInput == "0") {
          break;
        } else {
          screenClear();
          std::cout << "Invalid Input\n";
          screenSleep();
        }
      }
    } else if (userInput == "2") {
      Blackjack Blackjack;

      while (true) {
        screenClear();
        std::cout << "BLACKJACK | Balance: $" << balance
                  << "\n(Enter) Play\n(1) Information\n(0) Exit\n> ";
        std::getline(std::cin, userInput);

        if (userInput.empty()) {
          unsigned bet = getBet(balance);

          if (bet != 0) {
            Blackjack.play(balance, bet);
          }
        } else if (userInput == "1") {
          screenClear();
          std::cout << "BLACKJACK | Information\nWin: 2x bet\n(0) Exit\n> ";
          std::getline(std::cin, userInput);
        } else if (userInput == "0") {
          break;
        } else {
          screenClear();
          std::cout << "Invalid Input\n";
          screenSleep();
        }
      }
    } else if (userInput == "0") {
      return;
    }
  }
}

unsigned getBet(unsigned balance) {
  const int MAX_BET = 99999;
  const int MIN_BET = 0;
  std::string userInput = "";

  while (true) {
    screenClear();
    std::cout << "Enter bet:\n> ";
    std::getline(std::cin, userInput);

    if (isStringValidInt(userInput)) {
      unsigned amount = std::stoul(userInput);

      if (amount >= MIN_BET && amount <= MAX_BET && amount <= balance) {
        screenClear();
        std::cout << "Betting $" << amount << "\n";
        screenSleep();

        return amount;
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
  }
}