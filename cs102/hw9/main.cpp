#include <iostream>
using namespace std;

int main(){
   double v, p, a, e;
   double shark1, shark2, shark3, shark4;
   int s; 
   cout<< "Please enter the company value: "; 
   cin>>v;
   cout<< "please enter the value added for shark 1: "; 
   cin>>shark1;
   cout<< "please enter the value added for shark 2: " ;
   cin>>shark2;
   cout<< "please enter the value added for shark 3: "; 
   cin>>shark3;
   cout<< "please enter the value added for shark 4: "; 
   cin>>shark4;

	p =1;

	while (p != 0) {
		cout << "Please enter the price: ";
		cin >> p;

		cout << "Please enter the equity: ";
		cin >> e;

		cout << "Which shark (1,2,3,4): " << endl;
		cin >> a;
   
   switch(static_cast<int> (a)) {
      case 1:
         a = shark1;
         break;
      case 2:
         a = shark2;
         break;
      case 3:
         a = shark3;
         break;
      case 4:
         a = shark4;
         break;
   }

   s = p - (e * v) + (a * v);

   if (p == 0)
      break;

   cout << "The final value would be " << fixed << s << endl;
	}
	
	return 0;
}// end of program
