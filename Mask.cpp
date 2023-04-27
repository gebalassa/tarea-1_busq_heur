#ifndef MASK
#define MASK
#include <iostream>
#include <bitset>

using namespace std;

namespace AllQueensChess {
	class Mask {
	public:
		const bitset<25> hmasks[5] = {
			0b1111100000000000000000000,
			0b0000011111000000000000000,
			0b0000000000111110000000000,
			0b0000000000000001111100000,
			0b0000000000000000000011111
		};

		const bitset<25> vmasks[5] = {
			0b1000010000100001000010000,
			0b0100001000010000100001000,
			0b0010000100001000010000100,
			0b0001000010000100001000010,
			0b0000100001000010000100001
		};

		const bitset<25> dmasks[25] = {
			0b1000000000000000000000000, // 00
			0b0100010000000000000000000, // 01
			0b0010001000100000000000000, // 02
			0b0001000100010001000000000, // 03
			0b0000100010001000100010000, // 04
			0b0100010000000000000000000, // 05
			0b0010001000100000000000000, // 06
			0b0001000100010001000000000, // 07
			0b0000100010001000100010000, // 08
			0b0000000001000100010001000, // 09
			0b0010001000100000000000000, // 10
			0b0001000100010001000000000, // 11
			0b0000100010001000100010000, // 12
			0b0000000001000100010001000, // 13
			0b0000000000000010001000100, // 14
			0b0001000100010001000000000, // 15
			0b0000100010001000100010000, // 16
			0b0000000001000100010001000, // 17
			0b0000000000000010001000100, // 18
			0b0000000000000000000100010, // 19
			0b0000100010001000100010000, // 20
			0b0000000001000100010001000, // 21
			0b0000000000000010001000100, // 22
			0b0000000000000000000100010, // 23
			0b0000000000000000000000001, // 24
		};

		const bitset<25> antidmasks[25] = {
			0b1000001000001000001000001, // 00
			0b0100000100000100000100000, // 01
			0b0010000010000010000000000, // 02
			0b0001000001000000000000000, // 03
			0b0000100000000000000000000, // 04


			0b0000010000010000010000010, // 05
			0b1000001000001000001000001, // 06
			0b0100000100000100000100000, // 07
			0b0010000010000010000000000, // 08
			0b0001000001000000000000000, // 09

			0b0000000000100000100000100, // 10
			0b0000010000010000010000010, // 11
			0b1000001000001000001000001, // 12
			0b0100000100000100000100000, // 13
			0b0010000010000010000000000, // 14

			0b0000000000000001000001000, // 15
			0b0000000000100000100000100, // 16
			0b0000010000010000010000010, // 17
			0b1000001000001000001000001, // 18
			0b0100000100000100000100000, // 19

			0b0000000000000000000010000, // 20
			0b0000000000000001000001000, // 21
			0b0000000000100000100000100, // 22
			0b0000010000010000010000010, // 23
			0b1000001000001000001000001, // 24
		};

		// Imprime tablero entregado
		void print_board(bitset<25> board) {
			for (int i = board.size() - 1; i >= 0; i--) {
				if (i % 5 == 0) {
					cout << board[i];
					cout << "\n";
				}
				else {
					cout << board[i];
				}
			}
		}

		// DEBUG: Imprimir todas las m�scaras de un arreglo
		template <int n>
		void debug_print_masks(const bitset<25>(&masks)[n]) {
			cout << "size: " << sizeof(masks) / sizeof(masks[0]) << "\n";
			for (int i = 0; i < (int)(sizeof(masks) / sizeof(bitset<25>)); i++) {
				cout << i << "\n";
				print_board(masks[i]); cout << "\n";
			}
		}
	};
}

#endif