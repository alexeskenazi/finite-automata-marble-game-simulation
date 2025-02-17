#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


using namespace std;

struct Test {
    string initialState;
    string input;
    char expectedOutput;
    string stateTrail;
};

char playGame(const string &initialState, const string& input, string& outputTrail);

vector<Test> tests = {
    // Provided test cases
    {"LLLL", "0000", 'C', "LLLL->RRLL->CRLR->LRRR->RLRR"},
    {"LLLL", "1111", 'C', "LLLL->CRLL->RRRL->LRRR->CLRR"},
    {"LLLL", "01010101", 'E', "LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL"},
    {"LLLL", "10101010", 'D', "LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL"},
    {"LLLL", "0", 'B', "LLLL->RRLL"},
    {"LLLL", "1", 'B', "LLLL->CRLL"},

    // Extra test cases
    {"LLLL", "00", 'D', "LLLL->RRLL->CRLR"},
    {"LLLL", "000", 'C', "LLLL->RRLL->CRLR->LRRR"},
    {"LLLL", "11", 'C', "LLLL->CRLL->RRRL"},
    {"LLLL", "111", 'D', "LLLL->CRLL->RRRL->LRRR"},
    {"LLLL", "01010101", 'E', "LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL"},
    {"LLLL", "10101010", 'D', "LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL"},
    {"LLLL", "0001", 'C', "LLLL->RRLL->CRLR->LRRR->CLRR"},

    // Different start state
    {"RRLL", "000", 'C', "RRLL->CRLR->LRRR->RLRR"},
    {"CRLL", "111", 'C', "CRLL->RRRL->LRRR->CLRR"},
    {"RRLL", "1010101", 'E', "RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL"},
    {"CRLL", "0101010", 'D', "CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL"},

    // generated
    {"LLLL", "1110", 'C', "LLLL->CRLL->RRRL->LRRR->RLRR"},
    {"LLLL", "0101010101", 'D', "LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR"},
    {"LLLL", "1010101010", 'C', "LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL"},
    {"LLLL", "00000001", 'D', "LLLL->RRLL->CRLR->LRRR->RLRR->CLRL->LLLL->RRLL->LRLR"},
    {"LLLL", "11111110", 'C', "LLLL->CRLL->RRRL->LRRR->CLRR->RLLR->LLLL->CRLL->LRRL"},
    {"LLLL", "010101010101", 'E', "LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL"},
    {"LLLL", "101010101010", 'D', "LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL"},
    {"LLLL", "00000000", 'D', "LLLL->RRLL->CRLR->LRRR->RLRR->CLRL->LLLL->RRLL->CRLR"},
    {"LLLL", "11111111", 'C', "LLLL->CRLL->RRRL->LRRR->CLRR->RLLR->LLLL->CRLL->RRRL"},
    {"LLLL", "0101010101010101", 'E', "LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL"},
    {"LLLL", "1010101010101010", 'D', "LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL"},
    {"LLLL", "0000000000000000", 'C', "LLLL->RRLL->CRLR->LRRR->RLRR->CLRL->LLLL->RRLL->CRLR->LRRR->RLRR->CLRL->LLLL->RRLL->CRLR->LRRR->RLRR"},
    {"LLLL", "1111111111111111", 'C', "LLLL->CRLL->RRRL->LRRR->CLRR->RLLR->LLLL->CRLL->RRRL->LRRR->CLRR->RLLR->LLLL->CRLL->RRRL->LRRR->CLRR"},
    {"LLLL", "01010101010101010101", 'E', "LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL"},
    {"LLLL", "10101010101010101010", 'D', "LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL"},
    {"LLLL", "00000000000000000000", 'D', "LLLL->RRLL->CRLR->LRRR->RLRR->CLRL->LLLL->RRLL->CRLR->LRRR->RLRR->CLRL->LLLL->RRLL->CRLR->LRRR->RLRR->CLRL->LLLL->RRLL->CRLR"},
    {"LLLL", "11111111111111111111", 'C', "LLLL->CRLL->RRRL->LRRR->CLRR->RLLR->LLLL->CRLL->RRRL->LRRR->CLRR->RLLR->LLLL->CRLL->RRRL->LRRR->CLRR->RLLR->LLLL->CRLL->RRRL"},
    {"LLLL", "010101010101010101010101", 'E', "LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL"},
    {"LLLL", "101010101010101010101010", 'D', "LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL"},
    {"LLLL", "000000000000000000000000", 'D', "LLLL->RRLL->CRLR->LRRR->RLRR->CLRL->LLLL->RRLL->CRLR->LRRR->RLRR->CLRL->LLLL->RRLL->CRLR->LRRR->RLRR->CLRL->LLLL->RRLL->CRLR->LRRR->RLRR->CLRL->LLLL"},
    {"LLLL", "111111111111111111111111", 'E', "LLLL->CRLL->RRRL->LRRR->CLRR->RLLR->LLLL->CRLL->RRRL->LRRR->CLRR->RLLR->LLLL->CRLL->RRRL->LRRR->CLRR->RLLR->LLLL->CRLL->RRRL->LRRR->CLRR->RLLR->LLLL"},
    {"LLLL", "01010101010101010101010101", 'D', "LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR"},
    {"LLLL", "10101010101010101010101010", 'C', "LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL"},
    {"LLLL", "00000000000000000000000000", 'D', "LLLL->RRLL->CRLR->LRRR->RLRR->CLRL->LLLL->RRLL->CRLR->LRRR->RLRR->CLRL->LLLL->RRLL->CRLR->LRRR->RLRR->CLRL->LLLL->RRLL->CRLR->LRRR->RLRR->CLRL->LLLL->RRLL->CRLR"},
    {"LLLL", "11111111111111111111111111", 'C', "LLLL->CRLL->RRRL->LRRR->CLRR->RLLR->LLLL->CRLL->RRRL->LRRR->CLRR->RLLR->LLLL->CRLL->RRRL->LRRR->CLRR->RLLR->LLLL->CRLL->RRRL->LRRR->CLRR->RLLR->LLLL->CRLL->RRRL"},
    {"LLLL", "0101010101010101010101010101", 'E', "LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL"},
    {"LLLL", "1010101010101010101010101010", 'D', "LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL"},
    {"LLLL", "0000000000000000000000000000", 'C', "LLLL->RRLL->CRLR->LRRR->RLRR->CLRL->LLLL->RRLL->CRLR->LRRR->RLRR->CLRL->LLLL->RRLL->CRLR->LRRR->RLRR->CLRL->LLLL->RRLL->CRLR->LRRR->RLRR->CLRL->LLLL->RRLL->CRLR->LRRR->RLRR"},
    {"LLLL", "1111111111111111111111111111", 'C', "LLLL->CRLL->RRRL->LRRR->CLRR->RLLR->LLLL->CRLL->RRRL->LRRR->CLRR->RLLR->LLLL->CRLL->RRRL->LRRR->CLRR->RLLR->LLLL->CRLL->RRRL->LRRR->CLRR->RLLR->LLLL->CRLL->RRRL->LRRR->CLRR"},
    {"LLLL", "010101010101010101010101010101", 'D', "LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR"},
    {"LLLL", "101010101010101010101010101010", 'C', "LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL"},

};

