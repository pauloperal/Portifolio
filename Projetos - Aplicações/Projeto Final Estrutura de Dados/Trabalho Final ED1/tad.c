#include "tad.h"
#include <stdio.h>

struct TMat2D{
  int nLinhas;
  int nColunas;
  int *data;
};

//-----------CRIAR MATRIZ----------------------------------------
TMat2D *mat2D_create(int nLinhas, int nColunas){
 if(nLinhas <= 0 || nColunas <=0){
    return NULL;
  }

  TMat2D *mat;
  mat = malloc(sizeof(TMat2D));
  if(mat == NULL){
    return NULL;
  }

  TMat2D *dados;
  mat->data = malloc(nLinhas*nColunas*sizeof(int));
  if(mat->data == NULL){
    free(mat);
    return NULL;
  }

  mat->nLinhas = nLinhas;
  mat->nColunas = nColunas; 

  return mat;
}

//------------SETAR VALOR-------------------------------------
int mat2D_set_value(TMat2D *mat, int i, int j, int val){
   int posicao;
    posicao = j*(mat->nLinhas)+i;
   int aux = mat->data[posicao];
    mat->data[posicao] = val;

   if(aux != mat->data[posicao]){
     return 0;
   }else{
     return (-1);
   }
}

//---------------PEGAR VALOR------------------------------------
int mat2D_get_value(TMat2D *mat, int i, int j, int *val){
  int posicao, aux;
  posicao = j*mat->nLinhas+i;

  *val = mat->data[posicao]; 
  aux = mat->data[posicao];
   
  if(aux == mat->data[posicao]){
     return 0;
   }else{
     return (-1);
   }
}

//----------------------RANDOMIZAR-------------------------------
int mat2D_randomize_number(TMat2D *mat){
   int i, tamanho;

   tamanho = mat->nLinhas * mat->nColunas;
   srand(time(NULL));

   for(i=0; i<=tamanho; i++){
     mat->data[i] = (int) (rand() % 100);
   } 

  return 0;
}

//-----------------------SOMAR-----------------------------------
int mat2D_add(TMat2D *pont, TMat2D *pont2, TMat2D *pont3, int lin, int col){
   int tamanho;
   tamanho = (lin*col);

   if(pont->nLinhas != lin || pont->nColunas != col){
    return -1;
   }
   else{
    for(int k=0; k<tamanho; k++){
      pont3->data[k] = pont->data[k] + pont2->data[k];
    }
   return 0;
   }
}
//--------------ESCALAR-------------------------------------------
int mat2D_escalar(TMat2D *mat, int escalar){
   int tamanho, aux, aux2;
   tamanho = mat->nLinhas*mat->nColunas;

   for(int i=0; i<tamanho; i++){
     aux = mat->data[i];
     mat->data[i] = mat->data[i]*escalar;

     if(aux != mat->data[i]){
      aux2 = 0;
     }else{
       aux2 = 1;
     }
   }

  if(aux2 == 0){
    return 0;
  }else{
    return (-1);
  }
}

//----------------FREE---------------------------------------------
int mat2D_free(TMat2D *mat){
  free(mat->data);
  free(mat);
  if(mat->data == NULL){
    return 0;
  }else{
    return (-1);
  }
}

//----------------------------------------------------------------------
int mat2D_prenencher(TMat2D *pont, int valor, int k){
     pont->data[k] = valor;
  if(pont->data[k] != valor){
    return  (-1);
  }else{
    return 0;
  }
}

//--------------Multiplying----------------------------------------------------
int mat2D_multiplying(int lin, int col, TMat2D *pont, TMat2D *pont2, TMat2D *pont3){
   if(pont->nColunas != lin){
     return (-1);
   }else{
     
     return 0;
   }
}

//-------------Add-Colunas--------------------------------------
int *mat2D_add_colunas(TMat2D *mat){
  int aux=0, aux2=0, i=0;
  int *vet;
  vet =(int *)calloc(mat->nColunas,sizeof(int));

  if(vet == NULL){
    return  NULL;
  }else{
    aux = mat->nColunas;
    for(int k=0; k<(mat->nLinhas); k++){
      for(int l=aux2; l<aux; l++){
        vet[k] += mat->data[i];
        i++;
      }
      aux2 = aux;
      aux += mat->nColunas;
    }

    return vet;
  }
}

//-----------Traco------------------------------------
int *mat2D_traco(TMat2D *mat, int *aux){
  int *vet;
   vet =(int *)calloc(mat->nLinhas,sizeof(int));  
   if(vet == NULL){
    return  NULL;
   }
   if(mat->nColunas != mat->nLinhas){
    *aux = -1;
   }else{
    int aux2 = 0;
        for(int k=0; k<(mat->nLinhas); k++){
          vet[k] += mat->data[aux2];
          aux2 += mat->nLinhas+1;
        }
      *aux = 0; 
   }
  return vet;
}

//-------------Add-Linhas----------------------------------------
int *mat2D_add_linhas(TMat2D *mat){
   int aux=0, aux2=0, i=0;
   int *vet;
   vet =(int *)calloc(mat->nLinhas,sizeof(int));  
   if(vet == NULL){
    return  NULL;
   }else{
    aux = mat->nColunas;
      for(int k=0; k<(mat->nLinhas); k++){
        for(int l=aux2; l<aux; l++){
          vet[k] += mat->data[i];
          i += mat->nLinhas+1;
        }
        aux2 =aux;
        aux += mat->nColunas;
        i = aux;
      }
    return vet;
   }
}

//-------------Get-Info----------------------------------------
int mat2D_GetInfo(TMat2D *mat, int *rows, int *cols){
    
  *cols = mat->nColunas;
  *rows = mat->nLinhas;

  return 0;
}

//-------------Get-Max----------------------------------------
int mat2D_GetMax(TMat2D *mat, int *max){

    int aux=0, aux2=0, i=0;
    while(aux != (mat->nLinhas * mat->nColunas)){

      if(mat->data[i] > aux2){
        aux2 = mat->data[i];
      }

      i++;
    } 
    *max = aux2;

  return 0;
}

//-------------Copy-Mat----------------------------------------
void mat2D_copyMat(TMat2D *mat1, TMat2D *mat2){
  mat2->nColunas = mat1->nColunas;
  mat2->nLinhas = mat1->nLinhas;

  int tamanho, aux=0;
  tamanho = mat1->nLinhas * mat1->nColunas;

  while(aux != tamanho){
    mat2->data[aux] = mat1->data[aux];
    aux++;
  }

  return;
}

//-------------Print-Matriz----------------------------------------
void print_matriz(TMat2D *mat){
    int pos;
    for(int i=0; i<mat->nLinhas; i++){
      for(int j=0; j<mat->nColunas; j++){
        pos = j*mat->nLinhas+i;
        printf("%d ", mat->data[pos]);
      }
      printf("\n");
    }
    return;
}