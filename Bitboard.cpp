#ifndef BITBOARD
#define BITBOARD
#include "Mask.cpp"
#include <iostream>
#include <bitset>
#include <intrin.h>
#include <stdexcept>
#include <string>

using namespace std;

namespace AllQueensChess {
	class Bitboard {
	public:
		const bitset<25> initial_board = 0b1111100000100010000011111; // Tablero base
		const bitset<25>  red_board = 0b1010100000000010000001010; // Tablero rojo
		const bitset<25>  black_board = 0b0101000000100000000010101; // Tablero negro
		bitset<25> board = initial_board;
		Mask mask = Mask();

		// Movimientos posibles totales
		bitset<25> valid_moves(bitset<25>& board, bitset<25>& piece) {
			// Índice jugador
			int index = index_from_bitset(piece);
			//cout << "Index: " << index << "\n";
			// Máscaras
			bitset<25> hmask = mask.hmasks[index / 5];
			//print_board(hmask); cout << "\n";
			bitset<25> vmask = mask.vmasks[index % 5];
			//print_board(vmask); cout << "\n";
			bitset<25> dmask = mask.dmasks[index];
			//print_board(dmask); cout << "\n";
			bitset<25> antidmask = mask.antidmasks[index];
			//print_board(antidmask); cout << "\n";
			// Movimientos Válidos
			bitset<25> hmoves = line_moves(board, piece, hmask);
			bitset<25> vmoves = line_moves(board, piece, vmask);
			bitset<25> dmoves = line_moves(board, piece, dmask);
			bitset<25> antidmoves = line_moves(board, piece, antidmask);
			bitset<25> moves = hmoves | vmoves | dmoves | antidmoves;
			return moves;
		}

		// Movimientos posibles mediante una máscara lineal (Ej.:hor, ver, diag, antidiag)
		bitset<25> line_moves(bitset<25>& board, bitset<25>& piece, bitset<25>& mask) {
			// Abreviaciones
			bitset<25> om = board & mask;
			//print_board(om); cout << "\n";
			// Calculos
			bitset<25> rpiece = reverse(piece);
			//print_board(rpiece); cout << "\n";
			bitset<25> left = om ^ bitsetSubtract(om, piece << 1);
			//print_board(left); cout << "\n";
			bitset<25> right = om ^ reverse(bitsetSubtract(reverse(om), rpiece << 1));
			//print_board(right); cout << "\n";
			bitset<25> line_moves_and_attacks = (left ^ right) & mask;
			//print_board(line_moves_and_attacks); cout << "\n";
			// No se puede atacar en AllQueensChess, por lo que se eliminan piezas enemigas
			bitset<25> line_moves = line_moves_and_attacks & ~board;
			return line_moves;
		}

		// Mover pieza
		bool move_piece(bitset<25>& piece, bitset<25>& new_pos, bitset<25>& board, bitset<25>& team_board) {
			//Chequeos
			// 1) Validez de pieza
			if (!is_piece_valid(piece, team_board)) { cout << "ERROR: Pieza inválida\n";  return false; }
			else if (!is_position_empty(new_pos)) { cout << "ERROR: Casilla ya está ocupada\n"; return false; }

			// 2) Mover pieza
			board = board & ~piece;
			board = board | new_pos;
		}

		// Detección de victoria (4 en línea). Recibe tabla de un equipo
		bool is_victory(bitset<25>& team_board) {
			int counter = 0;
			bitset<25> empty = 0b0;
			bitset<25> initial_state = team_board;
			bitset<25> current_state = initial_state;

			// Caso Horizontal
			while (current_state != empty) {
				current_state = erode(current_state, 1, "right");
				counter++;
			}
			if (counter >= 4) { return true; }
			else { counter = 0; current_state = initial_state; }
			// Caso Vertical
			while (current_state != empty) {
				current_state = erode(current_state, 1, "up");
				counter++;
			}
			if (counter >= 4) { return true; }
			else { counter = 0; current_state = initial_state; }
			// Caso diagonal
			while (current_state != empty) {
				current_state =
					erode(current_state, 1, "upper_right_corner");
				counter++;
			}
			if (counter >= 4) { return true; }
			else { counter = 0; current_state = initial_state; }
			// Caso Antidiagonal
			while (current_state != empty) {
				current_state =
					erode(current_state, 1, "lower_right_corner");
				counter++;
				print_board(current_state); cout << "\n";
			}
			if (counter >= 4) { return true; }
			else { counter = 0; current_state = initial_state; }

			return false;
		}

