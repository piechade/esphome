#include "bresser.h"
#include "esphome/core/log.h"

namespace esphome {
namespace bresser {

static const char *const TAG = "bresser";

void BresserComponent::setup() {
  ESP_LOGI(TAG, "BresserComponent setup started!");
  this->spi_setup();
  ESP_LOGI(TAG, "SPI setup finished!");
}

void BresserComponent::update() { ESP_LOGV(TAG, "Get message"); }

float BresserComponent::get_setup_priority() const { return setup_priority::DATA; }

void BresserComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "BRESSER:");

  LOG_SENSOR(TAG, "Temperature", this->temperature_sensor_);
  LOG_PIN("CS Pin: ", this->cs_);
  LOG_UPDATE_INTERVAL(this);
}

}  // namespace bresser
}  // namespace esphome
