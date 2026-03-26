#ifndef SEARCH_H
# define SEARCH_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include "types.h"

# include "dequeue.h"

# define START 'O'
# define WALL 'x'
# define PATH 'o'
# define DEST 'X'
# define PASSED '@'

# define UP { 0, -1 }
# define DOWN { 0, 1 }
# define LEFT { -1, 0 }
# define RIGHT { 1, 0 }

# ifndef DIRECTION
#  define DIRECTION { UP, DOWN, LEFT, RIGHT }
# endif

# ifndef DIRECTION_STR
#  define DIRECTION_STR "UP->DOWN->LEFT->RIGHT"
# endif

#define MAGENTA "\x1b[45m"
#define CYAN "\x1b[46m"
#define RESET "\x1b[0m"

char **alloc_map(int n, int m);
char **copy_map(char **map, int n, int m);
void free_map(char **map, int n);
void read_map(char **map, int n, int m);
void print_map(char **map, int n, int m);
pos_t search_starting_point(char **map, int n, int m);
int in_range(pos_t pos, int n, int m);

char **dfs(char **map, int n, int m);
char **bfs(char **map, int n, int m);

#endif
