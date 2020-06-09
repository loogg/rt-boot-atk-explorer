#include "led.h"
#include <board.h>
#include <agile_led.h>

//定义信号灯引脚
#define LED0_PIN GET_PIN(F, 9)
#define LED1_PIN GET_PIN(F, 10)

//定义信号灯对象
static agile_led_t *led0 = RT_NULL;
static agile_led_t *led1 = RT_NULL;

static uint8_t boot_ready_flag = 0;
static uint8_t recovery_flag = 0;

static const char *boot_ready_light_mode = "200,200";
static const char *recovery_light_mode = "1000,1000";

void led_boot_ready_mode(void)
{
    if(boot_ready_flag)
        return;
    
    boot_ready_flag = 1;
    agile_led_stop(led0);
    agile_led_set_light_mode(led0, boot_ready_light_mode, -1);
    agile_led_start(led0);
}

void led_recovery_mode(void)
{
    if(recovery_flag)
        return;
    
    recovery_flag = 1;
    agile_led_stop(led0);
    agile_led_set_light_mode(led0, recovery_light_mode, -1);
    agile_led_start(led0);
}

void led_boot_mode(void)
{
    if(boot_ready_flag)
    {
        boot_ready_flag = 0;
        agile_led_stop(led0);
    }
    agile_led_toggle(led0);
}

int led_init(void)
{
    //初始化信号灯对象
    led0 = agile_led_create(LED0_PIN, PIN_LOW, RT_NULL, 0);
    led1 = agile_led_create(LED1_PIN, PIN_LOW, RT_NULL, 0);

    RT_ASSERT(led0 != RT_NULL);
    RT_ASSERT(led1 != RT_NULL);

    agile_led_on(led0);
    agile_led_on(led1);
    rt_thread_mdelay(200);
    agile_led_off(led0);
    agile_led_off(led1);


    return RT_EOK;
}
