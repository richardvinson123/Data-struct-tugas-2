#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct Stack{
    int top;
    char items[MAX];
};

void initStack(struct Stack* s){
    s->top = -1;
}

int isFull(struct Stack* s){
    return s->top == MAX - 1;
}

int isEmpty(struct Stack* s){
    return s->top == -1;
}

void push(struct Stack* s, char item){
    if(!isFull(s)){
        s->items[++(s->top)] = item;
    }else{
        printf("Stack Overflow\n");
    }
}

char pop(struct Stack* s){
    if(!isEmpty(s)){
        return s->items[(s->top)--];
    }else{
        printf("Stack Underflow\n");
        return -1;
    }
}

char peek(struct Stack* s){
    if(!isEmpty(s)){
        return s->items[s->top];
    }else{
        return -1;
    }
}

int precedence(char c){
    if(c == '+' || c == '-')return 1;
    if(c == '*' || c == '/')return 2;
    return 0;
}

int isOperand(char c){
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9');
}

void infixToPostfix(char* infix, char* postfix){
    struct Stack s;
    initStack(&s);
    int j=0;
    for (int i=0;i<strlen(infix); i++){
        char c = infix[i];
    	
        if(c == ' '){
            continue;
        }else if(isOperand(c)){
            postfix[j++] = c;
        }else if (c == '('){
            push(&s, c);
        }else if(c == ')'){
            while (!isEmpty(&s) && peek(&s) != '('){
                postfix[j++] = pop(&s);
            }
            pop(&s);
        }else{
            while(!isEmpty(&s) && precedence(c) <= precedence(peek(&s))){
                postfix[j++] = pop(&s);
            }
            push(&s,c);
        }
    }
    
    while(!isEmpty(&s)){
        postfix[j++] = pop(&s);
    }
    
    postfix[j]='\0';
}

int main(){
    char infix[MAX], postfix[MAX];
    
    printf("Enter infix expression: ");
    scanf("%[^\n]%*c",infix);
    
    infixToPostfix(infix, postfix);
    
    printf("Postfix expression: %s\n",postfix);
    
    return 0;
}

