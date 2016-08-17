/* structure.c */

struct node a, *b;		/* incomplete type for 'a' */

struct node {
    int data;
    struct node *next;
};

struct node x, *y;

struct node node;

int node;			/* conflicting types for 'node' */

int foo;

struct foo {
    struct foo *foo;
    int x, y;
};

struct foo {
    int x, y;
};				/* redefinition of 'foo' */

struct foo f();			/* pointer type required for 'f' */

struct foo *g(struct foo *p,
	struct foo q) { }	/* pointer type required for 'q' */
