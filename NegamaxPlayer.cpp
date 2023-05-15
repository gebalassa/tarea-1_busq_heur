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
		const int DEFAULT_HEIGHT = 1;
		pair<bitset<25>, bitset<25>> move(bitset<25>& board, bitset<25>& team, int height) {
			// ESTADÍSTICAS
			Statistics::instance->reset();
			Statistics::instance->negamax_visited_nodes++;
			//RELOJ
			auto start = chrono::high_resolution_clock::now();
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
				bitset<25> other_team = board & ~team;
				int result = -p.negamax_score(board, other_team, height-1);
				if (result > score) {
					score = result; curr_move_pair = children[i];
				}
			}
			// Reiniciar variables recibidas
			board = initial_board;
			team = initial_team;
			// FIN ESTADÍSTICAS
			// CIERRA RELOJ
			auto end = chrono::high_resolution_clock::now();
			Statistics::instance->move_time_micro = 
				chrono::duration_cast<chrono::microseconds>(end - start).count();
			// IMPRIMIR
			cout << "Nodos: " << Statistics::instance->negamax_visited_nodes << endl;
			cout << "Tiempo (us): " << Statistics::instance->move_time_micro << endl;
			// Retornar movimiento
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
			// Si soy nodo victoria, retorno puntuación más alta
			Bitboard b = Bitboard(); // Bitboard auxiliar (solo necesito funciones)
			if (b.is_victory(team)) {
				return 99999;
			}
			// Si la altura llegó a 0, me evalúo y retorno
			if (height == 0) { return queens_in_line_heuristic(board, team); }
			// Puntuación inicial negativa muy baja
			int score = -99999;
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
				int result = -p.negamax_score(board, other_team, height-1);
				if (result > score) { 
					score = result; 
				}
			}
			// Retorno mayor puntuación
			return score;
		}

		// Puntaje según número de reinas de mi equipo en línea
		int queens_in_line_heuristic(bitset<25>& board, bitset<25>& team) {
			Bitboard b = Bitboard();
			return b.longest_line(team);
		}
	};
}




#endif MINMAXPLAYER