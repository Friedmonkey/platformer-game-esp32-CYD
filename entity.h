#pragma once
#include <TFT_eSPI.h>

struct Entity {
  float x;
  float y;
  int w;
  int h;
  uint16_t color;
};

inline void drawEntity(TFT_eSprite &spr, const Entity &entity) {
  spr.fillRect((int)entity.x, (int)entity.y, entity.w, entity.h, entity.color);
}

