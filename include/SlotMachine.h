#pragma once

#include <random>
#include <string>
#include <vector>

class SlotMachine {
public:
  SlotMachine();
  void play(unsigned &balance, unsigned bet);
  ~SlotMachine();

private:
  const int m_NumberOfReels = 3;
  std::vector<std::vector<std::string>> m_Reels;
  const std::vector<std::pair<std::string, int>> m_SymbolCounts = {
      {"C", 7}, {"O", 5}, {"B", 4}, {"G", 3}, {"7", 1}};
  std::mt19937 m_RandomGenerator;

  void display() const;
  void checkWinnings(unsigned &balance, unsigned bet);
  void spin();
  void initialize();
};