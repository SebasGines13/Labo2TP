#include <iostream>
#include "Controller.h"

void Controller::reset(){
	std::fill(_buttons, _buttons + 8, 0);
}

void Controller::push(Controller::Buttons button){
	_buttons[(int)button] = true;
}

bool Controller::isPressed(Controller::Buttons button){
	return _buttons[(int)button];
}
