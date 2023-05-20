#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <Windows.h>

void begin(int rows, int columns);
char* create(int rows, int columns);
double getRandomBoubleInRange(double min, double max);
void display(int rows, int columns, char* simulation);
int coutNeighborhood(int rows, int columns, int x, int y, char* simulation);
char* step(int rows, int columns, char* prevSimulation);


int main(int argc, char* argv[])
{
	int rows, columns;
	printf("Enter rows: \n");
	scanf("%d", &rows);
	if (rows <= 0) {
		printf("Row count must be greater than zero! Was %d\n", rows);
		return -1;
	}
	rows += 2;
	printf("Enter columns: \n");
	scanf("%d", &columns);

	if (columns <= 0) {
		printf("Column count must be greater than zero! Was %d\n", columns);
		return -1;
	}
	columns += 2;
	begin(rows, columns);
}

void display(int rows, int columns, char* simulation) {
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	for (int y = 1; y < rows-1; y++) {

		for (int x = 1; x < columns-1; x++) {
			printf("%c ", *(simulation + y * columns + x));
		}
		printf("\n");
	}
}

int coutNeighborhood(int rows, int columns, int x, int y, char* simulation) {
	int count = 0;
	int pivot = y * columns + x;
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			char c = *(simulation + pivot+(i * columns) + j);
			if (c == '#') count++;
		}
	}
	return count;
}
char* step(int rows, int columns, char* prevSimulation) {
	char* steppedSimulation = calloc(rows * columns, sizeof(int));
	if (steppedSimulation == NULL) return NULL;
	for (int y = 1; y < rows - 1; y++) {
		for (int x = 1; x < columns - 1; x++) {
			int live = coutNeighborhood(rows, columns, x, y, prevSimulation);
			char cell = *(prevSimulation + y * columns + x);
			if (cell == '#') live--;
			*(steppedSimulation + y * columns + x) = cell;
			if (live < 2)
			{
				*(steppedSimulation + y * columns + x) = '.';
			}
			else if ((live == 2 || live == 3) && cell == '#') {
				*(steppedSimulation+y*columns+x) = '#';
			}
			else if (live > 3 && cell == '#') {
				*(steppedSimulation + y * columns + x) = '.';
			}
			else if (live == 3 && cell == '.') {
				*(steppedSimulation + y * columns + x) = '#';
			}
		}
	}
	return steppedSimulation;
}

void begin(int rows, int columns) {
	char* simulation = create(rows, columns);
	if (simulation == NULL) return;
	display(rows, columns, simulation);

	while (1) {
		char* newsim = step(rows, columns, simulation);
		if (newsim == NULL) return;
		free(simulation);
		simulation = newsim;
		display(rows, columns, simulation);
		Sleep(1000);
	}
}

double getRandomBoubleInRange(double min, double max) {
	return ((double)rand() / RAND_MAX)* (max - min) + min;
}

char* create(int rows, int columns) {
	char* simulation = (char*)malloc(rows * columns* sizeof(char));
	if (simulation == NULL) return NULL;
	for (int y = 1; y < rows-1; y++) {
		for (int x = 1; x < columns-1; x++) {
			if (getRandomBoubleInRange(0.0, 1.0) <= 0.35) {
				*(simulation + y * columns + x) = '#';
			}
			else
			{
				*(simulation + y * columns + x) = '.';
			}
		}
	}
	return simulation;
}

