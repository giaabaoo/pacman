#include"header.h"

void inputfile(int &row, int &column, vector<vector<Cell>> &matrix, Cell &first_position, vector<Cell> &goals, vector<Cell> &total_foods, vector<Cell> &total_ghosts) {
	int xPac, yPac;
	ifstream fin;
	fin.open("input5.txt");
	if (!fin.is_open()) {
		cout << "Cannot open file" << endl;
		return;
	}

	vector<vector<int>> input;

	while (!fin.eof()) {
		fin >> row >> column;

		for (int i = 0; i < row; i++) {
			vector<Cell> temp;
			for (int j = 0; j < column; j++) {
				int tmp;
				fin >> tmp;
				Cell t = Cell(j, i, tmp);
				temp.push_back(t);
				if (tmp == 3 || tmp == 2) {
					goals.push_back(Cell(j, i, tmp));
				}
				if (tmp == 3)
					total_ghosts.push_back(Cell(j, i, tmp));
				else if (tmp == 2)
					total_foods.push_back(Cell(j, i, tmp));

			}
			matrix.push_back(temp);
		}
		fin >> xPac >> yPac;
		first_position = Cell(xPac, yPac, -1);
	}
	fin.close();
}

void display(int &row, int &column, vector<vector<Cell>> matrix, Cell &first_position) {
	cout <<"Size of matrix: " << row << " " << column << endl;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++)
			cout << matrix[i][j].value << " ";
		cout << endl;
	}
	cout << "Pacman first position: " << first_position.x << " " << first_position.y << endl;
}


//void heuristicCal(int &row, int &column, vector<vector<Cell>>&matrix) {
//	for (int i = 1; i < row -1; i++) {
//		for (int j = 1; j < column - 1; j++) {
//			if (matrix[i][j].value == 0) {
//				BFS b(0);
//				vector<Cell> return_path = b.search(matrix[i][j], matrix);
//				int heuristic = (return_path.size()) * (-1) + 20;
//				matrix[i][j].heuristic = heuristic;
//			}
//		}
//	}
//
//
//}

/**************************************** Graphics ****************************************/

int once = 0;

