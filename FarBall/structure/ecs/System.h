#pragma once

class Manager;
class System {
protected:
	Manager* mngr;

public:
	virtual ~System() { }
	void setContext(Manager* _mngr) {
		mngr = _mngr;
	}
	virtual void initSystem() { }
	virtual void update() { }
	//virtual void receive(const Message& m) { }
};