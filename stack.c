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

    int temp = stack[top--];
    return temp;
}

void display() {
    printf("\n\n");
    for(int i = 0; i< MAX; i++) {
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

    return 0;
}