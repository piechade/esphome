#include "bresser.h"
#include "WeatherSensor.h"
#include "esphome/core/log.h"

namespace esphome {
namespace bresser {

static const char *const TAG = "bresser";

void BresserComponent::setup() {
  Serial.begin(115200);

  weather_sensor_.begin();
}

void BresserComponent::update() {
  // Tries to receive radio message (non-blocking) and to decode it.
  // Timeout occurs after a small multiple of expected time-on-air.
  bool decode_ok = weather_sensor_.get_message();

  if (decode_ok) {
    const float meters_sec_to_mph = 2.237;

    if (this->weather_sensor_.temp_ok) {
      temperature_sensor_->publish_state(temperature);
    }
  }
}

void BresserComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "BRESSER:");

  LOG_SENSOR(TAG, "Temperature", this->temperature_sensor_);
}

float BresserComponent::get_setup_priority() const { return setup_priority::DATA; }

}  // namespace bresser
}  // namespace esphome
