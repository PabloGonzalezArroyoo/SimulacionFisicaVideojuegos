#pragma once
#include "Constants.h"

class Manager;
class System {
public:
	virtual ~System() {}

	void setContext(Manager* _mngr) { mngr = _mngr; }
	virtual void initSystem() {}
	virtual void update(double t) {}
	//virtual void receive(const Message& m) { }

protected:
	Manager* mngr;
};