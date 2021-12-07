//#include"header.h"
//
//vector<Cell> AStar::search(Cell c, vector<vector<Cell>> matrix) {
//	vector<Cell> return_path;
//	int path_cost = 0;
//	if (goal_test(c)) {
//		return_path.push_back(matrix[c.y][c.x]);
//		return return_path;
//	}
//	matrix[c.y][c.x].exist_priorityQueue = true;
//	priorityQueue.push(matrix[c.y][c.x]);
//	table.push(backtrack_tuple(Cell(matrix[c.y][c.x]), Cell(matrix[c.y][c.x])));
//
//	while (priorityQueue.size() > 0) {
//		vector<int> possible_moves; //1: right, 2: top, 3: left, 4: bottom
//
//		for (auto it : possible_moves) {
//			cout << "Possible move: " << it << " ";
//		}
//
//		if (check_empty(priorityQueue))
//			return return_path; //failure so check if empty then failure
//		else if ((*priorityQueue.data.begin()).value == 3) {
//			for (int i=0;i<priorityQueue.size();i++)
//				cout << priorityQueue.at(i).heuristic << " ";
//			cout << endl;
//			return backtrack(matrix[c.y][c.x], (*priorityQueue.data.begin()));
//		}
//		for (int i = 0; i < priorityQueue.size(); i++)
//			cout << priorityQueue.at(i).heuristic << " ";
//		cout << endl;
//		Cell temp = priorityQueue.pop();
//		matrix[temp.y][temp.x].exist_priorityQueue = false;
//		matrix[temp.y][temp.x].visited = true;
//		explored.push_back(temp);
//		path_cost--;
//		choose_possible_moves(temp, matrix, possible_moves);
//
//		for (auto it : possible_moves) {
//			Cell child_temp = action(temp, matrix, it);
//
//			if (child_temp.value == 3) {
//				matrix[child_temp.y][child_temp.x].heuristic = path_cost-1;
//			}
//
//			Cell child = matrix[child_temp.y][child_temp.x];
//
//			if (!check_exists_priorityQueue_or_explored(child)) {
//				if (goal_test(child)) {
//					table.push(backtrack_tuple(Cell(child), Cell(temp)));
//					//table.display();
//					for (int i = 0; i < priorityQueue.size(); i++)
//						cout << priorityQueue.at(i).heuristic << " ";
//					cout << endl;
//					return backtrack(matrix[c.y][c.x], child); // child == goal
//				}
//				matrix[child.y][child.x].exist_priorityQueue = true;
//				priorityQueue.push(child);
//				priorityQueue.quickSort(0, priorityQueue.size() - 1);
//				//sort(priorityQueue.data.begin(), priorityQueue.data.end(), greater<int>());
//				table.push(backtrack_tuple(Cell(child), Cell(temp)));
//			}
//			
//		}
//	}
//
//	return return_path;
//}
//
//bool AStar::check_exists_priorityQueue_or_explored(Cell child) {
//	if (child.visited || child.exist_priorityQueue)
//		return true;
//
//	return false;
//}
//
//void AStar::choose_possible_moves(Cell temp, vector<vector<Cell>> matrix, vector<int> &possible_moves) {
//	if (matrix[temp.y][temp.x + 1].value != 1)
//		possible_moves.push_back(1);
//	if (matrix[temp.y + 1][temp.x].value != 1)
//		possible_moves.push_back(2);
//	if (matrix[temp.y][temp.x - 1].value != 1)
//		possible_moves.push_back(3);
//	if (matrix[temp.y - 1][temp.x].value != 1)
//		possible_moves.push_back(4);
//};
//
//Cell AStar::action(Cell temp, vector<vector<Cell>> matrix, int possible_moves) {
//	if (possible_moves == 1) {
//		return Cell(temp.x + 1, temp.y, matrix[temp.y][temp.x + 1].value);
//	}
//	else if (possible_moves == 2) {
//		return Cell(temp.x, temp.y + 1, matrix[temp.y + 1][temp.x].value);
//	}
//	else if (possible_moves == 3) {
//		return Cell(temp.x - 1, temp.y, matrix[temp.y][temp.x - 1].value);
//	}
//	else if (possible_moves == 4) {
//		return Cell(temp.x, temp.y - 1, matrix[temp.y - 1][temp.x].value);
//	}
//};
//
//bool AStar::check_empty(Queue q) {
//	if (q.empty())
//		return true;
//	return false;
//};
//bool AStar::goal_test(Cell c) {
//	if (c.value == 2)
//		return true;
//	return false;
//};
//
//vector<Cell> AStar::explored_set() {
//	return explored;
//}
//
//vector<Cell> AStar::backtrack(Cell start, Cell goal) {
//	vector<Cell> return_path;
//	return_path.push_back(goal);
//	Cell temp = table.search_key(goal);
//
//	while (!(temp == start)) {
//		return_path.push_back(temp);
//		temp = table.search_key(temp);
//	}
//
//
//	return_path.push_back(start);
//	return return_path;
//}
//
//void AStar::solution(vector<Cell> return_path) {
//	if (return_path.empty()) {
//		cout << "Can't find goal" << endl;
//		return;
//	}
//
//	cout << "Return path: ";
//	vector<int>::size_type sz = return_path.size();
//
//	for (int i = sz - 1; i >= 0; i--) {
//		cout << "(" << return_path[i].x << "," << return_path[i].y << ") ";
//	}
//
//	cout << endl;
//	cout << "Expanded nodes: ";
//	for (auto it : explored_set()) {
//		cout << "(" << it.x << "," << it.y << ") ";
//	}
//}
