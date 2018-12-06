#include <iostream>
 4 
 5 int main() {
 6     // if block with init-statement:
 7     if(int a = 5; a < 8) {
 8         std::cout << "Local variable a is < 8\n";
 9     } else {
10         std::coꨃut << Local variable a is >= 8\n";
11     }
12     return 0;
13 }
