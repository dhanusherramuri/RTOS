// /*
//  * three-thread-blink_priority/main.c
//  *
//  * Three independent FreeRTOS tasks, each blinking its own LED at its
//  * own fixed interval:
//  *   - PC13 (the Bluepill's onboard LED, active-low)  -> 1 s
//  *   - PA0  (external LED + ~330R resistor to ground)  -> 2 s
//  *   - PA1  (external LED + ~330R resistor to ground)  -> 3 s
//  *
//  * Only PC13 exists on the board itself; wire the other two LEDs up
//  * yourself, or just change led_b/led_c to reuse GPIOC/13 to see all
//  * three task periods overlaid on the one onboard LED instead.

#include <stdint.h>

#include "stm32f103_regs.h"

#include "FreeRTOS.h"
#include "task.h"

typedef struct
{
    GPIO_TypeDef *port;
    uint32_t pin;
    uint32_t period_ms;
} led_task_args_t;

/*------------------------------------------------------------------
  LED Configuration
-------------------------------------------------------------------*/

static const led_task_args_t led_a = {GPIOA, 3, 500};
static const led_task_args_t led_b = {GPIOA, 0, 450};
static const led_task_args_t led_c = {GPIOA, 1, 350};
static const led_task_args_t led_d = {GPIOA, 2, 350};

/*------------------------------------------------------------------
  GPIO Initialization
-------------------------------------------------------------------*/

static void gpio_output_init(GPIO_TypeDef *port, uint32_t pin)
{
    volatile uint32_t *cr;
    uint32_t shift;

    if (pin < 8)
        cr = &port->CRL;
    else
        cr = &port->CRH;

    shift = (pin % 8U) * 4U;

    /* Clear configuration bits */
    *cr &= ~(0xFU << shift);

    /* Output Push-Pull, 2 MHz */
    *cr |= (GPIO_CNF_MODE_OUTPUT_PP_2MHZ << shift);

    /* Start LED LOW */
    port->ODR &= ~(1U << pin);
}

/*------------------------------------------------------------------
  LED Task
-------------------------------------------------------------------*/

static void led_task(void *pvParameters)
{
    const led_task_args_t *args = (const led_task_args_t *)pvParameters;

    while (1)
    {
        /* Toggle LED */
        args->port->ODR ^= (1U << args->pin);

        /* Delay WITHOUT blocking CPU */
        vTaskDelay(pdMS_TO_TICKS(args->period_ms));
    }
}

/*------------------------------------------------------------------
  Main
-------------------------------------------------------------------*/

int main(void)
{
    /* Enable GPIOA and GPIOC clocks */
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPCEN;

    /* Configure GPIO pins */
    gpio_output_init(led_a.port, led_a.pin);
    gpio_output_init(led_b.port, led_b.pin);
    gpio_output_init(led_c.port, led_c.pin);
    gpio_output_init(led_d.port, led_d.pin);

    /* Create Tasks */

    xTaskCreate(led_task,"LED_A",configMINIMAL_STACK_SIZE,(void *)&led_a,tskIDLE_PRIORITY + 3,NULL);
    xTaskCreate(led_task,"LED_B",configMINIMAL_STACK_SIZE,(void *)&led_b,tskIDLE_PRIORITY + 2,NULL);
    xTaskCreate(led_task,"LED_C",configMINIMAL_STACK_SIZE,(void *)&led_c,tskIDLE_PRIORITY+0,NULL);
    xTaskCreate(led_task,"LED_D",configMINIMAL_STACK_SIZE,(void *)&led_d,tskIDLE_PRIORITY + 1,NULL);

    /* Start Scheduler */
    vTaskStartScheduler();

    /* Should never reach here */
    while (1)
    {
    }
}

/*------------------------------------------------------------------
  Stack Overflow Hook
-------------------------------------------------------------------*/

void vApplicationStackOverflowHook(TaskHandle_t xTask,
                                   char *pcTaskName)
{
    (void)xTask;
    (void)pcTaskName;

    while (1)
    {
    }
}

void vApplicationTickHook(void)
{
}

// /* Required because FreeRTOSConfig.h sets configCHECK_FOR_STACK_OVERFLOW=2 */
// void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
// {
//     (void)xTask;
//     (void)pcTaskName;
//     for (;;) {
//     }
// }


/*
 * four-thread-blink_priority/main.c
 *
 * Four independent FreeRTOS tasks blinking four LEDs.
 *
 * PA3 -> 500 ms
 * PA0 -> 450 ms
 * PA1 -> 350 ms
 * PA2 -> 350 ms
 */