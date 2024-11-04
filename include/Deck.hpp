#pragma once

#include <array>
#include <random>
#include <string>
#include <utility>
#include <vector>

class Deck {
public:
  Deck();
  void pullCard(std::vector<std::pair<std::string, std::string>> &hand,
                int count = 1);
  void shuffle();
  void reset();
  ~Deck();

private:
  std::vector<std::pair<std::string, std::string>> deck_;
  const std::array<std::string, 4> suits_ = {"Diamond", "Spades", "Hearts",
                                              "Clubs"};
  const std::array<std::string, 13> ranks_ = {
      "Ace", "2", "3",  "4",    "5",     "6",   "7",
      "8",   "9", "10", "Jack", "Queen", "King"};
  std::mt19937 randomGenerator_;

  void initialize();
};