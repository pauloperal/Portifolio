#include "stackInt.h"

struct stackInt{
    int data[MAXST];
    int size;
};

//------------------CREATE--------------------------------
Stack *create_stack(){

    Stack *st;
    st = malloc(sizeof(Stack));

    if(st != NULL){
        st->size = 0;
    }
    
    return st;
}

//------------------PUSH---------------------------------
int push_stack(Stack *st, int val){
    if(st == NULL){
        return INVALID_NULL_POINTER;
    }else{
        if(st->size == MAXST){
            return OUT_OF_MEMORY;
        }else{
            int i= st->size;

            while(i>0){
                st->data[i] = st->data[i-1];
                i--;
            }

            st->data[0] = val;
            st->size = st->size + 1;
            return SUCCESS;
        }
    }
}

//------------------POP---------------------------------
int pop_stack(Stack *st){
    if(st == NULL){
        return INVALID_NULL_POINTER;
    }else{
        if(st->size == 0){
            return EMPTY;
        }else{
            int i=0;
            while(i <= st->size){
                st->data[i] = st->data[i+1];
                i++;
            }

            st->size--;
            return SUCCESS;
        }
    }
}

//------------------TOP---------------------------------
int top_stack(Stack *st, int *val){
    if(st == NULL){
        return INVALID_NULL_POINTER;
    }else{
        if(st->size == 0){
            return EMPTY;
        }else{
            *val = st->data[0];
            return SUCCESS;
        }
    }
}

//------------------SIZE--------------------------------
int size_stack(Stack *st){
    if(st == NULL){
        return INVALID_NULL_POINTER;
    }else{
        if(st->size == 0){
            return EMPTY;
        }else{
            if(st->size == MAXST){
                return FULL;
            }else{
                return st->size;
            }
        }
    }
}

//------------------FREE-------------------------------
int free_stack(Stack *st){
    if(st == NULL){
        return INVALID_NULL_POINTER;
    }else{
        free(st);
        return SUCCESS;
    }
}

//------------------PRINT-STACK-------------------------------
void print_stack(Stack *st){
  int i=0;
  while(i <= st->size){
    printf("%d ", st->data[i]);
    i++;
  }
  return;
}