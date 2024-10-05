#pragma once

#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class SlotMachine {
public:
  SlotMachine();
  void play(unsigned &balance, unsigned bet);
  ~SlotMachine();

private:
  int m_NumberOfReels = 3;
  std::vector<std::vector<std::string>> m_Reels;
  std::vector<std::pair<std::string, int>> m_SymbolCounts = {
      {"C", 7}, {"O", 5}, {"B", 4}, {"G", 3}, {"7", 1}};
  std::mt19937 m_RandomGenerator;

  void display();
  void checkWinnings(unsigned &balance, unsigned bet);
  void spin();
  void initialize();
};