#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAX_LIVES 5 // Maximum lives a player has

// Stack structure
typedef struct {
    int *arr;   // Dynamic array for the stack
    int top;    // Index of the top element
    int maxSize; // Maximum size of the stack
} Stack;

// Function prototypes
void initializeStack(Stack *stack, int size);
bool isFull(Stack *stack);
bool isEmpty(Stack *stack);
void push(Stack *stack, int value);
int pop(Stack *stack);
void displayStack(Stack *stack);
void displayHUD(int level, int lives, int score, int timeRemaining);
void showStackVisual(Stack *stack);
void startGame();

int main() {
    startGame();
    return 0;
}

// Initialize the stack
void initializeStack(Stack *stack, int size) {
    stack->arr = (int *)malloc(size * sizeof(int));
    stack->top = -1;
    stack->maxSize = size;

    // Pre-fill the stack with some random values
    int initialElements = size / 2; // Fill half the stack
    for (int i = 0; i < initialElements; i++) {
        stack->arr[++stack->top] = rand() % 100;
    }
}

// Check if the stack is full
bool isFull(Stack *stack) {
    return stack->top == stack->maxSize - 1;
}

// Check if the stack is empty
bool isEmpty(Stack *stack) {
    return stack->top == -1;
}

// Push a value onto the stack
void push(Stack *stack, int value) {
    if (isFull(stack)) {
        printf("Stack is full! Cannot push %d.\n", value);
        return;
    }
    stack->arr[++stack->top] = value;
    printf("Pushed %d onto the stack.\n", value);
}

// Pop a value from the stack
int pop(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty! Cannot pop.\n");
        return -1;
    }
    int value = stack->arr[stack->top--];
    printf("Popped %d from the stack.\n", value);
    return value;
}

// Display the stack visually
void showStackVisual(Stack *stack) {
    printf("Stack Visual: ");
    for (int i = 0; i < stack->maxSize; i++) {
        if (i <= stack->top) {
            printf("* ");
        } else {
            printf("_ ");
        }
    }
    printf("\n");
}

// Display the stack contents
void displayStack(Stack *stack) {
    printf("Current Stack: ");
    if (isEmpty(stack)) {
        printf("[Empty]\n");
    } else {
        for (int i = 0; i <= stack->top; i++) {
            printf("%d ", stack->arr[i]);
        }
        printf("\n");
    }
    showStackVisual(stack);
}

// Display the Head-Up Display (HUD)
void displayHUD(int level, int lives, int score, int timeRemaining) {
    printf("\n========================\n");
    printf("Level: %d | Lives: %d | Score: %d | Time: %d seconds\n", level, lives, score, timeRemaining);
    printf("========================\n\n");
}

// Start the game
void startGame() {
    int lives = MAX_LIVES;
    int score = 0;
    int currentLevel = 1;

    printf("Welcome to the Stack Game!\n");
    printf("Objective: Perform push and pop operations to score points.\n");
    printf("Rules: Push adds stones, pop removes stones. Lose a life for invalid actions or wrong answers.\n\n");

    while (lives > 0) {
        int stackSize = 4 + currentLevel; // Increase stack size with each level
        Stack stack;
        initializeStack(&stack, stackSize);

        bool levelComplete = false; // Flag to track level completion
        int timeLimit = 90; // Set time limit for the level
        time_t startTime = time(NULL); // Record the start time

        printf("Level %d\n", currentLevel);
        while (lives > 0 && !levelComplete) {
            int elapsedTime = time(NULL) - startTime; // Calculate elapsed time
            int timeRemaining = timeLimit - elapsedTime; // Calculate remaining time

            if (timeRemaining <= 0) {
                // printf("Time's up! You lose a life.\n");
                // lives--;
                lives = 0;
                break;
            }

            displayHUD(currentLevel, lives, score, timeRemaining);
            displayStack(&stack);

            // Ask user to check stack status
            printf("What is the status of the stack? (Enter 1 for Full, 2 for Empty, 3 for Neither): ");
            int statusAnswer;
            scanf("%d", &statusAnswer);

            // Validate the user's answer
            if ((statusAnswer == 1 && isFull(&stack)) ||
                (statusAnswer == 2 && isEmpty(&stack)) ||
                (statusAnswer == 3 && !isFull(&stack) && !isEmpty(&stack))) {
                printf("Correct!\n");
                if (statusAnswer == 1 || statusAnswer == 2) {
                    levelComplete = true; // Complete level only for "Full" or "Empty" answers
                }
            } else {
                printf("Incorrect! You lose a life.\n");
                lives--;
                continue;
            }

            if (!levelComplete) { // Allow stack operations only if the level is not complete
                printf("Choose an action: \n1. Push\n2. Pop\nEnter your choice: ");
                int choice;
                scanf("%d", &choice);

                if (choice == 1) { // Push operation
                    if (isFull(&stack)) {
                        printf("Invalid action! Stack is full.\n");
                        lives--;
                    } else {
                        int value = rand() % 100; // Generate a random stone value
                        push(&stack, value);
                        score += 10;
                    }
                } else if (choice == 2) { // Pop operation
                    if (isEmpty(&stack)) {
                        printf("Invalid action! Stack is empty.\n");
                        lives--;
                    } else {
                        pop(&stack);
                        score += 10;
                    }
                } else {
                    printf("Invalid choice! Please enter 1 or 2.\n");
                }
            }
        }

        if (levelComplete && lives > 0) {
            printf("Congratulations! You passed Level %d.\n", currentLevel);
            currentLevel++;
        }
        free(stack.arr); // Free allocated memory for the stack
    }

    printf("\nGame Over! Your final score: %d\n", score);
}
