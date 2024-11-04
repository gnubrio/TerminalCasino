#pragma once

#include <array>
#include <string>
#include <unordered_map>
#include <utility>

class Chip {
public:
  Chip();
  Chip(int value, std::string color);
  Chip(int value, std::string color, int amount);
  ~Chip();

  int getValue() const;
  std::string getColor() const;
  int getAmount() const;

  void add(const int amountToAdd);
  void remove(const int amountToRemove);
  static std::string getColorFromValue(int value);
  void displayChip() const;
  static std::unordered_map<int, int>
  displayChipOptions(std::unordered_map<int, int> &options);

  bool operator==(const Chip &other) const { return value_ == other.value_; }

private:
  int value_ = 0;
  std::string color_ = "";
  unsigned int amount_ = 0;
  static const std::array<std::pair<int, std::string>, 8> chipValues_;
};
