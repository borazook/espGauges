#include <LovyanGFX.hpp>
#include <LGFX_RA8875.hpp>

/* ===== Global display object ===== */
LGFX display;

/*------------------------------------------------------------------*/
void setup()
{
  display.init();              // initialise bus + panel
  display.setRotation(0);      // choose 0-3 so text is upright
  display.fillScreen(TFT_BLACK);         // clears full 800×480 (no grain!)
  display.setTextColor(TFT_WHITE);
  display.setTextSize(2);
  display.drawString("Hello, world!", 100, 100);
}

void loop()
{
  /* nothing yet – ready for gauges/UI code */
}
