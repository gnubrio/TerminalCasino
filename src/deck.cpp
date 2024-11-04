#include "Deck.hpp"
#include <algorithm>
#include <random>
#include <string>
#include <utility>
#include <vector>

Deck::Deck() { initialize(); }

Deck::~Deck() {}

void Deck::pullCard(std::vector<std::pair<std::string, std::string>> &hand,
                    int count) {
  for (int i = 0; i < count; ++i) {
    hand.push_back(deck_.back());
    deck_.pop_back();
  }
}

void Deck::shuffle() {
  std::shuffle(deck_.begin(), deck_.end(), randomGenerator_);
}

void Deck::reset() {
  deck_.clear();
  initialize();
}

void Deck::initialize() {
  deck_.reserve(52);

  for (auto &suit : suits_) {
    for (auto &rank : ranks_) {
      deck_.push_back(std::make_pair(suit, rank));
    }
  }

  randomGenerator_.seed(std::random_device{}());
}
