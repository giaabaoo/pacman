#include"header.h"
void Objects::Drawobjs(int x, int y) {
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
	glFlush();
}
void Objects::draw() {
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
	glFlush();
}
void Pacman::Drawobjs(int x, int y) {
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
	glFlush();
}

void PGraphics::initmap(Cell first_position, vector<vector<Cell> > matrix,int row, int col) {
	/* if (col > row && row * col > 50)
		glPointSize(col+row*2);
	else if(col > row && row + col > 20)
		glPointSize(col*2 + row );
	else if(row*col > 30)
	 glPointSize(row*col);
	else  glPointSize(row*col + 30);*/
	if(col+row<10)
		glPointSize(col*2);
	else if (col +row > 19)
		glPointSize(15);
	else 
	glPointSize(col + row+ 9);
	
	glColor3f(1, 1, 0.16);
	P = Pacman(first_position.x, first_position.y);
	P.Drawobjs(first_position.x, (row - 1) - first_position.y);
	glColor3f(1, 1, 1);

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (matrix[i][j].value == 1) {
				Objects wall(j, (row - 1) - i);
				wall.draw();
			}
			else if (matrix[i][j].value == 2) {
				glColor3f(1, 0, 0);
				Objects food(j, (row - 1) - i);
				food.draw();
				glColor3f(1, 1, 1);
				
			}
			else if (matrix[i][j].value == 3) {
				glColor3f(0, 0, 1);
				Objects ghost(j, (row - 1) - i);
				ghost.draw();

				glColor3f(1, 1, 1);
			}
			
		}
	}
}
void PGraphics::showresult(vector<Cell> return_path, int row) {
	int size = return_path.size()-1;
	for (int i = size ; i >= 0; i--) {
		glColor3f(0, 0, 0);
		P.Drawobjs(P.x, (row-1) - P.y);
		
		glColor3f(1, 1, 0.16);
		if (return_path[i].value == 3) {
			glColor3f(0, 0, 1);
		}
		P.Drawobjs(return_path[i].x, (row - 1) - return_path[i].y);
		glColor3f(1, 1, 1);
		P.x = return_path[i].x;
		P.y = return_path[i].y;
		glFlush();
		Sleep(500);
	}
	
}

void PGraphics::showresultLevel3(vector<Cell> rp, int row, vector<return_path> ghosts) {
	int size = rp.size();
	int count = 0;
	vector<Objects> DrawGhost;
	for (int i =0; i < ghosts.size(); i++) {
		DrawGhost.push_back(Objects(ghosts[i].path[0].x, ghosts[i].path[0].y));
	}
	for (int i = 0; i < size; i++) {

		if (rp[i].value == 3) {
			glColor3f(0, 0, 0);
			DrawGhost[count].Drawobjs(DrawGhost[count].x, (row - 1) - DrawGhost[count].y);
			glColor3f(0, 0, 1);
			DrawGhost[count].x = rp[i].x;
			DrawGhost[count].y = rp[i].y;
			DrawGhost[count].Drawobjs(DrawGhost[count].x, (row - 1) - DrawGhost[count].y);
			count++;
			if (count == ghosts.size()) {
				count = 0;
				Sleep(300);
			}
		}
		else if (rp[i].value == 0 || rp[i].value == 2) {
			glColor3f(0, 0, 0);
			P.Drawobjs(P.x, (row - 1) - P.y);
			glColor3f(1, 1, 0.16);
			P.Drawobjs(rp[i].x, (row - 1) - rp[i].y);
			P.x = rp[i].x;
			P.y = rp[i].y;
			Sleep(300);

		}
		glColor3f(1, 1, 1);
		glFlush();
	}

}

