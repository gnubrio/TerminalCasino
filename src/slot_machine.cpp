#include "Chip.hpp"
#include "Pocket.hpp"
#include "SlotMachine.hpp"
#include "Utility.hpp"
#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <unordered_map>

SlotMachine::SlotMachine() { initialize(); }

SlotMachine::~SlotMachine() {}

void SlotMachine::play(Pocket &pocket) {
  exit_ = false;
  bet(pocket);
  if (exit_) {
    return;
  }
  spin();
  display();
  checkWinnings(pocket);
  screenSleep(2);
}

void SlotMachine::bet(Pocket &pocket) {
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
    return;
  }
}

void SlotMachine::display() const {
  screenClear();

  for (const auto &reel : reels_) {
    std::cout << "| " << reel[0] << " | " << reel[1] << " | " << reel[2] << " |"
              << std::endl;
    screenSleep();
  }
}

void SlotMachine::checkWinnings(Pocket &pocket) {
  const int LOSE_AMOUNT = 1;
  int value = bettingChip_.getValue();
  bool won = false;
  bool jackpot = false;
  int betModifier = 0;
  std::unordered_map<std::string, int> betModifiers = {
      {"C", 6}, {"O", 10}, {"B", 20}, {"G", 50}, {"7", 100},
  };

  for (const auto &reel : reels_) {
    if (reel[0] == reel[1] && reel[1] == reel[2]) {
      won = true;

      if (reel[0] == "7") {
        jackpot = true;
      }

      betModifier += betModifiers[reel[0]];
    }
  }

  int winnings = value * betModifier;
  if (won) {
    pocket.addChips(bettingChip_, betModifier);

    if (jackpot) {
      std::cout << "Jackpot! You won $" << winnings << std::endl;
      screenSleep();
      return;
    } else {
      std::cout << "You won $" << winnings << std::endl;
      screenSleep();
      return;
    }
  } else {
    Chip chip = pocket.findChip(value);
    pocket.removeChips(chip, LOSE_AMOUNT);
    return;
  }
}

void SlotMachine::spin() {
  for (auto &reel : reels_) {
    std::shuffle(reel.begin(), reel.end(), randomGenerator_);
  }
}

void SlotMachine::initialize() {
  for (int i = 0; i < numberOfReels_; ++i) {
    std::vector<std::string> reel;
    reels_.push_back(reel);
  }

  for (auto &reel : reels_) {
    for (auto &[symbol, count] : symbolCounts_) {
      for (int i = 0; i < count; ++i) {
        reel.push_back(symbol);
      }
    }
  }

  randomGenerator_.seed(std::random_device{}());
}
