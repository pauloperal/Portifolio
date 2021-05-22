#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 0
#define FULL 1
#define INVALID_NULL_POINTER -1
#define OUT_OF_MEMORY -2
#define EMPTY -3
#define MAXST 1000

typedef struct stackInt Stack;

Stack *create_stack();
int free_stack(Stack *st);
int push_stack(Stack *st, int val);
int pop_stack(Stack *st);
int top_stack(Stack *st, int *val);
int size_stack(Stack *st);
void print_stack(Stack *st);
