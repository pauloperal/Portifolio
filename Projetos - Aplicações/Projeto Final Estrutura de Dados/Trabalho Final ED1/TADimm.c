#include "TADimm.h"

struct ponto{
    int x;
    int y;
};

struct lista{
  int qtd;
  int pixels;
};

//----------------------REVERSE-STRING----------------------------------------
int reverseString(char str_in[]){
    char in[100], out[100];
    int i, j ,cont = 0;

    strcpy(in, str_in);
    
    j = strlen(in);

    cont = j-1;
    for(i =1; i<=j; i++){
        out[cont] = in[i];
        cont--;
    }

    for(int i=0; i<=4; i++){
        if(out[i] == '\n'){
                i++;
        }
        if(out[i] == 't'){
                return TXT;
        }
        else if(out[i] == 'm'){
                return BIN;
        }
    }
    return SUCCESS;
}

//----------------------ONLY-OPEN----------------------------------------
TMat2D *only_open(char name_in[]){
    int txt_or_bin, aux2;
    char charAux, aux, aux3[4];
    TMat2D *mt;
    FILE *img;

    txt_or_bin = reverseString(name_in);
        if(txt_or_bin == TXT){
            img = fopen(name_in, "r");
        }
        else if(txt_or_bin == BIN){
            img = fopen(name_in, "rb");
        }
        else{
            fclose(img);
            return NULL;
        }

    if(img == NULL){
        fclose(img);
        return NULL;
    }

    int rows=0, cols=0, max=0;
    int val;
    if(txt_or_bin == BIN){
        fread(&rows, sizeof(int), 1 , img);
        fread(&cols, sizeof(int), 1 , img);
        mt = mat2D_create(rows, cols);

        if(mt == NULL){
            return NULL;
        }

        for(int i=0; i<rows; i++){
            for(int j=0; j<cols; j++){

                fread(&val, sizeof(int), 1, img);
                mat2D_set_value(mt, i, j, val);
            }
        }
        return mt;
    }
    while((charAux = fgetc(img)) != EOF){
        if(charAux == '\n'){
            rows++;
        }
        if(charAux == 9 && rows <1){
            cols++;
        }
    }

    rows = rows+1;
    cols = cols+1;

    mt = mat2D_create(rows, cols);

    if(mt == NULL){
        return NULL;
    }

    //printf("linhas = %d\n", rows);
    //printf("Colunas = %d\n", cols);

    rewind(img);//voltar para o inicio do arquivo

    int auxSet;
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            fscanf(img, "%d", &aux2);
            auxSet =  mat2D_set_value(mt, i, j, aux2);
            if(aux2 > max){
                max = aux2;
            }
        }
    }

    //printf("Valor maximo  = %d\n", max);

    fclose(img);
    return mt;
}

//----------------------CONVERT----------------------------------------
int Fconvert(char name_in[], char name_out[]){

    int  aux;

    TMat2D *mt;
    mt = only_open(name_in);
    
    aux = print_img(mt, CONV, name_out);

    if(aux != SUCCESS){
        return ERROR;
    }

    return SUCCESS;
}


//----------------------SEGMENT----------------------------------------
int Fsegment(char name_in[], char name_out[], int thr){

    TMat2D *mt;
    mt = only_open(name_in);

    int rows, cols;
    mat2D_GetInfo(mt, &rows, &cols);

    int aux=0;
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            mat2D_get_value(mt, i, j, &aux);
            if(aux >= thr){
                mat2D_set_value(mt, i, j, 1);
            }else{
                 mat2D_set_value(mt, i, j, 0);
            }
        }
    }

    aux = print_img(mt, SEG, name_out);

    if(aux != SUCCESS){
        return ERROR;
    }

    return SUCCESS;
}

//----------------------PRINT-IMG----------------------------------------
int print_img(TMat2D *mt, int opc, char name_out[]){

    if(opc == OPEN){
        int i=0, j=0, val;
        int rows, cols;
        mat2D_GetInfo(mt, &rows, &cols);

        for(int i=0; i<rows; i++){
            for(int j=0; j<cols; j++){
                mat2D_get_value(mt, i, j, &val);
                printf("%d", val);
            }
            printf("\n");
        }

        return SUCCESS;

    }else if(opc == CONV){
        FILE *imgOut;

        imgOut = fopen(name_out, "wb");
        if(imgOut == NULL){
            return ERROR;
        }

        int rows, cols, val;
        mat2D_GetInfo(mt, &rows, &cols);
        //printf("rows%d cols%d\n", rows, cols);

        fwrite(&rows, sizeof(val),  1, imgOut);
        fwrite(&cols, sizeof(val),  1, imgOut);

        for(int i=0; i<rows; i++){
            for(int j=0; j<cols; j++){
                mat2D_get_value(mt, i, j, &val);
                fwrite(&val, sizeof(val),  1, imgOut);
            }
        }

        fclose(imgOut);
        return SUCCESS;

    }else if(opc == SEG){
        FILE *imgOut;

        imgOut = fopen(name_out, "wb");

        if(imgOut == NULL){
            return ERROR;
        }

        int rows, cols, val;
        mat2D_GetInfo(mt, &rows, &cols);

        fwrite(&rows, sizeof(val),  1, imgOut);
        fwrite(&cols, sizeof(val),  1, imgOut);

        for(int i=0; i<rows; i++){
            for(int j=0; j<cols; j++){
                mat2D_get_value(mt, i, j, &val);
                fwrite(&val, sizeof(val),  1, imgOut);
            }
        }


        fclose(imgOut);
        return SUCCESS;

    }else if(opc == LAB){
        FILE *imgOut;

        imgOut = fopen(name_out, "w");

        if(imgOut == NULL){
            return ERROR;
        }

        int rows, cols, val;
        mat2D_GetInfo(mt, &rows, &cols);

        for(int i=0; i<rows; i++){
            for(int j=0; j<cols; j++){
                mat2D_get_value(mt, i, j, &val);
                fprintf(imgOut,"%d", val);
                if(j != cols-1){
                    fprintf(imgOut, "\t");
                }
            }
            if(i != rows-1){
                fprintf(imgOut, "\n");
            }
        }


        fclose(imgOut);
        return SUCCESS;
    }
}

