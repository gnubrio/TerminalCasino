#pragma once

#include <array>
#include <random>
#include <string>
#include <unordered_map>
#include <utility>

class Roulette {
public:
  Roulette();
  void play(unsigned &balance, unsigned &bet);
  ~Roulette();

private:
  const std::array<std::pair<std::string, std::string>, 37> m_Symbols = {
      {{"00", "Green"}, {"32", "Red"}, {"15", "Black"}, {"19", "Red"},
       {"04", "Black"}, {"21", "Red"}, {"02", "Black"}, {"25", "Red"},
       {"17", "Black"}, {"34", "Red"}, {"06", "Black"}, {"27", "Red"},
       {"13", "Black"}, {"36", "Red"}, {"11", "Black"}, {"30", "Red"},
       {"08", "Black"}, {"23", "Red"}, {"10", "Black"}, {"05", "Red"},
       {"24", "Black"}, {"16", "Red"}, {"33", "Black"}, {"01", "Red"},
       {"20", "Black"}, {"14", "Red"}, {"31", "Black"}, {"09", "Red"},
       {"22", "Black"}, {"18", "Red"}, {"29", "Black"}, {"07", "Red"},
       {"28", "Black"}, {"12", "Red"}, {"35", "Black"}, {"03", "Red"},
       {"26", "Black"}}};
  std::pair<std::string, std::string> m_WinningSymbol;
  const std::array<std::string, 12> m_TableSymbols = {
      "1st 12", "2nd 12", "3rd 12", "1 to 18",  "19 to 36", "Even",
      "Odd",    "Red",    "Black",  "Column 1", "Column 2", "Column 3"};
  std::unordered_map<std::string, std::string> m_TableSymbolOptions;
  bool m_Exit = false;
  std::vector<std::string> m_UserChoices;
  std::mt19937 m_RandomGenerator;

  void spin();
  void getSymbolBets();
  void checkWinnings(unsigned &balance, unsigned &bet);
  int getRandomNumber(int min, int max);
  void initialize();
};