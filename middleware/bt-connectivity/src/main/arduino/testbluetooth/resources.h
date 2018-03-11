#ifndef __RESOURCES__
#define __RESOURCES__

#include "Resource.h"
#include "ButtonImpl.h"
#include "Led.h"
#include "LedExt.h"
#include "flags.h"
#include "PhotoResistor.h"
#include "AnalogTempSensor.h"
#include "PIR.h"
#include "Motor.h"
#include "Sonar.h"

#define BUTTON BIT(0)
#define OBSERVABLE_BUTTON (BIT(1) | BUTTON)
#define LIGHT BIT(2)
#define LIGHT_EXT (BIT(3) | LIGHT)
#define PHOTO_RESISTOR BIT(4)
#define ANALOG_TEMP_SENSOR BIT(5)
#define PIR_ BIT(6)
#define MOTOR BIT(7)
#define SONAR BIT(8)

struct ButtonResource : public Resource, public ButtonImpl {
  ButtonResource(int pin);
};

struct LedExtResource : public Resource, public LedExt {
  LedExtResource(int pin);
};

struct PhotoResistorResource : public Resource, public PhotoResistor {
  PhotoResistorResource(int pin);
};

struct AnalogTempSensorResource : public Resource, public AnalogTempSensor {
  AnalogTempSensorResource(int pin);
};

struct PirResource : public Resource, public PIR {
  PirResource(int pin);
};

struct MotorResource : public Resource, public Motor {
  MotorResource(int pin);
};

struct SonarResource : public Resource, public Sonar {
  SonarResource(int echoPin, int trigPin);
};


#endif /* __RESOURCES__ */
