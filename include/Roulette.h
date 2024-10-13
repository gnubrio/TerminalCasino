#pragma once

#include "pch.h"

class Roulette {
public:
  Roulette();
  void play(unsigned &balance, unsigned &bet);
  ~Roulette();

private:
  std::array<std::pair<std::string, std::string>, 37> m_Symbols = {
      {{"00", "Green"}, {"01", "Red"},   {"02", "Black"}, {"03", "Red"},
       {"04", "Black"}, {"05", "Red"},   {"06", "Black"}, {"07", "Red"},
       {"08", "Black"}, {"09", "Red"},   {"10", "Black"}, {"11", "Black"},
       {"12", "Red"},   {"13", "Black"}, {"14", "Red"},   {"15", "Black"},
       {"16", "Red"},   {"17", "Black"}, {"18", "Red"},   {"19", "Red"},
       {"20", "Black"}, {"21", "Red"},   {"22", "Black"}, {"23", "Red"},
       {"24", "Black"}, {"25", "Red"},   {"26", "Black"}, {"27", "Red"},
       {"28", "Black"}, {"29", "Black"}, {"30", "Red"},   {"31", "Black"},
       {"32", "Red"},   {"33", "Black"}, {"34", "Red"},   {"35", "Black"},
       {"36", "Red"}}};
  std::array<std::string, 12> m_tableSymbols = {
      "1st 12", "2nd 12", "3rd 12", "1 to 18",  "19 to 36", "Even",
      "Odd",    "Red",    "Black",  "Column 1", "Column 2", "Column 3"};
  std::vector<std::string> userChoices;
  std::mt19937 m_RandomGenerator;

  void spin() const;
  void getSymbolBets();
  void initialize();
};