//----------------------COMPONENTE-CONEXO----------------------------------------
int Fcc(char name_in[], char name_out[]){
    
    TMat2D *mt, *mt2;
    Stack *st;

    int rows, cols, aux, auxMt2=0;
    mt = only_open(name_in);

    aux = mat2D_GetInfo(mt, &rows, &cols);

    mt2 = mat2D_create(rows, cols);
    mat2D_copyMat(mt, mt2);

    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            mat2D_set_value(mt2, i, j, 0);
        }
    }

    int label = 1, i, j, aux2, getValue, getValue2, sizeSt;
    st = create_stack();
    Ponto p, p_atual;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++){ 
            p.x = i;
            p.y = j;

            aux = mat2D_get_value(mt, i, j, &getValue);
            aux2 = mat2D_get_value(mt2, i, j, &getValue2);

            if((getValue == 1) &&  (getValue2 == 0)){
                aux2 = mat2D_set_value(mt2, i, j, label);
                push_stack(st, p.x);
                push_stack(st, p.y);

                while(size_stack(st) != EMPTY){
                
                    top_stack(st, &p_atual.y);
                    pop_stack(st);
                    
                    top_stack(st, &p_atual.x);
                    pop_stack(st);

                    Ponto pp[4];
                    pp[0].x = p_atual.x-1;
                    pp[0].y = p_atual.y;

                    pp[1].x = p_atual.x;
                    pp[1].y = p_atual.y -1;

                    pp[2].x = p_atual.x + 1;
                    pp[2].y = p_atual.y;

                    pp[3].x = p_atual.x;
                    pp[3].y = p_atual.y + 1;

                    for(int k=0; k<4; k++){
                        aux = mat2D_get_value(mt, pp[k].x, pp[k].y, &getValue);
                        aux2 = mat2D_get_value(mt2, pp[k].x, pp[k].y, &getValue2);

                        if((getValue == 1) &&  (getValue2 == 0)){
                            aux2 = mat2D_set_value(mt2, pp[k].x, pp[k].y, label);
                            push_stack(st, pp[k].x);
                            push_stack(st, pp[k].y);
                            
                        }
                    }
                }
                label++;
            }
        }
    }

    aux = print_img(mt2, SEG, name_out);

    if(aux != SUCCESS){
        return ERROR;
    }

    return SUCCESS;
}


//----------------------LAB----------------------------------------
int Flab(char name_in[], char name_out[]){
    struct ponto p_inicio, inicio;
    Ponto atual;
    Stack *st;
    st = create_stack();
    TMat2D *mt, *mt2;
    int  sem_saida = 0;

    int rows, cols;
    mt = only_open(name_in);
    mat2D_GetInfo(mt, &rows, &cols);
    mt2 = mat2D_create(rows, cols);
    
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            mat2D_set_value(mt2, i, j, 0);
        }
    }
    
    int aux=0;  
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            mat2D_get_value(mt, i, j, &aux);
            if(aux == 1 && (i==0 || j==0 || i==rows-1 || j==cols-1)){
                p_inicio.x = i;
                p_inicio.y = j;
            }
        }
    }

    int bordaCima, bordaBaixo, bordaEsquerda, bordaDireita;
    bordaCima = 0;
    bordaEsquerda = 0;
    bordaBaixo = rows-1;
    bordaDireita = cols-1;

    inicio = p_inicio;
    atual = inicio;

    int val1,val2;
    while(1){
        mat2D_get_value(mt, atual.x, atual.y, &val1);
        
        if(
            (atual.x != inicio.x || atual.y != inicio.y) && 
            (atual.x == bordaCima || atual.x == bordaBaixo || atual.y == bordaEsquerda || atual.y == bordaDireita) && 
            val1 == 1){
                push_stack(st, atual.x);
                push_stack(st, atual.y);
            break;
        }
        
        Ponto p[4];
        p[0].x = atual.x -1;
        p[0].y = atual.y;

        p[1].x = atual.x;
        p[1].y = atual.y - 1;

        p[2].x = atual.x + 1;
        p[2].y = atual.y;

        p[3].x = atual.x;
        p[3].y = atual.y + 1;
        
        for(int k=0; k<4; k++){
            mat2D_get_value(mt, p[k].x, p[k].y, &val1);
            mat2D_get_value(mt2, p[k].x, p[k].y, &val2);

            if(val1 == 1 && val2 == 0){
                mat2D_set_value(mt2, atual.x, atual.y, 1);
                push_stack(st, atual.x);
                push_stack(st, atual.y);
                atual = p[k];
                break;	
            }
            if( k == 3 ){
                if(size_stack(st) == EMPTY){
                    return LAB_EXIT;
                }
                mat2D_set_value(mt2, atual.x, atual.y, 1);

                top_stack(st, &atual.y);
                pop_stack(st);

                top_stack(st, &atual.x);
                pop_stack(st);
            }
        }
    }

    while(size_stack(st) != EMPTY){
        top_stack(st, &atual.y);
        pop_stack(st);

        top_stack(st, &atual.x);
        pop_stack(st);

        mat2D_set_value(mt, atual.x, atual.y, 2);
    }

    aux = print_img(mt, LAB, name_out);

    if(aux != SUCCESS){
        return ERROR;
    }

    return SUCCESS;
}