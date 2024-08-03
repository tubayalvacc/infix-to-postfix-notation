// This program converts an infix expression to postfix notation (Reverse Polish Notation)

#include <iostream> // For standard input/output operations
#include <cstring>  // For C-string manipulation functions like strcpy, strcat
#include <cstdlib>  // For general-purpose functions like memory allocation

int top = -1; // Variable to keep track of the top of the stack
char stack[100] = {0}; // Stack to store operators during conversion

// Function prototypes
void push(const char symbol);   // Function to push an element onto the stack
char pop();                    // Function to pop an element from the stack
void infixToPostfix(const char* infixExpression); // Function to convert infix to postfix

int main() {
    char infixExpression[100] = {0}; // Array to store the input infix expression

    // Prompt the user to enter an infix expression
    std::cout << "\nEnter the infix expression: ";
    std::cin.getline(infixExpression, 80); // Read the input infix expression

    infixToPostfix(infixExpression); // Call the function to convert infix to postfix

    std::getchar(); // Wait for a key press before closing the program
    return 0; // End of the program
}

// Function to push an element onto the stack
void push(const char symbol) {
    if (top == 99) {
        std::cout << "\nStack is full"; // Stack overflow condition
    } else {
        top++; // Increment the top index
        stack[top] = symbol; // Place the symbol at the top of the stack
    }
}

// Function to pop an element from the stack
char pop() {
    char symbol = 0; // Initialize symbol to 0 (equivalent to '\0' in char)

    if (top == -1) {
        std::cout << "Stack is empty"; // Stack underflow condition
    } else {
        symbol = stack[top]; // Get the top element from the stack
        stack[top] = 0; // Reset the stack position to 0
        top--; // Decrement the top index
    }
    return symbol; // Return the popped symbol
}

// Function to convert an infix expression to postfix notation
void infixToPostfix(const char* infixExpression) {
    char infixExpWithParentheses[100] = {0}; // Array to store the modified infix expression
    char postfixExpression[100] = {0};       // Array to store the resulting postfix expression
    char symbol[2] = {0};                    // Temporary array to store single characters
    char temp[2] = {0};                      // Temporary array for operations

    // Add opening and closing parentheses to the infix expression
    strcpy(infixExpWithParentheses, "(");
    strcat(infixExpWithParentheses, infixExpression);
    strcat(infixExpWithParentheses, ")");

    // Iterate through each character in the modified infix expression
    for (int i = 0; i < strlen(infixExpWithParentheses); i++) {
        symbol[0] = infixExpWithParentheses[i]; // Get the current symbol

        if (symbol[0] == '(') {
            push(symbol[0]); // Push opening parenthesis onto the stack
        } else if (symbol[0] == ')') {
            symbol[0] = pop(); // Pop from stack until an opening parenthesis is found
            while (symbol[0] != '(') {
                strncat(postfixExpression, symbol, 1); // Add popped operators to postfix expression
                symbol[0] = pop();
            }
        } else if (symbol[0] == '*' || symbol[0] == '/' || symbol[0] == '+' || symbol[0] == '-') {
            // If the symbol is an operator, handle precedence and associativity
            if (symbol[0] == '*' || symbol[0] == '/') {
                temp[0] = pop();
                while (temp[0] == '*' || temp[0] == '/') {
                    strncat(postfixExpression, temp, 1); // Add operators to postfix expression
                    temp[0] = pop();
                }
                push(temp[0]);
            } else {
                temp[0] = pop();
                while (temp[0] != '(') {
                    strncat(postfixExpression, temp, 1); // Add operators to postfix expression
                    temp[0] = pop();
                }
                push(temp[0]);
            }
            push(symbol[0]); // Push the current operator onto the stack
        } else {
            strncat(postfixExpression, symbol, 1); // Add operands (numbers, variables) directly to postfix
        }
    }
         // Output the current state of the postfix expression
        std::cout << "\n\nPostfix Expression: " << postfixExpression;
}
