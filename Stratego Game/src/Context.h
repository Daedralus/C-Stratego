#pragma once
#include "header.h"
#include "State.h"
class Context
{
private:
    State* state_;

public:
    Context(State* state) : state_(nullptr) {
        this->TransitionTo(state);
    }
    ~Context() {
        delete state_;
    }
    /**
     * The Context allows changing the State object at runtime.
     */
    void TransitionTo(State* state) {
        std::cout << "Context: Transition to " << typeid(*state).name() << ".\n";
        if (this->state_ != nullptr)
            delete this->state_;
        this->state_ = state;
        this->state_->set_context(this);
    }
    /**
     * The Context delegates part of its behavior to the current State object.
     */
    void Background() {
        this->state_->virtSetupBackgroundBuffer();
    }
    void Objects() {
        this->state_->virtInitialiseObjects();
    }
    void Mouse() {
        this->state_->virtMouseDown(iButton, iX, iY);
    }
    void Key() {
        this->state_->virtKeyDown(iKeyCode);
    }
protected:
    int iButton;
    int iX;
    int iY;
    int iKeyCode;
    //AudioManager audio;

};

