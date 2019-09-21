#include "../stm32_wrapper/hal/f4/include/led.hpp"
#include "../stm32_wrapper/hal/f4/include/button.hpp"

#include "main.h"

#include "core.hpp"

void core() {
    hal::Led leds[] = {
            hal::Led(LD3_GPIO_Port, LD3_Pin),
            hal::Led(LD4_GPIO_Port, LD4_Pin),
            hal::Led(LD6_GPIO_Port, LD6_Pin),
            hal::Led(LD5_GPIO_Port, LD5_Pin),
    };

    auto all = [&leds](const bool is_on) {
        for (auto &l : leds) {
            is_on ? l.On() : l.Off();
        }
    };

    const auto button = hal::Button(B1_GPIO_Port, B1_Pin);

    uint8_t count = 0;
    while (1) {
        if (button.IsPushed()) {

            all(true);

        } else {

            for (uint8_t i = 0; i < 4; ++i) {
                count % 4 == i ? leds[i].On() : leds[i].Off();
            }
        }

        if (++count > 200) { count = 0; }
        HAL_Delay(100);
    }

    while (true);
}

