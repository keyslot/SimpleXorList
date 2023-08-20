/*
 *  simple xor list
 *  author: raulantonio@protonmail.com
 *
 *  Example program of XOR of memory addresses. Please use with precaution.
 *  Advantages: Less memory used by a pointer (8bytes approx) for each node. Instead of doubly linked lists.
 *  Disadvantages: Calculation of an xor for each node visited.
 *
 *  Recommended reading: https://www.linuxjournal.com/article/6828
 *
 */
#include <stdio.h>
#include <stdlib.h>
/* Macro xoring to address  (ptr_a ^ ptr_b) return a void address */
#define XOR(ptr_a,ptr_b)({ (void *)((unsigned long) ptr_a ^ (unsigned long) ptr_b); })

struct Node { 
	int value;
	struct Node *next;
};
/* More easy when you have these address */
struct List {
	struct Node *head;
	struct Node *tail;
};

struct List *
newList(void)
{
	struct List *l = (struct List*)malloc(sizeof(struct List));
	l->head = l->tail = NULL;
	return l;
}

struct Node *
newNode(int value) {
	struct Node *n = (struct Node*)malloc(sizeof(struct Node));
	n->value = value;
	n->next = NULL;
	return n;
}

struct List *
append(struct List *l,int value) {
	struct Node *n = newNode(value);
	/* Avoid xor with null values */
	n->next = l->tail;
	if(!l->head) 
		l->head = n;
	else
		l->tail->next = (struct Node*)XOR(n, l->tail->next);  
	l->tail = n;
	return l;
}

struct List *
destroyList(struct List *l) 
{
	struct Node *next = NULL;
	struct Node *prev = NULL;
	struct Node *current = l->head;
	while (current) {
	        printf("Pointer \t Address %p, value = %d\n",current,current->value);
		next = (struct Node*)XOR(prev,current->next);
		prev = current;
		free(current);
		current = NULL;
		current = next;

	}
	free(l);
	return NULL;
}

void 
fromTail(struct List  *l) 
{
        struct Node *current= l->tail;
	struct Node *prev = NULL;
	struct Node *next = NULL;
        while (current) {
	      printf("Pointer from tail \t Address %p, value = %d\n",current,current->value);
	      prev = (struct Node*)XOR(current->next,next);
	      next = current;
	      current = prev;
	}
}

int main(void) {
	struct List *l = newList();
	int i = 0;
	for(; i < 10; i++) 
 	      l = append(l,i);
	
	fromTail(l);
	l = destroyList(l);
	return 0;
}


