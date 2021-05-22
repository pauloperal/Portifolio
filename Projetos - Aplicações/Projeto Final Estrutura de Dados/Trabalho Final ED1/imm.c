#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "TADimm.h"

//Graduação em Sistemas da Informação - Universidade Federal de Uberlândia
//Paulo Ponciano Peral Filho
//Paulo Henrique Alves Santos
//Guilherme Ferreira Santa Cecília 

int main(int argc, char *argv[]){
    int thr = 0, opc=0;
    int verification;
    TMat2D *mt;

    if(strcmp("-open", argv[1]) == 0){
       opc = 1;
    }
    else if(strcmp("-convert", argv[1]) == 0){
        opc = 2;
    }
    else if(strcmp("-segment", argv[1]) == 0){
        opc = 3;
    }
    else if(strcmp("-cc", argv[1]) == 0){
        opc = 4;
    }
    else if(strcmp("-lab", argv[1]) == 0){
        opc = 5;
    }
    else{
        opc = 9;
    }


    switch(opc){

        case 1:
            mt = only_open(argv[2]);
            verification = print_img(mt, OPEN, NULL);

            if(verification != 0)
                printf("Erro!\n");
            else
                printf("Sucesso!\n");

        break;

        case 2:
            verification = Fconvert(argv[2],argv[3]);

                if(verification != 0)
                    printf("Erro na Conversão!\n");
                else
                    printf("Sucesso!\n");
        break;

        case 3:
            thr = atoi(argv[2]);
            verification = Fsegment(argv[3],argv[4],thr);

            if(verification != 0)
                printf("Erro na Segmentação\n");
            else
                printf("Sucesso!\n");
        break;

        case 4:
            verification = Fcc(argv[2],argv[3]);

           if(verification != 0)
                printf("Erro!\n");
            else
                printf("Sucesso!\n");
        break;

        case 5:
            verification = Flab(argv[2],argv[3]);
            
            if(verification != 0){
                if(verification == LAB_EXIT){
                    printf("Oh não! Saída não Encontrada, its a TRAP");
                }
                printf("Erro no Labirinto!");
            }else
                printf("Sucesso!");
                
        break;

        default:
            printf("Erro, comando não encontrado!");
        break;
    }

    return 0;
}