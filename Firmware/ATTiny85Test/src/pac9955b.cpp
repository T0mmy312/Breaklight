#include <pac9955b.h>

uint8_t pac9955b_write(uint8_t addr, uint8_t reg, uint8_t val) {
    Wire.beginTransmission(addr);
    if (Wire.write(reg & 0b01111111) == 0)
        return FAILED;
    if (Wire.write(val) == 0)
        return FAILED;
    if (Wire.endTransmission(true) != 0)
        return FAILED;
    return SUCCESS;
}

uint8_t pac9955b_write_seq(uint8_t addr, uint8_t start_reg, uint8_t amount, uint8_t* vals) {
    Wire.beginTransmission(addr);
    if (Wire.write((start_reg & 0b01111111) | 0b10000000) == 0) // set to inc mode
        return FAILED;
    for (uint8_t i = 0; i < amount; i++) {
        if (Wire.write(vals[i]) == 0)
            return FAILED;
    }
    if (Wire.endTransmission(true) != 0)
        return FAILED;
    return SUCCESS;
}

uint8_t pac9955b_read(uint8_t addr, uint8_t reg, uint8_t& failed) {
    Wire.beginTransmission(addr);
    if (Wire.write(reg & 0b01111111) == 0) {
        failed = FAILED;
        return 0x00;
    }
    if (Wire.endTransmission(false) != 0) {
        failed = FAILED;
        return 0x00;
    }
    if (Wire.requestFrom(addr, 1, true) != 1) {
        failed = FAILED;
        return 0x00;
    }
    failed = SUCCESS;
    return Wire.read();
}

uint8_t pac9955b_read_seq(uint8_t addr, uint8_t reg, uint8_t amount, uint8_t* buffer) {
    Wire.beginTransmission(addr);
    if (Wire.write((reg & 0b01111111) | 0b10000000) == 0)
        return FAILED;
    if (Wire.endTransmission(false) != 0)
        return FAILED;
    if (Wire.requestFrom(addr, amount, true) != amount)
        return FAILED;
    for (uint8_t i = 0; i < amount; i++)
        buffer[i] = Wire.read();
    return SUCCESS;
}

uint8_t pac9955b_init(pac9955b& pac) {
    pac.status = pac9955b_Status::INITED;
    return SUCCESS;
}

uint8_t pac9955b_update(pac9955b& pac) {
    if (pac.status == pac9955b_Status::NOT_INITED)
        pac9955b_init(pac);
    if (pac.status == pac9955b_Status::ERROR_STATE)
        return FAILED;
    if (pac9955b_write_seq(pac.addr, LEDOUT0, 4, pac.ledout) == FAILED) {
        pac.status = pac9955b_Status::ERROR_STATE;
        return FAILED;
    }
    if (pac9955b_write_seq(pac.addr, PWM0, 16, pac.pwm) == FAILED) {
        pac.status = pac9955b_Status::ERROR_STATE;
        return FAILED;
    }
    return SUCCESS;
}

uint8_t pac9955b_setLedState(pac9955b& pac, uint8_t led, uint8_t state) {
    if (led >= 16)
        return FAILED;
    uint8_t index = led / 4;
    uint8_t mask = (led % 4) * 2;
    pac.ledout[index] |= (pac.ledout[index] & ~(0b11 << mask)) | ((state & 0b11) << mask);
    return SUCCESS;
}