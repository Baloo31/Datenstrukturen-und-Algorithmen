#include "Aufgabe.h"
#include "Queue.h"
#include <vector>
#include <iostream>

using namespace std;


struct Cell {
	char cellType;
	bool visited;
};


void getRobotLocation(int& robotStartRow, int& robotStartColumn, int nrRows, int nrColumns, const vector<vector<Cell>>& matrix) {
	for (int row = 0; row < nrRows; row++) {
		for (int col = 0; col < nrColumns; col++) {
			if (matrix[row][col].cellType == 'r') {
				robotStartColumn = col;
				robotStartRow = row;
				break;
			}
		}
	}
}


/*
Bestimmt ob das Robot aus dem Labyrinth herauskommen kann und generiert das Weg falls es einem gibt
*/
bool findPath(Queue& path, int x, int y, int nrRows, int nrColumns, vector<vector<Cell>>& matrix) {
	// Falls die aktuelle Position gultig ist und auf dem Kontur des Labyrinthes liegt
	if (((x == 0) || (x == nrRows - 1) || (y == 0) || (y == nrColumns - 1)) && !(matrix[x][y].visited)) {
		TElem loc; loc.column = y; loc.row = x;
		path.push(loc);
		return true;
	}
	// Falls die aktuelle Position ungultig ist (Zelle wurde schon besucht oder sie ist nicht frei)
	if (matrix[x][y].visited) {
		return false;
	}

	// Aktuelle Position ist frei und wird als besucht markiert
	matrix[x][y].visited = true;

	// Suchen nach oben
	if (findPath(path, x - 1, y, nrRows, nrColumns, matrix)) {
		TElem loc; loc.column = y; loc.row = x;
		path.push(loc);
		return true;
	}

	// Suchen nach links
	if (findPath(path, x, y - 1, nrRows, nrColumns, matrix)) {
		TElem loc; loc.column = y; loc.row = x;
		path.push(loc);
		return true;
	}

	// Suchen nach unten
	if (findPath(path, x + 1, y, nrRows, nrColumns, matrix)) {
		TElem loc; loc.column = y; loc.row = x;
		path.push(loc);
		return true;
	}

	// Suchen nach rechts
	if (findPath(path, x, y + 1, nrRows, nrColumns, matrix)) {
		TElem loc; loc.column = y; loc.row = x;
		path.push(loc);
		return true;
	}
}

void generateLabyrinth(vector<vector<Cell>>& matrix) {
	Cell r; r.cellType = 'r'; r.visited = false;
	Cell x; x.cellType = 'x'; x.visited = true;
	Cell e; e.cellType = '*'; e.visited = false;

	vector<Cell> line;
	line.push_back(x); line.push_back(e); line.push_back(e); line.push_back(x); line.push_back(x); line.push_back(x); line.push_back(e); line.push_back(e); matrix.push_back(line); line = {};
	line.push_back(x); line.push_back(e); line.push_back(x); line.push_back(e); line.push_back(e); line.push_back(e); line.push_back(e); line.push_back(e); matrix.push_back(line); line = {};
	line.push_back(x); line.push_back(e); line.push_back(e); line.push_back(e); line.push_back(e); line.push_back(e); line.push_back(x); line.push_back(e); matrix.push_back(line); line = {};
	line.push_back(x); line.push_back(x); line.push_back(x); line.push_back(e); line.push_back(x); line.push_back(e); line.push_back(x); line.push_back(e); matrix.push_back(line); line = {};
	line.push_back(e); line.push_back(x); line.push_back(e); line.push_back(x); line.push_back(r); line.push_back(x); line.push_back(x); line.push_back(e); matrix.push_back(line); line = {};
	line.push_back(e); line.push_back(e); line.push_back(e); line.push_back(x); line.push_back(x); line.push_back(x); line.push_back(x); line.push_back(e); matrix.push_back(line); line = {};
	line.push_back(e); line.push_back(e); line.push_back(e); line.push_back(e); line.push_back(e); line.push_back(e); line.push_back(e); line.push_back(x); matrix.push_back(line); line = {};
	line.push_back(x); line.push_back(x); line.push_back(x); line.push_back(x); line.push_back(x); line.push_back(x); line.push_back(e); line.push_back(x); matrix.push_back(line); line = {};
}

void showLabyrinth(const vector<vector<Cell>>& matrix, int nrRows, int nrColumns) {
	for (int row = 0; row < nrRows; row++) {
		for (int col = 0; col < nrColumns; col++) {
			cout << matrix[row][col].cellType << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

void aufgabeLosung() {

	// Labyrinth wird generiert
	vector<vector<Cell>> matrix;
	int nrRows = 8, nrColumns = 8;
	generateLabyrinth(matrix);

	// Labyrinth wird gezeigt
	showLabyrinth(matrix, nrRows, nrColumns);

	// Man sucht die Koordinaten des Robotes
	int robotStartRow, robotStartColumn;
	getRobotLocation(robotStartRow, robotStartColumn, nrRows, nrColumns, matrix);

	// Weg wird initialisiert (Am Anfang leer)
	Queue path;

	// Wird gefragt ob es einem Weg gibt und er wird gleichzeitig generiert
	if (findPath(path, robotStartRow, robotStartColumn, nrRows, nrColumns, matrix)) {
		cout << "Es gibt ein Weg um aus der Labyrinth rauszukommen: " << endl;
	}
	else {
		cout << "Es gibt kein Weg!" << endl;
	}

	// Man zeigt das generierte Weg
	while (!path.isEmpty()) {
		TElem cell = path.pop();
		cout << cell.row << ' ' << cell.column << endl;
	}
}