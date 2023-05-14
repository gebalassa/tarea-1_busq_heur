#ifndef MINMAXPLAYER
#define MINMAXPLAYER
#include <bitset>
#include <string>
#include <vector>
#include <utility>
#include <stdexcept>
#include <time.h>  
#include "Player.h"  
#include "Bitboard.cpp"

using namespace std;
using namespace AllQueensChess;

namespace AllQueensChess {
	class NegamaxPlayer : public Player {
	public:
		pair<bitset<25>, bitset<25>> move(bitset<25>& board, bitset<25>& team) {
			clean();
			generate(board, team);

			// TERMINARRRR ALGORITMOO NEGAMAX
		}

		// Limpia listas
		void clean() {
			children.clear();
			pieces.clear();
		}

		// Puntuación de un estado del tablero según algoritmo Negamax
		int negamax_score(bitset<25> initial_board, bitset<25> team, int max_depth) {
			// Si la altura máxima fue alcanzada, me evalúo y retorno
			// 
			// Genero hijos de este nodo inicial
			generate(initial_board, team);
			// Por cada hijo creo un NegamaxPlayer y aplico func. recursiva
			// para obtener mejor puntuación.
			for (int i = 0; i < children.size(); i++) {

			}
		}


	private:
		int _negamax_score(bitset<25> board, bitset<25> team, int depth) {

		}
	};
}




#endif MINMAXPLAYER