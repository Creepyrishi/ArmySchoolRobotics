#include <FlexLibrary.h>

int 
minPinky,
minRing,
minMiddle,
minIndex,
minThumb,
maxPinky,
maxRing,
maxMiddle,
maxIndex,
maxThumb;

Flex pinky (A0,minPinky,maxPinky,10,RUN_AVG,0),
ring(A1,minRing,maxRing,10,RUN_AVG),
middle(A2,minMiddle,maxMiddle,10,RUN_AVG),
index(A3,minIndex,maxIndex,10,RUN_AVG),
thumb(A4,minThumb,maxIndex,10,RUN_AVG);
void setup() {
  Serial.begin(9600);
}

void loop() {
  ring.updateVal();
  thumb.updateVal();
  pinky.updateVal();
  middle.updateVal();
  index.updateVal();

  int ringPos = map(ring.getSensorValue(), minRing, maxRing, 180, 0);
  ringPos = constrain(ringPos, 0, 180);
  int thumbPos = map(thumb.getSensorValue(), minThumb, maxThumb, 180, 0);
  thumbPos = constrain(thumbPos, 0, 180);
  int pinkyPos = map(pinky.getSensorValue(), minPinky, maxPinky, 0, 180);
  pinkyPos = constrain(pinkyPos, 0, 180);
  int middlePos = map(middle.getSensorValue(), minMiddle, maxMiddle, 0, 180);
  middlePos = constrain(middlePos, 0, 180);
  int indexPos = map(index.getSensorValue(), minIndex, maxIndex, 0, 180);
  indexPos = constrain(indexPos, 0, 180);
  Serial.print(pinkyPos);Serial.print("/");
  Serial.print(ringPos);Serial.print("/");
  Serial.print(middlePos);Serial.print("/");
  Serial.print(indexPos);Serial.print("/");
  Serial.println(thumbPos);
}
