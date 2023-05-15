#ifndef ALLQUEENSCHESSGAME
#define ALLQUEENSCHESSGAME
#include <iostream>
#include <string>
#include <map>
#include <bitset>
#include <time.h>
#include <utility>
#include <iomanip>
#include <limits>
#include "Player.h"
#include "RandomPlayer.cpp"
#include "NegamaxPlayer.cpp"
#include "Bitboard.cpp"

using namespace std;
using namespace AllQueensChess;

namespace AllQueensChess {
	class AllQueensChessGame {
	public:
		map<int, string> number_to_team = { {0,"RED"}, {1, "BLACK"} };
		map<string, int> team_to_number = { {"RED", 0}, {"BLACK", 1} };
		int turn = 0;
		Bitboard board;
		bool victory = false;
		bool exit = false;

		AllQueensChessGame() {
			board = Bitboard();
		}

		// Juego entre dos IAs
		void play_ai_game(Player& red, Player& black, int length, int height = 0, bool isPrinted = false) {
			int counter = 0;

			cout << "TABLERO ACTUAL" << endl;
			board.print_board_teams(); cout << endl;
			while (!victory && !exit && counter < length) {
				// Info
				if (isPrinted) {
					cout << "Turno:" << number_to_team[turn] << endl;
					cout << "Jugada:" << counter + 1 << endl;
				}
				//Jugada
				if (number_to_team[turn] == "RED") {
					pair<bitset<25>, bitset<25>> move = red.move(board.board, board.red_board, height);
					board.move_piece(move.first, move.second, board.board,
						board.red_board);
				}
				else if (number_to_team[turn] == "BLACK") {
					pair<bitset<25>, bitset<25>> move = black.move(board.board, board.black_board, height);
					board.move_piece(move.first, move.second, board.board,
						board.black_board);
				}
				if (isPrinted) {
					board.print_board_teams(); cout << endl;
				}

				// Chequeo victoria
				if (board.is_victory((turn == team_to_number["RED"]) ? board.red_board : board.black_board)) {
					cout << "¡FIN! Ha ganado el equipo " << number_to_team[turn] << endl;
					cout << "Turno:" << number_to_team[turn] << endl;
					cout << "Jugada:" << counter + 1 << endl;
					board.print_board_teams(); cout << endl;
					cout << "Presione ENTER para cerrar" << endl;
					cin.get();
					victory = true;
					break;
				}
				// Aumenta contador
				counter++; if (counter >= length) { break; }
				// Cambio de turno
				if (turn == team_to_number["RED"]) { turn = team_to_number["BLACK"]; }
				else { turn = team_to_number["RED"]; }
			}
			// Acaban jugadas disponibles
			if (counter == length) {
				cout << "¡Se acabaron las jugadas!" << endl;
				cout << "Turno:" << number_to_team[turn] << endl;
				cout << "Jugada:" << counter << endl;
				board.print_board_teams(); cout << endl;
				cout << "Presione ENTER para continuar" << endl;
				cin.get();
			}
		}

		// Inicializar juego
		void play_game() {
			// GAME LOOP
			srand((unsigned int)time(NULL));
			restart();
			// INTRO
			cout << "                  --- Bienvenido a AllQueensChess ---" << "\n";
			cout << "         (por Gabriel Balassa, basado en juego del mismo nombre)" << "\n";
			cout << "   El objetivo es colocar 4 reinas de tu color (RED (R) o BLACK (N)) en línea." << "\n";
			cout << "Las reinas pueden bloquearse, pero no capturarse. Se mueven tal y como en el ajedrez." << "\n";
			cout << "       Los jugadores se turnan ingresando coordenadas <fila>-<columna>." << "\n";
			cout << "                           ¡Mucha suerte!" << "\n";
			cout << "            Ingrese \'q\' en cualquier momento para salir." << "\n\n";
			board.print_board_teams();
			int initial_turn = (int)rand() % 2; //0 o 1
			turn = initial_turn;
			cout << "Turno inicial: " << number_to_team[turn] << "\n";
			cout << "------------------------------------" << endl;

			while (!victory && !exit) {
				// Input movimiento
				// Selección
				input_choice();
				// Salida
				if (exit) { cout << "Saliendo...\n";  break; }
				// Chequeo victoria
				if (board.is_victory((turn == team_to_number["RED"]) ? board.red_board : board.black_board)) {
					cout << "¡FIN! Ha ganado el equipo " << number_to_team[turn] << endl;
					board.print_board_teams();
					cout << "Presione ENTER para cerrar" << endl;
					cin.get();
					victory = true;
					break;
				}
				// Cambio de turno
				if (turn == team_to_number["RED"]) { turn = team_to_number["BLACK"]; }
				else { turn = team_to_number["RED"]; }
				// Imprimir nuevo tablero
				board.print_board_teams(); cout << endl;
				// Imprimir equipo de turno actual
				cout << "Turno actual:" << number_to_team[turn] << endl;
			}
		}

