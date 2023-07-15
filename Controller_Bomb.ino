#include <AxisJoystick.h>
#include <DelegateJoystick.h>
#include <Joystick.h>
#include <XInverterJoystick.h>
#include <XYReplacerJoystick.h>
#include <YInverterJoystick.h>

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>



AxisJoystick move(20, A0, A1);
AxisJoystick cameraStick(20, A2, A3);
RF24 radio(7, 8);

const byte address[6] = "00001";
int moveValX, moveValY, camAngleX, camAngleY, armX, armY;
String moveData, camData, armData, data;
void setup() {
  Serial.begin(9600);
  //start the radio
  radio.begin();
  //open writing pipe
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  //mark the radio as reciver
  radio.stopListening();
}

void loop() {
  car();
  camera();
  arm();
  sendData();
}

void car() {
  if (move.isRight())
  {
    moveData = "R";
  }
  else if (move.isLeft())
  {
    moveData = "L";
  }
  else if (move.isUp())
  {
    moveData = "B";
  }
  else if (move.isDown())
  {
    moveData = "F";
  }
  else
  {
    moveData = "";
  }
}

void camera()
{
  camAngleY = map(cameraStick.yAxis(), 0, 1023, -180, 180);
  camAngleX = cameraStick.xAxis();
  camData = String(camAngleY) + "/" + String(camAngleX);
}

void arm()
{
  armY = map(cameraStick.yAxis(), 0, 1023, -180, 180);
  armX = cameraStick.xAxis();
  armData = String(camAngleY) + "/" + String(camAngleX);
}

void sendData()
{
  data = moveData;
  radio.write(&data, sizeof(data));
  Serial.println(data);
}
