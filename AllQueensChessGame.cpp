#ifndef ALLQUEENSCHESSGAME
#define ALLQUEENSCHESSGAME
#include <iostream>
#include <map>
#include <time.h>
#include <iomanip>
#include <limits>
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
				input_move();


				exit = true;
			}
		}

		// Realizar ciclo de un input de movimiento
		void input_move(){
			
			bool valid_piece = false;
			bool valid_move = false;
			int piece_fil;
			int piece_col;
			while (!valid_move && !exit){
				// Elección de pieza
				while (!valid_piece && !exit){
					char raw[4] = "EEE";
					piece_fil = -1;
					piece_col = -1;
					int parsed = -1;
					// Instrucción
					cout << "Ingrese pieza (fil-col): ";

					// PARSING
					// **POR TEMAS DE TIEMPO SUPONDREMOS ALGUN GRADO DE RESTRICCION DEL USUARIO Y SUS INPUTS**
					// Limita input a 3 chars+terminador. Ignora el resto hasta newline.
					cin >> std::setw(4) >> raw; cin.ignore(numeric_limits<streamsize>::max(), '\n');
					// DEBUG: Imprime esto si falla en parsear a chars
					if (cin.fail()){
						cout << "FAILED" <<endl;
					}
					// Chequeo símbolos correctos
					// Chequeo salida
					if (raw[0] == 'q'){ exit = true; break; }
					// Chequeo caracter fila
					parsed = raw[0] - '0'; // Char numérico->Valor int real
					switch(parsed){
						case 0:
							piece_fil = 0; break;
						case 1:
							piece_fil = 1; break;
						case 2:
							piece_fil = 2; break;
						case 3:
							piece_fil = 3; break;
						case 4:
							piece_fil = 4; break;
						default:
							cout << "Fila invalida" << endl; break;
					}
					if (piece_fil == -1) { continue; }
					
					// Chequeo caracter guión central "-"
					if (raw[1] != '-') { cout << "Separador fil-col invalido." << endl; continue; }
					
					// Chequeo caracter columna
					parsed = raw[2] - '0'; // Char numérico->Valor int real
					switch(parsed){
						case 0:
							piece_col = 0; break;
						case 1:
							piece_col = 1; break;
						case 2:
							piece_col = 2; break;
						case 3:
							piece_col = 3; break;
						case 4:
							piece_col = 4; break;
						default:
							cout << "Columna invalida" << endl; break;
					}
					if (piece_col == -1) { continue; }
					
					//----DEBUG-------
					// cout << "Fila: " << piece_fil << " Columna: "<< piece_col << endl;
					// cin.get();
					//----------------
					
					
					//exit = true;
				}
			}
		}
	};
}









#endif