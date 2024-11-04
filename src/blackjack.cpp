#include "Blackjack.hpp"
#include "Chip.hpp"
#include "Deck.hpp"
#include "Pocket.hpp"
#include "Utility.hpp"
#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

Blackjack::Blackjack() {}

Blackjack::~Blackjack() {}

void Blackjack::play(Pocket &pocket) {
  playerWin_ = false;
  playerBust_ = false;
  houseBust_ = false;
  exit_ = false;
  playerHand_.clear();
  houseHand_.clear();
  deck_.reset();
  deck_.shuffle();

  bet(pocket);
  if (exit_) {
    return;
  }

  initialDeal();
  checkWin(pocket);

  if (playerWin_) {
    return;
  }

  playerTurn();
  checkWin(pocket);

  if (playerWin_ || playerBust_) {
    return;
  }

  houseTurn();
  checkWin(pocket, true);

  screenSleep(3);
}

void Blackjack::bet(Pocket &pocket) {
  std::string userInput = "";

  while (true) {
    int value = 0;
    std::string color = "";

    screenClear();
    std::cout << "BET | ";
    pocket.displayPocket();
    std::cout << "\n";
    std::unordered_map<int, int> options;
    pocket.displayPocketOptions(options);
    std::cout << "(0) Leave\n> ";
    std::getline(std::cin, userInput);

    if (userInput == "0") {
      exit_ = true;
      return;
    } else if (!isStringValidInt(userInput)) {
      screenClear();
      std::cout << userInput << " is not a number." << std::endl;
      screenSleep();
      continue;
    }
    int choice = std::stoi(userInput);

    if (!options.contains(choice)) {
      screenClear();
      std::cout << userInput << " isn't an option." << std::endl;
      screenSleep();
      continue;
    }
    value = options[choice];
    color = Chip::getColorFromValue(value);
    int amount = 1;
    bettingChip_ = Chip(value, color);

    std::transform(color.begin(), color.end(), color.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    if (!pocket.hasEnoughChips(bettingChip_, amount)) {
      screenClear();
      std::cout << "I don't have enough " << color << " chips." << std::endl;
      screenSleep();
      continue;
    }
    screenClear();
    std::cout << "Betting " << color << " chip." << std::endl;
    screenSleep();
    return;
  }
}

void Blackjack::initialDeal() {
  deck_.pullCard(playerHand_, 2);
  deck_.pullCard(houseHand_, 2);

  screenClear();
  std::cout << "You drew: | " << (playerHand_[0].second) << " of "
            << playerHand_[0].first << " |\n";
  screenSleep();
  std::cout << "House drew: | ################|\n";
  screenSleep();
  std::cout << "You drew: | " << playerHand_[1].second << " of "
            << playerHand_[1].first << " |\n";
  screenSleep();
  std::cout << "House drew: | " << houseHand_[1].second << " of "
            << houseHand_[1].first << " |\n";
  screenSleep();

  int playerScore = checkHandValue(playerHand_);

  if (playerScore == 21) {
    playerWin_ = true;
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
      deck_.pullCard(playerHand_);
      playerScore = checkHandValue(playerHand_);

      if (playerScore == 21) {
        playerWin_ = true;
        return;
      } else if (playerScore > 21) {
        playerBust_ = true;
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

    houseScore = checkHandValue(houseHand_);

    if (houseScore > 21) {
      houseBust_ = true;
      return;
    } else if (houseScore < 17) {
      deck_.pullCard(houseHand_);
    } else {
      return;
    }
  }
}

void Blackjack::displayHands(bool hide) const {
  screenClear();
  std::cout << "House hand: | ";
  for (const auto &card : houseHand_) {
    if (hide) {
      std::cout << "################ | ";
      hide = false;
    } else {
      std::cout << card.second << " of " << card.first << " | ";
    }
  }
  std::cout << "\n";

  std::cout << "Your hand: | ";
  for (const auto &card : playerHand_) {
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

void Blackjack::checkWin(Pocket &pocket, bool end) {
  const int WIN_AMOUNT = 1;
  const int LOSE_AMOUNT = 1;
  int value = bettingChip_.getValue();
  std::string color = "";

  screenClear();
  if (!end) {
    displayHands();
  } else {
    displayHands(false);
  }

  if (playerWin_) {
    pocket.addChips(bettingChip_, WIN_AMOUNT);

    std::cout << "Blackjack! You won: $" << value << "\n";
    screenSleep();

    return;
  } else if (playerBust_) {
    std::string color = Chip::getColorFromValue(value);
    Chip chip(value, color);
    pocket.removeChips(chip, LOSE_AMOUNT);

    std::cout << "Bust!\n";
    screenSleep();

    return;
  }

  if (houseBust_) {
    pocket.addChips(bettingChip_, WIN_AMOUNT);

    std::cout << "House bust! You won: $" << value << "\n";
    screenSleep();

    return;
  }

  if (end) {
    int playerScore = checkHandValue(playerHand_);
    int houseScore = checkHandValue(houseHand_);

    if (playerScore >= houseScore) {
      pocket.addChips(bettingChip_, WIN_AMOUNT);

      std::cout << "You won: $" << value << "\n";
      screenSleep();

      return;
    } else {
      std::string color = Chip::getColorFromValue(value);
      Chip chip(value, color);
      pocket.removeChips(chip, LOSE_AMOUNT);

      std::cout << "You lost\n";
      screenSleep();

      return;
    }
  }
}
