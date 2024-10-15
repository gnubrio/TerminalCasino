#pragma once

#include "Deck.h"
#include <string>
#include <utility>
#include <vector>

class Blackjack {
public:
  Blackjack();
  void play(unsigned &balance, unsigned &bet);
  ~Blackjack();

private:
  Deck m_Deck;
  bool m_PlayerWin = false;
  bool m_PlayerBust = false;
  bool m_HouseBust = false;
  std::vector<std::pair<std::string, std::string>> m_PlayerHand;
  std::vector<std::pair<std::string, std::string>> m_HouseHand;

  void initialDeal();
  void playerTurn();
  void houseTurn();
  void displayHands(bool hide = true) const;
  int checkHandValue(
      std::vector<std::pair<std::string, std::string>> &hand) const;
  void checkWin(unsigned &balance, unsigned &bet, bool end = false);
};