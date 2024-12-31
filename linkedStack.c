#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* stack = NULL;

Node* createNode(int data) {
    Node* temp = malloc(sizeof(Node));
    if(temp == NULL) {
        return NULL;
    }

    temp->data = data;
    temp->next = NULL;

    return temp;
}

void push(int data) {
    Node* node = createNode(data);

    if(node == NULL) {
        printf("Overflow!");
        return;
    }

    if(stack == NULL) {
        stack = node;
    } else {
        node->next = stack;
        stack = node;
    }

    printf("\n%d pushed to stack", data);
}

int pop() {
    if(stack == NULL) {
        printf("Underflow!");
        return 0;
    }

    Node* temp = stack;
    stack = temp->next;
    
    int tempData = temp->data;

    free(temp);
    temp = NULL;

    printf("\n%d popped from stack", tempData);

    return tempData;
}

void display() {
    if(stack == NULL) {
        printf("\n\nEmpty stack\n");
        return;
    }

    Node* temp = stack;
    printf("\n\n");
    while(temp != NULL) {
        printf("%d\t->\t", temp->data);
        temp = temp->next;
    }
    printf("NULL\n\n");
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