#include <stdlib.h>
#include <stdio.h>

int getLengthString(char * string);
int isNumber(char  character);
int isSignal(char  character);
long double expression(char * string);
long double toNumber(char * string);
long double inicializeExpression(char * string);

/*
 *
 * 
 */

/*
 * Structs para definir as listas
 */
typedef struct NodeNumber{
    
    struct NodeNumber * nextNode;
    struct NodeNumber * previusNode;
    long double number;
    int position;

} nodeNumber;


typedef struct NodeChar{
    
    struct NodeChar * nextNode;
    struct NodeChar * previusNode;
    char character;
    int position;

}  nodeChar;


/*
 * Metodos para trabalhar com as listas
 */

/*
 * Metodos de incersao à lista
 */
nodeNumber* insertNodeNumber(nodeNumber* nodeArg, long double valueNumber, int position){
    nodeNumber * newNode = malloc(sizeof(nodeNumber));
    newNode->number = valueNumber;
    newNode->nextNode = nodeArg;
    newNode->position = position;
    newNode->previusNode = NULL;
    /* verifica se lista não está vazia */

    if (nodeArg != NULL)
        nodeArg->previusNode = newNode;

    return newNode;
}

nodeChar* insertNodeForChar( nodeChar* nodeArg, char characterArg, int position){
    nodeChar * newNode = malloc(sizeof( nodeChar));

    newNode->character = characterArg;
    newNode->nextNode = nodeArg;
    newNode->position = position;
    newNode->previusNode = NULL;

    /* verifica se lista não está vazia */
    if (nodeArg != NULL)
        nodeArg->previusNode = newNode;

    return newNode;
}

/*
 * Metodos de pesquisa na lista
 */

//Por posicao
nodeNumber* searchNodeNumberByPosition (nodeNumber* nodeArg, int position){
    nodeNumber* nodeAUX = NULL;
    for (nodeAUX = nodeArg; nodeAUX->nextNode != NULL; nodeAUX = nodeAUX -> nextNode)
        if (nodeAUX -> position == position)
            return nodeAUX;
    return NULL; /* não achou o elemento */
}

//Por posicao
nodeChar* searchNodeForCharByPosition ( nodeChar* nodeArg, int position){
    nodeChar* nodeAUX;
    nodeAUX = nodeArg;

    while(nodeAUX->previusNode != NULL){
        nodeAUX = nodeAUX->nextNode;
    }

    for (; nodeAUX != NULL; nodeAUX = nodeAUX -> nextNode){
        if (nodeAUX -> position == position){
            return nodeAUX;
        }
    }
    return NULL; /* não achou o elemento */
}


//Por valor
nodeChar* searchNodeForChar ( nodeChar* nodeArg, char value){
    nodeChar* nodeAUX = NULL;
    nodeAUX = nodeArg;

    while(nodeAUX -> nextNode != NULL){
        nodeAUX = nodeAUX->nextNode;
    }
    for (; nodeAUX != NULL; nodeAUX = nodeAUX -> previusNode){
        if (nodeAUX -> character == value){
            return nodeAUX;
        }
    }
    return NULL; /* não achou o elemento */
}


/*
 * Metodo de remocao da lista
 */
nodeNumber* removeNodeNumberByPosition (nodeNumber* nodeArg, int position){
    nodeNumber* nodeAUX = searchNodeNumberByPosition(nodeArg, position);

    if (nodeAUX == NULL){
        return nodeArg; //não achou o elemento : retorna lista inalterada
    }

    /* retira elemento do encadeamento */
    if (nodeArg == nodeAUX)
        nodeArg = nodeAUX->nextNode;
    else
        nodeAUX ->previusNode->nextNode = nodeAUX->nextNode;

    if (nodeAUX->nextNode != NULL)
        nodeAUX->nextNode->previusNode = nodeAUX->previusNode;
    free(nodeAUX);

    return nodeArg;
}

nodeChar* removeNodeForCharByPosition ( nodeChar* nodeArg, int position){
    nodeChar* nodeAUX = searchNodeForCharByPosition(nodeArg,position);

    if (nodeAUX == NULL){
        return nodeArg; //não achou o elemento : retorna lista inalterada
    }

    /* retira elemento do encadeamento */
    if (nodeArg == nodeAUX)
        nodeArg = nodeAUX->nextNode;
    else
        nodeAUX ->previusNode->nextNode = nodeAUX->nextNode;

    if (nodeAUX->nextNode != NULL)
        nodeAUX->nextNode->previusNode = nodeAUX->previusNode;
    free(nodeAUX);
    
    return nodeArg;
}

/*
 * Metodos de debug da lista:
 * printar a lista no console
 */


void printNodeNumber(nodeNumber * nodeNumberArg){
    while(nodeNumberArg != NULL){
        printf("=====================================\n");
        printf("Posiçao do node: %d    \nNumero Do Node: %Lf\n",nodeNumberArg->position, nodeNumberArg->number );
        nodeNumberArg = nodeNumberArg->nextNode;

    }
}


void printNodeChar(nodeChar * nodeCharArg){
    while(nodeCharArg != NULL){
        printf("=====================================\n");
        printf("Posiçao do node: %d    \nChar Do Node: %c\n",nodeCharArg->position, nodeCharArg->character );
        nodeCharArg = nodeCharArg->nextNode;

    }
}







/*
 * Funçoes utilitarias
 */

/*
 * Retorna o tamanho do array de char
 * retorno (int): tamanho do array
 */
