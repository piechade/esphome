import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor

# from esphome.const import (
#     CONF_ID,
#     STATE_CLASS_MEASUREMENT,
#     ENTITY_CATEGORY_DIAGNOSTIC,
#     CONF_TEMPERATURE,
#     CONF_HUMIDITY,
#     CONF_BATTERY,
#     CONF_CH,
#     CONF_WIND_SPEED_MAX,
#     CONF_WIND_SPEED_AVG,
#     CONF_WIND_DIRECTION_DEGREES,
#     CONF_SIGNAL_STRENGTH,
#     DEVICE_CLASS_TEMPERATURE,
#     DEVICE_CLASS_HUMIDITY,
#     UNIT_EMPTY,
#     UNIT_CELSIUS,
#     UNIT_PERCENT,
#     UNIT_KILOMETER_PER_HOUR,
#     UNIT_DEGREES,
#     UNIT_DECIBEL_MILLIWATT,
#     DEVICE_CLASS_SIGNAL_STRENGTH,
#     ICON_WEATHER_WINDY,
#     ICON_SIGN_DIRECTION,
# )

from esphome.const import (
    CONF_ID,
    CONF_TEMPERATURE,
    STATE_CLASS_MEASUREMENT,
    DEVICE_CLASS_TEMPERATURE,
    UNIT_CELSIUS,
)

bresser_ns = cg.esphome_ns.namespace("bresser")
BRESSER = bresser_ns.class_("BresserComponent", cg.PollingComponent)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(BRESSER),
        cv.Optional(CONF_TEMPERATURE): sensor.sensor_schema(
            unit_of_measurement=UNIT_CELSIUS,
            accuracy_decimals=2,
            device_class=DEVICE_CLASS_TEMPERATURE,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
    }
).extend(cv.polling_component_schema("5s"))

#  Id: [44539295] Battery: [OK ] Ch: [0] Temp: [ 29.3C] Hum: [ 31%] Wind max: [ 0.9m/s] Wind avg: [ 0.9m/s] Wind dir: [241.0deg] Rain: [-----.-mm] RSSI: [-82.0dBm]

# CONFIG_SCHEMA = cv.Schema(
#     {
#         cv.GenerateID(): cv.declare_id(BRESSER),
#         cv.Optional(CONF_BATTERY): sensor.sensor_schema(
#             unit_of_measurement=UNIT_EMPTY,
#             state_class=STATE_CLASS_MEASUREMENT,
#             entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
#         ),
#         cv.Optional(CONF_CH): sensor.sensor_schema(
#             unit_of_measurement=UNIT_EMPTY,
#             state_class=STATE_CLASS_MEASUREMENT,
#             entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
#         ),
#         cv.Optional(CONF_TEMPERATURE): sensor.sensor_schema(
#             unit_of_measurement=UNIT_CELSIUS,
#             accuracy_decimals=1,
#             device_class=DEVICE_CLASS_TEMPERATURE,
#             state_class=STATE_CLASS_MEASUREMENT,
#         ),
#         cv.Optional(CONF_HUMIDITY): sensor.sensor_schema(
#             unit_of_measurement=UNIT_PERCENT,
#             accuracy_decimals=0,
#             device_class=DEVICE_CLASS_HUMIDITY,
#             state_class=STATE_CLASS_MEASUREMENT,
#         ),
#         cv.Optional(CONF_WIND_SPEED_MAX): sensor.sensor_schema(
#             unit_of_measurement=UNIT_KILOMETER_PER_HOUR,
#             icon=ICON_WEATHER_WINDY,
#             accuracy_decimals=1,
#             state_class=STATE_CLASS_MEASUREMENT,
#         ),
#         cv.Optional(CONF_WIND_SPEED_AVG): sensor.sensor_schema(
#             unit_of_measurement=UNIT_KILOMETER_PER_HOUR,
#             icon=ICON_WEATHER_WINDY,
#             accuracy_decimals=1,
#             state_class=STATE_CLASS_MEASUREMENT,
#         ),
#         cv.Optional(CONF_WIND_DIRECTION_DEGREES): sensor.sensor_schema(
#             unit_of_measurement=UNIT_DEGREES,
#             icon=ICON_SIGN_DIRECTION,
#             accuracy_decimals=1,
#             state_class=STATE_CLASS_MEASUREMENT,
#         ),
#         cv.Optional(CONF_SIGNAL_STRENGTH): sensor.sensor_schema(
#             unit_of_measurement=UNIT_DECIBEL_MILLIWATT,
#             accuracy_decimals=0,
#             device_class=DEVICE_CLASS_SIGNAL_STRENGTH,
#             state_class=STATE_CLASS_MEASUREMENT,
#             entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
#         ),
#     }
# ).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    # if CONF_BATTERY in config:
    #     sens = await sensor.new_sensor(config[CONF_BATTERY])
    #     cg.add(var.set_battery_sensor(sens))

    # if CONF_CH in config:
    #     sens = await sensor.new_sensor(config[CONF_CH])
    #     cg.add(var.set_ch_sensor(sens))

    if CONF_TEMPERATURE in config:
        sens = await sensor.new_sensor(config[CONF_TEMPERATURE])
        cg.add(var.set_temperature_sensor(sens))

    # if CONF_HUMIDITY in config:
    #     sens = await sensor.new_sensor(config[CONF_HUMIDITY])
    #     cg.add(var.set_humidity_sensor(sens))

    # if CONF_WIND_SPEED_MAX in config:
    #     sens = await sensor.new_sensor(config[CONF_WIND_SPEED_MAX])
    #     cg.add(var.set_wind_speed_max_sensor(sens))

    # if CONF_WIND_SPEED_AVG in config:
    #     sens = await sensor.new_sensor(config[CONF_WIND_SPEED_AVG])
    #     cg.add(var.set_wind_speed_avg_sensor(sens))

    # if CONF_WIND_DIRECTION_DEGREES in config:
    #     sens = await sensor.new_sensor(config[CONF_WIND_DIRECTION_DEGREES])
    #     cg.add(var.set_wind_direction_degrees_sensor(sens))

    # if CONF_SIGNAL_STRENGTH in config:
    #     sens = await sensor.new_sensor(config[CONF_SIGNAL_STRENGTH])
    #     cg.add(var.set_singal_strength_sensor(sens))
