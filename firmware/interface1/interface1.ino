/*
 *
 * Robotska ruka:
 *  Osnovne kretnje
 *
 * Autor: Milos Zivlak - ZI (zivlakmilos@gmail.com)
 */

#include <Servo.h>

#define MAGIC_NUMBER    0x38    // Megicni broj, da bi ga software prepoznao

#define SPEED_NORMAL    50      // Normalna brzina = 50

typedef struct
{
    int rot;        // Rotacija
    int seg1;       // Segment 1
    int seg2;       // Segment 2
    int seg3;       // Segment 3
    int hvat;       // Hvataljka
} position_t;       // Pozicije motora (struktura)

Servo rot, seg1, seg2, seg3, hvat;  // Servo motori
position_t position;                // Pozicije motora
position_t endPosition;             // Krajnja pozicija

void postavi(void)
{
    rot.write(position.rot);
    seg1.write(position.seg1);
    seg2.write(position.seg2);
    seg3.write(position.seg3);
    hvat.write(position.hvat);
}

void pomeri(int rotacija, int segment1, int segment2, int segment3, int hvataljka, int brzina)
{
    unsigned char finish;

    do
    {
        finish = 0;

        if(position.rot > rotacija)
            position.rot--;
        else if(position.rot < rotacija)
            position.rot++;
        else
            finish++;
        if(position.seg1 > segment1)
            position.seg1--;
        else if(position.seg1 < segment1)
            position.seg1++;
        else
            finish++;
        if(position.seg2 > segment2)
            position.seg2--;
        else if(position.seg2 < segment2)
            position.seg2++;
        else
            finish++;
        if(position.seg3 > segment3)
            position.seg3--;
        else if(position.seg3 < segment3)
            position.seg3++;
        else
            finish++;
        if(position.hvat > hvataljka)
            position.hvat--;
        else if(position.hvat < hvataljka)
            position.hvat++;
        else
            finish++;

        postavi();
        delay(brzina);
    } while(finish < 5);
}

void setup(void)
{
    rot.attach(3);      // Motor rotacije na pinu 3
    seg1.attach(4);     // Motor segmenta 1 na pinu 4
    seg2.attach(5);     // Motor segmenta 2 na pinu 5
    seg3.attach(6);     // Motor segmenta 3 na pinu 5
    hvat.attach(11);    // Motor hvataljke na pinu 11

    /* Pocetni polozaj */

    position.rot = 90;
    position.seg1 = 90;
    position.seg2 = 90;
    position.seg3 = 90;
    position.hvat = 90;
    endPosition.rot = 90;
    endPosition.seg1 = 90;
    endPosition.seg2 = 90;
    endPosition.seg3 = 90;
    endPosition.hvat = 90;
    postavi();

    /* USB konekcija */
    Serial.begin(9600);
    while(!Serial);

    /* Posalji racunaru da je arduino spreman */
    Serial.write(MAGIC_NUMBER);
}

void loop(void)
{
//  while(!Serial.available());
//  robotState[0] = Serial.read();
//  while(!Serial.available());
//  robotState[1] = Serial.read();
//  //robotState[2] = Serial.read();
//  //robotState[3] = Serial.read();
//  //robotState[4] = Serial.read();
//  
//  position.rot = robotState[0];
//  position.seg1 = robotState[1];
//  postavi();

//  while(!Serial.available());
//  position.rot = Serial.read();
//  while(!Serial.available());
//  position.seg1 = Serial.read();
//  position.seg1 = 180 - position.seg1;
//  while(!Serial.available());
//  position.seg2 = Serial.read();
//  position.seg2 = 180 - position.seg2;
//  while(!Serial.available());
//  position.seg3 = Serial.read();
//  while(!Serial.available());
//  position.hvat = Serial.read();

  if(Serial.available())
  {
    endPosition.rot = Serial.read();
    while(!Serial.available());
    endPosition.seg1 = Serial.read();
    while(!Serial.available());
    endPosition.seg2 = Serial.read();
    while(!Serial.available());
    endPosition.seg3 = Serial.read();
    while(!Serial.available());
    endPosition.hvat = Serial.read();
  }
  
  if(endPosition.rot > position.rot)
    position.rot++;
  else if(endPosition.rot < position.rot)
    position.rot--;
  if(endPosition.seg1 > position.seg1)
    position.seg1++;
  else if(endPosition.seg1 < position.seg1)
    position.seg1--;
  if(endPosition.seg2 > position.seg2)
    position.seg2++;
  else if(endPosition.seg2 < position.seg2)
    position.seg2--;
  if(endPosition.seg3 > position.seg3)
    position.seg3++;
  else if(endPosition.seg3 < position.seg3)
    position.seg3--;
  if(endPosition.hvat > position.hvat)
    position.hvat++;
  else if(endPosition.hvat < position.hvat)
    position.hvat--;
  
  postavi();
  delay(SPEED_NORMAL);
}
