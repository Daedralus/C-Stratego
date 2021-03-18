#pragma once
#include "header.h"
#include "BaseEngine.h"
#include "State.h"

class Context;
class State : public BaseEngine
{
protected:
	Context* context_;

public:
	virtual ~State() {

	}
	void set_context(Context *context) {
		this->context_ = context;
	}

	virtual void virtSetupBackgroundBuffer() = 0;
	virtual void virtKeyDown(int iKeyCode) = 0;
	virtual void virtMouseDown(int iButton, int iX, int iY) = 0;
	virtual int virtInitialiseObjects() = 0;
};

