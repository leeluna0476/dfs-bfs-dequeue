#include <stdio.h>
#include <stdlib.h>

typedef struct pos {
	int x;
	int y;
} pos_t;

#define START 'O'
#define WALL 'x'
#define PATH 'o'
#define DEST 'X'
#define PASSED '@'

#define UP { 0, -1 }
#define DOWN { 0, 1 }
#define LEFT { -1, 0 }
#define RIGHT { 1, 0 }

typedef struct stack {
	pos_t *storage;
	int top;
	int max;
} stk_t;

void error(char *errmsg);
void init_stack(stk_t *stk, int max_elements);
void destroy_stack(stk_t *stk);
int is_empty(stk_t *stk);
int is_full(stk_t *stk);
void push(stk_t *stk, pos_t val);
pos_t pop(stk_t *stk);
pos_t peek(stk_t *stk);

char **alloc_map(int n, int m);
void free_map(char **map, int n, int m);

void read_map(char **map, int n, int m);
void print_map(char **map, int n, int m);

pos_t search_starting_point(char **map, int n, int m);
int in_range(pos_t pos, int n, int m);
pos_t dfs(char **map, int n, int m);

int main(void) {
	int n, m; // for n*m map
	scanf("%d %d", &n, &m);

	char **map = alloc_map(n, m);

	read_map(map, n, m);
	printf("starting point=%c\nwall=%c\npath=%c\ndestination=%c\npassed=%c\n\n", START, WALL, PATH, DEST, PASSED);
	printf("=====The Maze=====\n");
	print_map(map, n, m);

	pos_t exit = dfs(map, n, m);
	printf("\n=====After DFS=====\n");
	if (exit.x == -1) {
		printf("No solution\n");
	}
	else {
		print_map(map, n, m);
	}

	free_map(map, n, m);
}

void error(char *errmsg) {
	fprintf(stderr, "%s", errmsg);
	exit(1);
}

void init_stack(stk_t *stk, int max_elements) {
	// not considering pop
	// every element pushed by its neighbors => 4 * elements_#
	// n*m elements, time complexity=O(n*m)
	stk->storage = (pos_t *)malloc(sizeof(pos_t) * max_elements * 4);
	stk->top = -1;
	stk->max = max_elements * 4;
}

void destroy_stack(stk_t *stk) {
	free(stk->storage);
}

int is_empty(stk_t *stk) {
	return stk->top == -1;
}

int is_full(stk_t *stk) {
	return stk->top + 1 == stk->max;
}

void push(stk_t *stk, pos_t val) {
	if (is_full(stk)) {
		error("Overflow\n");
	}
	else {
		stk->storage[++stk->top] = val;
	}
}

pos_t pop(stk_t *stk) {
	if (is_empty(stk)) {
		error("Underflow\n");
	}
	else {
		return stk->storage[stk->top--];
	}
}

pos_t peek(stk_t *stk) {
	if (is_empty(stk)) {
		error("Underflow\n");
	}
	else {
		return stk->storage[stk->top];
	}
}

char **alloc_map(int n, int m) {
	char **map = (char **)malloc(sizeof(char *) * n);
	for (int i = 0; i < n; ++i) {
		map[i] = (char *)malloc(sizeof(char) * m);
	}
	return map;
}

void free_map(char **map, int n, int m) {
	for (int i = 0; i < n; ++i) {
		free(map[i]);
	}
	free(map);
}

void read_map(char **map, int n, int m) {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			scanf(" %c", &map[i][j]);
		}
	}
}

void print_map(char **map, int n, int m) {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			putchar(map[i][j]);
		}
		putchar('\n');
	}
}

pos_t search_starting_point(char **map, int n, int m) {
	pos_t pos = { -1, -1 };
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (map[i][j] == START) {
				pos.x = j;
				pos.y = i;
				return pos;
			}
		}
	}
	return pos;
}

int in_range(pos_t pos, int n, int m) {
	return pos.x >= 0 && pos.x < m && pos.y >= 0 && pos.y < n;
}

pos_t dfs(char **map, int n, int m) {
	stk_t stk;
	init_stack(&stk, n * m);

	int diff[4][2] = { UP, DOWN, LEFT, RIGHT };
	pos_t pos = search_starting_point(map, n, m);
	if (pos.x != -1) {
		push(&stk, pos);
	}

	pos_t exit = { -1, -1 };
	printf("\n=====DFS=====\n");
	while (!is_empty(&stk)) {
		pos = pop(&stk);
		printf("(%d, %d)\n", pos.y, pos.x);
		if (map[pos.y][pos.x] == DEST) {
			exit = pos;
			break;
		}
		// if pushed more than twice and already marked as passed
		else if (map[pos.y][pos.x] != PASSED) {
			map[pos.y][pos.x] = PASSED;
			for (int i = 0; i < 4; ++i) { // search from up->down->left->right
				pos_t new_pos = { pos.x + diff[i][0], pos.y + diff[i][1] };
				if (in_range(new_pos, n, m) &&
						(map[new_pos.y][new_pos.x] == PATH || map[new_pos.y][new_pos.x] == DEST)) {
					push(&stk, new_pos);
				}
			}
		}
	}

	destroy_stack(&stk);
	return exit;
}
