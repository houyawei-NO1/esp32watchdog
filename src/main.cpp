#include <Arduino.h>
#include <esp_task_wdt.h>
//3 seconds WDT
#define WDT_TIMEOUT 10
int i,j;

TaskHandle_t Task1;
void Task1_senddata(void * pvParameters )
{
  esp_task_wdt_init(WDT_TIMEOUT, true); //enable panic so ESP32 restarts
  esp_task_wdt_add(NULL); //add current thread to WDT watch
  for(j = 0;j<10;j++)
  {
    Serial.println("feed_0");
    esp_task_wdt_reset();
    delay(1000);
  }
  delay(30*1000);
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println("setup");


  esp_task_wdt_init(WDT_TIMEOUT, true); //enable panic so ESP32 restarts
  esp_task_wdt_add(NULL); //add current thread to WDT watch

  xTaskCreatePinnedToCore(Task1_senddata, /*任务实际对应的Function*/"Task1", /*任务名称*/10000, /*堆栈空间*/NULL, /*无输入值*/0, /*优先序0*/&Task1, /*对应的任务变量地址*/0); /*指定在核心0执行 */
  for(i = 0;i<10;i++)
  {
    Serial.println("feed_1");
    esp_task_wdt_reset();
    delay(1000);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("not feed");
  delay(1000);

  // delay(120*1000);
}


  /*second*/
  //enableCore0WDT();
  //enableCore1WDT();
  //enableLoopWDT();


  /*third*/
//https://github.com/adafruit/Adafruit_SleepyDog
//Watchdog.enable(4000);milliseconds
// Watchdog.reset();