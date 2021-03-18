#pragma once
#include "header.h"
#include "State.h"

class Play : public State
{
public:

    void virtSetupBackgroundBuffer() override;
    int virtInitialiseObjects() override;
    void virtMouseDown(int iButton, int iX, int iY) override;
    void virtKeyDown(int iKeyCode) override;

    /*void Handle1() override;

    void Handle2() override {
        std::cout << "ConcreteStateA handles request2.\n";
    }*/
};

