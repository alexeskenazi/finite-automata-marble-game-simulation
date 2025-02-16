#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


using namespace std;

struct Test {
    string input;
    char expectedOutput;
    string stateTrail;
};

char playGame(const string &initialState, const string& input, string& outputTrail);

vector<Test> tests = {
    // Provided test cases
    {"0000", 'C', "LLLL->RRLL->CRLR->LRRR->RLRR"},
    {"1111", 'C', "LLLL->CRLL->RRRL->LRRR->CLRR"},
    {"01010101", 'E', "LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL"},
    {"10101010", 'D', "LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL"},
    {"0", 'B', "LLLL->RRLL"},
    {"1", 'B', "LLLL->CRLL"},

    // Extra test cases
    {"00", 'D', "LLLL->RRLL->CRLR"},
    {"000", 'C', "LLLL->RRLL->CRLR->LRRR"},
    {"11", 'C', "LLLL->CRLL->RRRL"},
    {"111", 'D', "LLLL->CRLL->RRRL->LRRR"},
    {"01010101", 'E', "LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL"},
    {"10101010", 'D', "LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL"},
    {"0001", 'C', "LLLL->RRLL->CRLR->LRRR->CLRR"},


    // generated
    {"1110", 'C', "LLLL->CRLL->RRRL->LRRR->RLRR"},
    {"0101010101", 'D', "LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR"},
    {"1010101010", 'C', "LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL"},
    {"00000001", 'D', "LLLL->RRLL->CRLR->LRRR->RLRR->CLRL->LLLL->RRLL->LRLR"},
    {"11111110", 'C', "LLLL->CRLL->RRRL->LRRR->CLRR->RLLR->LLLL->CRLL->LRRL"},
    {"010101010101", 'E', "LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL"},
    {"101010101010", 'D', "LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL"},
    {"00000000", 'D', "LLLL->RRLL->CRLR->LRRR->RLRR->CLRL->LLLL->RRLL->CRLR"},
    {"11111111", 'C', "LLLL->CRLL->RRRL->LRRR->CLRR->RLLR->LLLL->CRLL->RRRL"},
    {"0101010101010101", 'E', "LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL"},
    {"1010101010101010", 'D', "LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL"},
    {"0000000000000000", 'C', "LLLL->RRLL->CRLR->LRRR->RLRR->CLRL->LLLL->RRLL->CRLR->LRRR->RLRR->CLRL->LLLL->RRLL->CRLR->LRRR->RLRR"},
    {"1111111111111111", 'C', "LLLL->CRLL->RRRL->LRRR->CLRR->RLLR->LLLL->CRLL->RRRL->LRRR->CLRR->RLLR->LLLL->CRLL->RRRL->LRRR->CLRR"},
    {"01010101010101010101", 'E', "LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL"},
    {"10101010101010101010", 'D', "LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL"},
    {"00000000000000000000", 'D', "LLLL->RRLL->CRLR->LRRR->RLRR->CLRL->LLLL->RRLL->CRLR->LRRR->RLRR->CLRL->LLLL->RRLL->CRLR->LRRR->RLRR->CLRL->LLLL->RRLL->CRLR"},
    {"11111111111111111111", 'C', "LLLL->CRLL->RRRL->LRRR->CLRR->RLLR->LLLL->CRLL->RRRL->LRRR->CLRR->RLLR->LLLL->CRLL->RRRL->LRRR->CLRR->RLLR->LLLL->CRLL->RRRL"},
    {"010101010101010101010101", 'E', "LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL"},
    {"101010101010101010101010", 'D', "LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL"},
    {"000000000000000000000000", 'D', "LLLL->RRLL->CRLR->LRRR->RLRR->CLRL->LLLL->RRLL->CRLR->LRRR->RLRR->CLRL->LLLL->RRLL->CRLR->LRRR->RLRR->CLRL->LLLL->RRLL->CRLR->LRRR->RLRR->CLRL->LLLL"},
    {"111111111111111111111111", 'E', "LLLL->CRLL->RRRL->LRRR->CLRR->RLLR->LLLL->CRLL->RRRL->LRRR->CLRR->RLLR->LLLL->CRLL->RRRL->LRRR->CLRR->RLLR->LLLL->CRLL->RRRL->LRRR->CLRR->RLLR->LLLL"},
    {"01010101010101010101010101", 'D', "LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR"},
    {"10101010101010101010101010", 'C', "LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL"},
    {"00000000000000000000000000", 'D', "LLLL->RRLL->CRLR->LRRR->RLRR->CLRL->LLLL->RRLL->CRLR->LRRR->RLRR->CLRL->LLLL->RRLL->CRLR->LRRR->RLRR->CLRL->LLLL->RRLL->CRLR->LRRR->RLRR->CLRL->LLLL->RRLL->CRLR"},
    {"11111111111111111111111111", 'C', "LLLL->CRLL->RRRL->LRRR->CLRR->RLLR->LLLL->CRLL->RRRL->LRRR->CLRR->RLLR->LLLL->CRLL->RRRL->LRRR->CLRR->RLLR->LLLL->CRLL->RRRL->LRRR->CLRR->RLLR->LLLL->CRLL->RRRL"},
    {"0101010101010101010101010101", 'E', "LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL"},
    {"1010101010101010101010101010", 'D', "LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL"},
    {"0000000000000000000000000000", 'C', "LLLL->RRLL->CRLR->LRRR->RLRR->CLRL->LLLL->RRLL->CRLR->LRRR->RLRR->CLRL->LLLL->RRLL->CRLR->LRRR->RLRR->CLRL->LLLL->RRLL->CRLR->LRRR->RLRR->CLRL->LLLL->RRLL->CRLR->LRRR->RLRR"},
    {"1111111111111111111111111111", 'C', "LLLL->CRLL->RRRL->LRRR->CLRR->RLLR->LLLL->CRLL->RRRL->LRRR->CLRR->RLLR->LLLL->CRLL->RRRL->LRRR->CLRR->RLLR->LLLL->CRLL->RRRL->LRRR->CLRR->RLLR->LLLL->CRLL->RRRL->LRRR->CLRR"},
    {"010101010101010101010101010101", 'D', "LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR->RLLR->LLLL->RRLL->LRLR"},
    {"101010101010101010101010101010", 'C', "LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL->CLRL->LLLL->CRLL->LRRL"},

};

