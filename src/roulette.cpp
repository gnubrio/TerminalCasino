#include "Roulette.h"
#include "Utility.h"
#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <thread>
#include <unordered_map>

Roulette::Roulette() { initialize(); }

void Roulette::play(unsigned &balance, unsigned &bet) {
  m_UserChoices.clear();

  getSymbolBets();
  if (m_Exit) {
    return;
  }

  spin();
  checkWinnings(balance, bet);
}

void Roulette::spin() {
  int ms = getRandomNumber(50, 150);
  screenClear();

  for (unsigned i = getRandomNumber(0, 37);; ++i) {
    if (i == m_Symbols.size()) {
      i = 0;
    }
    std::cout << "| " << m_Symbols[i].first << m_Symbols[i].second[0] << " |"
              << std::flush;
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));

    if (ms > 250) {
      m_WinningSymbol = m_Symbols[i];
      screenSleep();
      break;
    }
    ms += 2;
    screenClear();
  }
}

void Roulette::getSymbolBets() {
  std::string userInput = "";

  while (true) {
    screenClear();

    for (unsigned i = 0; i < m_TableSymbols.size(); ++i) {
      std::cout << "(" << i + 1 << ") " << m_TableSymbols[i] << "\n";
    }
    std::cout << "(0) Cancel\n> " << std::flush;
    std::getline(std::cin, userInput);

    if (userInput == "0") {
      m_Exit = true;
      return;
    }

    if (!m_TableSymbolOptions.contains(userInput)) {
      screenClear();
      std::cout << "Invalid Input" << std::endl;
      screenSleep();
      continue;
    }

    for (const auto &[key, value] : m_TableSymbolOptions) {
      if (key == userInput) {
        m_UserChoices.push_back(value);
        return;
      }
    }
  }
}

void Roulette::checkWinnings(unsigned &balance, unsigned &bet) {
  int betModifer = 0;
  int winningNumber = std::stoi(m_WinningSymbol.first);
  std::string winningColor = m_WinningSymbol.second;

  auto inOrderedRange = [](int x, int min, int max) {
    return x >= min && x <= max;
  };
  auto inColumnRange = [](int x, int start, int end) {
    for (int i = start; i < end + 1; i += 3) {
      return (i == x);
    }
    return false;
  };

  for (const auto &choice : m_UserChoices) {
    if (choice == m_TableSymbols[0]) {
      if (inOrderedRange(winningNumber, 1, 12)) {
        betModifer += 3;
      }
    } else if (choice == m_TableSymbols[1]) {
      if (inOrderedRange(winningNumber, 13, 24)) {
        betModifer += 3;
      }
    } else if (choice == m_TableSymbols[2]) {
      if (inOrderedRange(winningNumber, 25, 36)) {
        betModifer += 3;
      }
    } else if (choice == m_TableSymbols[3]) {
      if (inOrderedRange(winningNumber, 1, 18)) {
        betModifer += 2;
      }
    } else if (choice == m_TableSymbols[4]) {
      if (inOrderedRange(winningNumber, 19, 36)) {
        betModifer += 2;
      }
    } else if (choice == m_TableSymbols[5]) {
      if (winningNumber % 2 == 0) {
        betModifer += 2;
      }
    } else if (choice == m_TableSymbols[6]) {
      if (winningNumber % 2 != 0) {
        betModifer += 2;
      }
    } else if (choice == m_TableSymbols[7]) {
      if (winningColor == "Red") {
        betModifer += 2;
      }
    } else if (choice == m_TableSymbols[8]) {
      if (winningColor == "Black") {
        betModifer += 2;
      }
    } else if (choice == m_TableSymbols[9]) {
      if (inColumnRange(winningNumber, 1, 34)) {
        betModifer += 3;
      }
    } else if (choice == m_TableSymbols[10]) {
      if (inColumnRange(winningNumber, 2, 35)) {
        betModifer += 3;
      }
    } else if (choice == m_TableSymbols[11]) {
      if (inColumnRange(winningNumber, 3, 36)) {
        betModifer += 3;
      }
    }
  }

  if (betModifer == 0) {
    balance -= bet;
  } else {
    int winnings = bet * betModifer;
    balance += winnings;

    screenClear();
    std::cout << "You won $" << winnings << "!" << std::endl;
    screenSleep();
  }
}

int Roulette::getRandomNumber(int min, int max) {
  std::uniform_int_distribution<int> dist(min, max);
  return dist(m_RandomGenerator);
}

void Roulette::initialize() {
  for (unsigned i = 0; i < m_TableSymbols.size(); ++i) {
    m_TableSymbolOptions[std::to_string(i + 1)] = m_TableSymbols[i];
  }

  m_RandomGenerator.seed(std::random_device{}());
}

Roulette::~Roulette() {}