		// Consulta método de entrada: Manual, Random, Negamax o Juego Automático Negamax h=3.
		void input_choice() {
			cout << "1=Manual, 2=Random, 3=Negamax, 4=IA vs IA Negamax h=3 (10 jugadas)" << endl;
			cout << "Seleccione opción para siguiente movimiento (o juego automático):" << endl;
			bool valid = false;
			int parsed = -1;
			while (!valid & !exit) {
				char raw[2] = "E";
				cin >> std::setw(2) >> raw; cin.ignore(numeric_limits<streamsize>::max(), '\n');
				// DEBUG: Imprime esto si falla en parsear a chars
				if (cin.fail()) {
					cout << "FAILED in CHOICE" << endl;
				}
				// Chequeo salida "q"
				if (raw[0] == 'q') { exit = true; break; }
				// Opción
				parsed = raw[0] - '0'; // Char numérico->Valor int real
				if (parsed == 1) {
					input_move();
					valid = true;
				}
				else if (parsed == 2) {
					RandomPlayer r = RandomPlayer();
					pair<bitset<25>, bitset<25>> move = r.move(board.board,
						turn == team_to_number["RED"] ? board.red_board : board.black_board);
					board.move_piece(move.first, move.second, board.board,
						turn == team_to_number["RED"] ? board.red_board : board.black_board);
					valid = true;
				}
				else if (parsed == 3) {
					NegamaxPlayer n = NegamaxPlayer();
					pair<bitset<25>, bitset<25>> move = n.move(board.board,
						turn == team_to_number["RED"] ? board.red_board : board.black_board, 3);
					board.move_piece(move.first, move.second, board.board,
						turn == team_to_number["RED"] ? board.red_board : board.black_board);
					valid = true;
				}
				else if (parsed == 4) {
					NegamaxPlayer n1 = NegamaxPlayer();
					NegamaxPlayer n2 = NegamaxPlayer();
					play_ai_game(n1, n2, 10, 3, true);
					valid = true;
				}
				else {
					cout << "Input inválido" << endl << endl;
				}
			}
		}

		// Realizar ciclo de un input de movimiento
		void input_move() {

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
						// Limita input a 3 chars+terminador. Ignora el resto hasta newline.
						cin >> std::setw(4) >> raw; cin.ignore(numeric_limits<streamsize>::max(), '\n');
						// DEBUG: Imprime esto si falla en parsear a chars
						if (cin.fail()) {
							cout << "FAILED in PIECE" << endl;
						}
						// Chequeo símbolos correctos
						// Chequeo salida "q"
						if (raw[0] == 'q') { exit = true; break; }
						// Chequeo caracter fila
						parsed = raw[0] - '0'; // Char numérico->Valor int real
						switch (parsed) {
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
						switch (parsed) {
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
					if (exit) { break; }

					// II) Parseo de input de posición objetivo (SIMILAR al de pieza!)
					char raw[4] = "EEE";
					int parsed = -1;
					obj_fil = -1;
					obj_col = -1;
					// Instrucción
					cout << "Ingrese posicion objetivo (fil-col): ";
					// PARSING (similar al de pieza, arriba)
					cin >> std::setw(4) >> raw; cin.ignore(numeric_limits<streamsize>::max(), '\n');
					if (cin.fail()) {
						cout << "FAILED in OBJECTIVE" << endl;
					}
					// Chequeo símbolos correctos
					// Chequeo salida
					if (raw[0] == 'q') { exit = true; break; }
					// Chequeo caracter fila
					parsed = raw[0] - '0';
					switch (parsed) {
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
					switch (parsed) {
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
				if (exit) { break; }

				// Realización efectiva del movimiento con tableros y chequeos de validez
				bitset<25> piece_board = board.bitset_from_index(piece_fil * 5 + piece_col);
				bitset<25> new_pos_board = board.bitset_from_index(obj_fil * 5 + obj_col);
				// Resultado. Si es inválido, se repite ciclo de función.
				bool result = board.move_piece(piece_board, new_pos_board, board.board,
					(turn == team_to_number["RED"]) ? board.red_board : board.black_board);
				if (result == false) {
					parsed_move = false;
					parsed_piece = false;
					continue;
				}

				// Confirmación de movimiento hecho
				valid_move = true;
			}
		}
	private:
		// Reinicio de variables
		void restart() {
			victory = false;
			exit = false;
			turn = 0;
			board = Bitboard();
		}
	};
}
#endif