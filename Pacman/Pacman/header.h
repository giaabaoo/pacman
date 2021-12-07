#include <iostream>
#include<fstream>
#include<vector>
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include<iterator>
#include<algorithm>
#include<Windows.h>
#include"windows.h"
using namespace std;
struct Objects {

	int x, y;
	Objects()=default;
	Objects(int x, int y) {
		this->x = x;
		this->y = y;
	};
	void Drawobjs(int x, int y);
	void draw();
};
struct Pacman :Objects {
public:
	Pacman() = default;
	Pacman(int x, int y): Objects(x,y) {

	};
	void Drawobjs(int x, int y);
};

struct Cell {
	int x, y, value;
	bool visited, exist_frontier, exist_priorityQueue;
	int heuristic;
	int utility;
	Cell(int x, int y, int value) {
		this->x = x;
		this->y = y;
		this->heuristic = 0;
		this->utility = 0;
		this->value = value;
		this->visited = false;
		this->exist_frontier = false;
		this->exist_priorityQueue = false;
	};
	Cell() { //default constructor
	
	};
	Cell &operator=(const Cell &c) {
		if (this == &c)
			return *this;
		this->x = c.x;
		this->y = c.y;
		this->heuristic = c.heuristic;
		this->value = c.value;
		this->visited = c.visited;
		this->exist_frontier = c.exist_frontier;
		this->exist_priorityQueue = c.exist_priorityQueue;
		return *this;
	}
	bool operator==(const Cell &c) {
		if (this->value == c.value && this->x == c.x && this->y == c.y)
			return true;
		return false;
	};
};

struct backtrack_tuple {
	Cell key, previous;
	backtrack_tuple(Cell key, Cell previous){
		this->key = key;
		this->previous = previous;
	};
};

struct backtrack_table {
	vector<backtrack_tuple> tuples;
	Cell search_key(Cell search) {
		for (auto it : tuples) {
			if (search == it.key)
				return it.previous;
		}
	};
	void push(backtrack_tuple t) {
		tuples.push_back(t);
	};
	void display() {
		for (auto it : tuples) {
			cout << "Cell (" << it.key.x << "," << it.key.y << "," << it.key.value << ") | " 
				<< "Cell (" << it.previous.x << "," << it.previous.y << "," << it.previous.value << ")" << endl;
		}
	}
};

struct Queue {
	void push(Cell c); //enqueue
	Cell pop(); //dequeue
	void display();
	bool empty();
	int size();
	Cell at(int);
	vector<Cell> data;

	void quickSort(int low, int high);
	void swap(Cell *a, Cell *b);
	int partition(int low, int high);
};


class BFS {
protected:
	Queue frontier; //self implement queue
	vector<Cell> explored;
	backtrack_table table;
	int score;
public:
	BFS(int score) {
		this->score = score;
	};
	int get_score() {
		return score;
	};
	vector<Cell> search(Cell c, vector<vector<Cell>> matrix, Cell goal);
	bool check_exists_frontier_or_explored(Cell child);
	void choose_possible_moves(Cell temp, vector<vector<Cell>> matrix, vector<int> &possible_moves, Cell goal);
	Cell action(Cell temp, vector<vector<Cell>> matrix, int possible_moves);
	bool check_empty(Queue q);
	bool goal_test(Cell c, Cell goal);
	vector<Cell> explored_set();
	vector<Cell> backtrack(Cell start, Cell goal);
	void solution(vector<Cell> return_path);
};

class return_path {
public:
	vector<Cell> path;
	int score;
	return_path(vector<Cell> path, int score) {
		this->path = path;
		this->score = score;
	};
	return_path(vector<Cell> path) {
		this->path = path;
	};
	void display() {
		int j = 0;
		vector<int>::size_type sz = path.size();
		cout << "Return path: " << j;
		for (int i = sz - 1; i >= 0; i--) {
			cout << "(" << path[i].x << "," << path[i].y << ") ";
		}
		j++;
		cout << " ==> " << score;
		cout << endl;
	};
	void display_ghosts() {
		int j = 0;
		vector<int>::size_type sz = path.size();
		for (int i = 0; i < sz; i++) {
			cout << "(" << path[i].x << "," << path[i].y << ") ";
		}
		j++;
		cout << endl;
	};
};

class GBFS {
public:
	vector<Cell> search(Cell c, vector<vector<Cell>> matrix, vector<Cell> goals);
	void solution(vector<Cell> return_path);
};

//class AStar {
//protected:
//	Queue priorityQueue;
//	vector<Cell> explored;
//	backtrack_table table;
//public:
//	vector<Cell> search(Cell c, vector<vector<Cell>> matrix);
//	bool check_exists_priorityQueue_or_explored(Cell child);
//	void choose_possible_moves(Cell temp, vector<vector<Cell>> matrix, vector<int> &possible_moves);
//	Cell action(Cell temp, vector<vector<Cell>> matrix, int possible_moves);
//	bool check_empty(Queue q);
//	bool goal_test(Cell c);
//	vector<Cell> explored_set();
//	vector<Cell> backtrack(Cell start, Cell goal);
//	void solution(vector<Cell> return_path);
//};

class PGraphics {
public:
	Pacman P;
	void initmap(Cell first_position, vector<vector<Cell> > matrix,int row, int col);
	void showresult(vector<Cell> return_path, int row);
	void showresultLevel3(vector<Cell> rp, int row, vector<return_path> ghosts);
};




void inputfile(int &row, int &column, vector<vector<Cell> > &matrix, Cell &first_position, vector<Cell> &goals, vector<Cell> &total_foods, vector<Cell> &total_ghosts);
void display(int &row, int &column, vector<vector<Cell> > matrix, Cell &first_position);
void heuristicCal(int &row, int &column, vector<vector<Cell>> &matrix);
void SetupRC(int row, int column);
void graphics_display();

void pacman_scan(int row, int col, Cell position, vector<vector<Cell>>& scan_matrix, vector<vector<Cell>> matrix
, vector<Cell>& foods, vector<Cell>& ghosts);

vector<Cell> search_level3(int row, int col, Cell position, vector<vector<Cell>> matrix
	, vector<Cell> foods, vector<Cell> ghosts, vector<return_path> &ghost_rp, vector<Cell>& list_all_actions);
void random_possible_moves(vector<Cell> &visited, Cell &position, vector<vector<Cell>> scan_matrix);
void utility(vector<vector<Cell>> matrix, vector<Cell> &possible_moves, Cell position, vector<Cell> foods, vector<Cell> ghosts);
void choose_possible_moves(Cell position, vector<Cell> &possible_moves, vector<vector<Cell>> scan_matrix);
Cell min_utility(vector<Cell> possible_moves);
Cell max_utility(vector<Cell> possible_moves);
bool check_visited_random_moves(vector<Cell> visited, Cell check);
