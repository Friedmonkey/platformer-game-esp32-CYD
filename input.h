#pragma once

#include "game_objects.h"

inline void loop_input() {
  // Move player right and down by 1 pixel every frame
  player.x += 1;
  player.y += 1;

  // Wrap around screen edges to keep player visible
  if (player.x > 320) player.x = 0;
  if (player.y > 240) player.y = 0;
}
