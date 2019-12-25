#ifndef ND_FSM_H
#define ND_FSM_H

#include <iostream>
//#include <ostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <sstream>

struct io_succsesor {
    int nextState;
    bool activeFlag;

    io_succsesor(int nextState = -1, bool activeFlag = false)
        : nextState(nextState)
        , activeFlag(activeFlag) {}
};

class ND_FSM {
    int statesNumber;
    int inputsNumber;
    int outputsNumber;
    int transitionsNumber;
    int extInputsNumber;
    std::vector<int> initialStateVector;
    std::vector<std::vector<io_succsesor>> io_succsesor_table;

    void convertStrToVectorInt(const std::string &str, int startIndex, std::vector<int> &vec);
    void ReadHeader(std::ifstream &fsmIn);
    void ReadTransitions(std::ifstream &fsmIn);

public:
    ND_FSM();
    ND_FSM(const std::string &inputFile);
    ND_FSM(const ND_FSM &otherND_FSM);
    void PrintFSM() const;
    int GetStatesNumber() const;

    friend std::ostream& operator<< (std::ostream &out, const ND_FSM &fsm);
    friend class Homing_FSM;
};

#endif