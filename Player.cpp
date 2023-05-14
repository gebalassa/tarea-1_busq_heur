#include "Player.h"

// Genero piezas en "pieces" e hijos en "children"
void AllQueensChess::Player::generate(bitset<25> board, bitset<25> team) {
	// Genero piezas en "pieces"
	separate_piece_boards(team);

	// Genero movimientos y agrego a "children"
	bitset<25> curr_piece = 0b0;
	Bitboard b = Bitboard();
	for (int i = 0; i < pieces.size(); i++) {
		curr_piece = pieces[i];
		bitset<25> valid_moves = b.valid_moves(board, curr_piece);
		// Agrega a "children"
		separate_valid_move_boards(pieces[i], valid_moves);
	}
}

// Separa tablero de equipo en varios tableros de una pieza
// y agrega a "pieces"
void AllQueensChess::Player::separate_piece_boards(bitset<25>& team) {
	for (int i = 0; i < 25; i++) {
		if (team[i] == 1) {
			bitset<25> new_piece = 0b0;
			new_piece[i] = 1;
			pieces.push_back(new_piece);
		}
	}
	if (pieces.size() > 6) {
		throw invalid_argument("Hay más de 6 piezas!!!");
	}
}

// Separa tablero de movimientos validos en varios tableros
// de un solo movimiento válido,  y agrega a "children"
// un "pair" <pieza, pos_objetivo>,
// antes comprobando que no esté repetido.
void AllQueensChess::Player::separate_valid_move_boards(bitset<25>& piece, bitset<25>& valid_moves) {
	for (int i = 0; i < 25; i++) {
		if (valid_moves[i] == 1) {
			// Armo posible pieza
			bitset<25> possible_new_move = 0b0;
			possible_new_move[i] = 1;
			// Chequea repetición
			bool isRepeated = false;
			pair<bitset<25>, bitset<25>> possible_pair =
			{ piece, possible_new_move };
			if (children.size() == 0) { children.push_back(possible_pair); }
			for (int j = 0; j < children.size(); j++) {
				possible_pair = { piece, possible_new_move };
				if (possible_pair == children[j]) {
					isRepeated = true; break;
				}
			}
			if (!isRepeated) { children.push_back(possible_pair); }
		}
	}
}


