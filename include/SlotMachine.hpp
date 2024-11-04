#pragma once

#include "Pocket.hpp"
#include "Chip.hpp"
#include <random>
#include <string>
#include <vector>

class SlotMachine {
public:
  SlotMachine();
  void play(Pocket &pocket);
  ~SlotMachine();

private:
  Chip bettingChip_;
  const int numberOfReels_ = 3;
  std::vector<std::vector<std::string>> reels_;
  const std::vector<std::pair<std::string, int>> symbolCounts_ = {
      {"C", 7}, {"O", 5}, {"B", 4}, {"G", 3}, {"7", 1}};
  bool exit_ = false;
  std::mt19937 randomGenerator_;

  void bet(Pocket &pocket);
  void display() const;
  void checkWinnings(Pocket &pocket);
  void spin();
  void initialize();
};