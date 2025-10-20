#include <Arduino.h>
#include <debug.h>

int main() {
    init();

    BEGIN_DEBUG;

    DB_PRINTLN("TEST!");
    
    while (1) {
        DB_PRINTLN("TEST!");
        delay(500);
    }
}