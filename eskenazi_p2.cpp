#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


using namespace std;

bool debug = false;


int main(int argc, char* argv[]) {

    if(argc == 2 && (string(argv[1]) == "test" || string(argv[1]) == "tests")) {
        cout << "Running tests" << endl;
        //runTests();

        // We get a character from the input string
        // Decide where it goes
        //.	Depending on X1 we choose X2,X3, or X4
        //	Depending on the gate we determine the exit

        // Update the state:
        // For X1 we follow the algo for 0 or 1
        // For the X2 to X4 we swap the value of the gate used


        // X1 on 0 L->R->C
        // X1 on 1 L->C->R

        // X2 to X4  L->R
        return 0;
    }
    char X1 = 'L';
    char X2 = 'L';
    char X3 = 'L';
    char X4 = 'L';

    char* gate = nullptr;
    string input = "01011";
    for(size_t i = 0; i < input.size(); ++i){
        // We get a character from the input string
        char read = input[i];

        // Decide where it goes
        // Depending on X1 we choose X2,X3, or X4
        if(X1 == 'L'){
            gate = &X2;
            
        }

        if(X1 == 'C'){
            gate = &X3;
            
        }

        if(X1 == 'R'){
            gate = &X4;
            
        }

        //	Depending on the gate we determine the exit
        char output;
        if(gate == &X2 && X2 == 'L'){
            output = 'B';
            cout << "Result is " << output << endl;
        }

    }

    return 0;
}
    