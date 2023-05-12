#ifndef RANDOMPLAYER
#define RANDOMPLAYER
#include <bitset>

using namespace std;
using namespace AllQueensChess;

namespace AllQueensChess {
	class RandomPlayer {
	public:
		static void move(bitset<25> board, bitset<25> team) {

		}

		static void generate(bitset<25> board, bitset<25> team) {
			//  - Bitboard.valid_moves() obtiene todos los movimientos
			// de una pieza determinada. Cada uno de esos movimientos
			// debe anexarse por separado a una lista generada: Para
			// Separar los movimientos se necesita una función que itere
			// y separe cada movimiento legal para agregarlo.
			// - El mismo proceso se debe aplicar a cada pieza de mi equipo.
			// - El resultado será una lista con todas las movidas posibles
			// desde un estado dado y siendo el turno de mi equipo.
			//
			// - Luego, en el caso del algoritmo RANDOM, se escoge uno de estos
			// objetos al azar.
			// DIFICULTADES:
			// 1. Funcion que separe el tablero de movidas legales en
			// multiples tableros de una pieza.
			//
			//
		}
	};
}






#endif RANDOMPLAYER