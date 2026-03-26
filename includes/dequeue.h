#ifndef DEQUEUE_H
# define DEQUEUE_H

# include <stdlib.h>
# include <stdio.h>
# include "types.h"

typedef struct node {
	Element data;
	struct node *flink;
	struct node *blink;
} node_t;

node_t *create_node(Element data);
Element remove_node(node_t *n);

typedef struct dequeue {
	node_t *rear;
} dequeue_t;

void error(char *errmsg);

void init(dequeue_t *dq);
int is_empty(dequeue_t *dq);
void add_back(dequeue_t *dq, Element data);
void add_front(dequeue_t *dq, Element data);
Element delete_back(dequeue_t *dq);
Element delete_front(dequeue_t *dq);
Element back(dequeue_t *dq);
Element front(dequeue_t *dq);
void destroy(dequeue_t *dq);

#endif
