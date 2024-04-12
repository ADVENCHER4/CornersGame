#pragma once
#define MAX_DISTANCE 12
#define FIELD_SIZE 8
#define DECK_SIZE 536
#define WINDOW_HEIGHT 636
#define EDGE_SIZE 20
#define CELL_SIZE 62
#define CHECKERS_COUNT 9
#define LOSE_MOVES_COUNT 10 * CHECKERS_COUNT
#define DEPTH 9

const int BOTTOM_CORNER[CHECKERS_COUNT][2] = { {0, 7}, {0, 6}, {0, 5}, {1, 7}, {1, 6}, {1, 5}, {2, 7}, {2, 6}, {2, 5} };
const int TOP_CORNER[CHECKERS_COUNT][2] = { {7, 0}, {6, 0}, {5, 0}, {7, 1}, {6, 1}, {5, 1}, {7, 2}, {6, 2}, {5, 2} };
