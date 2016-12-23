#include <bits/stdc++.h>

using namespace std;

struct SudokuSolver {

	int RowMask[9], ColMask[9], SqMask[9];
	char Table[9][10];

	int GetSquare(int r, int c) {
		r /= 3; c /= 3;
		return 3 * r + c;
	}

	void CompleteEntry(int r, int c, int v) {
		--v;
		RowMask[r] |= (1 << v);
		ColMask[c] |= (1 << v);
		SqMask[GetSquare(r, c)] |= (1 << v);
		Table[r][c] = '1' + v;
	}
	void ClearEntry(int r, int c) {
		int v = Table[r][c] - '1';
		RowMask[r] ^= (1 << v);
		ColMask[c] ^= (1 << v);
		SqMask[GetSquare(r, c)] ^= (1 << v);
		Table[r][c] = 0;
	}

	void ReadSudoku(istream &in) {
		memset(Table, 0, sizeof(Table));
		for(int i = 0; i < 9; ++i) {
			RowMask[i] = ColMask[i] = SqMask[i] = 0;
		}
		for(int i = 0; i < 9; ++i) {
			string temp;
			in >> temp;
			for(int j = 0; j < 9; ++j)
				if(temp[j] >= '1' && temp[j] <= '9')
					CompleteEntry(i, j, temp[j] - '0');
		}
	}

	bool BackTrack(int step) {
		if(step == 81) return true;

		int r = step / 9, c = step % 9;
		if(Table[r][c] >= '1' && Table[r][c] <= '9') 
			return BackTrack(step + 1);

		int mask = (RowMask[r] | ColMask[c] | SqMask[GetSquare(r, c)]); 

		for(int v = 0; v < 9; ++v) {
			if(mask & (1 << v))
				continue;

			CompleteEntry(r, c, v + 1);
			if(BackTrack(step + 1)) 
				return true;
			ClearEntry(r, c);
		}

		return false;
	}

	bool Solve() {
		return BackTrack(0);
	}

	void OutputSolution(ostream &out) {
		for(int i = 0; i < 9; ++i)
			out << Table[i] << endl;
	}
};

int main() {

	SudokuSolver s;
	ifstream in("sudoku_in.txt");
	ofstream out("sudoku_out.txt");

	while(true) {
		cout << "Put puzzle in sudoku_in.txt, with character X instead of blank spaces" << endl;
		cout << "Then press any key to solve" << endl;
		cout << "Or press Q to quit" << endl;

		char q; cin >> q;
		if(q == 'q' || q == 'Q') 
			break;

		s.ReadSudoku(in);
		if(!s.Solve()) {
			cout << "No solution found!" << endl;
		} else {
			cout << "Solution is in sudoku_out.txt" << endl;
			s.OutputSolution(out);
		}
		cout << "-----------" << endl << endl;
	}

	in.close();
	out.close();

	return 0;
}