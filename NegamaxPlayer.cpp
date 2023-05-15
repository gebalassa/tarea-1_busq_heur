#ifndef MINMAXPLAYER
#define MINMAXPLAYER
#include <bitset>
#include <string>
#include <vector>
#include <utility>
#include <stdexcept>
#include <time.h>  
#include "Player.h"  
#include "Statistics.h"  
#include "Bitboard.cpp"

using namespace std;
using namespace AllQueensChess;

namespace AllQueensChess {
	class NegamaxPlayer : public Player {
	public:
		const int DEFAULT_HEIGHT = 0;
		pair<bitset<25>, bitset<25>> move(bitset<25>& board, bitset<25>& team, int height) {
			clean();
			generate(board, team);

			// Se aplica negamax sobre cada hijo inicial
			int score = INT_MIN + 100;
			auto curr_move_pair = children[0];
			bitset<25> initial_board = board;
			bitset<25> initial_team = team;
			for (int i = 0; i < children.size(); i++) {
				// Variables
				NegamaxPlayer p = NegamaxPlayer(); // Player auxiliar
				Bitboard b = Bitboard(); // Bitboard auxiliar (solo necesito funciones)
				board = initial_board; // Reinicia variable
				team = initial_team; // Reinicia variable
				// Movimiento
				b.move_piece(children[i].first, children[i].second, board, team); // Se modifica "board" y "team"
				int result = p.negamax_score(board, team, height);
				if (result > score) { score = result; curr_move_pair = children[i]; }
			}
			return curr_move_pair;
		}
		pair<bitset<25>, bitset<25>> move(bitset<25>& board, bitset<25>& team) {
			return move(board, team, DEFAULT_HEIGHT);
		}

		// Limpia listas
		void clean() {
			children.clear();
			pieces.clear();
		}

		// Puntuación de un estado del tablero según algoritmo Negamax
		int negamax_score(bitset<25> board, bitset<25> team, int height) {
			// ESTADÍSTICAS
			Statistics::instance->negamax_visited_nodes++;
			// Si soy nodo victoria, retorno puntuación más alta (-100 para evitar desb)
			Bitboard b = Bitboard(); // Bitboard auxiliar (solo necesito funciones)
			if (b.is_victory(team)) { return INT_MAX - 100; }
			// Si la altura llegó a 0, me evalúo y retorno
			if (height == 0) { return next_move_victory_heuristic(board, team); }
			// Puntuación inicial negativa muy baja (+100 para evitar desbordamientos)
			int score = INT_MIN + 100;
			// Genero hijos de este nodo
			generate(board, team);
			// Por cada hijo aplico func. recursiva para obtener la mejor puntuación.
			bitset<25> initial_board = board;
			bitset<25> initial_team = team;
			for (int i = 0; i < children.size(); i++) {
				// Reinicio variables
				board = initial_board;
				team = initial_team;
				// Hago movimiento con Bitboard auxiliar
				b.move_piece(children[i].first, children[i].second, board, team);
				// Entrego el OTRO equipo
				bitset<25> other_team = board & ~team;
				// Hago recursión con NegamaxPlayer auxiliar
				NegamaxPlayer p = NegamaxPlayer();
				int result = -1 * p.negamax_score(board, other_team, height-1);
				if (result > score) { score = result; }
			}
			// Retorno mayor puntuación
			return score;
		}

		// Si puedo ganar en un solo movimiento, elijo ese movimiento,
		// sino, elijo al azar.
		int next_move_victory_heuristic(bitset<25>& board, bitset<25>& team) {
			//TERMINARRRRR
			return 10; // BORRAR
		}
	};
}




#endif MINMAXPLAYER