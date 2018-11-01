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


typedef struct NodeForNumber{
    
    struct NodeForNumber * nextNode;
    struct NodeForNumber * previusNode;
    long double number;
    int position;

} nodeForNumber;


typedef struct NodeForChar{
    
    struct NodeForChar * nextNode;
    struct NodeForChar * previusNode;
    char character;
    int position;

} nodeForChar;

nodeForNumber* insertNodeForNumber(nodeForNumber* nodeArg, long double valueNumber, int position){
    
    nodeForNumber * newNode = malloc(sizeof(nodeForNumber));
    newNode->number = valueNumber;
    newNode->nextNode = nodeArg;
    newNode->position = position;
    newNode->previusNode = NULL;
    /* verifica se lista não está vazia */

    if (nodeArg != NULL)
        nodeArg->previusNode = newNode;

    return newNode;
}



nodeForChar* insertNodeForChar(nodeForChar* nodeArg, char characterArg, int position){
    
    nodeForChar * newNode = malloc(sizeof(nodeForChar));
    newNode->character = characterArg;
    newNode->nextNode = nodeArg;
    newNode->position = position;
    newNode->previusNode = NULL;
    /* verifica se lista não está vazia */

    if (nodeArg != NULL)
        nodeArg->previusNode = newNode;

    return newNode;
}


nodeForNumber* searchNodeForNumberByPosition (nodeForNumber* nodeArg, int position){
    nodeForNumber* nodeAUX;
    for (nodeAUX = nodeArg; nodeAUX != NULL; nodeAUX = nodeAUX -> nextNode)
        if (nodeAUX -> position == position)
            return nodeAUX;
    return NULL; /* não achou o elemento */
}



nodeForNumber* searchNodeForNumber (nodeForNumber* nodeArg, long int value){
    nodeForNumber* nodeAUX;
    for (nodeAUX = nodeArg; nodeAUX != NULL; nodeAUX = nodeAUX -> nextNode)
        if (nodeAUX -> number == value)
            return nodeAUX;
    return NULL; /* não achou o elemento */
}




nodeForChar* searchNodeForCharByPosition (nodeForChar* nodeArg, int position){
    nodeForChar* nodeAUX;
    for (nodeAUX = nodeArg; nodeAUX != NULL; nodeAUX = nodeAUX -> nextNode)
        if (nodeAUX -> position == position)
            return nodeAUX;
    return NULL; /* não achou o elemento */
}




nodeForChar* searchNodeForChar (nodeForChar* nodeArg, char value){
    
    nodeForChar* nodeAUX;
    for (nodeAUX = nodeArg; nodeAUX != NULL; nodeAUX = nodeAUX -> nextNode)
        if (nodeAUX -> character == value)
            return nodeAUX;
            printf("ola");
    return NULL; /* não achou o elemento */
}



nodeForNumber* removeNodeForNumberByPosition (nodeForNumber* nodeArg, int position){
        nodeForNumber* nodeAUX = searchNodeForNumber(nodeArg,position);
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

nodeForChar* removeNodeForCharByPosition (nodeForChar* nodeArg, int position){
        nodeForChar* nodeAUX = searchNodeForChar(nodeArg,position);
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

    nodeForNumber * listOfNumber = NULL;

    nodeForChar * listOfChar = NULL;

    nodeForNumber * listOfNumberAux1 = NULL;
    nodeForNumber * listOfNumberAux2 = NULL;
    nodeForChar * listOfCharAux = NULL;

    int cont;
    int positionNumber = 0;
    int positionChar = 0;
    int stringLength = getLengthString(string);
    long double result = 0;

    /*
     *Aloca a string dentro das listas dinamicas
     * 
     */
    listOfNumber = insertNodeForNumber(listOfNumber, 0, positionNumber++);// iniciar a lista
    for(cont = 0; cont < stringLength+1 ; cont++){

        if(isNumber(string[cont] == 1)){
            listOfNumber = insertNodeForNumber(listOfNumber, toNumber(string+cont), positionNumber++);
            while(isNumber(string[cont])){
                cont++;
            }
        }else{
            listOfChar = insertNodeForChar(listOfChar, string[cont], positionChar++);
        }
        
    }
    for(cont = 0; cont < positionChar; cont++){
        listOfCharAux = searchNodeForChar(listOfChar, '*');
        if (listOfCharAux != NULL){
        listOfNumberAux1 = searchNodeForNumberByPosition(listOfNumber, listOfCharAux->position);
        listOfNumberAux2 = searchNodeForNumberByPosition(listOfNumber, listOfCharAux->position+2);
            listOfNumberAux1->number = listOfNumberAux1->number * listOfNumberAux2->number;
            removeNodeForCharByPosition(listOfChar, listOfChar->position);
            removeNodeForNumberByPosition(listOfNumber, listOfNumberAux2->position);
        }
         free(listOfCharAux);
    }
    for(cont = 0; cont < positionChar; cont++){
        printf("ReturnNUll?");
        nodeForChar * listOfCharAux = searchNodeForChar(listOfChar, '+');
        if (listOfCharAux != NULL){
            listOfNumberAux1 = searchNodeForNumberByPosition(listOfNumber, listOfCharAux->position);
            listOfNumberAux2 = listOfNumberAux1->previusNode;
                printf("1%Lf\n", listOfNumberAux1->number);
                printf("2%Lf\n", listOfNumberAux2->number);
            printf("%Lf + %Lf = %Lf",listOfNumberAux1->number, listOfNumberAux2->number, listOfNumberAux1->number + listOfNumberAux2->number );
            listOfNumberAux1->number = listOfNumberAux1->number + listOfNumberAux2->number;
            
            removeNodeForCharByPosition(listOfChar, listOfCharAux->position);
            removeNodeForNumberByPosition(listOfNumber, listOfNumberAux2->position);
        }
    }
    

    // if(isSignal(*string) == 1){ // + ou -
    //     result = sunAndSub(string, result);
    // }else if(isSignal(*string) == 2){ // * ou /
    //     result = multAndDiv(string, result);
    // }
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
    char* string = "22+10";

    
    printf("%Lf\n", inicializeExpression(string));


    // string = "10 * 10";
    // printf("%Lf\n", inicializeExpression(string));


    // long double numeber = toNumber("10.44");
    // printf("Number: %Lf\n", numeber);
    return 0;
}