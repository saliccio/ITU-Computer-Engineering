/* @Author
Student Name: Furkan Salık
Student ID : 150200056
Date: 9/11/2021 */


#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <stack>
#include <string>
#include <iomanip>

using namespace std;

void infix_to_postfix(string, string &);
bool higher_priority(char, char);
double eval_postfix(string);
double evaluate(double, double, char);

bool isHigherPriority(char first, char second);

int main()
{
    string infix;
    string postfix;
    bool is_exit = false;

    while (!is_exit)
    {
        cout << "Input the expression in infix: ";
        cin >> infix;

        if (infix == "E" || infix == "e")
            is_exit = true;

        else
        {
            infix_to_postfix(infix, postfix);
            cout << postfix << endl;
            cout << setprecision(2) << fixed << eval_postfix(postfix) << endl;
        }

        cin.clear();
        cin.ignore();
        infix.clear();
        postfix.clear();
    }
    return EXIT_SUCCESS;
}

void infix_to_postfix(string infix, string &postfix)
{
    stack<char> s;

    for (auto it = infix.begin(); it != infix.end(); it++)
    {
        char character = *(it.base());
        if (character >= 48 && character <= 57)
        {
            postfix.append(1, character);
        }
        else if (character == '+' || character == '-' || character == '*' || character == '/')
        {
            while (true)
            {
                if (s.empty())
                {
                    s.push(character);
                    break;
                }

                char topMostCharacter = s.top();
                bool scannedCharHasHigherPriority = isHigherPriority(character, topMostCharacter);

                if (scannedCharHasHigherPriority)
                {
                    s.push(character);
                    break;
                }
                else
                {
                    postfix.append(1, topMostCharacter);
                    s.pop();
                }
            }
        }
    }

    while (!s.empty())    // Append remaining operators to the string, if any. 
    {
        char topCharacter = s.top();
        s.pop();
        postfix.append(1, topCharacter);
    }
}

bool isHigherPriority(char first, char second)
{
    if ((first == second) || (first == '+' && second == '-') || (first == '-' && second == '+') || (first == '*' && second == '/') || (first == '/' && second == '*'))      // If their priorities are same, return false.
    {
        return false;
    }
    else if (first == '*' || first == '/')
        return true;
    else if (second == '+' || second == '-')
        return true;
    else
        return false;
}

bool higher_priority(char first,char second){
    if(first=='*' || first=='/')
        return true;
    else if(second=='+' || second=='-')
        return true;
    else return false;
}

double eval_postfix(string expr)
{
    stack<double> s;
    double first, second;

    for (auto it = expr.begin(); it != expr.end(); it++)
    {
        char character = *(it.base());
        if (character >= 48 && character <= 57)
        {
            s.push(character - 48);
        }
        else if (character == '+' || character == '-' || character == '*' || character == '/')
        {
            second = s.top();
            s.pop();

            first = s.top();
            s.pop();

            double operationResult = evaluate(first, second, character);
            s.push(operationResult);
        }
    }

    return s.top();
}

double evaluate(double first, double second, char c)
{
    switch (c)
    {
    case '*':
        return first * second;
    case '+':
        return first + second;
    case '-':
        return first - second;
    case '/':
        return first / second;
    default:
        return 0;
    }
}
