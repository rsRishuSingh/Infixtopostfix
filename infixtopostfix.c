#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

struct stack
{
    int size;
    int top;
    char *arr;
};

void initialize(struct stack *sp, int size)
{
    sp->size = size;
    sp->top = -1;
    sp->arr = (char *)malloc(size * sizeof(char));
}

void push(struct stack *sp, char val)
{
    if (sp->top == sp->size - 1)
    {
        printf("Stack Overflow!\n");
    }
    else
    {
        sp->top++;
        sp->arr[sp->top] = val;
    }
}

char pop(struct stack *sp)
{
    if (sp->top == -1)
    {
        printf("Stack Underflow!\n");
        return '\0';
    }
    else
    {
        char val = sp->arr[sp->top];
        sp->top--;
        return val;
    }
}

int isEmpty(struct stack *sp)
{
    return sp->top == -1;
}

int isOperator(char ch)
{
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

int precedence(char ch)
{
    if (ch == '^')
        return 4;
    else if (ch == '*' || ch == '/')
        return 3;
    else if (ch == '+' || ch == '-')
        return 2;
    else
        return 0;
}

void infixToPostfix(char *infix, char *postfix)
{
    struct stack sp;
    initialize(&sp, strlen(infix));

    int i = 0;
    int j = 0;

    while (infix[i] != '\0')
    {
        if (isalnum(infix[i]))
        {
            postfix[j] = infix[i];
            j++;
            i++;
        }
        else if (infix[i] == '(')
        {
            push(&sp, infix[i]);
            i++;
        }
        else if (infix[i] == ')')
        {
            while (!isEmpty(&sp) && sp.arr[sp.top] != '(')
            {
                postfix[j] = pop(&sp);
                j++;
            }
            if (!isEmpty(&sp) && sp.arr[sp.top] == '(')
            {
                pop(&sp);
            }
            i++;
        }
        else if (isOperator(infix[i]))
        {
            while (!isEmpty(&sp) && precedence(infix[i]) <= precedence(sp.arr[sp.top]))
            {
                postfix[j] = pop(&sp);
                j++;
            }
            push(&sp, infix[i]);
            i++;
        }
        else
        {

            printf("Invalid character in the infix expression: %c\n", infix[i]);
            exit(1);
        }
    }

    while (!isEmpty(&sp))
    {
        postfix[j] = pop(&sp);
        j++;
    }

    postfix[j] = '\0';
}

int main()
{
    char infix[] = "x-y/(z-k)*d";
    char postfix[50];

    infixToPostfix(infix, postfix);

    printf("Infix Expression: %s\n", infix);
    printf("Postfix Expression: %s\n", postfix);

    return 0;
}
