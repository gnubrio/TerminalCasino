#pragma once

#include "Deck.hpp"
#include "Chip.hpp"
#include "Pocket.hpp"
#include <string>
#include <utility>
#include <vector>

class Blackjack {
public:
  Blackjack();
  void play(Pocket &pocket);
  ~Blackjack();

private:
  Deck deck_;
  Chip bettingChip_;
  bool exit_;
  bool playerWin_ = false;
  bool playerBust_ = false;
  bool houseBust_ = false;
  std::vector<std::pair<std::string, std::string>> playerHand_;
  std::vector<std::pair<std::string, std::string>> houseHand_;

  void bet(Pocket &pocket);
  void initialDeal();
  void playerTurn();
  void houseTurn();
  void displayHands(bool hide = true) const;
  int checkHandValue(
      std::vector<std::pair<std::string, std::string>> &hand) const;
  void checkWin(Pocket &pocket, bool end = false);
};