#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/spi/spi.h"

namespace esphome {
namespace bresser {

// Board   SCK   MOSI  MISO
// ESP32   D18   D23   D19

// #define PIN_RECEIVER_CS 27
// #define PIN_RECEIVER_IRQ 21
// #define PIN_RECEIVER_GPIO 33
// #define PIN_RECEIVER_RST 32

// carrier frequency:                   868.3 MHz
// bit rate:                            8.22 kbps
// frequency deviation:                 57.136417 kHz
// Rx bandwidth:                        270.0 kHz (CC1101) / 250 kHz (SX1276)
// output power:                        10 dBm
// preamble length:                     40 bits


class BresserComponent : public PollingComponent,
                         public spi::SPIDevice<spi::BIT_ORDER_MSB_FIRST, spi::CLOCK_POLARITY_LOW,
                                               spi::CLOCK_PHASE_LEADING, spi::DATA_RATE_250KHZ> {
 public:
  BresserComponent() = default;

  void setup() override;
  void dump_config() override;
  void update() override;
  float get_setup_priority() const override;

  void set_temperature_sensor(sensor::Sensor *temperature_sensor) { this->temperature_sensor_ = temperature_sensor; }

 protected:
  sensor::Sensor *temperature_sensor_{nullptr};
};

}  // namespace bresser
}  // namespace esphome
