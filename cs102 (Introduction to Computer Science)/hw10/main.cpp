#include <iostream>

#include <iomanip>

 

using namespace std;

 

int main()

{

    int choice;

    int amt;

   

    do {

        cout << "Make a choice from the following menu:" << endl;

        cout << "   1. Add a user" << endl;

        cout << "   2. Delete a user" << endl;

        cout << "   3. Modify a user" << endl;

        cout << "   4. View a user" << endl;

        cout << "   5. Contact a user" << endl;

        cin >> choice;

        // I want to keep looping if the choice is outside of 1-5,

    } while (choice < 0 || choice > 5);

 

    switch (choice) {

        case 1: {

            cout << "You chose 'add a user'" << endl;
            break;

        }

        case 2: {

            cout << "You chose 'delete a user'" << endl;
            break;

        }

        case 3: {

            cout << "You chose 'modify a user'" << endl;
            break;

        }

        case 4: {

            cout << "You chose 'view a user'" << endl;
            break;

        }

        case 5: {

            cout << "How many users? ";

            cin >> amt;

            cout << "Enter users:" << endl;

            //I want to grab a name for each of the users that

            //the user gives me and output it with "Contacting <username>"

            for (int i = 0;i < amt;i++) {

                string name;

                cin >> name;
                  
                cout << "Contacting " << name << endl;

            }

            break;

        }

        default: {

            cout << "Unknown choice: " << choice << endl;

            break;

        }

    }

   

    return 0;

}