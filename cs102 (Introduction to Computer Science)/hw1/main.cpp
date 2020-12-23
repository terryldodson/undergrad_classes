#include <iostream>
using namespace std;

int main() {
		double cost, money, change;
		
		cout << "Enter cost $";
		cin >> cost;
		
		cout << "Enter money $";
		cin >> money;
		
		change = money-cost;
		
		cout << "Change = $" << change << endl;
		
		return 0;
}
