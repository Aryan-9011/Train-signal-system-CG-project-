#include <iostream>
#include <string>
using namespace std;
#define MAX 50;

char stack[20];
int top = -1;

void push(char value)
{
  if (top == 19)
  {
    cout << "STACK FULL";
  }
  else
  {
    top++;
    stack[top] = value;
  }
}

char pop()
{
  if (top == -1)
  {
    cout << "Stack EMPTY";
  }
  else
  {
    char returnchar = stack[top];
    stack[top] = '\0';
    top--;
    return returnchar;
  }
  return 0;
}

int checkPresedance(char value)
{
  if (value == '+' || value == '-')
  {
    return 1;
  }
  else if (value == '*' || value == '/')
  {
    return 2;
  }
  else if (value == '$')
  {
    return 3;
  }
  else
  {
    return 0;
  }
}

string infixToPostfix(string infix)
{
  string postFix = "";
  for (int i = 0; i < infix.length(); i++)
  {
    if (infix[i] >= 'a' && infix[i] <= 'z' || infix[i] >= 'A' && infix[i] <= 'Z')
    {
      postFix.insert(postFix.end(), infix[i]);
    }
    else if (infix[i] == '(' || infix[i] == '{' || infix[i] == '[')
    {
      push(infix[i]);
    }
    else if (infix[i] == ')' || infix[i] == '}' || infix[i] == ']')
    {
      if (infix[i] == ')')
      {
        while (stack[top] != '(')
        {
          postFix.insert(postFix.end(), pop());
        }
        pop();
      }
      if (infix[i] == ']')
      {
        while (stack[top] != '[')
        {
          postFix.insert(postFix.end(), pop());
        }
        pop();
      }
    }
    else
    {
      if (top == -1)
      {
        push(infix[i]);
      }
      else if (checkPresedance(infix[i]) <= checkPresedance(stack[top]))
      {
        postFix.insert(postFix.end(), pop());
        while (checkPresedance(stack[top]) == checkPresedance(infix[i]))
        {
          postFix.insert(postFix.end(), pop());
          if (top < 0)
          {
            break;
          }
        }
        push(infix[i]);
      }
      else if (checkPresedance(infix[i]) > checkPresedance(stack[top]))
      {
        push(infix[i]);
      }
    }
  }
  while (top != -1)
  {
    postFix.insert(postFix.end(),pop());
  }
  cout<<"The converted postfix string is : "<<postFix<<endl;
  return postFix;
}

int main()
{
  int count;
  string infix,postfix;
  cout<<"\nEnter the infix expression : "<<endl;
  cin>>infix;
  postfix = infixToPostfix(infix);
  return 0;
}