#include "Roulette.h"
#include "Utility.h"

Roulette::Roulette() { initialize(); }

void Roulette::play(unsigned &balance, unsigned &bet) {
  getSymbolBets(); 
}

void Roulette::getSymbolBets() {
  std::string userInput = "";

  while (true) {
    std::cout << 
  }
}

void Roulette::initialize() {
  for (int i = 0; i < m_SymbolCount; ++i) {
    m_tableSymbols.push_back(i);
  }
}

Roulette::~Roulette() {}