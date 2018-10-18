#include <Mozzi_ESP32.h>
#include <Oscil.h>
#include <tables/sin2048_int8.h>

#include "freertos/task.h"
#include "esp_err.h"
#include "esp_log.h"

// Set the sample rate to 32768 Hz.
#define OUR_SAMPLE_RATE (0x8000)

// Set the control rate to 64 Hz.
#define OUR_CONTROL_RATE (0x40)

Oscil <SIN2048_NUM_CELLS, OUR_SAMPLE_RATE> aSin(SIN2048_DATA);

void
Mozzi_ESP32::updateControl()
{
}

Mozzi::StereoStruct_t
Mozzi_ESP32::updateAudio()
{
    Mozzi::StereoStruct_t stereo;
    stereo.left = 0;
    stereo.right = aSin.next();
    return stereo;
}

void mozziTask(void*arg)
{
    aSin.setFreq(262); // middle-C = 261.625565 Hz
    Mozzi_ESP32 mozzi(OUR_SAMPLE_RATE, OUR_CONTROL_RATE);
    printf("Doing 1 Mozzi loop.\n");
    mozzi.loop(1);
    printf("Now run Mozzi forever...\n");
    mozzi.loop();
    vTaskDelete(NULL);
}

#ifdef __cplusplus
extern "C" {
    esp_err_t app_main()
    {
        esp_log_level_set("I2S", ESP_LOG_INFO);
        xTaskCreate(mozziTask, "example_i2s_adc_dac", 1024 * 2, NULL, 5, NULL);
        return ESP_OK;
    }
}
#endif
