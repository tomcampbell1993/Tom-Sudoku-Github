#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/* This change better show up in master */

struct cell {

	int x;
	int y;
	int value;
} cells[81];

void insertCoordinates() {

	int oneToNine;
	oneToNine = 1;

	int yNumber;
	yNumber = 1;

	int yCounter;
	yCounter = 1;

	for (int i = 0; i < 81; i++) {

		cells[i].x = oneToNine;
		oneToNine++;
		if (oneToNine == 10) {
			oneToNine = 1;
		}

		cells[i].y = yNumber;
		yCounter++;
		if (yCounter > 9) {
			yNumber = yNumber + 1;
			yCounter = 1;
		}
	}
}

void insertZeroValues() {

	for (int i = 0; i < 81; i++) {
		cells[i].value = 0;
	}
}

void listCoordinates() {

	for (int i = 0; i < 81; i++) {

		cout << cells[i].x << "," << cells[i].y << endl;
	}
}

void printCoordinates() {

	int yNumber;
	yNumber = 10;

	for (int i = 0; i < 9; i++) {

		yNumber = yNumber - 1;

		for (int i = 0; i < 81; i++) {

			if (cells[i].y == yNumber) {
				cout << " " << cells[i].x << "," << cells[i].y;
			}
		}
		cout << endl;
	}
}

void printSudoku() {

	int yNumber;
	yNumber = 10;

	for (int i = 0; i < 9; i++) {

		yNumber = yNumber - 1;

		for (int i = 0; i < 81; i++) {

			if (cells[i].y == yNumber) {
				cout << " " << cells[i].value;
			}
		}
		cout << endl;
	}
}

void setCellValue(int x, int y, int newValue) {

	cout << "Cell at coordinates " << x << "," << y << " set to value " << newValue << endl;

	for (int i = 0; i < 81; i++) {
		if (cells[i].x == x && cells[i].y == y) {
			cells[i].value = newValue;
		}
	}
}

int insertX() {
	int x;
	cout << "insert X coord: " << endl;
	cin >> x;

	if (x > 9 || x < 1) {
		cout << "Must be a value between 1 and 9!" << endl;
		cout << "Try again: " << endl;
	}
	return x;
}

int insertY() {
	int y;
	cout << "insert Y coord: " << endl;
	cin >> y;

	if (y > 9 || y < 1) {
		cout << "Must be a value between 1 and 9!" << endl;
		cout << "Try again: " << endl;
	}

	return y;
}

int insertValue() {
	int v;
	cout << "insert Value: " << endl;
	cin >> v;
	return v;
}

void manualInsert() {

	int x = insertX();
	int y = insertY();
	int v = insertValue();

	setCellValue(x, y, v);
}

void checkRow(int x) {

	int searchNumber = 1;
	int duplicates = 0;
	int errors = 0;

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 81; j++) {
			if (cells[j].y == x && cells[j].value == searchNumber) {
				duplicates = duplicates + 1;

				if (duplicates > 1) {
					cout << duplicates << " Duplicates of number " << searchNumber << " found on row " << x << endl;
					errors = errors + 1;
				}
			}
		}

		searchNumber = searchNumber + 1;
		duplicates = 0;
	}

	for (int k = 0; k < 81; k++) {
		if (cells[k].y == x && cells[k].value == 0) {
			errors = errors + 1;
			cout << "Empty Cell found" << endl;
		}
	}

	cout << errors << " Errors found on row " << x << endl;

}

void checkColumn(int x) {

	int searchNumber = 1;
	int duplicates = 0;
	int errors = 0;

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 81; j++) {
			if (cells[j].x == x && cells[j].value == searchNumber) {
				duplicates = duplicates + 1;

				if (duplicates > 1) {
					cout << duplicates << " Duplicates of number " << searchNumber << " found on Column " << x << endl;
					errors = errors + 1;
				}
			}
		}

		searchNumber = searchNumber + 1;
		duplicates = 0;
	}

	for (int k = 0; k < 81; k++) {
		if (cells[k].x == x && cells[k].value == 0) {
			errors = errors + 1;
			cout << "Empty Cell found" << endl;
		}
	}

	cout << errors << " Errors found on Column " << x << endl;

}

void checkAllRowsAndColumns() {

	for (int i = 1; i < 10; i++) {
		checkRow(i);
		checkColumn(i);
	}

}

void importFile(string fileName) {

	cout << "Importing file with filename: " << fileName << endl;

	string line;
	ifstream importFile(fileName);
	if (importFile.is_open()) {

		while (getline(importFile, line)) {
			cout << line << endl;
			string sx, sy, sz;
			sx = line[0];
			sy = line[1];
			sz = line[2];

			int x, y, z;
			x = stoi(sx);
			y = stoi(sy);
			z = stoi(sz);

			setCellValue(x, y, z);
		}
		importFile.close();
	}
	else {
		cout << "failed to import file :( " << endl;
	}

}

void navigation() {

	cout << "To print the soduko enter the value '1' " << endl;
	cout << "To enter a value into a cell, enter the value '2' " << endl;
	cout << "To check a row, enter the value '3' " << endl;
	cout << "To check a column, enter the value '4' " << endl;
	cout << "To check all rows and columns, enter the value '5' " << endl;
	cout << "To Import a text file, enter the value '6' " << endl;
	cout << "To exit enter any other value " << endl;

	int x;
	cin >> x;

	if (x == 1) {

		cout << "Current Sudoku: " << endl;
		printSudoku();
		cout << endl;
		navigation();
	}

	if (x == 2) {
		manualInsert();
		cout << endl;
		navigation();
	}

	if (x == 3) {
		cout << "Enter the row number to check:" << endl;
		int rowNumber;
		cin >> rowNumber;
		checkRow(rowNumber);
		cout << endl;
		navigation();
	}

	if (x == 4) {
		cout << "Enter the column number to check:" << endl;
		int columnNumber;
		cin >> columnNumber;
		checkColumn(columnNumber);
		cout << endl;
		navigation();
	}

	if (x == 5) {
		cout << "Checking all rows and Columns..." << endl;
		checkAllRowsAndColumns();
		cout << endl;
		cout << "Check complete." << endl;
		navigation();
	}

	if (x == 6) {
		cout << "Text file must be in the form of a list of three integers per line, example: " << endl;
		cout << "123" << endl;
		cout << "123" << endl;
		cout << " Values in order left to right are: X coord, Y coord and cell value" << endl;
		cout << "Type the name of file to import: " << endl;
		string file;
		cin >> file;
		importFile(file);
		navigation();
	}

}



void main() {

	insertZeroValues();
	insertCoordinates();
	//listCoordinates();
	//printCoordinates();

	cout << "Welcome to Toms Improvised Sudoku, enter any value to continue " << endl;

	int cont1;
	cin >> cont1;

	navigation();
	//printSudoku();

	cout << "Enter anything to exit ";

	int exit;
	cin >> exit;

}