#include"header.h"

vector<Cell> GBFS::search(Cell c, vector<vector<Cell>> matrix, vector<Cell> goals) {
	vector<return_path> RP;
	int pos = 0;

	for (auto it : goals) {
		BFS b(0);
		vector<Cell> p = b.search(c, matrix, it);
		int s = b.get_score();
		if (it.value == 2 && !p.empty())
			RP.push_back(return_path(p, s + 200));
		else if (it.value == 3 && !p.empty())
			RP.push_back(return_path(p, s));
	}


	//sort
	if (!RP.empty()) {
		return_path max = RP[0];
		for (auto it : RP) {
			if (it.score > max.score) {
				max = it;
			}
			it.display();
		}
		return max.path;
	}
	vector<Cell> empty;
	return empty;
};
void GBFS::solution(vector<Cell> return_path) {
	if (return_path.empty()) {
		cout << "Can't find goal" << endl;
		return;
	}

	cout << "GBFS return path: ";
	vector<int>::size_type sz = return_path.size();

	for (int i = sz - 1; i >= 0; i--) {
		cout << "(" << return_path[i].x << "," << return_path[i].y << ") ";
	}

	cout << endl;
};