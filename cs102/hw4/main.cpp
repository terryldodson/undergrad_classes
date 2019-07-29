#include <iostream>
#include <iomanip>

using namespace std;

double const DOLLAR_BILL_THICKNESS = 0.0043; //in inches

int main()
{
	double distance, debt, trips;
	
	cout << "Enter a distance in miles: ";
	cin >> distance;
	
	cout << "Enter the debt in dollars: ";
	cin >> debt;
	
	trips = (DOLLAR_BILL_THICKNESS * debt) / (distance * 5280 * 12);
	
	cout <<fixed<<showpoint<<setprecision(3);
	cout << "\n\nYour debt travels " << debt * DOLLAR_BILL_THICKNESS << " inches\nor " << (debt * DOLLAR_BILL_THICKNESS) / 1. / 5280 << " miles.\n";
	cout << "\n\nWith a debt of " << debt << "\nand a distance of " << distance << ",\nyou can make " << trips << " trips." << endl;

   return 0;
}                 