void SetupRC(int row, int column) {
	glClearColor(0, 0, 0, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluOrtho2D(-(column - 1), (column - 1) * 2, -(row - 1), ((row - 1) * 2));
	if(column >= row)
	gluOrtho2D(-1,column,-1,column);
	else gluOrtho2D(-1, row, -1, row);
}

void graphics_display() {
	if (once == 0) {
		int row = 0, column = 0;
		Cell first_position(0, 0, 0);
		vector<vector<Cell>> matrix;
		int score = 0;
		vector<Cell> goals;
		PGraphics g;

		//matrix display
		vector<Cell> total_foods, total_ghosts;
		inputfile(row, column, matrix, first_position, goals, total_foods, total_ghosts);
		display(row, column, matrix, first_position);

		//BFS
	/*	BFS b;
		vector<Cell> return_path;

		return_path = b.search(first_position, matrix, score);
		b.solution(return_path);*/

		//GBFS
	/*	GBFS gbfs;
		vector<Cell> return_path;
		return_path = gbfs.search(first_position, matrix, goals);
		gbfs.solution(return_path);*/

		//Level 3
		vector<Cell> rp;
		vector<return_path> ghost_rp;
		vector<Cell> list_all_actions;
		rp = search_level3(row, column, first_position, matrix, total_foods, total_ghosts
		, ghost_rp, list_all_actions);
		cout << first_position.x << endl;
		cout << "Ghosts P: ";
		for (auto it : rp) {
			cout << "(" << it.x << "," << it.y << ") ";
		}

		cout << endl;
		for (int i = 0; i < ghost_rp.size();i++) {
			cout << "Ghosts " << i<< ": "; 
			ghost_rp[i].display_ghosts();
		}

		cout << "List all actions: ";
		for (auto it : list_all_actions)
			cout << it.value << " ";


		//graphics display
		SetupRC(row, column);
		g.initmap(first_position, matrix, row, column);
		/*if (!rp.empty())
			g.showresult(rp, row);*/
		if (!rp.empty())
			g.showresultLevel3(list_all_actions, row, ghost_rp);
		once++;


	}
	else return;
}

void pacman_scan(int row, int col, Cell position, vector<vector<Cell>>& scan_matrix, vector<vector<Cell>> matrix
	, vector<Cell>& foods, vector<Cell>& ghosts) {

	for (int i = -3; i <= 3; i++) {
		for (int j = -3; j <= 3; j++) {
			if (position.x + j < 0 || position.y + i < 0 || position.x + j > col - 1 || position.y + i > row -1
				|| abs(i+j) > 3 || abs(i-j) > 3)
				scan_matrix[i+3][j + 3].value = 5;
			else {
				scan_matrix[i + 3][j + 3] = matrix[position.y + i][position.x + j];
				if (scan_matrix[i + 3][j + 3].value == 2)
					foods.push_back(scan_matrix[i + 3][j + 3]);
				else if (scan_matrix[i + 3][j + 3].value == 3)
					ghosts.push_back(scan_matrix[i + 3][j + 3]);
			}

		}
	}

	
}

vector<Cell> search_level3(int row, int col, Cell position, vector<vector<Cell>> matrix
	, vector<Cell> f, vector<Cell> g, vector<return_path> &ghost_rp, vector<Cell>& list_all_actions) {
	Cell start = position;
	vector<vector<Cell>> scan_matrix;
	vector<Cell> return_paths, ghosts, foods;
	int count = 0;
	bool is_dead = false;

	for (int i = 0; i < 7; i++) {
		vector<Cell> temp;
		for (int j = 0; j < 7; j++) {
			temp.push_back(Cell(j, i, -1));
		}
		scan_matrix.push_back(temp);
	}
	return_paths.push_back(start);

	for (auto it : g) {
		vector<Cell> rp;
		ghost_rp.push_back(return_path(rp));
	}

	int c = 0;
	vector<Cell> visited;

	while (true) {

		if (count == f.size() || is_dead) {
			return return_paths;
		}
	
		for (int i = 0; i < g.size();i++) {
			int random = rand() % ((4 - 1) + 1) + 1;
			Cell temp;

			if (c == 0) {
				ghost_rp[i].path.push_back(matrix[g[i].y][g[i].x]);
				c++;
			}

			if (random == 1) {
				if (matrix[g[i].y][g[i].x + 1].value == 0) {
					matrix[g[i].y][g[i].x].value = 0;
					matrix[g[i].y][g[i].x + 1].value = 3;
					g[i].x++;
				}
			}
			else if (random == 3) {
				if (matrix[g[i].y][g[i].x - 1].value == 0) {
					matrix[g[i].y][g[i].x].value = 0;
					matrix[g[i].y][g[i].x - 1].value = 3;
					g[i].x--;
				}
			}
			else if (random == 2) {
				if (matrix[g[i].y + 1][g[i].x].value == 0) {
					matrix[g[i].y][g[i].x].value = 0;
					matrix[g[i].y + 1][g[i].x].value = 3;
					g[i].y++;
				}
			}
			else if (random == 4) {
				if (matrix[g[i].y - 1][g[i].x].value == 0) {
					matrix[g[i].y][g[i].x].value = 0;
					matrix[g[i].y - 1][g[i].x].value = 3;
					g[i].y--;
				}
			}
			ghost_rp[i].path.push_back(matrix[g[i].y][g[i].x]);
			list_all_actions.push_back(matrix[g[i].y][g[i].x]);


			if (g[i].x == position.x && g[i].y == position.y) {
				cout << "Pacman is eaten by ghosts" << endl;
				is_dead = true;
				return return_paths;
			}
		}

		pacman_scan(row, col, position, scan_matrix, matrix, foods, ghosts);


		if (foods.empty() && ghosts.empty()) {
			random_possible_moves(visited, position, scan_matrix); 
		}
		else {
			if (ghosts.empty() && !foods.empty()) { //only see food
				//check possible moves: check walls

				vector<Cell> possible_moves;
				choose_possible_moves(position, possible_moves, scan_matrix);
				utility(matrix, possible_moves, position, foods, ghosts);
				if (possible_moves.size() > 0)
					position = min_utility(possible_moves);
				if (position.value == 2) {
					count++;
					
				}
			}
			else if (foods.empty() && !ghosts.empty()) { //only see ghosts
				//check eat ghosts
				vector<Cell> possible_moves;
				choose_possible_moves(position, possible_moves, scan_matrix);
				utility(matrix, possible_moves, position, foods, ghosts);
				if (possible_moves.size() > 0)
					position = max_utility(possible_moves);
				else if (position.value == 3) {
					cout << "Pacman meets ghost" << endl;
					is_dead = true;
				}
			}
			else { //see both
				vector<Cell> possible_moves;
				choose_possible_moves(position, possible_moves, scan_matrix);
				utility(matrix, possible_moves, position, foods, ghosts);
				if (possible_moves.size() > 0)
					position = max_utility(possible_moves);
				if (position.value == 2) {
					count++;
				}
				else if (position.value == 3)
					is_dead = true;
			}
		}
		return_paths.push_back(position);
		list_all_actions.push_back(position);
	}
}

void random_possible_moves(vector<Cell> &visited, Cell &position, vector<vector<Cell>> scan_matrix) {
	if (scan_matrix[3][4].value % 2 == 0 && !check_visited_random_moves(visited, scan_matrix[3][4])) {
		position = scan_matrix[3][4];
		visited.push_back(position);
	}
	if (scan_matrix[2][3].value % 2 == 0 && !check_visited_random_moves(visited, scan_matrix[2][3])) {
		position = scan_matrix[2][3];
		visited.push_back(position);
	}
	if (scan_matrix[3][2].value % 2 == 0 && !check_visited_random_moves(visited, scan_matrix[3][2])) {
		position = scan_matrix[3][2];
		visited.push_back(position);
	}
	if (scan_matrix[4][3].value % 2 == 0 && !check_visited_random_moves(visited, scan_matrix[4][3])) {
		position = scan_matrix[4][3];
		visited.push_back(position);
	}
}

bool check_visited_random_moves(vector<Cell> visited, Cell check) {
	for (auto it : visited)
		if (it == check)
			return true;
	return false;
}


void utility(vector<vector<Cell>> matrix, vector<Cell> &possible_moves, Cell position, vector<Cell> foods, vector<Cell> ghosts) {
	if (ghosts.empty() && !foods.empty()) {
		for (int i = 0; i < possible_moves.size();i++) {
			int utility_food = 0;
			for (auto f : foods) {
				BFS b(0);
				b.search(possible_moves[i], matrix, f);
				utility_food += abs(b.get_score());
			}
			possible_moves[i].utility = utility_food;
		}
	}
	else if (!ghosts.empty() && foods.empty()) {
		for (int i = 0; i < possible_moves.size(); i++) {
			int utility_ghost = 0;
			for (auto g : ghosts) {
				utility_ghost += abs(g.x - possible_moves[i].x) + abs(g.y - possible_moves[i].y);
			}
			possible_moves[i].utility = utility_ghost;
		}
	}
	else {
		for (int i = 0; i < possible_moves.size(); i++) {
			int utility_ghost = 0;
			int utility_food = 0;
			for (auto g : ghosts) {
				utility_ghost += abs(g.x - possible_moves[i].x) + abs(g.y - possible_moves[i].y);
			}
			for (auto f : foods) {
				BFS b(0);
				b.search(possible_moves[i], matrix, f);
				utility_food += abs(b.get_score());
			}
			possible_moves[i].utility = utility_ghost + utility_food;
		}
	}
}

void choose_possible_moves(Cell position, vector<Cell> &possible_moves, vector<vector<Cell>> scan_matrix) {
	cout << "Scan matrix: " << endl;
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			int val = scan_matrix[i][j].value;

			cout << "(" << i << "," << j << ") = " << val << " ";
		}
		cout << endl;
	}

	if (scan_matrix[3][4].value % 2 == 0)
		possible_moves.push_back(scan_matrix[3][4]);
	if (scan_matrix[2][3].value % 2 == 0)
		possible_moves.push_back(scan_matrix[2][3]);
	if (scan_matrix[3][2].value % 2 == 0)
		possible_moves.push_back(scan_matrix[3][2]);
	if (scan_matrix[4][3].value % 2 == 0)
		possible_moves.push_back(scan_matrix[4][3]);
}

Cell min_utility(vector<Cell> possible_moves) {
	Cell min = possible_moves[0];
	for (auto it : possible_moves) {
		if (it.utility < min.utility)
			min = it;
	}
	return min;
}

Cell max_utility(vector<Cell> possible_moves) {
	Cell max = possible_moves[0];
	for (auto it : possible_moves) {
		if (it.utility > max.utility)
			max = it;
	}
	return max;
}
