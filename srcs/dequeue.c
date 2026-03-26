#include "dequeue.h"

void error(char *errmsg) {
	fprintf(stderr, "%s", errmsg);
	exit(1);
}

node_t *create_node(Element data) {
	node_t *n = (node_t *)malloc(sizeof(node_t));
	n->data = data;
	n->flink = NULL;
	n->blink = NULL;
	return n;
}

Element remove_node(node_t *n) {
	Element e = n->data;
	free(n);
	return e;
}

void init(dequeue_t *dq) {
	dq->rear = NULL;
}

int is_empty(dequeue_t *dq) {
	return dq->rear == NULL;
}

// 1. n1<->n2<->n3(rear)<->n1
//    n1<->n2<->n3<->[n4](rear)<->n1
// 2. NULL(rear)
//    [n4](rear)<->n4
void add_back(dequeue_t *dq, Element data) {
	node_t *n = create_node(data);
	if (is_empty(dq)) {
		dq->rear = n;
		n->flink = n;
		n->blink = n;
	}
	else {
		n->flink = dq->rear;
		n->blink = dq->rear->blink;
		dq->rear->blink = n;
		dq->rear = n;
	}
}

// 1. n1<->n2<->n3(rear)<->n1
//    n4<->n1<->n2<->n3(rear)<->n4
// 2. NULL(rear)
//    [n4](rear)<->n4
void add_front(dequeue_t *dq, Element data) {
	node_t *n = create_node(data);
	if (is_empty(dq)) {
		dq->rear = n;
		n->flink = n;
		n->blink = n;
	}
	else {
		n->flink = dq->rear;
		n->blink = dq->rear->blink;
		dq->rear->blink = n;
	}
}

// 1. n1<->n2<->n3(rear)<->n1
//    n1<->n2(rear)<->n1
// 2. n1(rear)<->n1
//    NULL(rear)
Element delete_back(dequeue_t *dq) {
	if (is_empty(dq)) {
		error("Underflow\n");
	}
	else {
		node_t *r = dq->rear;
		r->flink->blink = r->blink;
		r->blink->flink = r->flink;
		dq->rear = r->flink;
		if (r == dq->rear) {
			dq->rear = NULL;
		}
		return remove_node(r);
	}
}

// 1. n1<->n2<->n3(rear)<->n1
//    n2<->n3(rear)<->n2
// 2. n1(rear)<->n1
//    NULL(rear)
Element delete_front(dequeue_t *dq) {
	if (is_empty(dq)) {
		error("Underflow\n");
	}
	else {
		node_t *f = dq->rear->blink;
		dq->rear->blink = f->blink;
		f->blink->flink = dq->rear;
		if (f == dq->rear) {
			dq->rear = NULL;
		}
		return remove_node(f);
	}
}

Element back(dequeue_t *dq) {
	if (is_empty(dq)) {
		error("Underflow\n");
	}
	else {
		return dq->rear->data;
	}
}

Element front(dequeue_t *dq) {
	if (is_empty(dq)) {
		error("Underflow\n");
	}
	else {
		return dq->rear->blink->data;
	}
}

void destroy(dequeue_t *dq) {
	while (!is_empty(dq)) {
		delete_front(dq);
	}
}
