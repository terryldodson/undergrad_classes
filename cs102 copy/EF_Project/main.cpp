#include <stdio.h>
#include <iostream>
#include <cmath>
using namespace std;

const double mpuck = 0.009; //killograms
const double f1 = 0.0164921466; //friction force on puck on table - Newtons
const double f2 = 0.0185950413; //friction force of the bottom
const double d2 = 12; //distance from where puck is to the end of the board - cm
const double hofbase = 0.5; //centimeters or .005 m
const double g = 9.81;
const double mhammer = 0.072; //kg
const double e = 0.0955964176; //coefficient of restitution between hammer and puck
const double eEF = .9207269659; //coefficient of restitution between EF puck and puck
const double mEFpuck = .01; // mass of ef puck
const double Fef = .01875; //friction force on ef puck on table - Newtons

int main(){
	double heightofhammer,vhammer, vpucktab, distance, x, y, degangle, radangle, vpafth, Vef, V1, Vpt; //distance in cm
	int number;
	
	cout << "Enter box number: " << endl;
	cin >> number;
	
	switch(number){
		case 1:
			x = -25;
			y = 50;
			break;
		case 2:
			x = 0;
			y = 50;
			break;
		case 3:
			x = 25;
			y = 50;
			break;
		case 4:
			x = -25;
			y = 75;
			break;
		case 5:
			x = 0;
			y = 75;
			break;
		case 6:
			x = 25;
			y = 75;
			break;
		case 7:
			x = -25;
			y = 100;
			break;
		case 8:
			x = 0;
			y = 100;
			break;
		case 9:
			x = 25;
			y = 100;
			break;
		case 10:
			Vef = sqrt((2 * Fef * .4) / mEFpuck);
			V1 = (Vef * ((.01 / .009) + 1)) / (1 + eEF);
			Vpt = sqrt(pow(V1,2) + (2 / .009) * (f1 * .85));
			vpafth = sqrt(pow(Vpt,2) + ((2/mpuck) * f2 * d2) - 2*g*hofbase);
			vhammer = (vpafth * (mpuck/mhammer + 1))/(1+e);
			heightofhammer = (pow(vhammer,2)/19.62);
			cout << "Put pin on EF puck setting"<< endl;
			return 1;
			break;
		default:
			cout << "Box number doesn't exist" << endl;
			return -1;
	}
	distance = sqrt(pow(x,2) + pow(y,2));
	radangle = asin(x/distance);
	degangle = radangle * 57.2958;
	
	cout << "Angle: " << degangle << endl;
	
	vpucktab = sqrt((2*f1*distance)/mpuck);

	vpafth = sqrt(pow(vpucktab,2) + ((2/mpuck) * f2 * d2) - 2*g*hofbase);

	vhammer = (vpafth * (mpuck/mhammer + 1))/(1+e);
	heightofhammer = (pow(vhammer,2)/19.62);
	
	cout << "Put pin at setting: " << number << endl;
	return 0;
}