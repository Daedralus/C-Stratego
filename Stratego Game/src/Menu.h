#pragma once
#include "header.h"
#include "State.h"
#include "Game.h"
#include "Play.h"

class Menu : public State
{
public:
    void virtSetupBackgroundBuffer() override;
    int virtInitialiseObjects() override;
    void virtMouseDown(int iButton, int iX, int iY) override;
    void virtKeyDown(int iKeyCode) override;

   /* void Handle2() override {
        std::cout << "ConcreteStateB handles request2.\n";
        std::cout << "ConcreteStateB wants to change the state of the context.\n";
        this->context_->TransitionTo(new Play);
    }*/

protected:
    BaseEngine* engine;
};

