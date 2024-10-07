#include <string>
#include <utility>
#include <vector>

class Roulette {
public:
  Roulette();
  void play(unsigned &balance, unsigned &bet);
  ~Roulette();

private:
  int m_SymbolCount = 36;
  std::vector<int> m_tableSymbols;

  void getSymbolBets();
  void initialize();
};