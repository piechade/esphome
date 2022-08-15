#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "WeatherSensor.h"

namespace esphome {
namespace bresser {

class BresserComponent : public sensor::Sensor, public PollingComponent {
 public:
  BresserComponent() = default;

  void setup() override;
  void dump_config() override;
  void loop() override;

  float get_setup_priority() const override;

  void set_temperature_sensor(sensor::Sensor *temperature_sensor) { this->temperature_sensor_ = temperature_sensor; }

 protected:
  WeatherSensor weather_sensor_;
  sensor::Sensor *temperature_sensor_{nullptr};
};

}  // namespace bresser
}  // namespace esphome
