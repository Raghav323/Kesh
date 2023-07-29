#pragma once 
#include "defs.hpp"
#include "Search.hpp"

void parseGo(const std::string& s, Search& chessSearch);
void parsePosition(string s);

void uci_loop();
