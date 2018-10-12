#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const char * expressao = "(10+10)/(2+2) \0";



char peek(){
    return *expressao;
}

char nextPeek(){
    return *expressao++;
}

int getNumber(){
    int result = 0;
    while(peek() >= '0' && peek() <= '9'){
       result = result*10 + (nextPeek() - '0');
    }
    return result;
}

int firstOpperation(){

    int result;
    switch (peek()){

    case '^':
            nextPeek();
            result += peek() - '0';
        break;

    case '\0':
        printf("Como raios vc entrou aqui??");
    break;

    default:
        return secondOpperation();
    break;
    }

    return result;

}

int secondOpperation(){
    int result;
    switch (peek()){

    case '*':
            printf("%c\n", peek());
            nextPeek();
            result += peek() - '0';
        break;

    case '/':
            printf("%c\n", peek());
            nextPeek();
            result += peek() - '0';
        break;

    default:
        return thirdOpperation();
    break;
    }

    return result;
}

int thirdOpperation(){
    int result;

    if(peek() >= '0' && peek() <= '9'){
            return getNumber();
    }else

    switch (peek()){

    case '+':
            printf("%c\n", peek());
            nextPeek();
            printf("%d + %d", result, getNumber());
            result += getNumber();
            printf(" = %d",result);
        break;

    case '-':
            printf("%c\n", peek());
            nextPeek();
            result += peek() - '0';
        break;

    case '(':
            printf("%c\n", peek());
            nextPeek();
            result = expression();
        break;

    }

    return result;
}


int expression(){

    int result = 0;
    while(peek() != '\0' && peek() != ')'){
        result += firstOpperation();
        printf("o resultado eh %d\n", result);
    }
    return result;
}



int main(){



    printf("\n\n%d\n\n", expression());

    return 0;

}
