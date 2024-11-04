#include "Pocket.hpp"
#include "Chip.hpp"
#include "Utility.hpp"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <limits>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

Pocket::Pocket() {}

Pocket::~Pocket() {}

void Pocket::addChips(const Chip &chipToAdd, const int amountToAdd) {
  auto it = std::find_if(pocket_.begin(), pocket_.end(),
                         [&chipToAdd](const Chip &chipInPocket) {
                           return chipToAdd == chipInPocket;
                         });
  if (it != pocket_.end()) {
    it->add(amountToAdd);
    return;
  } else {
    Chip newChip(chipToAdd.getValue(), chipToAdd.getColor(), amountToAdd);
    pocket_.emplace_back(newChip);
    return;
  }
}

void Pocket::removeChips(const Chip &chipToRemove, const int amountToRemove) {
  auto it = std::find_if(pocket_.begin(), pocket_.end(),
                         [&chipToRemove](const Chip &chipInPocket) {
                           return chipToRemove == chipInPocket;
                         });
  if (it != pocket_.end()) {
    it->remove(amountToRemove);
  }
  return;
}

bool Pocket::hasChip(const Chip &chipToCheck) const {
  if (pocket_.empty()) {
    return false;
  }
  return std::any_of(pocket_.begin(), pocket_.end(),
                     [&chipToCheck](const Chip &chipInPocket) {
                       return chipToCheck == chipInPocket;
                     });
}

bool Pocket::hasEnoughChips(const Chip &chipToCheck, const int amount) const {
  if (pocket_.empty()) {
    return false;
  }
  for (auto &chip : pocket_) {
    if (chip == chipToCheck) {
      if (amount <= chip.getAmount())
        return true;
    }
  }
  return false;
}

Chip Pocket::findChip(const int value) {
  for (auto &chip : pocket_) {
    if (chip.getValue() == value) {
      return chip;
    }
  }
  throw std::runtime_error("Object not found");
}

bool Pocket::ifPocketEmpty() const {
  if (pocket_.empty()) {
    return true;
  }
  return false;
}

void Pocket::displayPocket() const {
  if (pocket_.empty()) {
    return;
  }

  unsigned int i = 0;
  std::cout << "Chips: ";
  for (; i < pocket_.size() - 1; ++i) {
    pocket_[i].displayChip();
    std::cout << ", ";
  }
  pocket_[i].displayChip();
}

void Pocket::displayPocketOptions(std::unordered_map<int, int> &options) const {
  if (pocket_.empty()) {
    return;
  }

  unsigned int i = 0;
  for (; i < pocket_.size(); ++i) {
    std::cout << "(" << i + 1 << ") $" << pocket_[i].getValue() << " "
              << pocket_[i].getColor() << "\n";
    options[i + 1] = pocket_[i].getValue();
  }
}