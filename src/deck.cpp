#include "Deck.h"
#include "pch.h"

Deck::Deck() { initialize(); }

void Deck::pullCard(std::vector<std::pair<std::string, std::string>> &hand,
                    int count) {
  for (int i = 0; i < count; ++i) {
    hand.push_back(m_Deck.back());
    m_Deck.pop_back();
  }
}

void Deck::shuffle() {
  std::shuffle(m_Deck.begin(), m_Deck.end(), m_RandomGenerator);
}

void Deck::reset() {
  m_Deck.clear();
  initialize();
}

void Deck::initialize() {
  m_Deck.reserve(52);

  for (auto &suit : m_Suits) {
    for (auto &rank : m_Ranks) {
      m_Deck.push_back(std::make_pair(suit, rank));
    }
  }

  m_RandomGenerator.seed(std::random_device{}());
}

Deck::~Deck() {}