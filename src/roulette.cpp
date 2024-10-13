#include "Roulette.h"
#include "Utility.h"
#include "pch.h"

Roulette::Roulette() { initialize(); }

void Roulette::play(unsigned &balance, unsigned &bet) {
  getSymbolBets();
  spin();
}

void Roulette::spin() const {
  int milliseconds = 100;
  std::shuffle(m_Symbols.begin(), m_Symbols.end(), m_RandomGenerator);

  for (unsigned i = 0; i < m_Symbols.size(); ++i) {
    if (i == m_Symbols.size()) {
      i = 0;
    }

    screenClear();
    std::cout << "| " << m_Symbols[i].first << m_Symbols[i].second[0] << " |"
              << std::flush;
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    milliseconds += 2;
  }
}

void Roulette::getSymbolBets() {
  std::string userInput = "";
  std::unordered_map<std::string, std::string> options;

  for (unsigned i = 0; i < m_tableSymbols.size(); ++i) {
    options.insert({std::to_string(i + 1), m_tableSymbols[i]});
  }

  while (true) {
    screenClear();
    for (unsigned i = 0; i < m_tableSymbols.size(); ++i) {
      std::cout << "(" << i + 1 << ")" << m_tableSymbols[i] << std::endl;
    }
    std::cout << "> " << std::flush;
    std::getline(std::cin, userInput);

    if (!isStringValidInt(userInput)) {
      screenClear();
      std::cout << "Invalid Input" << std::endl;
      screenSleep();

      continue;
    }

    if (options.contains(userInput)) {
      for (const auto &symbol : m_tableSymbols) {
        if (userInput == symbol) {
          userChoices.push_back(symbol);
        }
      }
    } else {
      screenClear();
      std::cout << "Invalid Input" << std::endl;
      screenSleep();

      continue;
    }

    return;
  }
}

void Roulette::initialize() { m_RandomGenerator.seed(std::random_device{}()); }

Roulette::~Roulette() {}