void runTests(){
    bool passed = true;
    for(size_t i = 0; i < tests.size(); ++i){
        string outputTrail;
        playGame(tests[i].initialState, tests[i].input, outputTrail);

        string temp = tests[i].stateTrail;
        temp += " ";
        temp.push_back(tests[i].expectedOutput);

        cout << "play output: " << outputTrail << endl;
        cout << "Test output: " << temp << endl;


        if(temp==outputTrail) {
            cout << "Test  " << i << " passed input: " << tests[i].input << endl;
        } else {
            cout << "Test  " << i << " FAILED input: " << tests[i].input << endl;
            passed = false;
        }
    }
    if(passed){
        cout << "All tests passed" << endl;
    } else {
        cout << "Some tests failed" << endl;
    }

}


char playGame(const string &initialState, const string& input, string& outputTrail) {
    char X1 = 'L';
    char X2 = 'L';
    char X3 = 'L';
    char X4 = 'L';

    if(initialState.size() == 4){
        X1 = initialState[0];
        X2 = initialState[1];
        X3 = initialState[2];
        X4 = initialState[3]; 
    }

    outputTrail.push_back(X1);
    outputTrail.push_back(X2);
    outputTrail.push_back(X3);
    outputTrail.push_back(X4);
    if(input.size()>0){
        outputTrail += "->";
    }

    char* gate = &X2;
    char output = ' ';
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
        if(gate == &X2 && X2 == 'L'){
            output = 'B';
        }

        if(gate == &X2 && X2 == 'R'){
            output = 'C';
        }

        if(gate == &X3 && X3 == 'L'){
            output = 'C';
        }

        if(gate == &X3 && X3 == 'R'){
            output = 'D';
        }

        if(gate == &X4 && X4 == 'L'){
            output = 'D';
        }

        if(gate == &X4 && X4 == 'R'){
            output = 'E';
        }

         // Update the state:
        // For X1 we follow the algo for 0 or 1
        // For the X2 to X4 we swap the value of the gate used
        // X1 on 0 goes L->R->C->L
        // X1 on 1 goes L->C->R->L
        if(read == '0'){
            if(X1 == 'L'){
                X1 = 'R';
            }
            else if (X1 == 'R'){
                X1 = 'C';
            }
            else if(X1 == 'C'){
                X1 = 'L';
            }

        }
        else if(read == '1'){
            if(X1 == 'L'){
                X1 = 'C';
            }
            else if(X1 == 'C'){
                X1 = 'R';
            }
            else if(X1 == 'R'){
                X1 = 'L';
            }
        }

        // X2, X3, X4 are always swapped
        if(*gate == 'L'){
            *gate = 'R';
        }
        else if(*gate == 'R'){
            *gate = 'L';
        }

        // Keep track of the state history
        outputTrail.push_back(X1);
        outputTrail.push_back(X2);
        outputTrail.push_back(X3);
        outputTrail.push_back(X4);

        if(i != input.size()-1){
            outputTrail += "->";
        }
    }
    // if(output == 'B' || output == 'D'){
    //     cout << "Final output is " << output << ", You Win!" << endl;
    // }
    // else if(output == 'C' || output == 'E'){
    //     cout << "Final output is " << output << ", You Lose" << endl;
    // }

    outputTrail += " ";
    outputTrail.push_back(output);

    // cout << "input: " << input << " trail: " << outputTrail  << endl;

    return output;
}



