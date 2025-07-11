#pragma once

//use port CN1
//connect ground to ground and vcc to the v3.3
//connect gpio27 to out
#define INPUT_PIN 27

enum ADKEY
{
  ADKEY_none,
  ADKEY_up,
  ADKEY_down,
  ADKEY_left,
  ADKEY_right,
  ADKEY_select,
};

inline ADKEY get_pressed_key()
{
  int val = analogRead(INPUT_PIN);

  if (val > 4000) {
    return ADKEY_none;
  } else if (val < 10) {
    return ADKEY_left;
  } else if (val >= 550 && val <= 580) {
    return ADKEY_up;
  } else if (val >= 1250 && val <= 1300) {
    return ADKEY_down;
  } else if (val >= 2020 && val <= 2060) {
    return ADKEY_right;
  } else if (val >= 3180 && val <= 3210) {
    return ADKEY_select;
  } else {
    Serial.print("Unknown value: ");
    Serial.println(val);
    return ADKEY_none;
  }
}