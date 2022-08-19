#include "bresser.h"
#include "esphome/core/log.h"

namespace esphome {
namespace bresser {

static const char *const TAG = "bresser";

static const uint8_t PIN_RECEIVER_CS = 27;
static const uint8_t PIN_RECEIVER_IRQ = 21;
static const uint8_t PIN_RECEIVER_GPIO = 33;
static const uint8_t PIN_RECEIVER_RST = 32;

void BresserComponent::setup() {
  // https://github.com/RFD-FHEM/RFFHEM/issues/607#issuecomment-830818445
  // Freq: 868.300 MHz, Bandwidth: 203 KHz, rAmpl: 33 dB, sens: 8 dB, DataRate: 8207.32 Baud

  // carrier frequency:                   868.3 MHz
  // bit rate:                            8.22 kbps
  // frequency deviation:                 57.136417 kHz
  // Rx bandwidth:                        270.0 kHz (CC1101) / 250 kHz (SX1276)
  // output power:                        10 dBm
  // preamble length:                     40 bits

  ESP_LOGD(TAG, "Initializing ...");
  // static SX1276 radio = new Module(PIN_RECEIVER_CS, PIN_RECEIVER_IRQ, PIN_RECEIVER_RST, PIN_RECEIVER_GPIO);
  // int state = radio.beginFSK(868.3, 8.21, 57.136417, 250, 10, 32);
  // ESP_LOGD(TAG, "beginFSK!");
  // if (state == RADIOLIB_ERR_NONE) {
  //   ESP_LOGD(TAG, "success!");
  //   state = radio.setCrcFiltering(false);
  //   if (state != RADIOLIB_ERR_NONE) {
  //     ESP_LOGD(TAG, "Error disabling crc filtering!");
  //     while (true)
  //       ;
  //   }
  //   state = radio.fixedPacketLengthMode(27);
  //   if (state != RADIOLIB_ERR_NONE) {
  //     ESP_LOGD(TAG, "Error setting fixed packet length!");
  //     while (true)
  //       ;
  //   }
  //   // Preamble: AA AA AA AA AA
  //   // Sync is: 2D D4
  //   // Preamble 40 bits but the CC1101 doesn't allow us to set that
  //   // so we use a preamble of 32 bits and then use the sync as AA 2D
  //   // which then uses the last byte of the preamble - we recieve the last sync byte
  //   // as the 1st byte of the payload.

  //   uint8_t sync_word[] = {0xAA, 0x2D};
  //   state = radio.setSyncWord(sync_word, 2);
  //   if (state != RADIOLIB_ERR_NONE) {
  //     ESP_LOGD(TAG, "Error setting sync words!");
  //     while (true)
  //       ;
  //   }
  // } else {
  //   ESP_LOGD(TAG, "Setup complete - awaiting incoming messages...");
  //   while (true)
  //     ;
  // }

  // rssi = radio.getRSSI();
}

void BresserComponent::update() {
  // Tries to receive radio message (non-blocking) and to decode it.
  // Timeout occurs after a small multiple of expected time-on-air.
  // bool decode_ok = this->get_message();

  // if (decode_ok) {
  //   const float meters_sec_to_mph = 2.237;

  //   if (this->temp_ok) {
  //     temperature_sensor_->publish_state(temp_c);
  //   }
  // }
}

void BresserComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "BRESSER:");

  LOG_SENSOR(TAG, "Temperature", this->temperature_sensor_);
}

float BresserComponent::get_setup_priority() const { return setup_priority::HARDWARE; }

// bool BresserComponent::get_message() {
//   uint8_t recvData[27];

//   // reset status flag
//   message_ok = false;

//   // Receive data
//   //     1. flush RX buffer
//   //     2. switch to RX mode
//   //     3. wait for expected RX packet or timeout [~500us in this configuration]
//   //     4. flush RX buffer
//   //     5. switch to standby
//   int state = radio.receive(recvData, 27);
//   rssi = radio.getRSSI();

//   if (state == RADIOLIB_ERR_NONE) {
//     // Verify last syncword is 1st byte of payload (see setSyncWord() above)
//     if (recvData[0] == 0xD4) {
//       message_ok = (decode_payload(&recvData[1], sizeof(recvData) - 1) == DECODE_OK);

//       // Fixed set of data for 5-in-1 sensor
//       temp_ok = true;
//       uv_ok = false;
//       wind_ok = true;
//       rain_ok = true;
//       moisture_ok = false;

//     }  // if (recvData[0] == 0xD4)
//     else {
//       // some other error occurred
//     }
//   }  // if (state == RADIOLIB_ERR_NONE)

//   return message_ok;
// }

// DecodeStatus BresserComponent::decode_payload(uint8_t *msg, uint8_t msgSize) {
//   // First 13 bytes need to match inverse of last 13 bytes
//   for (unsigned col = 0; col < msgSize / 2; ++col) {
//     if ((msg[col] ^ msg[col + 13]) != 0xff) {
//       return DECODE_PAR_ERR;
//     }
//   }

//   // Verify checksum (number number bits set in bytes 14-25)
//   uint8_t bitsSet = 0;
//   uint8_t expectedBitsSet = msg[13];

//   for (uint8_t p = 14; p < msgSize; p++) {
//     uint8_t currentByte = msg[p];
//     while (currentByte) {
//       bitsSet += (currentByte & 1);
//       currentByte >>= 1;
//     }
//   }

//   if (bitsSet != expectedBitsSet) {
//     return DECODE_CHK_ERR;
//   }

//   sensor_id = msg[14];

//   int temp_raw = (msg[20] & 0x0f) + ((msg[20] & 0xf0) >> 4) * 10 + (msg[21] & 0x0f) * 100;
//   if (msg[25] & 0x0f) {
//     temp_raw = -temp_raw;
//   }
//   temp_c = temp_raw * 0.1f;

//   humidity = (msg[22] & 0x0f) + ((msg[22] & 0xf0) >> 4) * 10;

//   wind_direction_deg = ((msg[17] & 0xf0) >> 4) * 22.5f;
//   wind_direction_deg_fp1 = wind_direction_deg * 10;

//   int gust_raw = ((msg[17] & 0x0f) << 8) + msg[16];
//   wind_gust_meter_sec_fp1 = gust_raw;
//   wind_gust_meter_sec = gust_raw * 0.1f;

//   int wind_raw = (msg[18] & 0x0f) + ((msg[18] & 0xf0) >> 4) * 10 + (msg[19] & 0x0f) * 100;
//   wind_avg_meter_sec_fp1 = wind_raw;
//   wind_avg_meter_sec = wind_raw * 0.1f;

//   int rain_raw = (msg[23] & 0x0f) + ((msg[23] & 0xf0) >> 4) * 10 + (msg[24] & 0x0f) * 100;
//   rain_mm = rain_raw * 0.1f;

//   battery_ok = (msg[25] & 0x80) ? false : true;

//   return DECODE_OK;
// }

}  // namespace bresser
}  // namespace esphome
