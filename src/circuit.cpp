#include "nd_fsm.h"

#include <cstdlib>
#include <ctime>

ND_FSM::ND_FSM() {}

ND_FSM::ND_FSM(const std::string &inputFile) {
    std::ifstream fsmIn(inputFile);
    ReadHeader(fsmIn);
    ReadTransitions(fsmIn);
}

ND_FSM::ND_FSM(const ND_FSM &otherND_FSM)
    : statesNumber(otherND_FSM.statesNumber) 
    , inputsNumber(otherND_FSM.inputsNumber)
    , outputsNumber(otherND_FSM.outputsNumber)
    , transitionsNumber(otherND_FSM.transitionsNumber)
    , extInputsNumber(otherND_FSM.extInputsNumber)
    , initialStateVector(otherND_FSM.initialStateVector)
    , io_succsesor_table(otherND_FSM.io_succsesor_table) {}

int ND_FSM::GetStatesNumber() const {
    return statesNumber;
}

void ND_FSM::ReadHeader(std::ifstream &fsmIn) {
    std::string str;
    int F;
    fsmIn >> str; fsmIn >> F;
    fsmIn >> str; fsmIn >> statesNumber;
    fsmIn >> str; fsmIn >> inputsNumber;
    fsmIn >> str; fsmIn >> outputsNumber;
    fsmIn >> str;
    fsmIn >> str;
    while (str != "p") {
        int currentInitialState = 0;
        for (int i = 0; i < str.size(); ++i) {
            if ((str[i] >= '0') && (str[i] <= '9')) {
                currentInitialState = currentInitialState * 10 + (str[i] - '0');
            }
        }
        initialStateVector.push_back(currentInitialState);
        str.clear();
        fsmIn >> str;
    }
    fsmIn >> transitionsNumber;
    extInputsNumber = inputsNumber * outputsNumber;
    for (int i = 0; i < statesNumber; ++i) {
        std::vector<io_succsesor> stateVector(extInputsNumber);
        io_succsesor_table.push_back(stateVector);
    }
}

void ND_FSM::ReadTransitions(std::ifstream &fsmIn) {
    int currentState, input, output, nextState;
    int ext_input;
    for (int i = 0; i < transitionsNumber; ++i) {
        fsmIn >> currentState;
        fsmIn >> input;
        fsmIn >> nextState;
        fsmIn >> output;
        ext_input = input * outputsNumber + output;
        if (io_succsesor_table[currentState][ext_input].activeFlag == false) {
            io_succsesor_table[currentState][ext_input].nextState = nextState;
            io_succsesor_table[currentState][ext_input].activeFlag = true;
        } else {
            std::cout << "nonobservable_FSM" << std::endl;
            exit(0);
        }
    }
}

void ND_FSM::convertStrToVectorInt(const std::string &str, int startIndex, std::vector<int> &vec) {
    int dig = 0;
    for (int i = startIndex; i < str.size(); ++i) {
        while ((i < str.size()) && (str[i] != ' ')) {
            dig = dig * 10 + (str[i] - '0');
            ++i;
        }
        if (str[i] == ' ') {
            vec.push_back(dig);
            dig = 0;
        }
    }
    vec.push_back(dig);
    dig = 0;
}

void ND_FSM::PrintFSM() const {
    std::cout << "statesNumber = " << statesNumber << std::endl;
    std::cout << "inputsNumber = " << inputsNumber << std::endl;
    std::cout << "outputsNumber = " << outputsNumber << std::endl;
    std::cout << "transitionsNumber = " << transitionsNumber << std::endl;
    std::cout << "extInputsNumber = " << extInputsNumber << std::endl;
    std::cout << "initialStateVector: ";
    for (const auto &elem: initialStateVector) {
        std::cout << elem << ' ';
    }
    std::cout << std::endl;

    std::cout << "io_succsesor_table" << std::endl;
    for (int i = 0; i < io_succsesor_table.size(); ++i) {
        std::cout << "state_" << i << ": " << std::endl;
        for (int j = 0; j < io_succsesor_table[i].size(); ++j) {
            if (io_succsesor_table[i][j].activeFlag == false) {
                std::cout << "- ";
            } else {
                std::cout << io_succsesor_table[i][j].nextState << " ";
            }
        }
        std::cout << std::endl;
    }
}

/*
std::ostream& operator<< (std::ostream &out, const ND_FSM &fsm) {
    out << "F " << 1 << std::endl;
    out << "s " << fsm.statesNumber << std::endl;
    out << "i " << fsm.inputsNumber << std::endl;
    out << "o " << fsm.outputsNumber << std::endl;
    out << "n0";
    for (int i = 0; i < fsm.initialStateVector.size(); ++i) {
        out << ' ' << fsm.initialStateVector[i];
    }
    out << std::endl << "p " << fsm.transitionsNumber << std::endl;
    for (unsigned int s = 0; s < fsm.statesNumber; s++) {
        for (unsigned int i = 0; i < fsm.inputsNumber; i++) {
            for (unsigned int t = 0; t < fsm.stateTable[s][i].size(); t++) {
                out << s << ' ' << i << ' ' << fsm.stateTable[s][i][t].nextState<< ' '
                << fsm.stateTable[s][i][t].output<< std::endl;
            }
        }
    }
    return out;
}
*/
