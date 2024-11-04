#include "Utility.hpp"
#include <chrono>
#include <iostream>
#include <string>
#include <thread>

bool isStringValidInt(const std::string &str) {
  if (str.empty()) {
    return false;
  }

  std::string::const_iterator it = str.begin();

  while (it != str.end() && std::isdigit(*it)) {
    ++it;
  }

  return !str.empty() && it == str.end();
}

void screenClear() { std::cout << "\x1b[2J\x1b[H"; }

void screenSleep(int seconds) {
  std::this_thread::sleep_for(std::chrono::seconds(seconds));
}