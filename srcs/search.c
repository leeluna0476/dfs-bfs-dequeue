#include "search.h"

char **alloc_map(int n, int m) {
	char **map = (char **)malloc(sizeof(char *) * n);
	for (int i = 0; i < n; ++i) {
		map[i] = (char *)malloc(sizeof(char) * m);
	}
	return map;
}

char **copy_map(char **map, int n, int m) {
	char **map_copy = alloc_map(n, m);
	for (int i = 0; i < n; ++i) {
		memcpy(map_copy[i], map[i], sizeof(char) * m);
	}
	return map_copy;
}

void free_map(char **map, int n) {
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
			switch (map[i][j]) {
				case '@':
					printf("%s%c%s", MAGENTA, map[i][j], RESET);
					break;
				case 'O': case 'X':
					printf("%s%c%s", CYAN, map[i][j], RESET);
					break;
				default:
					putchar(map[i][j]);
			}
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

char **dfs(char **map, int n, int m) {
	char **map_copy = copy_map(map, n, m);

	dequeue_t stk;
	init(&stk);

	int diff[4][2] = DIRECTION;
	pos_t start = search_starting_point(map_copy, n, m);
	pos_t pos = start;
	if (pos.x != -1) {
		add_back(&stk, pos);
	}

	printf("\n=====DFS=====\n");
	while (!is_empty(&stk)) {
		pos = delete_back(&stk);
		printf("(%d, %d)\n", pos.y, pos.x);
		if (map_copy[pos.y][pos.x] == DEST) {
			break;
		}
		// if pushed more than twice and already marked as passed
		else if (map_copy[pos.y][pos.x] != PASSED) {
			map_copy[pos.y][pos.x] = PASSED;
			for (int i = 0; i < 4; ++i) { // search from up->down->left->right
				pos_t new_pos = { pos.x + diff[i][0], pos.y + diff[i][1] };
				if (in_range(new_pos, n, m) &&
						(map_copy[new_pos.y][new_pos.x] == PATH || map_copy[new_pos.y][new_pos.x] == DEST)) {
					add_back(&stk, new_pos);
				}
			}
		}
	}

	destroy(&stk);

	map_copy[start.y][start.x] = 'O';
	return map_copy;
}

char **bfs(char **map, int n, int m) {
	char **map_copy = copy_map(map, n, m);
	dequeue_t q;
	init(&q);

	int diff[4][2] = DIRECTION;
	pos_t start = search_starting_point(map_copy, n, m);
	pos_t pos = start;
	if (pos.x != -1) {
		add_back(&q, pos);
	}

	printf("\n=====BFS=====\n");
	while (!is_empty(&q)) {
		pos = delete_front(&q);
		printf("(%d, %d)\n", pos.y, pos.x);
		if (map_copy[pos.y][pos.x] == DEST) {
			break;
		}
		else if (map_copy[pos.y][pos.x] != PASSED) {
			map_copy[pos.y][pos.x] = PASSED;
			for (int i = 0; i < 4; ++i) { // search from up->down->left->right
				pos_t new_pos = { pos.x + diff[i][0], pos.y + diff[i][1] };
				if (in_range(new_pos, n, m) &&
						(map_copy[new_pos.y][new_pos.x] == PATH || map_copy[new_pos.y][new_pos.x] == DEST)) {
					add_back(&q, new_pos);
				}
			}
		}
	}

	destroy(&q);

	map_copy[start.y][start.x] = 'O';
	return map_copy;
}
