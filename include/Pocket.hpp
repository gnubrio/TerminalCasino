#pragma once

#include "Chip.hpp"
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class Pocket {
public:
  Pocket();
  ~Pocket();

  void addChips(const Chip &chipToAdd, const int amountToAdd);
  void removeChips(const Chip &chipToRemove, const int amountToRemove);
  void outOfChipsCheck();
  bool hasChip(const Chip &chipToCheck) const;
  bool hasEnoughChips(const Chip &chipToCheck, const int amount) const;
  Chip findChip(const int value);
  bool ifPocketEmpty() const;
  void displayPocket() const;
  void displayPocketOptions(std::unordered_map<int, int> &options) const;

private:
  std::vector<Chip> pocket_;
};