int getLengthString(char * string){
    int stringLength = 0;

    while(*string != '\0'){
        stringLength++;
        string++;
    }
    return stringLength;
}

/*
 * verifica se o caractere é um numero 
 * retorno (int): 1 -> true
 *                0 -> false
 */
int isNumber(char character){
    if((character >= '0' && character<='9'))
        return 1;
    return 0;
}

/*
 * verifica se o caractere é um sinal(+,-,*,/,^) 
 * retorno (int): 1 -> true
 *                0 -> false
 */

int isSignal(char character){
    if(character == '+' || character=='-')
        return 1;
    if(character == '/' || character=='*')
        return 2;
    if(character == '^')
        return 3;
    return 0;
}


int getNumberOfPrimarySignals(nodeChar* nodeCharArg){
    int result = 0;
    while(nodeCharArg != NULL){
        if(nodeCharArg -> character == '*'||nodeCharArg -> character == '/')   
            result++;
        nodeCharArg = nodeCharArg->nextNode;
    }
    return result;
}


/*
 * Retorna o numero que a string representa
 * retorno (Long Double): numero que a string representa;
 */


long double toNumber(char * string){
    long double result = 0;
    float contDiv = 1;
    int isFloatable = 0;

    while(isNumber(*string) || *string == '.'){
        
        if(*string == '.'){
            string++;
            isFloatable = 1;
            continue;
        }
        
        result = result * 10 + (*string - '0');

        if(isFloatable == 1)
            contDiv *= 10;

        string++;
    }
    return result/contDiv;
}


void test(int size, char* string, int position){
    char string_[size];
    int cont = 0;
    
    for(cont = 0; string[cont] != ')'|| cont < 10 ; cont++){
        string_[cont] = string[cont+position];
    }
    string_[cont] = '\n';

    for(cont = 0; string[cont] != ')' ; cont++){
        printf("String_ = %c\n", string_[cont]);
    }

    long double aa = expression(string_);
    printf("Result = %Lf\n", aa);
}


long double expression(char * string){

    nodeNumber * listOfNumber = NULL;

    nodeChar * listOfChar = NULL;

    int cont;
    int positionNumber = 1;
    int positionChar = 2;
    int stringLength = getLengthString(string);
    int numberOfPrimarySignals = 0;
    char* string_;
    long double result = 0;

    /*
     *Aloca a string dentro das listas dinamicas
     * 
     */
    listOfNumber = insertNodeNumber(listOfNumber, 0, positionNumber++);// iniciar a lista
    for(cont = 0; cont < stringLength ; cont++){
        if(isNumber(string[cont])){
            listOfNumber = insertNodeNumber(listOfNumber, toNumber(string+cont), positionNumber++);
            while(isNumber(string[cont])|| string[cont] == '.'){
                cont++;
            }
            cont--;//para corrigir o cont pois o while retorna um cont a mais
        }else{
            if(isSignal(string[cont]) != 0)
                listOfChar = insertNodeForChar(listOfChar, string[cont], positionChar++);
            else
                listOfChar = insertNodeForChar(listOfChar, string[cont], cont);
        }
    }

    
    
    numberOfPrimarySignals =  getNumberOfPrimarySignals(listOfChar);
    for(cont = 0; cont < positionChar-2; cont++){
        nodeChar * listOfCharAux = NULL;

        listOfCharAux = searchNodeForChar(listOfChar, '(');

        if(listOfCharAux == NULL){
            if(cont < numberOfPrimarySignals){
                listOfCharAux = searchNodeForChar(listOfChar, '*');
                if(listOfCharAux == NULL)
                    listOfCharAux = searchNodeForChar(listOfChar, '/');
            }
            else{
                listOfCharAux = searchNodeForChar(listOfChar, listOfChar->character);
            }
        }
        else{
            test(stringLength,string,listOfCharAux->position);
        }
        
        if (listOfCharAux != NULL){
            nodeNumber* listOfNumberAux1 = searchNodeNumberByPosition(listOfNumber, listOfCharAux->position);
            if(listOfNumberAux1 == NULL)
                continue;
            if(listOfNumberAux1->previusNode == NULL){
                listOfNumber = insertNodeNumber(listOfNumber, 0, positionNumber++);// iniciar a lista
            }
            nodeNumber* listOfNumberAux2 = listOfNumberAux1->previusNode;

            switch (listOfCharAux -> character ){
                
                case('*'):
                    listOfNumberAux2->number = listOfNumberAux1->number * listOfNumberAux2->number;
                    break;

                case('/'):
                    if(listOfNumberAux2->number != 0)
                        listOfNumberAux2->number = listOfNumberAux1->number / listOfNumberAux2->number;
                    else 
                        listOfNumberAux2->number = 0;
                    break;

                case('+'):
                    listOfNumberAux2->number = listOfNumberAux1->number + listOfNumberAux2->number;
                    break;

                case('-'):
                    listOfNumberAux2->number = listOfNumberAux1->number - listOfNumberAux2->number;
                    break;
            }

            listOfChar = removeNodeForCharByPosition(listOfChar, listOfCharAux->position);
            listOfNumber = removeNodeNumberByPosition(listOfNumber, listOfNumberAux1->position);
            
        }
        
    }
    return listOfNumber->number;

}



long double inicializeExpression(char * string){
    long double result;
    
    result = expression(string);
    return result;
}

int main(int argc, char const *argv[])
{
    float result = (10+10*10-10);
    char* string = "(10+10*10-10)";
    printf("%s = %Lf porem o result real eh : %f\n", string,  inicializeExpression(string), result);

    return 0;
}