#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

#include "FreeRTOS/include/FreeRTOS.h"
#include "FreeRTOS/include/task.h"

void ledInit(void);
// RTOS task
void vTaskLedRed(void *p);
void vTaskLedYellow(void *p);
void vTaskLedGreen(void *p);

int main(void)
{
    // Configure GPIO for LED
    ledInit();

    // Create LED blink task
    xTaskCreate(vTaskLedRed, (const char*) "Red LED Blink", 
        128, NULL, 1, NULL);
    xTaskCreate(vTaskLedYellow, (const char*) "Yellow LED Blink",
        128, NULL, 1, NULL);
    xTaskCreate(vTaskLedGreen, (const char*) "Green LED Blink",
        128, NULL, 1, NULL);
    // Start RTOS scheduler
    vTaskStartScheduler();

    return 0;
}

void ledInit()
{
    GPIO_InitTypeDef GPIO_InitStruct;

    // Configure PB3, PB4, PB5 as push-pull output
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void vTaskLedRed(void *p)
{
    for (;;)
    {
        GPIOB->ODR ^= GPIO_Pin_14;
        vTaskDelay(500/portTICK_RATE_MS);
    }
}

void vTaskLedYellow(void *p)
{
    for (;;)
    {
        GPIOB->ODR ^= GPIO_Pin_13;
        vTaskDelay(1000/portTICK_RATE_MS);
    }
}

void vTaskLedGreen(void *p)
{
    for (;;)
    {
        GPIOB->ODR ^= GPIO_Pin_15;
        vTaskDelay(2000/portTICK_RATE_MS);
    }
}
