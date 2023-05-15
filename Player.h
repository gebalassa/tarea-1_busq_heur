#ifndef PLAYER
#define PLAYER
#include <bitset>
#include <utility>
#include <vector>
#include <iostream>
#include "Bitboard.cpp"

using namespace std;

namespace AllQueensChess {
	class Player {
	public:
		vector<pair<bitset<25>, bitset<25>>> children;
		vector<bitset<25>> pieces;

		virtual ~Player() {};
		virtual pair<bitset<25>, bitset<25>> move(bitset<25>& board, bitset<25>& team, int height) = 0;
		virtual void clean() = 0;
		virtual void generate(bitset<25> board, bitset<25> team);
		void separate_piece_boards(bitset<25>& team);
		void separate_valid_move_boards(bitset<25>& piece, bitset<25>& valid_moves);
		void print_children() {
			for (int i = 0; i < children.size(); i++) {
				cout << children[i].first << endl << children[i].second
					<< endl << endl;
			}
		}
	};
}

#endif PLAYER