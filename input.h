#pragma once

#include "game_objects.h"
#include "ADKeyboardDectector.h"
#include <FriedMusicPlayer.h>

static int velocity_x = 0;
static int velocity_y = 0;

const int gravity = 1;
const int maxFallSpeed = 8;
const int jumpStrength = -15;
const int speed = 2;

inline bool is_walkable_pixel(int px, int py) {
  int tile_x = px / TILE_SIZE;
  int tile_y = py / TILE_SIZE;

  if (tile_x < 0 || tile_x >= MAP_W || tile_y < 0 || tile_y >= MAP_H)
    return false;

  char tile = level[tile_y][tile_x];

  if (tile == 'W')
  {
    has_won = true;
  }
  
  return (tile == '.' || tile == 'W');
}

inline bool is_colliding(int x, int y, int w, int h) {
  // Check all 4 corners of the bounding box
  return !(
    is_walkable_pixel(x,     y)     &&
    is_walkable_pixel(x + w, y)     &&
    is_walkable_pixel(x,     y + h) &&
    is_walkable_pixel(x + w, y + h)
  );
}

inline void loop_input() {
  // Player movement (horizontal)
  velocity_x = 0;
  ADKEY key = get_pressed_key();

  if (key == ADKEY_left)  velocity_x = -speed;
  if (key == ADKEY_right) velocity_x = speed;

  if (key == ADKEY_select) {
    // Check if on ground before jumping
    if (is_colliding(player.x, player.y + 1, 15, 15)) {
      velocity_y = jumpStrength;
      play_sfx(jump_sound);
    }
  }

  // Apply gravity
  velocity_y += gravity;
  if (velocity_y > maxFallSpeed) velocity_y = maxFallSpeed;

  // Horizontal collision
  int new_x = player.x + velocity_x;
  if (!is_colliding(new_x, player.y, 15, 15)) {
    player.x = new_x;
  } else {
    velocity_x = 0; // stop hitting wall
  }

  // Vertical collision
  int new_y = player.y + velocity_y;
  if (!is_colliding(player.x, new_y, 15, 15)) {
    player.y = new_y;
  } else {
    velocity_y = 0; // stop falling or going up into ceiling
  }

  // Optional: wrap-around or clamp
  if (player.x < 0) player.x = 0;
  if (player.y < 0) player.y = 0;
  if (player.x > 320 - 16) player.x = 320 - 16;
  if (player.y > 240 - 16) player.y = 240 - 16;
}


