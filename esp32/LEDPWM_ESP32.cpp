#include "LEDPWM_ESP32.h"

LEDPWM_ESP32::LEDPWM_ESP32(uint16_t port,ledc_timer_t timerNo, uint32_t freq, float percentage){
    ledc_timer_config_t ledc_timer;
    ledc_timer.duty_resolution=LEDC_TIMER_10_BIT;
    ledc_timer.freq_hz = 40000;
    ledc_timer.speed_mode = LEDC_HIGH_SPEED_MODE;
    ledc_timer.timer_num = timerNo;
    ledc_timer_config(&ledc_timer);

    ledc_channel_config_t ledc_channel;

    ledc_channel.channel    = LEDC_CHANNEL_0;
    ledc_channel.duty       = convertDutyPercentage(percentage);
    ledc_channel.gpio_num   = port;
    ledc_channel.speed_mode = LEDC_HIGH_SPEED_MODE;
    ledc_channel.hpoint     = 0;
    ledc_channel.timer_sel  = timerNo;
    ledc_channel_config(&ledc_channel);
}

void LEDPWM_ESP32::start()
{
}

void LEDPWM_ESP32::stop()
{
}

void LEDPWM_ESP32::reset()
{
}

void LEDPWM_ESP32::setFrequency(uint32_t freq)
{
}

void LEDPWM_ESP32::setDutyCycle(float percentage)
{
    ledc_set_duty(LEDC_HIGH_SPEED_MODE,LEDC_CHANNEL_0,convertDutyPercentage(percentage));
    ledc_update_duty(LEDC_HIGH_SPEED_MODE,LEDC_CHANNEL_0);
}

void LEDPWM_ESP32::setInterruptCallback(std::function<void ()> callback)
{
}

uint32_t LEDPWM_ESP32::convertDutyPercentage(float percentage){
    if(percentage<0.0f)
        percentage=0.0f;
    if(percentage > 100.0f)
        percentage=100.0f;
    return static_cast<uint32_t>((percentage*1024.0f)/100.0f);
}
