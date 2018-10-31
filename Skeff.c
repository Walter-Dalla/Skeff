#include <stdlib.h>
#include <stdio.h>

int getLengthString(char * string);
long double teste(char * string);
int isNumber(char  character);
int isSignal(char  character);
long double expression(char * string, long double result);
long double multAndDiv(char * string, long double result);
long double sunAndSub(char * string, long double result);
long double toNumber(char * string);
long double inicializeExpression(char * string);


typedef struct Node{
    
    struct Node * nextNode;
    struct Node * previusNode;

    long double number;
    char character;

} node;

node* insertNode(node* nodeArg, long double valueNumber, char valueChar){
    
    node * newNode = malloc(sizeof(node));
    newNode->number = valueNumber;
    newNode->character = valueChar;
    newNode->nextNode = nodeArg;
    newNode->previusNode = NULL;
    /* verifica se lista não está vazia */

    if (nodeArg != NULL)
        nodeArg->previusNode = newNode;

    return newNode;
}

node* searchNode (node* nodeArg, char value){
    node* nodeAUX;
    for (nodeAUX = nodeArg; nodeAUX != NULL; nodeAUX = nodeAUX -> nextNode)
        if (nodeAUX -> character == value)
            return nodeAUX;
    return NULL; /* não achou o elemento */
}


node* removeNode (node* nodeArg, int v){
    node* nodeAUX = searchNode(nodeArg,v);
    if (nodeAUX == NULL)
        return nodeArg; //não achou o elemento : retorna lista inalterada
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


void printNode(node * nodeArg){
    while(nodeArg->nextNode != NULL){
        printf(" %Lf\n", nodeArg->number);
        nodeArg = nodeArg->nextNode;
    }
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



long double expression(char * string, long double result){

    if(isSignal(*string) == 1){ // + ou -
        result = sunAndSub(string, result);
    }else if(isSignal(*string) == 2){ // * ou /
        result = multAndDiv(string, result);
    }
    return result;

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
    result = expression(string, 0);
    return result;
}

int main(int argc, char const *argv[])
{
    int cont = 0;
    node* nodeJs;


    for(cont = 0; cont < 127; cont++){
        nodeJs = insertNode(nodeJs, cont, 'a');
        //printf("%d\n", cont);
    }

    printNode(nodeJs);


    // char * expressao = "+10"; 

    // printf("%Lf\n", inicializeExpression(expressao));


    // expressao = "10 * 10";
    // printf("%Lf\n", inicializeExpression(expressao));


    // long double numeber = toNumber("10.44");
    // printf("Number: %Lf\n", numeber);
    // return 0;
}