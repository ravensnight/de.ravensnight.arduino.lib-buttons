#include <Arduino.h>
#include <ButtonController.h>

ButtonController controller(4);

void setup() {
    controller.link(PB0);
    controller.link(PB1);
    controller.link(PB2);
    controller.link(PB3);
}

void loop() {
    controller.poll();
    delay(10);
}
