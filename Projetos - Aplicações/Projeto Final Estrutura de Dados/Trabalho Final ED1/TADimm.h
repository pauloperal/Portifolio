#ifndef TADimmh
#define TADimmh

#define SUCCESS 0
#define ERROR -1
#define INVALID_TYPE -2
#define TXT 1
#define BIN 2
#define OPEN 3
#define CONV 4
#define SEG 5
#define LAB 6
#define LAB_EXIT 7
#define MAX 1000

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "tad.h"
#include "stackInt.h"

typedef struct ponto Ponto;

int open_print(char name_in[]);
TMat2D *only_open(char name_in[]);
int print_img(TMat2D *mt, int opc, char name_out[]);
int Fconvert(char name_in[], char name_out[]);
int Fsegment(char name_in[], char name_out[], int thr);
int Fcc(char name_in[], char name_out[]);
int Flab(char name_in[], char name_out[]);
int reverseString(char name_in[]);

#endif