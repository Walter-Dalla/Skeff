#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* rem(char * string);
int isNumber(char * string);
long double toNumber(char * string);
long double sunAndSub(char * string, long double result);
long double multAndDiv(char * string, long double result);
long double splitExpression(char * string, long double result);
long double expression(char * string, long double result);
long double inicializeExpression(char * string);


char peek(char * string){
    return *string;
}

char* nextPeek(char * string){
    string++;
    if(*string == ' '){
        string++;
    }
        
return string;
}





//=10+10*10-(10-5) = 95;



int isNumber(char * string){
    if((peek(string) >= '0' && peek(string)<='9'))
        return 1;
    return 0;
}

int isSignal(char * string){
    if(peek(string) == '+' || peek(string)=='-')
        return 1;
    if(peek(string) == '/' || peek(string)=='*')
        return 2;
    if(peek(string) == '^')
        return 3;
    return 0;
}


long double inicializeExpression(char * string){
    long double result = 0;
    printf("%s\n", string);
    
    result = splitExpression(string, result);
    
}

long double splitExpression(char * string, long double result){

    if( peek(string) == '('){
        while(peek(string) != ')' || peek(string) != '\0'){

            string = nextPeek(string);

            result = expression(string, result);

        }
    }else{
        string = nextPeek(string);

        result = expression(string, result);
    }

    return result;

}


long double expression(char * string, long double result){

    result = splitExpression(string, result);

    if(isSignal(string) == 1){ // + ou -
        result = sunAndSub(string, result);
    }else if(isSignal(string) == 2){ // * ou /
        result = multAndDiv(string, result);
    }
    return result;

}

long double multAndDiv(char * string, long double result){

    char signal = *string;
    
    long double number = 0;
    string = nextPeek(string);
    if(isNumber(string) == 1){
        
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


long double sunAndSub(char * string, long double result){

    char signal = *string;
    
    long double number = 0;
    string = nextPeek(string);
    if(isNumber(string) == 1){
        
        number = toNumber(string);
        if(signal == '+')
            result += number;
        else
            result -= number;   
    }
    return result;
}





long double toNumber(char * string){
    long double result = 0;
    float contDiv = 1;
    int isFloatable = 0;

    while(isNumber(string) || peek(string) == '.'){
        
        if(peek(string) == '.'){
            string++;
            isFloatable = 1;
            continue;
        }
        
        result = result * 10 + (peek(string) - '0');

        if(isFloatable == 1)
            contDiv *= 10;

        string++;
    }
    return result/contDiv;
}

int main(int argc, char const *argv[])
{
    char * expressao = "10 + 10";
    printf("%Lf\n", inicializeExpression(expressao));


    expressao = "10 * 10";
    printf("%Lf\n", inicializeExpression(expressao));


    long double numeber = toNumber("10.44");
    printf("Number: %Lf", numeber);
    return 0;
}
