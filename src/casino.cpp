#include "Casino.hpp"
#include "Blackjack.hpp"
#include "Chip.hpp"
#include "Pocket.hpp"
#include "Roulette.hpp"
#include "SlotMachine.hpp"
#include "Utility.hpp"
#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>

void mainMenu() {
  unsigned int balance = 1000;
  Pocket pocket;
  std::string userInput = "";

  screenClear();
  std::cout << "Time to get rich!" << std::endl;
  screenSleep();

  while (true) {
    screenClear();
    std::cout << "LOBBY | Balance: $" << balance << " | ";
    pocket.displayPocket();
    std::cout << "\n(1) Cardroom\n(2) Cashier's Cage\n(0) Exit\n> "
              << std::flush;
    std::getline(std::cin, userInput);

    if (userInput == "1") {
      if (pocket.ifPocketEmpty()) {
        screenClear();
        std::cout << "I don't have any chips." << std::endl;
        screenSleep();
        continue;
      }
      cardroomMenu(pocket);
    } else if (userInput == "2") {
      cashiersCage(balance, pocket);
    } else if (userInput == "0") {
      while (true) {
        screenClear();
        std::cout << "Do I really want to leave? (Y/N)\n> " << std::flush;
        std::getline(std::cin, userInput);
        std::transform(userInput.begin(), userInput.end(), userInput.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        if (userInput == "y") {
          screenClear();
          return;
        } else if (userInput == "n") {
          break;
        } else {
          continue;
        }
      }
    } else {
      continue;
    }
  }
}

void cashiersCage(unsigned int &balance, Pocket &pocket) {
  std::string userInput = "";

  while (true) {
    screenClear();
    std::cout << "CASHIER'S CAGE | Balance: $" << balance << " | ";
    pocket.displayPocket();
    std::cout << "\n(1) Buy Chips\n(2) Trade in Chips\n(0) Leave\n> "
              << std::flush;
    std::getline(std::cin, userInput);

    if (userInput == "1") {
      buyChips(balance, pocket);
    } else if (userInput == "2") {
      tradeInChips(balance, pocket);
    } else if (userInput == "0") {
      return;
    } else {
      continue;
    }
  }
}

void buyChips(unsigned int &balance, Pocket &pocket) {
  std::string userInput = "";

  while (true) {
    int value = 0;
    std::string color = "";
    int amount = 0;

    screenClear();
    std::cout << "BUY CHIPS | Balance $" << balance << " | ";
    pocket.displayPocket();
    std::cout << "\n";
    std::unordered_map<int, int> options;
    options = Chip::displayChipOptions(options);
    std::cout << "(0) Leave\n> " << std::flush;
    std::getline(std::cin, userInput);

    if (userInput == "0") {
      return;
    } else if (!isStringValidInt(userInput)) {
      screenClear();
      std::cout << userInput << " is not a number." << std::endl;
      screenSleep();
      continue;
    }
    int choice = std::stoi(userInput);

    if (!options.contains(choice)) {
      screenClear();
      std::cout << userInput << " isn't an option." << std::endl;
      screenSleep();
      continue;
    }
    value = options[choice];
    color = Chip::getColorFromValue(value);

    while (true) {
      screenClear();
      std::cout << "BUY CHIPS | Balance $" << balance << " | ";
      pocket.displayPocket();
      std::cout << "\nHow many chips do I want to buy?\n> " << std::flush;
      std::getline(std::cin, userInput);

      if (userInput == "0") {
        break;
      } else if (!isStringValidInt(userInput)) {
        screenClear();
        std::cout << userInput << " is not a number." << std::endl;
        screenSleep();
        continue;
      }
      amount = std::stoi(userInput);
      Chip chip(value, color);

      std::transform(color.begin(), color.end(), color.begin(),
                     [](unsigned char c) { return std::tolower(c); });
      unsigned int amountToAdd = static_cast<unsigned int>(value * amount);
      if (balance < amountToAdd) {
        screenClear();
        std::cout << "I don't have enough money to buy " << amount << " of "
                  << color << " chips." << std::endl;
        screenSleep();
        continue;
      }
      balance -= value * amount;
      pocket.addChips(chip, amount);
      screenClear();
      std::cout << "Buying " << amount << " " << color << " chips."
                << std::endl;
      screenSleep();
      return;
    }
  }
}

void tradeInChips(unsigned int &balance, Pocket &pocket) {
  std::string userInput = "";

  while (true) {
    int value = 0;
    std::string color = "";
    int amount = 0;

    screenClear();
    std::cout << "TRADE IN CHIPS | Balance $" << balance << " | ";
    pocket.displayPocket();
    std::cout << "\n";
    std::unordered_map<int, int> options;
    pocket.displayPocketOptions(options);
    std::cout << "(0) Leave\n> " << std::flush;
    std::getline(std::cin, userInput);

    if (userInput == "0") {
      return;
    } else if (!isStringValidInt(userInput)) {
      screenClear();
      std::cout << userInput << " is not a number." << std::endl;
      screenSleep();
      continue;
    }
    int choice = std::stoi(userInput);

    if (!options.contains(choice)) {
      screenClear();
      std::cout << userInput << " isn't an option." << std::endl;
      screenSleep();
      continue;
    }
    value = options[choice];
    color = Chip::getColorFromValue(value);

    while (true) {
      screenClear();
      std::cout << "TRADE IN CHIPS | Balance $" << balance << " | ";
      pocket.displayPocket();
      std::cout << "\nHow many chips do I want to trade in?\n> " << std::flush;
      std::getline(std::cin, userInput);

      if (userInput == "0") {
        break;
      } else if (!isStringValidInt(userInput)) {
        screenClear();
        std::cout << userInput << " is not a number." << std::endl;
        screenSleep();
        continue;
      }
      amount = std::stoi(userInput);
      Chip chip = pocket.findChip(value);

      std::transform(color.begin(), color.end(), color.begin(),
                     [](unsigned char c) { return std::tolower(c); });
      if (amount > chip.getAmount()) {
        screenClear();
        std::cout << "I don't have " << amount << " " << color
                  << " chips to trade in." << std::endl;
        screenSleep();
        continue;
      }
      balance += value * amount;
      pocket.removeChips(chip, amount);
      break;
    }
    screenClear();
    std::cout << "Trading in " << amount << " " << color << " chips."
              << std::endl;
    screenSleep();
    return;
  }
}

void cardroomMenu(Pocket &pocket) {
  std::string userInput = "";

  while (true) {
    screenClear();
    std::cout << "CARDROOM | ";
    pocket.displayPocket();
    std::cout << "\n(1) Slots\n(2) Blackjack\n(3) Roulette\n(0) Exit\n> "
              << std::flush;
    std::getline(std::cin, userInput);

    if (userInput == "1") {
      SlotMachine SlotMachine;
      const char *location = "SLOTS";
      const char *information =
          "SLOTS | Information\nSymbol Values:\n| C | 6x bet\n| O | "
          "10x bet\n| B | 20x bet\n| G | 50x bet\n| 7 | 100x bet\n(0) "
          "Exit\n> ";
      displayGameMenu(SlotMachine, location, information, pocket);
    } else if (userInput == "2") {
      Blackjack Blackjack;
      const char *location = "BLACKJACK";
      const char *information =
          "BLACKJACK | Information\nWin: 2x bet\n(0) Exit\n> ";
      displayGameMenu(Blackjack, location, information, pocket);
    } else if (userInput == "3") {
      Roulette Roulette;
      const char *location = "ROULETTE";
      const char *information =
          "ROULETTE | Information\n| 1st 12 | 3x\n| 2nd 12 | "
          "3x\n| 3rd 12 | 3x\n| 1 to 18 | 2x\n| 19 to 36 | 2x\n| "
          "Even/Odd | 2x\n| Red/Black | 2x\n| Columns | 3x\n(0) Exit\n> ";
      displayGameMenu(Roulette, location, information, pocket);
    } else if (userInput == "0") {
      return;
    } else {
      continue;
    }
  }
}

template <typename T>
void displayGameMenu(T &game, const char *&location, const char *&information,
                     Pocket &pocket) {
  std::string userInput = "";

  while (true) {
    pocket.outOfChipsCheck();
    screenClear();
    std::cout << location << " | ";
    pocket.displayPocket();
    std::cout << "\n(Enter) Play\n(1) Information\n(0) Exit\n> " << std::flush;
    std::getline(std::cin, userInput);

    if (userInput.empty()) {
      game.play(pocket);
    } else if (userInput == "1") {
      while (true) {
        screenClear();
        std::cout << information << std::flush;
        std::getline(std::cin, userInput);
        if (userInput == "0") {
          break;
        }
      }
    } else if (userInput == "0") {
      return;
    } else {
      continue;
    }
  }
}
