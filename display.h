#pragma once
#include <TFT_eSPI.h>
#include "level.h"
#include "entity.h"
#include "game_objects.h"


const int TILE_SIZE = 16;

inline void drawTile(TFT_eSprite &spr, char tile, int x, int y) {
  int px = x * TILE_SIZE;
  int py = y * TILE_SIZE;
  uint16_t color = TFT_SKYBLUE;
  if (tile == '#') color = TFT_GREEN; 
  if (tile == 'W') color = TFT_PURPLE;
  
  spr.fillRect(px, py, TILE_SIZE, TILE_SIZE, color);
}

inline void drawLevel(TFT_eSprite &spr) {
  for (int y = 0; y < MAP_H; y++) {
    for (int x = 0; x < MAP_W; x++) {
      drawTile(spr, level[y][x], x, y);
    }
  }
}

inline void loop_draw(TFT_eSprite &framebuffer)
{
  framebuffer.fillSprite(TFT_BLACK); // clear previous frame
  drawLevel(framebuffer);
  drawEntity(framebuffer, player);
  framebuffer.pushSprite(0, 0);      // now push entire buffer to screen
}
