// Copyright 2021 Igumnova Natasha
#include "postfix.h"
#include "MyStack.h"

int priorit(char sign) {
    switch (sign) {
    case '(': return 0; break;
    case ')': return 1; break;
    case '+': return 2; break;
    case '-': return 2; break;
    case '*': return 3; break;
    case '/': return 3; break;
    default: return -1; break;
    }
}
bool isNum(char elem) {
    return (elem >= '0' && elem <= '9' || elem == '.');
}
std::string infix2postfix(std::string s1) {
    MyStack<char> operstack(10);
    std::string res = "";
    std::string num = "";
    for (int i = 0; i < s1.length(); i++) {
        if (s1[i] == ' ') {
            if (num != "") {
                res = res + num + " ";
                num = "";
            }
            continue;
        }	
        if (isNum(s1[i])) {
            num += s1[i];
        }
        if (priorit(s1[i]) == 0) {
            operstack.push(s1[i]);
        }
        if (priorit(s1[i]) == 1) {
            if (num != "") {
                res = res + num + " ";
                num = "";
            }
            while (operstack.get() != '(') {
                res = res + operstack.pop() + " ";
            }
            operstack.pop();
        }
        if (priorit(s1[i]) == 2 || priorit(s1[i]) == 3) {
            if (operstack.isEmpty() || priorit(operstack.get()) < priorit(s1[i])) {
                operstack.push(s1[i]);
            } else {
                res = res + operstack.pop() + " ";
                operstack.push(s1[i]);
            }
        }
    }
    if (num != "") {
        res = res + num + " ";
    }
    while (!operstack.isEmpty()) {
        res = res + operstack.pop() + " ";
    }
    return res;
}
