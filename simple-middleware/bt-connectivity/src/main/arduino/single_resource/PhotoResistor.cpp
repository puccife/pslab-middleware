#include "PhotoResistor.h"

PhotoResistor::PhotoResistor(const int pin) : pin(pin){
	pinMode(pin, OUTPUT);
}

int PhotoResistor::getBrightness(){
	return analogRead(pin);
}
