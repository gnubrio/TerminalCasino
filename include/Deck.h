#pragma once

#include <algorithm>
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
  std::vector<std::pair<std::string, std::string>> m_Deck;
  const std::vector<std::string> m_Suits = {"Diamond", "Spades", "Hearts",
                                            "Clubs"};
  const std::vector<std::string> m_Ranks = {"Ace",  "2",     "3",   "4", "5",
                                            "6",    "7",     "8",   "9", "10",
                                            "Jack", "Queen", "King"};
  std::mt19937 m_RandomGenerator;

  void initialize();
};