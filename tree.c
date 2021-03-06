
/*
    tree.c - Interface to binary search tree

    -------------------------------------------------------------
    UNSW COMP2521 17s2 Assignment 2 - Yaggle
    (http://www.cse.unsw.edu.au/~cs2521/17s2/ass/ass02/Ass2.html)
    ass2grp (Yaggle) members:
    - Rahil Agrawal (z5165505) rahil.agrawal@student.unsw.edu.au
    - Dennis Gann (z5164328) d.gann@unsw.edu.au
    - Kongwei Ying (z5014882) k.ying@student.unsw.edu.au
    -------------------------------------------------------------

 */


#include "tree.h"
#include "vertexQueue.h"


typedef struct TreeRep {
	struct Vertex *root;
} TreeRep;

static void dropTraversal(Vertex *v);
static Vertex *newVertex(char *str);
static Vertex *findVertex(Vertex *v, char *str);
static void inOrderTraversal(Vertex *v, FILE *fp);
static int findDepth(Vertex *root);
static int vertexKeyCompare(Vertex *v1, Vertex *v2);

Tree newTree() {
	Tree t = malloc(sizeof(struct TreeRep));
	t->root = NULL;

	return t;
}

void dropTree(Tree t) {
	dropTraversal(t->root);
	free(t);
}

static void dropTraversal(Vertex *v) {
	if (v != NULL){
		dropTraversal(v->left);
		dropTraversal(v->right);
		free(v->word);
		dropList(v->urls);
		free(v);
	}
}

void insertIntoTree(Tree t, char *word) {
	// If the word we're trying to insert is already in the tree
	if (findVertex(t->root, word) != NULL){
		return;
	}

	Vertex *new = newVertex(word);
	// pred always trails new
	Vertex *pred = t->root;

	if (pred == NULL){
		t->root = new;
		return;
	}

	while (1){
		// Check which branch pred should go down
		// If new.key < pred.key
		if (vertexKeyCompare(new, pred) < 0){
			// If pred cannot
			if (pred->left == NULL)
				break;
			// If pred can, go down the left branch
			else
				pred = pred->left;
		}
		else
		if (pred->right == NULL)
			break;
		else
			pred = pred->right;

	}

	new->parent = pred;

	if (vertexKeyCompare(new, pred) < 0)
		pred->left = new;
	else
		pred->right = new;
}

// Create a new Vertex for the tree
static Vertex *newVertex(char *str) {
	Vertex *v = malloc(sizeof(struct Vertex));
	v->left = NULL;
	v->right = NULL;
	v->parent = NULL;
	v->word = malloc(sizeof(char) * MAX_CHAR);
	memset(v->word, 0, sizeof(char) * MAX_CHAR);
	v->urls = newList();

	strcpy(v->word, str);

	return v;
}

void addUrl(Tree t, char *word, char *url) {
	Vertex *v = findVertex(t->root, word);

	if (v == NULL){
		fprintf(stderr, "Could not find word '%s' in tree\n", word);
	}
	else {
		// Insert into the vertex's list of urls
		appendList(v->urls, url, 0, 0);
	}
}

static Vertex *findVertex(Vertex *v, char *str) {
	if (v == NULL || strcmp(v->word, str) == 0)
		return v;

	if (strcmp(str, v->word) < 0)
		return findVertex(v->left, str);
	else
		return findVertex(v->right, str);
}

void printInOrder(Tree t, FILE *fp) {
	inOrderTraversal(t->root, fp);
}

static void inOrderTraversal(Vertex *v, FILE *fp) {
	if (v != NULL){
		inOrderTraversal(v->left, fp);
		fprintf(fp, "%s  ", v->word);
		int nNodes = ALL_NODES;
		sortList(v->urls, cmpStr);
		showList(v->urls, fp, ' ', &nNodes);
		inOrderTraversal(v->right, fp);
	}
}

int getDepth(Tree t) {
	// Zero indexed so subtract 1
	return findDepth(t->root) - 1;
}

static int findDepth(Vertex *root) {
	int maxLeftDepth = 0;
	int maxRightDepth = 0;
	if (root == NULL) return 0;

	maxLeftDepth = findDepth(root->left);
	maxRightDepth = findDepth(root->right);

	return (maxLeftDepth >= maxRightDepth) ? maxLeftDepth + 1 : maxRightDepth + 1;
}

static int vertexKeyCompare(Vertex *v1, Vertex *v2) {
	return strcmp(v1->word, v2->word);
}
