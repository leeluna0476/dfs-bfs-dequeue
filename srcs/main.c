#include <stdio.h>
#include <stdlib.h>
#include "search.h"

int main(void) {
	int n, m; // for n*m map
	scanf("%d %d", &n, &m);

	char **map = alloc_map(n, m);

	read_map(map, n, m);
	printf("starting point=%c\nwall=%c\npath=%c\ndestination=%c\npassed=%c\n", START, WALL, PATH, DEST, PASSED);
	printf("searching order: %s\n\n", DIRECTION_STR);
	printf("=====The Maze=====\n");
	print_map(map, n, m);

	char **path_dfs = dfs(map, n, m);
	printf("\n=====After DFS=====\n");
	print_map(path_dfs, n, m);

	char **path_bfs = bfs(map, n, m);
	printf("\n=====After BFS=====\n");
	print_map(path_bfs, n, m);

	free_map(path_dfs, n);
	free_map(path_bfs, n);
	free_map(map, n);
}