		// Índice REAL, desde esquina superior izq. a esq. inf. der.
		int getIndex(int raw_index) {
			return 24 - raw_index;
		}
		// Índice de pieza desde bitset
		bitset<25> bitset_from_index(int raw_index) {
			if (raw_index < 0 || raw_index > 24) {
				throw invalid_argument("Index between 0-24.");
			}
			int index = getIndex(raw_index);
			bitset<25> canvas = 0b0;
			canvas[index] = 1;
			return canvas;
		}

		// Bitset desde índice de pieza
		int index_from_bitset(bitset<25> piece) {
			unsigned long index;
			if (piece.none()) {
				throw invalid_argument("Empty bitset!");
			}
			else {
				_BitScanForward(&index, piece.to_ulong());
				index = getIndex(index);
			}
			return index;
		}

		// Chequear existencia y validez de pieza
		bool is_piece_valid(bitset<25>& piece, bitset<25>& team_board) {
			if ((piece & team_board).none()) { return false; }
			else return true;
		}

		// Chequear si posición objetivo está vacía
		bool is_position_empty(bitset<25>& position) {
			if ((position & board).any()) { return false; }
			else return true;
		}

		// Erosión
		// Genera erosión 'times' veces sobre la tabla. Retorna tabla erosionada.
		bitset<25> erode(bitset<25> b, int times, string direction = "all") {

			// Máscaras para traslape izquierda y derecha
			// (lados al revés pues origen es esq. sup. izq)
			bitset<25> left_mask = 0b1000010000100001000010000; left_mask.flip();
			bitset<25> right_mask = 0b0000100001000010000100001; right_mask.flip();
			// Máscaras diagonales ( al revés por origen esq sup izq)
			bitset<25> antidiag_mask = 0b0000100001000010000111111; antidiag_mask.flip();
			bitset<25> diag_mask = 0b1111100001000010000100001; diag_mask.flip();


			if (direction == "all") {
				for (int i = 0; i < times; i++) {
					bitset<25> up = b >> 5;
					bitset<25> down = b << 5;
					bitset<25> left = b >> 1 & left_mask;
					bitset<25> right = b << 1 & right_mask;
					b = b & down & up & left & right;
				}
				return b;
			}
			else if (direction == "left") {
				for (int i = 0; i < times; i++) {
					bitset<25> left = (b >> 1) & left_mask;
					b = b & left;
				}
				return b;
			}
			else if (direction == "right") {
				for (int i = 0; i < times; i++) {
					bitset<25> right = (b << 1) & right_mask;
					b = b & right;
				}
				return b;
			}
			else if (direction == "up") {
				for (int i = 0; i < times; i++) {
					bitset<25> up = (b >> 5);
					b = b & up;
				}
				return b;
			}
			else if (direction == "down") {
				for (int i = 0; i < times; i++) {
					bitset<25> down = (b << 5);
					b = b & down;
				}
				return b;
			}
			// Diagonal
			else if (direction == "upper_right_corner") {
				for (int i = 0; i < times; i++) {
					bitset<25> diag = (b >> 4) & diag_mask;
					b = b & diag;
				}
				return b;
			}
			// Anti-Diagonal
			else if (direction == "lower_right_corner") {
				for (int i = 0; i < times; i++) {
					bitset<25> antidiag = (b << 6) & antidiag_mask;
					b = b & antidiag;
				}
				return b;
			}
			else {
				throw invalid_argument("¡Dirección inválida!");
			}

		}

		// Dilatación
		// Genera dilatación 'times' veces sobre la tabla. Retorna tabla dilatada.
		bitset<25> dilate(bitset<25> b, int times) {
			// Máscaras para traslape izquierda y derecha
			// (lados al revés pues origen es esq. sup. izq)
			bitset<25> right_mask = 0b0000100001000010000100001; right_mask.flip();
			bitset<25> left_mask = 0b1000010000100001000010000; left_mask.flip();

			for (int i = 0; i < times; i++) {
				bitset<25> up = b >> 5;
				bitset<25> down = b << 5;
				bitset<25> left = b >> 1 & left_mask;
				bitset<25> right = b << 1 & right_mask;

				b = b | down | up | left | right;
				//print_board(down); cout << "\n";
			}
			return b;
		}


