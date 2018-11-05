#include <stdlib.h>
#include <stdio.h>

int getLengthString(char * string);
long double teste(char * string);
int isNumber(char  character);
int isSignal(char  character);
long double expression(char * string);
long double multAndDiv(char * string, long double result);
long double sunAndSub(char * string, long double result);
long double toNumber(char * string);
long double inicializeExpression(char * string);


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


nodeNumber* searchNodeNumberByPosition (nodeNumber* nodeArg, int position){
    nodeNumber* nodeAUX = NULL;
    for (nodeAUX = nodeArg; nodeAUX->nextNode != NULL; nodeAUX = nodeAUX -> nextNode)
        if (nodeAUX -> position == position)
            return nodeAUX;
    return NULL; /* não achou o elemento */
}



nodeNumber* searchNodeNumber (nodeNumber* nodeArg, long int value){
    nodeNumber* nodeAUX;
    for (nodeAUX = nodeArg; nodeAUX != NULL; nodeAUX = nodeAUX -> nextNode)
        if (nodeAUX -> number == value)
            return nodeAUX;
    return NULL; /* não achou o elemento */
}




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




 nodeChar* searchNodeForChar ( nodeChar* nodeArg, char value){
    nodeChar* nodeAUX = NULL;
    nodeAUX = nodeArg;


    while(nodeAUX -> nextNode != NULL){
        nodeAUX = nodeAUX->nextNode;
    }
    printf("TESTE %d\n", nodeAUX->position);

    for (; nodeAUX != NULL; nodeAUX = nodeAUX -> nextNode){
        if (nodeAUX -> character == value){
            printf("Achou na pos %d\n", nodeAUX -> position);
            return nodeAUX;
        }
    }
    return NULL; /* não achou o elemento */
}



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
         nodeChar* nodeAUX = searchNodeForChar(nodeArg,position);

         
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


// long double expression(char * string){

//     node nodes = null;
//     int cont = 0;
//     int stringLength = getLengthString(string);

//     for(cont = 0; cont < stringLength; cont++){

//         if(string[cont])

//     }
//     return 0;

// }






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



















int getLengthString(char * string){
    int stringLength = 0;


    while(*string != '\0'){
        stringLength++;
        string++;
    }


    string -= stringLength;


    return stringLength;
}


/*
 *  sunAndSub(char * string, long double result)
 * 
 * it recives an string return if the first char is a signal like 1,2,3,4,5,6,7,8,9,0;
 * 
 */

int isNumber(char character){
    if((character >= '0' && character<='9'))
        return 1;
    return 0;
}

/*
 *  sunAndSub(char * string, long double result)
 * 
 * it recives an string return if the first char is a signal like *,/,+,-;
 * 
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




long double expression(char * string){

    nodeNumber * listOfNumber = NULL;

     nodeChar * listOfChar = NULL;

     nodeChar * listOfCharAux = NULL;
    

    int cont;
    int positionNumber = 1;
    int positionChar = 2;
    int stringLength = getLengthString(string);
    long double result = 0;

    /*
     *Aloca a string dentro das listas dinamicas
     * 
     */
    listOfNumber = insertNodeNumber(listOfNumber, 0, positionNumber++);// iniciar a lista
    for(cont = 0; cont < stringLength ; cont++){
        if(isNumber(string[cont])){
            listOfNumber = insertNodeNumber(listOfNumber, toNumber(string+cont), positionNumber++);
            while(isNumber(string[cont])){
                cont++;
            }
            cont--;//para corrigir o cont pois o while retorna um cont a mais
        }else{
            if(isSignal(string[cont]))
            listOfChar = insertNodeForChar(listOfChar, string[cont], positionChar++);
        }
    }
    printNodeChar(listOfChar);
    printf("\n\n");
    printNodeNumber(listOfNumber);
    printf("\n\n\n\n\n\n\nParte da soma\n");
    for(cont = 0; cont < 1; cont++){
        nodeChar * listOfCharAux = searchNodeForChar(listOfChar, '+');
        if (listOfCharAux != NULL){
            printf("error %d", cont+1);
            nodeNumber* listOfNumberAux1 = searchNodeNumberByPosition(listOfNumber, listOfCharAux->position);
            nodeNumber* listOfNumberAux2 = listOfNumberAux1->previusNode;

            printf("listOfNumberAux1 = %Lf   listOfNumberAux2 = %Lf\n", listOfNumberAux1->number, listOfNumberAux2->number);
            listOfNumberAux2->number = listOfNumberAux1->number + listOfNumberAux2->number;

            listOfChar = removeNodeForCharByPosition(listOfChar, listOfCharAux->position);
            printf("Destruindo posicao %d\n",listOfNumberAux2->position);
            listOfNumber = removeNodeNumberByPosition(listOfNumber, listOfNumberAux2->position);
            
        }
        
    }
    printf("\n\n\n\n\n\n\nResultado\n");


    printNodeNumber(listOfNumber);

    return listOfNumber->number;

}



/*
 *  sunAndSub(char * string, long double result)
 * 
 * it recives an string and a preveus result and make the multiplication or sub division according to string;
 * 
 */


long double multAndDiv(char * string, long double result){

    char signal = *string;
    
    long double number = 0;
    string++;
    if(isNumber(*string) == 1){
        
        number = toNumber(string);
        if(signal == '*'){
            result *= number;
        }
        else{
            if(number == 0)
                return 0;
            result /= number;   
        }
    }
    return result;
}

/*
 *  sunAndSub(char * string, long double result)
 * 
 * it recives an string and a preveus result and make the sun or sub operation according to string;
 * 
 */

long double sunAndSub(char * string, long double result){

    char signal = *string;
    
    long double number = 0;
    string++;
    if(isNumber(*string) == 1){
        
        number = toNumber(string);
        if(signal == '+')
            result += number;
        else
            result -= number;   
    }
    return result;
}




/* 
 * toNumber(char * string)
 * 
 * parse an string into a number, it can be float and int but the return is always long double;
 * 
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





long double inicializeExpression(char * string){
    long double result;
    
    result = expression(string);
    return result;
}

int main(int argc, char const *argv[])
{
    char* string = "10+11+12";

    
    printf("%Lf\n",  inicializeExpression(string));


    // nodeNumber * teste = NULL;
    // int cont =0;

    // for(cont = 0; cont < 5; cont++)
    //     teste = insertNodeNumber(teste, cont, cont);

    // printNodeNumber(teste);

    // printf("O inicio da fila é em %d\n\n\n\n\n",teste->position);



    // for(cont = 0; cont < 5; cont++)
    //     teste = removeNodeNumberByPosition(teste,  cont);

    // printNodeNumber(teste);

    // printf("O inicio da fila é em %d\n",teste->position);






    // string = "10 * 10";
    // printf("%Lf\n", inicializeExpression(string));
                                                             

    // long double numeber = toNumber("10.44");
    // printf("Number: %Lf\n", numeber);
    return 0;
}
