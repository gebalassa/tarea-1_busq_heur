#ifndef ALLQUEENSCHESSGAME
#define ALLQUEENSCHESSGAME
#include <iostream>
#include <map>
#include <time.h>
#include "Bitboard.cpp"

using namespace std;
using namespace AllQueensChess;

namespace AllQueensChess {
	class AllQueensChessGame {
		// IMPRIME TABLERO + TURNO ACTUAL
		// SOLICITA PIEZA A MOVER
		// VERIFICA VALIDEZ (Posicion valida (en rango, sintaxis), posicion no-vacia, pieza del jugador del turno)
		// // SI NO, CONSULTA POS INICIAL DE NUEVO^ 
		// SOLICITA POSICION A MOVER
		// VERIFICA VALIDEZ DE POS NUEVA (Posicion válida, posicion aceptable con valid_moves())
		// SI NO, CONSULTA POS FINAL DE NUEVO ^
		// CHEQUEO DE VICTORIA (TODO: FUNCION DE CHEQUEO DE VICTORIA!!!!! 4 EN LINEA!!!)
		// -- NO?
		// CAMBIA TURNO, VUELVE AL PRINCIPIO
		// -- SI?
		// -- IMPRIMIR ESTADO FINAL DEL TABLERO, GANADOR, NUM. DE TURNOS
	public:
		map<int, string> number_to_team = { {0,"RED"}, {1, "BLACK"} };
		map<string, int> team_to_number = { {"RED", 0}, {"BLACK", 1}};
		int turn = 0;
		Bitboard board = Bitboard();
		bool victory = false;
		bool exit = false;
		
		void initialize() {
			// GAME LOOP
			srand((unsigned int) time(NULL));
			while (!victory && !exit) {
				// INTRO
				cout << "Bienvenido a AllQueensChess" << "\n\n";
				board.print_board(board.board);

				int initial_turn = (int) rand() % 2; //0 o 1
				turn = initial_turn;
				cout << "Turno inicial: " << number_to_team[turn] << "\n";

				// Input movimiento




				exit = true;
			}
		}

		void input_move(){
			
			bool valid_piece = false;
			bool valid_move = false;
			while (!valid_move && !exit){
				// Elección de pieza
				while (!valid_piece && !exit){
					char raw[4] = "EEE";
					cout << "Ingrese pieza (fil-col): ";
					// Parsing
					cin >> raw;
					cout << raw;
					exit = true;
				}
			}
		}
	};
}









#endif