int main(int argc, char* argv[]) {

    if(argc == 2 && (string(argv[1]) == "test" || string(argv[1]) == "tests")) {
        cout << "Running tests" << endl;
        runTests();
        return 0;
    }

    if(argc < 3) {
        // output usage instructions
        if (argc != 3) {
            cout << "******************************************************" << endl;
            cout << "* Marble game state machine" << endl;
            cout << "******************************************************" << endl;
            cout << "* " << endl;
            cout << "* Usage 1: " << argv[0] << " <initial State> <input string>" << endl;
            cout << "* Usage 2: " << argv[0] << " test" << endl;
            cout << "* Examples:" << endl;
            cout << "*    " << argv[0] << " CRLL 010111" << endl;
            cout << "*    " << argv[0] << " test" << endl;
            cout << "* " << endl;
            cout << "* Notes:" << endl;
            cout << "* - Intial State has 4 letters representing the gate state:" << endl;
            cout << "* -- X1 can be L C R for Left Center Right" << endl;
            cout << "* -- X2, X3, X4 can be L or R for Left or Right" << endl;
            cout << "* - After a 0 hits X1 it switches L->R->C->L" << endl;
            cout << "* - After a 1 hits X1 it switches L->C->R->L" << endl;
            cout << "* - After a 0 or a 1 hits X2, X3, or X4 it switches L->R->L" << endl;
            cout << "* " << endl;
            cout << "******************************************************" << endl;
            return 0;
        }

        return 0;
    }

    string initialState = argv[1];
    string input = argv[2];

    string trail;
    playGame(initialState, input, trail);

    cout << trail << endl;

    return 0;
}
    