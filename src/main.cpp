#include <cmath>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
using namespace std;

bool isOperator(char c) { return c == '+' || c == '-' || c == '*' || c == '/' || c == '^'; }

int precedence(char c) {
    if (c == '^')
        return 3;
    if (c == '*' || c == '/')
        return 2;
    if (c == '+' || c == '-')
        return 1;
    return -1;
}

// Convert infix to postfix, numbers separated by space
string InfixToPostfix(const string &infix) {
    stack<char> s;
    string postfix;
    for (size_t i = 0; i < infix.size(); i++) {
        char c = infix[i];

        // Skip spaces
        if (c == ' ')
            continue;

        // Number (handle multi-digit)
        if (isdigit(c)) {
            while (i < infix.size() && (isdigit(infix[i]) || infix[i] == '.')) {
                postfix += infix[i];
                i++;
            }
            postfix += ' '; // separator
            i--;
        }
        // Parentheses
        else if (c == '(')
            s.push(c);
        else if (c == ')') {
            while (!s.empty() && s.top() != '(') {
                postfix += s.top();
                s.pop();
                postfix += ' ';
            }
            if (!s.empty())
                s.pop();
        }
        // Operator
        else if (isOperator(c)) {
            while (!s.empty() && precedence(c) <= precedence(s.top())) {
                postfix += s.top();
                s.pop();
                postfix += ' ';
            }
            s.push(c);
        }
    }

    while (!s.empty()) {
        postfix += s.top();
        s.pop();
        postfix += ' ';
    }

    return postfix;
}

// Evaluate postfix expression
double evaluatePostfix(const string &postfix) {
    stack<double> operands;
    stringstream ss(postfix);
    string token;

    while (ss >> token) {
        if (isdigit(token[0]) || (token.size() > 1 && token[0] == '-')) {
            operands.push(stod(token));
        } else if (isOperator(token[0])) {
            if (operands.size() < 2) {
                cerr << "Error: not enough operands for operator " << token << endl;
                return 0;
            }
            double val1 = operands.top();
            operands.pop();
            double val2 = operands.top();
            operands.pop();
            switch (token[0]) {
                case '+':
                    operands.push(val2 + val1);
                    break;
                case '-':
                    operands.push(val2 - val1);
                    break;
                case '*':
                    operands.push(val2 * val1);
                    break;
                case '/':
                    operands.push(val2 / val1);
                    break;
                case '^':
                    operands.push(pow(val2, val1));
                    break;
            }
        }
    }
    return operands.top();
}

int main() {
    string infix;
    cout << "Enter infix expression: ";
    getline(cin, infix);

    string postfix = InfixToPostfix(infix);
    cout << "Postfix expression: " << postfix << endl;

    double result = evaluatePostfix(postfix);
    cout << "Evaluated result: " << result << endl;

    return 0;
}
