#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include <RadioLib.h>

namespace esphome {
namespace bresser {

using DecodeStatus = enum DecodeStatus { DECODE_OK, DECODE_PAR_ERR, DECODE_CHK_ERR, DECODE_DIG_ERR };

class BresserComponent : public PollingComponent {
 public:
  BresserComponent() = default;

  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override;
  void update() override;

  void set_temperature_sensor(sensor::Sensor *temperature_sensor) { this->temperature_sensor_ = temperature_sensor; }

  uint8_t s_type;             // !> sensor type (only 6-in1)
  uint32_t sensor_id;         // !> sensor ID (5-in-1: 1 byte / 6-in-1: 4 bytes)
  uint8_t chan;               // !> channel (only 6-in-1)
  bool temp_ok = false;       // !> temperature o.k. (only 6-in-1)
  float temp_c;               // !> temperature in degC
  int humidity;               // !> humidity in %
  bool uv_ok = false;         // !> uv radiation o.k. (only 6-in-1)
  float uv;                   // !> uv radiation (only 6-in-1)
  bool wind_ok = false;       // !> wind speed/direction o.k. (only 6-in-1)
  float wind_direction_deg;   // !> wind direction in deg
  float wind_gust_meter_sec;  // !> wind speed (gusts) in m/s
  float wind_avg_meter_sec;   // !> wind speed (avg)   in m/s
  // For LoRa_Serialization:
  //   fixed point integer with 1 decimal -
  //   saves two bytes compared to "RawFloat"
  uint16_t wind_direction_deg_fp1;   // !> wind direction in deg (fixed point int w. 1 decimal)
  uint16_t wind_gust_meter_sec_fp1;  // !> wind speed (gusts) in m/s (fixed point int w. 1 decimal)
  uint16_t wind_avg_meter_sec_fp1;   // !> wind speed (avg)   in m/s (fixed point int w. 1 decimal)
  bool rain_ok = false;              // !> rain gauge level o.k.
  float rain_mm;                     // !> rain gauge level in mm
  bool battery_ok = false;           // !> battery o.k.
  bool moisture_ok = false;          // !> moisture o.k. (only 6-in-1)
  int moisture;                      // !> moisture in % (only 6-in-1)
  bool message_ok;                   // !> status of last getMessage() call (set to 'true' by genMessage() call)
  bool data_ok;                      // !> status of last getData() call    (set to 'true' by genMessage() call)
  float rssi;                        // !> received signal strength indicator in dBm
  DecodeStatus decode_payload(uint8_t *msg, uint8_t msgSize);

 protected:
  sensor::Sensor *temperature_sensor_{nullptr};
  bool get_message();
};

}  // namespace bresser
}  // namespace esphome
