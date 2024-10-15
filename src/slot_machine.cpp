#include "SlotMachine.h"
#include "Utility.h"
#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <unordered_map>

SlotMachine::SlotMachine() { initialize(); }

void SlotMachine::play(unsigned &balance, unsigned bet) {
  spin();
  display();
  checkWinnings(balance, bet);

  screenSleep(3);
}

void SlotMachine::display() const {
  screenClear();

  for (auto &reel : m_Reels) {
    std::cout << "| " << reel[0] << " | " << reel[1] << " | " << reel[2] << " |"
              << std::endl;
    screenSleep();
  }
}

void SlotMachine::checkWinnings(unsigned &balance, unsigned bet) {
  bool won = false;
  bool jackpot = false;
  int betModifier = 0;
  int winnings = 0;
  std::unordered_map<std::string, int> betModifers = {
      {"C", 6}, {"O", 10}, {"B", 20}, {"G", 50}, {"7", 100},
  };

  for (auto &reel : m_Reels) {
    if (reel[0] == reel[1] && reel[1] == reel[2]) {
      won = true;

      if (reel[0] == "7") {
        jackpot = true;
      }

      betModifier += betModifers[reel[0]];
    }
  }

  if (won) {
    winnings += bet * betModifier;
    balance += winnings;

    if (jackpot) {
      std::cout << "Jackpot! You won $" << winnings << std::endl;
      screenSleep();
    } else {
      std::cout << "You won $" << winnings << std::endl;
      screenSleep();
    }
  } else {
    balance -= bet;
  }
}

void SlotMachine::spin() {
  for (auto &reel : m_Reels) {
    std::shuffle(reel.begin(), reel.end(), m_RandomGenerator);
  }
}

void SlotMachine::initialize() {
  for (int i = 0; i < m_NumberOfReels; ++i) {
    std::vector<std::string> reel;
    m_Reels.push_back(reel);
  }

  for (auto &reel : m_Reels) {
    for (auto &[symbol, count] : m_SymbolCounts) {
      for (int i = 0; i < count; ++i) {
        reel.push_back(symbol);
      }
    }
  }

  m_RandomGenerator.seed(std::random_device{}());
}

SlotMachine::~SlotMachine() {}