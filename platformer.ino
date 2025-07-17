#include <TFT_eSPI.h>
#include <XPT2046_Bitbang.h>

//touchscreen pins
#define XPT2046_MOSI 32
#define XPT2046_MISO 39
#define XPT2046_CLK 25
#define XPT2046_CS 33

#include "display.h"
#include "level.h"
#include "entity.h"
#include "input.h"
#include "FriedPreferences.h"
#include "game_objects.h"
#include "mario_win_gif.h"

//#define FRIED_SAMPLE_RATE 16000
#include <FriedMusicPlayer.h>
#include <FriedGifPlayer.h>

XPT2046_Bitbang ts(XPT2046_MOSI, XPT2046_MISO, XPT2046_CLK, XPT2046_CS);
bool pressed = false;
bool musicPaused = false;
bool started_winning = false;

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite framebuffer = TFT_eSprite(&tft);
FriedGifPlayer gif_player(&tft);

Preferences prefs;

unsigned long lastInputTime = 0;
unsigned long lastDrawTime = 0;
// unsigned long lastAudioTime = 0;

const unsigned long INPUT_INTERVAL = 6;  // 66 FPS
const unsigned long DRAW_INTERVAL = 15;   // ~33 FPS
// const unsigned long AUDIO_INTERVAL = 500; //half a second

void setup() {
  Serial.begin(115200);
  ts.begin();
  tft.init();
  tft.setRotation(1); // landscape
  framebuffer.setColorDepth(8);
  framebuffer.createSprite(320, 240); // full screen sprite
  tft.fillScreen(TFT_BLACK);
  tft.setFreeFont(&FreeMono18pt7b);
  tft.setTextColor(TFT_PURPLE);
  tft.drawCentreString("Platformer", TFT_WIDTH / 2, 10, 4);
  
  prefs = FriedPreferences::init("platformer_game");


  jump_sound = load_sfx("/jump_effect.raw");

  start_audio("/mario_main.raw");

  set_audio_volume(0.2f);
  set_sfx_volume(0.3f);
  gif_player.begin();
}

void loop() {
  TouchPoint tp = ts.getTouch();
  if (pressed)
  {
    pressed = false;
    musicPaused = !musicPaused;
    if (musicPaused)
    {
      pause_audio();
    }
    else
    {
      resume_audio();
    }
  }
  else if (tp.zRaw > 0)
  {
    pressed = true;
  }

  unsigned long now = millis();
  if (!started_winning && now - lastInputTime >= INPUT_INTERVAL) {
    lastInputTime = now;
    loop_input();
  }

  if (has_won)
  {
    started_winning = true;
    has_won = false;
    start_audio("/mario_win.raw");
  }

  if (started_winning)
  {
    gif_player.play((uint8_t*)mario_win_gif, sizeof(mario_win_gif), true);
  }
  else if (now - lastDrawTime >= DRAW_INTERVAL) {
    lastDrawTime = now;
    loop_draw(framebuffer);
  }
}
