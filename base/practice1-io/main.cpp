#include <iostream>

using namespace std;

int main() {
  cout << "Enter the first number: ";
  int first_number = 0;
  cin >> first_number;
  
  cout << "Enter the second number: ";
  int second_number = 0;
  cin >> second_number;
  
  int sum = first_number + second_number;
  
  cout << "Sum: " << sum << "\n";
  
  return 0;
}
