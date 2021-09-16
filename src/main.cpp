#include <Arduino.h>
#include <esp_task_wdt.h>
#include "soc/rtc_wdt.h"
//3 seconds WDT

#define WDT_TIMEOUT 10
int i,j;

// TaskHandle_t Task1;
// void Task1_senddata(void * pvParameters )
// {
//   esp_task_wdt_init(WDT_TIMEOUT, true); //enable panic so ESP32 restarts
//   esp_task_wdt_add(NULL); //add current thread to WDT watch
//   for(j = 0;j<10;j++)
//   {
//     Serial.println("feed_0");
//     esp_task_wdt_reset();
//     delay(1000);
//   }
//   delay(30*1000);
// }
void setup() {
  // put your setup code here, to run once:
  delay(20);
  Serial.begin(115200);
  // Serial.setDebugOutput(true);
  Serial.println("setup");


  
  Serial.println(rtc_wdt_is_on());
  Serial.println(rtc_wdt_get_protect_status());

  rtc_wdt_protect_off();
  rtc_wdt_enable();

  rtc_wdt_feed();
  rtc_wdt_set_length_of_reset_signal(RTC_WDT_SYS_RESET_SIG, RTC_WDT_LENGTH_3_2us);
  rtc_wdt_set_stage(RTC_WDT_STAGE0, RTC_WDT_STAGE_ACTION_RESET_RTC);
  rtc_wdt_set_time(RTC_WDT_STAGE0, 120000);
  
  Serial.println(rtc_wdt_is_on());
  Serial.println(rtc_wdt_get_protect_status());



  // xTaskCreatePinnedToCore(Task1_senddata, /*任务实际对应的Function*/"Task1", /*任务名称*/10000, /*堆栈空间*/NULL, /*无输入值*/0, /*优先序0*/&Task1, /*对应的任务变量地址*/0); /*指定在核心0执行 */
  for(i = 0;i<10;i++)
  {
    Serial.println("feed_1");
    rtc_wdt_feed();
    delay(1000);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("not feed");
  delay(1000);

  // delay(120*1000);
}
/*first*/
// esp_task_wdt_init(WDT_TIMEOUT, true); //enable panic so ESP32 restarts
// esp_task_wdt_add(NULL); //add current thread to WDT watch
// esp_task_wdt_reset();

/*second*/
//enableCore0WDT();
//enableCore1WDT();
//enableLoopWDT();


/*third*/
//https://github.com/adafruit/Adafruit_SleepyDog
//Watchdog.enable(4000);milliseconds
// Watchdog.reset();

/*fourth*/
//#include "soc/rtc_wdt.h"
// rtc_wdt_set_length_of_reset_signal(RTC_WDT_SYS_RESET_SIG, RTC_WDT_LENGTH_3_2us);
// rtc_wdt_set_stage(RTC_WDT_STAGE0, RTC_WDT_STAGE_ACTION_RESET_RTC);
// rtc_wdt_set_time(RTC_WDT_STAGE0, 2000);
// rtc_wdt_feed();