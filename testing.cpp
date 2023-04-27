#ifndef TESTING
#define TESTING
#include <iostream>
#include <bitset>
#include "Bitboard.cpp"
#include "Mask.cpp"
#include "AllQueensChessGame.cpp"

using namespace AllQueensChess;

int main() {
	Bitboard b = Bitboard();

	//int a = 10;
	//a = a << 1;
	//cout << a;
	//a = a >> 1;
	//cout << a;

	//bitset<16> a = 10;
	//cout << a;

	//bitset<25> board = 10;
	//cout<<board<<"\n";
	//cout << board.size()<<"\n";
	//b.print_board(board);
	//b.print_board();

	//b.print_board(initial_board);
	//bitset<25> test_board = 0b1010100000110110010010001;
	//bitset<25> AND = initial_board & test_board;
	//bitset<25> OR = initial_board | test_board;
	//bitset<25> NOT = ~initial_board;
	//bitset<25> XOR = initial_board ^ test_board;
	//bitset<25> shiftl = initial_board << 1;
	//bitset<25> shiftr = initial_board >> 1;
	//cout << AND << "\n";
	//cout << OR << "\n";
	//cout << NOT << "\n";
	//cout << XOR << "\n";
	//cout << shiftl << "\n";
	//cout << shiftr << "\n";
	//b.print_board(initial_board.flip()); //flip() == NOT(~)

	//// ****Las multiplicaciones/sumas/substracciones deben definirse aparte de clase bitset!!!****
	//bitset<25> initial_board = 0b11111;
	//bitset<25> test_board = 0b10;

	// Test suma/substraccion/multiplicacion/reversa
	//bitset<25> two = 0b10; //cout << two.to_ulong();
	//bitset<25> five = 0b101; //cout << five.to_ulong();
	//bitset<25> sub1 = b.bitsetSubtract(five, two); cout << sub1;
	//bitset<25> sub2 = b.bitsetSubtract(two, five); cout << (int16_t)sub2.to_ulong();
	//bitset<25> add = b.bitsetAdd(two, five); cout << sub3;
	//bitset<25> mult = b.bitsetMultiply(two, five); cout << mult;
	//bitset<25> mult2 = b.bitsetMultiply(five, two); cout << mult2;
	//bitset<25> revtwo = b.reverse(two); cout << revtwo;
	//bitset<25> revfive = b.reverse(five); cout << revfive;

	// 2da Prueba Mov Posibles
	//bitset<25> two = 0b10; //cout << two.to_ulong();
	bitset<25> fake_init_board = 0b0011101000111000011100111;
	bitset<25> piece_board =     0b0000100000000000000000000;
	bitset<25> hline_mask =      0b0000000000000001111100000;
	bitset<25> vline_mask =      0b0100001000010000100001000;
	bitset<25> dline_mask =      0b0000100010001000100010000;
	bitset<25> antidline_mask = 0b1000001000001000001000001;
	// Abreviaciones
	//bitset<25> om = fake_init_board & hline_mask;
	//bitset<25> s = piece_board;
	////---
	//bitset<25> revs = b.reverse(s);
	//bitset<25> left = om ^ b.bitsetSubtract(om, b.bitsetMultiply(two, s));
	//bitset<25> right = om ^ b.reverse(b.bitsetSubtract(b.reverse(om), b.bitsetMultiply(two, revs)));
	//bitset<25> line_attacks_no_final_mask = left ^ right;
	//bitset<25> line_attacks = line_attacks_no_final_mask & hline_mask;
	// Prints
	//b.print_board(fake_init_board); cout << "\n";
	//b.print_board(om); cout << "\n";
	//b.print_board(piece_board); cout << "\n";
	//b.print_board(antidline_mask); cout << "\n";
	//b.print_board(left); cout << "\n";
	//b.print_board(right); cout << "\n";
	//b.print_board(line_attacks_no_final_mask); cout << "\n";
	//b.print_board(line_attacks);
	//b.print_board(b.line_moves(fake_init_board,piece_board,hline_mask)); cout << "\n";
	//b.print_board(b.line_moves(fake_init_board,piece_board,vline_mask)); cout << "\n";
	//b.print_board(b.line_moves(fake_init_board,piece_board,dline_mask)); cout << "\n";

	// Masks
	//Mask m = Mask();
	//m.debug_print_masks(m.vmasks);
	//m.debug_print_masks(m.dmasks);

	// Testeo de mov válidos (en todas direcciones)
	//bitset<25> moves = b.valid_moves(fake_init_board, piece_board);
	//b.print_board(moves);

	// Chequeo a través de AllQueensChessGame de Bitboard
	AllQueensChessGame game = AllQueensChessGame();
	//game.board.print_board();
	//game.board.print_board(game.board.red_board); cout "\n";
	//game.board.print_board(game.board.black_board); cout "\n";
	//game.board.print_board(game.board.bitset_from_index(5));
	//cout << game.board.index_from_bitset(piece_board) << "\n";
	//cout << game.board.index_from_bitset(game.board.bitset_from_index(5)) << "\n";
	//bitset<25> bfi10 = game.board.bitset_from_index(10);
	//cout << game.board.is_piece_valid(bfi10) << "\n";
	//cout << game.board.is_piece_valid(piece_board) << "\n";
	//bitset<25> ipe9 = game.board.bitset_from_index(9);
	//cout << game.board.is_position_empty(ipe9) << "\n";
	//cout << game.board.is_position_empty(piece_board) << "\n";
	
	// Test de dilatación
	//bitset<25> empty = 0b0;
	//empty[11] = 1;
	//empty[13] = 1;
	//b.print_board(empty); cout << "\n";
	//b.print_board(b.dilate(empty, 1)); cout << "\n";
	//b.print_board(b.dilate(empty, 2)); cout << "\n";
	//b.print_board(b.dilate(empty, 3)); cout << "\n";
	//b.print_board(b.dilate(empty, 4)); cout << "\n";

	// Test de erosión
	bitset<25> full = 0b0; full.flip();
	full[11] = 0;
	full[13] = 0;
	//b.print_board(full); cout << "\n";
	//b.print_board(b.erode(full, 2)); cout << "\n";
	//b.print_board(b.erode(full, 3)); cout << "\n";
	//b.print_board(b.erode(full, 4)); cout << "\n";
	//b.print_board(full >> 1); cout << "\n";
	//b.print_board(b.erode(full, 1, "down")); cout << "\n";
	//b.print_board(fake_init_board); cout << "\n";
	//b.print_board(b.erode(fake_init_board, 1, "right")); cout << "\n";
	//b.print_board(b.erode(fake_init_board, 1, "down")); cout << "\n";
	//b.print_board(b.erode(fake_init_board, 1, "upper_right_corner")); cout << "\n";
	//b.print_board(b.erode(fake_init_board, 1, "lower_right_corner")); cout << "\n";

	// Test de función inversa erosion-dilatación
	//bitset<25> inv_t = 0b0; inv_t[11] = 1; inv_t[13] = 1;
	//bitset<25> aux = b.dilate(inv_t, 1);
	//b.print_board(inv_t); cout << "\n";
	//b.print_board(aux); cout << "\n";
	//b.print_board(b.erode(aux,1)); cout << "\n";
	
	// Test de detección de 4-en-linea (VICTORIA)
	//bitset<25> fake_team_board = 0b0000001111000000000000000;
	//bitset<25> fake_team_board = 0b0100001000010000100000000;
	//bitset<25> fake_team_board = 0b0001000100010001000000000;	
	// ANTIDIAGONALES
	//bitset<25> fake_team_board = 0b0100000100000100000100000;
	//bitset<25> fake_team_board = 0b1000001000001000001000001;
	//bitset<25> fake_team_board = 0b0100000100000100000100000;	

	// VICTORY TEST
	//bitset<25> fake_team_board = 0b1010100010110101110000100;
	//b.print_board(fake_team_board); cout << "\n";
	////b.print_board(b.erode(fake_team_board, 1, "lower_right_corner"));
	//cout << b.is_victory(fake_team_board) << "\n";

	// INITIALIZE
	game.initialize();



	return 1;
}
#endif