		// Diferencia entre bitsets (https://www.geeksforgeeks.org/arithmetic-operations-with-stdbitset-in-c/)
		bitset<25> bitsetSubtract(bitset<25> x, bitset<25> y) {
			bool borrow = false;
			// bitset to store the sum of the two bitsets
			bitset<25> ans;
			for (int i = 0; i < 25; i++) {
				ans[i] = fullSubtractor(x[i], y[i], borrow);
			}
			return ans;
		}

		// Suma de bitsets (https://www.geeksforgeeks.org/arithmetic-operations-with-stdbitset-in-c/)
		bitset<25> bitsetAdd(bitset<25>& x, bitset<25>& y) {
			bool carry = false;
			// bitset to store the sum of the two bitsets
			bitset<25> ans;
			for (int i = 0; i < 25; i++) {
				ans[i] = fullAdder(x[i], y[i], carry);
			}
			return ans;
		}

		// Multiplicación de bitsets (https://alikhuram.wordpress.com/2013/05/15/performing-arithmetic-on-bitsets-in-c/)
		// **Se prefiere usar "<< 1" para mult. por 2, por orden!!!**
		bitset<25> bitsetMultiply(bitset<25>& x, bitset<25>& y) {
			bitset<25> copyx = x; // Copia para evitar modificar el puntero dentro de la función
			bitset<25> tmp = copyx;
			bitset<25> ans = copyx;
			copyx.reset(); // Aquí se usa la copia evitando modif. el puntero

			// we want to minimize the number of times we shift and add
			if (tmp.count() < y.count()) {
				for (int i = 0; i < 25; i++) {
					if (tmp[i]) {
						bitset<25> shifted_y = y << i;
						ans = bitsetAdd(copyx, shifted_y);
					}
				}
			}
			else {
				for (int i = 0; i < 25; i++) {
					if (y[i]) {
						bitset<25> shifted_tmp = tmp << i;
						ans = bitsetAdd(copyx, shifted_tmp);
					}
				}
			}
			return ans;
		}

		// Inversión (https://stackoverflow.com/questions/48556547/how-to-reverse-bits-in-a-bitset)
		bitset<25> reverse(bitset<25> b) {
			for (std::size_t i = 0; i < 25 / 2; ++i) {
				bool t = b[i];
				b[i] = b[25 - i - 1];
				b[25 - i - 1] = t;
			}
			return b;
		}

		// Imprime tablero entregado
		void print_board(bitset<25> board) {
			cout << "+ 0 1 2 3 4" << "\n";
			cout << "0 ";
			for (int i = board.size() - 1; i >= 0; i--) {
				if (i % 5 == 0 && i != 0) {
					cout << board[i] << "\n" << (5 - i / 5) << " ";
				}
				else if (i == 0) { cout << board[i] << "\n"; }
				else { cout << board[i] << " "; }
			}
		}
		// Por defecto
		void print_board() { print_board(board); }

	private:
		// Suma entre booleanos. Usado en suma de bitsets. (https://www.geeksforgeeks.org/arithmetic-operations-with-stdbitset-in-c/)
		bool fullAdder(bool b1, bool b2, bool& carry) {
			bool sum = (b1 ^ b2) ^ carry;
			carry = (b1 && b2) || (b1 && carry) || (b2 && carry);
			return sum;
		}

		// Resta entre booleanos. Usado en resta de bitsets. (https://www.geeksforgeeks.org/arithmetic-operations-with-stdbitset-in-c/)
		bool fullSubtractor(bool b1, bool b2, bool& borrow) {
			bool diff;
			if (borrow) {
				diff = !(b1 ^ b2);
				borrow = !b1 || (b1 && b2);
			}
			else {
				diff = b1 ^ b2;
				borrow = !b1 && b2;
			}
			return diff;
		}
	};
}
#endif