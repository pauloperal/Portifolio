#ifndef TMat2Dh
#define TMat2Dh

#include <stdlib.h>
#include <time.h>

typedef struct TMat2D TMat2D;

TMat2D *mat2D_create(int nrows, int ncolumns);
int mat2D_free(TMat2D *mat);
int mat2D_set_value(TMat2D *mat, int i, int j, int val);
int mat2D_get_value(TMat2D *mat, int i, int j, int *val);
int mat2D_randomize_number(TMat2D *mat);
int mat2D_add(TMat2D *pont, TMat2D *pont2, TMat2D *pont3, int lin, int col);
int mat2D_escalar(TMat2D *mat, int escalar);
int mat2D_prenencher(TMat2D *pont,int valor, int k);
int *mat2D_add_colunas(TMat2D *mat);
int *mat2D_add_linhas(TMat2D *mat);
int *mat2D_traco(TMat2D *mat, int *aux);
int mat2D_GetInfo(TMat2D *mat, int *rows, int *cols);
int mat2D_GetMax(TMat2D *mat, int *max);
int mat2D_multiplying(int lin, int col, TMat2D *pont, TMat2D *pont2, TMat2D *pont3);
void mat2D_copyMat(TMat2D *mat1, TMat2D *mat2);
void print_matriz(TMat2D *mat);

#endif