void runTests(){
    for(size_t i = 0; i < tests.size(); ++i){
        string outputTrail;
        playGame("LLLL", tests[i].input, outputTrail);

        string temp = tests[i].stateTrail;
        temp += " ";
        temp.push_back(tests[i].expectedOutput);

        cout << "play output: " << outputTrail << endl;
        cout << "Test output: " << temp << endl;


        if(temp==outputTrail) {
            cout << "Test passed " << i << " input: " << tests[i].input << endl;
        } else {
            cout << "Test FAILED " << i << " input: " << tests[i].input << endl;
        }
    }
}


char playGame(const string &initialState, const string& input, string& outputTrail) {
    char X1 = 'L';
    char X2 = 'L';
    char X3 = 'L';
    char X4 = 'L';

    X1 = initialState[0];
    X2 = initialState[1];
    X3 = initialState[2];
    X4 = initialState[3]; 
    

    outputTrail.push_back(X1);
    outputTrail.push_back(X2);
    outputTrail.push_back(X3);
    outputTrail.push_back(X4);
    if(input.size()>0){
        outputTrail += "->";
    }

    char* gate = nullptr;
    char output;
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

        if(*gate == 'L'){
            *gate = 'R';
        }
        else if(*gate == 'R'){
            *gate = 'L';
        }

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

    if(argc < 3) {
        cout << "Running tests" << endl;
        runTests();
        return 0;
    }

    string initialState = argv[1];
    string input = argv[2];

    string trail;
    playGame(initialState, input, trail);

    cout << trail << endl;

    return 0;
}
    