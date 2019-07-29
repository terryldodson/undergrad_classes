#include <iostream>
using namespace std;

int main()
{
    int volts, amps, watts;    

    cout << "Enter volts: ";
    cin >> volts;

    cout << "Enter amps: ";
    cin >> amps;

    watts = volts * amps;

    cout <<endl<< volts << " volts and " << amps << " amps = " << watts << " watts." << endl;
    return 0;
}
