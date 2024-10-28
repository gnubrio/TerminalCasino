#include "Blackjack.h"
#include "Deck.h"
#include "Utility.h"
#include <iostream>
#include <string>
#include <utility>
#include <vector>

Blackjack::Blackjack() {}

void Blackjack::play(unsigned &balance, unsigned &bet) {
  m_PlayerWin = false;
  m_PlayerBust = false;
  m_HouseBust = false;
  m_PlayerHand.clear();
  m_HouseHand.clear();
  m_Deck.reset();
  m_Deck.shuffle();

  initialDeal();
  checkWin(balance, bet);

  if (m_PlayerWin) {
    return;
  }

  playerTurn();
  checkWin(balance, bet);

  if (m_PlayerWin || m_PlayerBust) {
    return;
  }

  houseTurn();
  checkWin(balance, bet, true);

  screenSleep(3);
}

void Blackjack::initialDeal() {
  m_Deck.pullCard(m_PlayerHand, 2);
  m_Deck.pullCard(m_HouseHand, 2);

  screenClear();
  std::cout << "You drew: | " << (m_PlayerHand[0].second) << " of "
            << m_PlayerHand[0].first << " |\n";
  screenSleep();
  std::cout << "House drew: | ################|\n";
  screenSleep();
  std::cout << "You drew: | " << m_PlayerHand[1].second << " of "
            << m_PlayerHand[1].first << " |\n";
  screenSleep();
  std::cout << "House drew: | " << m_HouseHand[1].second << " of "
            << m_HouseHand[1].first << " |\n";
  screenSleep();

  int playerScore = checkHandValue(m_PlayerHand);

  if (playerScore == 21) {
    m_PlayerWin = true;
  }
}

void Blackjack::playerTurn() {
  std::string userInput = "";
  int playerScore;

  while (true) {
    screenClear();
    displayHands();

    std::cout << "(1) Hit\n(2) Stand\n> ";
    std::getline(std::cin, userInput);

    if (userInput == "1") {
      m_Deck.pullCard(m_PlayerHand);
      playerScore = checkHandValue(m_PlayerHand);

      if (playerScore == 21) {
        m_PlayerWin = true;
        return;
      } else if (playerScore > 21) {
        m_PlayerBust = true;
        return;
      }
    } else if (userInput == "2") {
      return;
    } else {
      screenClear();
      std::cout << "Invalid Input\n";
      screenSleep();
    }
  }
}

void Blackjack::houseTurn() {
  while (true) {
    int houseScore;
    screenClear();
    displayHands();
    screenSleep();

    houseScore = checkHandValue(m_HouseHand);

    if (houseScore > 21) {
      m_HouseBust = true;
      return;
    } else if (houseScore < 17) {
      m_Deck.pullCard(m_HouseHand);
    } else {
      return;
    }
  }
}

void Blackjack::displayHands(bool hide) const {
  screenClear();
  std::cout << "House hand: | ";
  for (const auto &card : m_HouseHand) {
    if (hide) {
      std::cout << "################ | ";
      hide = false;
    } else {
      std::cout << card.second << " of " << card.first << " | ";
    }
  }
  std::cout << "\n";

  std::cout << "Your hand: | ";
  for (const auto &card : m_PlayerHand) {
    std::cout << card.second << " of " << card.first << " | ";
  }
  std::cout << "\n";
}

int Blackjack::checkHandValue(
    std::vector<std::pair<std::string, std::string>> &hand) const {
  int score = 0;
  int aceCount = 0;

  for (auto &card : hand) {
    if (isStringValidInt(card.second)) {
      score += std::stoi(card.second);
    } else if (card.second == "Jack" || card.second == "Queen" ||
               card.second == "King") {
      score += 10;
    } else if (card.second == "Ace") {
      aceCount++;
    }
  }

  for (int i = 0; i < aceCount; ++i) {
    if (score + 11 > 21) {
      score += 1;
    } else {
      score += 11;
    }
  }

  return score;
}

void Blackjack::checkWin(unsigned &balance, unsigned &bet, bool end) {
  screenClear();
  if (!end) {
    displayHands();
  } else {
    displayHands(false);
  }

  if (m_PlayerWin) {
    int winnings = bet * 2;
    balance += winnings;

    std::cout << "Blackjack! You won: $" << winnings << "\n";
    screenSleep();

    return;
  } else if (m_PlayerBust) {
    balance -= bet;

    std::cout << "Bust!\n";
    screenSleep();

    return;
  }

  if (m_HouseBust) {
    int winnings = bet * 2;
    balance += winnings;

    std::cout << "House bust! You won: $" << winnings << "\n";
    screenSleep();

    return;
  }

  if (end) {
    int playerScore = checkHandValue(m_PlayerHand);
    int houseScore = checkHandValue(m_HouseHand);

    if (playerScore >= houseScore) {
      int winnings = bet * 2;
      balance += winnings;

      std::cout << "You won: $" << winnings << "\n";
      screenSleep();

      return;
    } else {
      balance -= bet;

      std::cout << "You lost\n";
      screenSleep();

      return;
    }
  }
}

Blackjack::~Blackjack() {}