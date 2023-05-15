#ifndef RANDOMPLAYER
#define RANDOMPLAYER
#include <bitset>
#include <vector>
#include <utility>
#include <stdexcept>
#include <time.h>  
#include "Player.h"  
#include "Bitboard.cpp"

using namespace std;
using namespace AllQueensChess;

namespace AllQueensChess {
	class RandomPlayer : public Player {
	public:
		pair<bitset<25>, bitset<25>> move(bitset<25>& board, bitset<25>& team, int height = 0) {
			clean();
			generate(board, team);

			// Regresa movimiento random (<pieza>-<pos.objetivo>)
			int rindex = rand() % children.size();
			pair<bitset<25>, bitset<25>> selected_pair = children[rindex];
			
			return selected_pair;
		}

		// Limpia listas
		void clean(){
			children.clear();
			pieces.clear();
		}
	};
}






#endif RANDOMPLAYER