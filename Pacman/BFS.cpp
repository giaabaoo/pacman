#include"header.h"

vector<Cell> BFS::search(Cell c, vector<vector<Cell>> matrix, Cell goal) {
	vector<Cell> return_path;
	if (goal_test(c, goal)) {
		return_path.push_back(c);
		return return_path;
	}
	matrix[c.y][c.x].exist_frontier = true;
	frontier.push(c);
	table.push(backtrack_tuple(Cell(c), Cell(c)));

	while (frontier.size() > 0) {
		vector<int> possible_moves; //1: right, 2: top, 3: left, 4: bottom

		for (auto it : possible_moves) {
			cout << "Possible move: " << it << " ";
		}

		if (check_empty(frontier))
			return return_path; //failure so check if empty then failure
		Cell temp = frontier.pop();
		matrix[temp.y][temp.x].exist_frontier = false;
		matrix[temp.y][temp.x].visited = true;
		explored.push_back(temp);
		choose_possible_moves(temp, matrix, possible_moves, goal);

		for (auto it : possible_moves) {
			Cell child_temp = action(temp, matrix, it);

			Cell child = matrix[child_temp.y][child_temp.x];


			if (!check_exists_frontier_or_explored(child)) {
				if (goal_test(child, goal)) {
					table.push(backtrack_tuple(Cell(child), Cell(temp)));
					//table.display();
					return backtrack(c, child); // child == goal
				}
				matrix[child.y][child.x].exist_frontier = true;
				frontier.push(child);
				table.push(backtrack_tuple(Cell(child), Cell(temp)));
			}
		}
	}

	return return_path;
}

bool BFS::check_exists_frontier_or_explored(Cell child) {
	if (child.visited || child.exist_frontier)
		return true;

	return false;
}

void BFS::choose_possible_moves(Cell temp, vector<vector<Cell>> matrix, vector<int> &possible_moves, Cell goal) {
	bool conditionR0 = matrix[temp.y][temp.x + 1].value == 0, conditionU0 = matrix[temp.y + 1][temp.x].value == 0
		, conditionL0 = matrix[temp.y][temp.x - 1].value == 0, conditionD0 = matrix[temp.y - 1][temp.x].value == 0;
	if (goal.value == 2) {
		conditionR0 = conditionR0 || matrix[temp.y][temp.x + 1].value == 2;
		conditionU0 = conditionU0 || matrix[temp.y + 1][temp.x].value == 2;
		conditionL0 = conditionL0 || matrix[temp.y][temp.x - 1].value == 2;
		conditionD0 = conditionD0 || matrix[temp.y - 1][temp.x].value == 2;
		if (conditionR0)
			possible_moves.push_back(1);
		if (conditionU0)
			possible_moves.push_back(2);
		if (conditionL0)
			possible_moves.push_back(3);
		if (conditionD0)
			possible_moves.push_back(4);
	}
	
	else if (goal.value == 3) {
		bool conditionR3 = matrix[temp.y][temp.x + 1].value == 3, conditionU3 = matrix[temp.y + 1][temp.x].value == 3
			, conditionL3 = matrix[temp.y][temp.x - 1].value == 3, conditionD3 = matrix[temp.y - 1][temp.x].value == 3;
		conditionR3 = conditionR3 && temp.y == goal.y && temp.x+1 == goal.x;
		conditionU3 = conditionU3 && temp.y+1 == goal.y && temp.x == goal.x;
		conditionL3 = conditionL3 && temp.y == goal.y && temp.x - 1 == goal.x;
		conditionD3 = conditionD3 && temp.y-1 == goal.y && temp.x == goal.x;
		if (conditionR0 || conditionR3)
			possible_moves.push_back(1);
		if (conditionU0 || conditionU3)
			possible_moves.push_back(2);
		if (conditionL0 || conditionL3)
			possible_moves.push_back(3);
		if (conditionD0 || conditionD3)
			possible_moves.push_back(4);
	}
};

Cell BFS::action(Cell temp, vector<vector<Cell>> matrix, int possible_moves) {
	if (possible_moves == 1) {
		return Cell(temp.x + 1, temp.y, matrix[temp.y][temp.x + 1].value);
	}
	else if (possible_moves == 2) {
		return Cell(temp.x, temp.y + 1, matrix[temp.y + 1][temp.x].value);
	}
	else if (possible_moves == 3) {
		return Cell(temp.x - 1, temp.y, matrix[temp.y][temp.x - 1].value);
	}
	else if (possible_moves == 4) {
		return Cell(temp.x, temp.y - 1, matrix[temp.y - 1][temp.x].value);
	}
};

bool BFS::check_empty(Queue q) {
	if (q.empty())
		return true;
	return false;
};
bool BFS::goal_test(Cell c, Cell goal) { 
	if (c == goal)
		return true;
	return false;
};

vector<Cell> BFS::explored_set() {
	return explored;
}

vector<Cell> BFS::backtrack(Cell start, Cell goal) {
	vector<Cell> return_path;
	return_path.push_back(goal);
	Cell temp = table.search_key(goal);

	while (!(temp == start)) {
		return_path.push_back(temp);
		temp = table.search_key(temp);
		score--;
	}
	score--;

	return_path.push_back(start);
	return return_path;
}

void BFS::solution(vector<Cell> return_path) {
	if (return_path.empty()) {
		cout << "Can't find goal" << endl;
		return;
	}

	cout << "Return path: ";
	vector<int>::size_type sz = return_path.size();

	for (int i = sz - 1; i >= 0; i--) {
		cout << "(" << return_path[i].x << "," << return_path[i].y << ") ";
	}

	cout << endl;
	cout << "Expanded nodes: ";
	for (auto it : explored_set()) {
		cout << "(" << it.x << "," << it.y << ") ";
	}
}
