#include "Chip.hpp"
#include <iostream>
#include <string>
#include <unordered_map>

const std::array<std::pair<int, std::string>, 8> Chip::chipValues_ = {{
    {1, "White"},
    {5, "Red"},
    {10, "Blue"},
    {25, "Green"},
    {100, "Black"},
    {500, "Purple"},
    {1000, "Gray"},
    {5000, "Orange"},
}};

Chip::Chip() {}

Chip::Chip(int value, std::string color) : value_(value), color_(color) {}

Chip::Chip(int value, std::string color, int amount)
    : value_(value), color_(color), amount_(amount) {}

Chip::~Chip() {}

int Chip::getValue() const { return value_; }

std::string Chip::getColor() const { return color_; }

int Chip::getAmount() const { return amount_; }

void Chip::add(const int amountToAdd) { amount_ += amountToAdd; }

void Chip::remove(const int amountToRemove) {
  if (amount_ - amountToRemove < 0) {
    return;
  }
  amount_ -= amountToRemove;
}

std::string Chip::getColorFromValue(int valueToCheck) {
  for (const auto &[value, color] : chipValues_) {
    if (valueToCheck == value) {
      return color;
    }
  }
  return "";
}

void Chip::displayChip() const {
  std::cout << color_ << " $" << value_ << " x" << amount_;
}

std::unordered_map<int, int>
Chip::displayChipOptions(std::unordered_map<int, int> &options) {
  for (unsigned int i = 0; i < chipValues_.size(); ++i) {
    std::cout << "(" << i + 1 << ") " << chipValues_[i].first << " "
              << chipValues_[i].second << "\n";

    options[i + 1] = chipValues_[i].first;
  }
  return options;
}