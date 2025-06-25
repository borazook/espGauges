#include <LovyanGFX.hpp>

/*----------------------------------------------------------------------
  LGFX custom class – ESP32-S3 DevKitC-1  +  RA8875 800×480  (SPI mode)
  ---------------------------------------------------------------------*/
class LGFX : public lgfx::LGFX_Device
{
  /* ===== Panel & Bus instances ===== */
  lgfx::Panel_RA8875 _panel_instance;   //  RA8875 display controller
  lgfx::Bus_SPI      _bus_instance;     //  SPI bus (FSPI on S3)

public:
  LGFX(void)
  {
    /* ---------- SPI BUS CONFIG ---------- */
    {
      auto cfg = _bus_instance.config();
      cfg.spi_host   = SPI2_HOST;      // ESP32-S3 FSPI peripheral
      cfg.spi_mode   = 0;
      cfg.freq_write = 16000000;       // 16 MHz  (bump later if stable)
      cfg.freq_read  = 16000000;
      cfg.dma_channel = 1;             // use DMA
      cfg.spi_3wire  = false;
      cfg.use_lock   = true;

      cfg.pin_sclk = 12;               // SCK
      cfg.pin_mosi = 11;               // MOSI
      cfg.pin_miso = 13;               // MISO  (tie RA8875 SDO; −1 if unused)
      cfg.pin_dc   = -1;               // RA8875 doesn’t need D/C

      _bus_instance.config(cfg);
      _panel_instance.setBus(&_bus_instance);
    }

    /* ---------- PANEL CONFIG (RA8875) ---------- */
    {
      auto cfg = _panel_instance.config();
      cfg.pin_cs   = 10;               // CS
      cfg.pin_rst  = 15;               // RESET
      cfg.pin_busy = 16;               // WAIT/BUSY  <-- NEW wire

      cfg.panel_width   = 800;         // visible resolution
      cfg.panel_height  = 480;

      cfg.memory_width  = 800;         // GRAM stride (portrait)
      cfg.memory_height = 480;

      cfg.dlen_16bit    = true;        // 16-bit RGB565 transfers
      cfg.readable      = true;
      cfg.bus_shared    = true;
      cfg.invert        = false;
      cfg.rgb_order     = false;       // flip if red/blue ever swap

      _panel_instance.config(cfg);
    }

    /* ---------- Finalise ---------- */
    setPanel(&_panel_instance);
  }
};

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
