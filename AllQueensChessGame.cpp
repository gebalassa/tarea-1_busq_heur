#ifndef ALLQUEENSCHESSGAME
#define ALLQUEENSCHESSGAME
#include <iostream>
#include <map>
#include <bitset>
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
			// INTRO
			cout << "Bienvenido a AllQueensChess" << "\n\n";
			board.print_board();
			int initial_turn = (int) rand() % 2; //0 o 1
			turn = initial_turn;
			cout << "Turno inicial: " << number_to_team[turn] << "\n";

			while (!victory && !exit) {

				// Input movimiento
				input_move();

				// Imprimir nuevo tablero
				board.print_board();
			}
		}

		// Realizar ciclo de un input de movimiento
		void input_move(){
			
			bool parsed_piece = false;
			bool parsed_move = false;
			bool valid_move = false;
			int piece_fil;
			int piece_col;
			int obj_fil;
			int obj_col;
			while (!valid_move && !exit) {
				while (!parsed_move && !exit) {
					// I) Parseo de input de pieza
					while (!parsed_piece && !exit) {
						char raw[4] = "EEE";
						int parsed = -1;
						piece_fil = -1;
						piece_col = -1;
						obj_fil = -1;
						obj_col = -1;
						// Instrucción
						cout << "Ingrese pieza (fil-col): ";

						// PARSING
						// **POR TEMAS DE TIEMPO SUPONDREMOS ALGUN GRADO DE RESTRICCION DEL USUARIO Y SUS INPUTS**
						// Limita input a 3 chars+terminador. Ignora el resto hasta newline.
						cin >> std::setw(4) >> raw; cin.ignore(numeric_limits<streamsize>::max(), '\n');
						// DEBUG: Imprime esto si falla en parsear a chars
						if (cin.fail()){
							cout << "FAILED in PIECE" << endl;
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
						parsed_piece = true;
					}

					// II) Parseo de input de posición objetivo (SIMILAR al de pieza!)
					char raw[4] = "EEE";
					int parsed = -1;
					obj_fil = -1;
					obj_col = -1;
					// Instrucción
					cout << "Ingrese posicion objetivo (fil-col): ";
					// PARSING (similar al de pieza, arriba)
					cin >> std::setw(4) >> raw; cin.ignore(numeric_limits<streamsize>::max(), '\n');
					if (cin.fail()){
						cout << "FAILED in OBJECTIVE" <<endl;
					}
					// Chequeo símbolos correctos
					// Chequeo salida
					if (raw[0] == 'q'){ exit = true; break; }
					// Chequeo caracter fila
					parsed = raw[0] - '0';
					switch(parsed){
						case 0:
							obj_fil = 0; break;
						case 1:
							obj_fil = 1; break;
						case 2:
							obj_fil = 2; break;
						case 3:
							obj_fil = 3; break;
						case 4:
							obj_fil = 4; break;
						default:
							cout << "Fila invalida" << endl; break;
					}
					if (obj_fil == -1) { continue; }
					// Chequeo caracter guión central "-"
					if (raw[1] != '-') { cout << "Separador fil-col invalido." << endl; continue; }					
					// Chequeo caracter columna
					parsed = raw[2] - '0'; // Char numérico->Valor int real
					switch(parsed){
						case 0:
							obj_col = 0; break;
						case 1:
							obj_col = 1; break;
						case 2:
							obj_col = 2; break;
						case 3:
							obj_col = 3; break;
						case 4:
							obj_col = 4; break;
						default:
							cout << "Columna invalida" << endl; break;
					}
					if (obj_col == -1) { continue; }

					parsed_move = true;
				}

				// Realización efectiva del movimiento con tableros y chequeos de validez
				bitset<25> piece_board = board.bitset_from_index(board.getIndex(piece_fil * 5 + piece_col));
				bitset<25> new_pos_board = board.bitset_from_index(board.getIndex(obj_fil * 5 + obj_col));
				bitset<25> team_board = (turn == team_to_number["RED"]) ? board.red_board : board.black_board;
				// Resultado. Si es inválido, se repite ciclo de función.
				bool result = board.move_piece(piece_board, new_pos_board, board.board, team_board);
				if (result == false ) { continue; }
				// Cambio de turno
				if (turn == team_to_number["RED"]) { turn = team_to_number["BLACK"]; }
				else {turn = team_to_number["RED"];}
				// Confirmación de movimiento hecho
				valid_move = true;
			}
		}		
	};
}
#endif