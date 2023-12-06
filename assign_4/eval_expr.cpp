/**
 * Implementation of the functions to evaluate arithmetic expressions
 * The implementation should use the Stack data structure
 */
//You should always comments to each function to describe its PURPOSE and PARAMETERS
#include "stack.h"
#include "eval_expr.h"

/**
 * Returns whether the specified character is a valid operator ('+', '-', '/', or '*')
*/
bool isOperator(char character) {
    return character == '+' || character == '-' || character == '/' || character == '*';
}

/**
 * @brief applies the supplied operation as a <op> b;
 * @param a the first argument
 * @param b the second argument
 * @param op either '+', '-', '/', or '*'. If op is not one of these, the function returns 0
 * @return the result, or 0 if the operator was invalid
*/
float applyOperator(float a, float b, char op) {
    switch (op)
    {
    case '+':
        return a+b;
        break;
    case '-':
        return a-b;
        break;
    case '/':
        return a/b;
        break;
    case '*':
        return a*b;
        break;
    default:
        return 0;
        break;
    }
}
/**
 * @brief Evaluate a postfix expression
 * @param postfix_expr The input expression in the postfix format.
 * @param result gets the evaluated value of the expression (by reference).
 * @return true if expression is a valid postfix expression and evaluation is done without error, otherwise false.
 */
bool evalPostfixExpr(string postfix_expr, float& result) {
    Stack<float> stack;
    for (auto it = postfix_expr.cbegin(); it != postfix_expr.cend(); it++) {
        if (*it >= '0' && *it <= '9') {
            stack.push(*it - '0');
        } else if (isOperator(*it)) {
            if (stack.size() >= 2) {
                float a,b;
                stack.pop(b);
                stack.pop(a);
                if (b == 0 && *it == '/') {
                    return false;
                }
                stack.push(applyOperator(a, b, *it));
            } else {
                return false;
            }
        } else {
            return false;
        }
    }
    if (stack.size() != 1) {
        return false;
    }
    stack.pop(result);
    return true;
}

/**
 * Returns true if b is of higher precedence than a, or if b is a left parenthesis.
*/
bool higherPrecedence (const char a, const char b) {
    if (b == '(') {
        return true;
    }
    if (b == '*' || b == '/') {
        return false;
    } else if (a == '*' || a == '/') {
        return true;
    } else {
        return false;
    }
}

/**
 * @brief Convert an infix expression to an equivalent postfix expression
 * @param infix_expr The input expression in the infix format.
 * @return the converted postfix expression. If the input infix expression is invalid, return an empty string "";
 */
string convertInfixToPostfix(string infix_expr) {
    Stack<char> stack;
    string postfix_expr = "";
    for (auto it = infix_expr.cbegin(); it <= infix_expr.cend(); it++) {
        // 2.	If it’s a operand (such as 2, 3, and 4), the item is directly appended to the output postfix expression.
        if (*it >= '0' && *it <= '9') {
            postfix_expr+=*it;
        } else
        // 3.	If it’s a left parenthesis, it is pushed onto a stack.
        if (*it == '(') {
            stack.push(*it);
        } else
        // 4.	If it’s a right parenthesis,
        // if the stack is empty, expression invalid, otherwise: 
        // the symbol on the top of the stack is popped off the stack
        //and appended to the output.
        // This process repeats until the top of the stack is a left parenthesis.
        //When that occurs, both parentheses are discarded. 
        if (*it == ')') {
            if (stack.isEmpty()) {
                return "";
            }
            while (stack.top() != '(') {
                char top;
                stack.pop(top);
                postfix_expr+=top;
            }
            char left_paren = '\0';
            stack.pop(left_paren);
        }
        else
        //   6.	If it’s an operator with a lower or the same precedence
        // than the one at the top of the stack,
        //the one at the top of the stack is popped off and
        //appended to the output.
        // The symbol being scanned will be compared with the new top element on the stack,
        // and the process continues.
        if ( isOperator(*it)) {
            while (true) {
                if (isOperator(*it) && higherPrecedence(*it, stack.top())) {
                    stack.push(*it);
                    break;
                } else if ( isOperator(*it) && stack.isEmpty()) {
                    stack.push(*it);
                    break;

                } else if (isOperator(*it) && !higherPrecedence(*it, stack.top())){
                    char top;
                    stack.pop(top);
                    postfix_expr += top;
                    continue;
                }
            }
        }
    }
    while (!stack.isEmpty()) {
        char top;
        
        stack.pop(top);
        if (top == ')') {
            return "";
        }
        postfix_expr += top;
    }
    return postfix_expr;
}

/**
 * @brief Evaluate an infix expression. It's converted to a postfix expression first and then evaluated
 * @param infix_expr The input expression in the infix format.
 * @param result gets the evaluated value of the expression (by reference).
 * @return true if expression is valid and evaluation is done without error, otherwise false.
 */
bool evalInfixExpr(string infix_expr, float& result) {
    return evalPostfixExpr(convertInfixToPostfix(infix_expr), result);
}