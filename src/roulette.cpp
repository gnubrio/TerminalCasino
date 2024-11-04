#include "Roulette.hpp"
#include "Pocket.hpp"
#include "Utility.hpp"
#include "Chip.hpp"
#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <thread>
#include <unordered_map>

Roulette::Roulette() { initialize(); }

Roulette::~Roulette() {}

void Roulette::play(Pocket &pocket) {
  userChoices_.clear();
  exit_ = false;

  bet(pocket);
  if (exit_) {
    return;
  }
  getSymbolBets(pocket);
  if (exit_) {
    return;
  }

  spin();
  checkWinnings(pocket);
}

void Roulette::bet(Pocket &pocket) {
  std::string userInput = "";

  while (true) {
    int value = 0;
    std::string color = "";

    screenClear();
    std::cout << "BET | ";
    pocket.displayPocket();
    std::cout << "\n";
    std::unordered_map<int, int> options;
    pocket.displayPocketOptions(options);
    std::cout << "(0) Leave\n> ";
    std::getline(std::cin, userInput);

    if (userInput == "0") {
      exit_ = true;
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
    int amount = 1;
    bettingChip_ = Chip(value, color);

    std::transform(color.begin(), color.end(), color.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    if (!pocket.hasEnoughChips(bettingChip_, amount)) {
      screenClear();
      std::cout << "I don't have enough " << color << " chips." << std::endl;
      screenSleep();
      continue;
    }
    screenClear();
    std::cout << "Betting " << color << " chip." << std::endl;
    screenSleep();
    return;
  }
}

void Roulette::spin() {
  int ms = getRandomNumber(50, 150);
  screenClear();

  for (unsigned i = getRandomNumber(0, 37);; ++i) {
    if (i == symbols_.size()) {
      i = 0;
    }
    std::cout << "| " << symbols_[i].first << symbols_[i].second[0] << " |"
              << std::flush;
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));

    if (ms > 250) {
      winningSymbol_ = symbols_[i];
      screenSleep();
      break;
    }
    ms += 2;
    screenClear();
  }
}

void Roulette::getSymbolBets(Pocket &pocket) {
  std::string userInput = "";

  while (true) {
    screenClear();
    std::cout << "BET | ";
    pocket.displayPocket();
    std::cout << "\n";
    for (unsigned i = 0; i < tableSymbols_.size(); ++i) {
      std::cout << "(" << i + 1 << ") " << tableSymbols_[i] << "\n";
    }
    std::cout << "(0) Cancel\n> " << std::flush;
    std::getline(std::cin, userInput);

    if (userInput == "0") {
      exit_ = true;
      return;
    }

    if (!tableSymbolOptions_.contains(userInput)) {
      screenClear();
      std::cout << "Invalid Input" << std::endl;
      screenSleep();
      continue;
    }

    for (const auto &[key, value] : tableSymbolOptions_) {
      if (key == userInput) {
        userChoices_.push_back(value);
        return;
      }
    }
  }
}

void Roulette::checkWinnings(Pocket &pocket) {
  const int LOSE_AMOUNT = 1;
  int value = bettingChip_.getValue();
  int betModifer = 0;
  int winningNumber = std::stoi(winningSymbol_.first);
  std::string winningColor = winningSymbol_.second;

  auto inOrderedRange = [](int x, int min, int max) {
    return x >= min && x <= max;
  };
  auto inColumnRange = [](int x, int start, int end) {
    for (int i = start; i < end + 1; i += 3) {
      return (i == x);
    }
    return false;
  };

  for (const auto &choice : userChoices_) {
    if (choice == tableSymbols_[0]) {
      if (inOrderedRange(winningNumber, 1, 12)) {
        betModifer += 3;
      }
    } else if (choice == tableSymbols_[1]) {
      if (inOrderedRange(winningNumber, 13, 24)) {
        betModifer += 3;
      }
    } else if (choice == tableSymbols_[2]) {
      if (inOrderedRange(winningNumber, 25, 36)) {
        betModifer += 3;
      }
    } else if (choice == tableSymbols_[3]) {
      if (inOrderedRange(winningNumber, 1, 18)) {
        betModifer += 2;
      }
    } else if (choice == tableSymbols_[4]) {
      if (inOrderedRange(winningNumber, 19, 36)) {
        betModifer += 2;
      }
    } else if (choice == tableSymbols_[5]) {
      if (winningNumber % 2 == 0) {
        betModifer += 2;
      }
    } else if (choice == tableSymbols_[6]) {
      if (winningNumber % 2 != 0) {
        betModifer += 2;
      }
    } else if (choice == tableSymbols_[7]) {
      if (winningColor == "Red") {
        betModifer += 2;
      }
    } else if (choice == tableSymbols_[8]) {
      if (winningColor == "Black") {
        betModifer += 2;
      }
    } else if (choice == tableSymbols_[9]) {
      if (inColumnRange(winningNumber, 1, 34)) {
        betModifer += 3;
      }
    } else if (choice == tableSymbols_[10]) {
      if (inColumnRange(winningNumber, 2, 35)) {
        betModifer += 3;
      }
    } else if (choice == tableSymbols_[11]) {
      if (inColumnRange(winningNumber, 3, 36)) {
        betModifer += 3;
      }
    }
  }

  if (betModifer == 0) {
    Chip chip = pocket.findChip(value);
    pocket.removeChips(chip, LOSE_AMOUNT);
  } else {
    int winnings = value * betModifer;
    pocket.addChips(bettingChip_, betModifer);

    screenClear();
    std::cout << "You won $" << winnings << "!" << std::endl;
    screenSleep();
  }
}

int Roulette::getRandomNumber(int min, int max) {
  std::uniform_int_distribution<int> dist(min, max);
  return dist(randomGenerator_);
}

void Roulette::initialize() {
  for (unsigned i = 0; i < tableSymbols_.size(); ++i) {
    tableSymbolOptions_[std::to_string(i + 1)] = tableSymbols_[i];
  }

  randomGenerator_.seed(std::random_device{}());
}
