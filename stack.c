#include<stdio.h>
#include<stdlib.h>

#define MAX 5

int stack[MAX];
int top = -1;

void push(int data) {
    if(top >= MAX) {
        printf("Overflow!");
        return;
    }

    stack[++top] = data;
    printf("\n\n%d pushed to stack", data);
}

int pop() {
    if(top <= -1) {
        printf("\nUnderflow!");
        return 0;
    }

    int tempData = stack[top--];

    printf("\n%d popped from stack", tempData);

    return tempData;
}

void display() {
    printf("\n\n");
    for(int i = 0; i<= top; i++) {
        if(stack[i] != 0)
        printf("%d\t", stack[i]);
    }
    printf("\n");
}

int main() {
    push(5);
    push(9);
    push(30);

    display();

    pop();
    pop();

    display();

    return 0;
}