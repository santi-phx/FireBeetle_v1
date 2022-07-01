// Una prueba de bajo consumo en modo Deep Sleep

#include <Arduino.h>

#define uS_TO_S_FACTOR 1000000 // Conversion factor for micro seconds to seconds
#define TIME_TO_SLEEP 5		   // Time ESP32 will go to sleep (in seconds)

RTC_DATA_ATTR int bootCount = 0;

// Function that prints the reason by which ESP32 has been awaken from sleep
void print_wakeup_reason()
{
	esp_sleep_wakeup_cause_t wakeup_reason;
	wakeup_reason = esp_sleep_get_wakeup_cause();
	/*switch(wakeup_reason)
	{
		case 1  : Serial.println("Wakeup caused by external signal using RTC_IO"); break;
		case 2  : Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
		case 3  : Serial.println("Wakeup caused by timer"); break;
		case 4  : Serial.println("Wakeup caused by touchpad"); break;
		case 5  : Serial.println("Wakeup caused by ULP program"); break;
		default : Serial.println("Wakeup was not caused by deep sleep"); break;
	}*/
	switch (wakeup_reason)
	{
	case ESP_SLEEP_WAKEUP_EXT0:
		Serial.println("Wakeup caused by external signal using RTC_IO");
		break;
	case ESP_SLEEP_WAKEUP_EXT1:
		Serial.println("Wakeup caused by external signal using RTC_CNTL");
		break;
	case ESP_SLEEP_WAKEUP_TIMER:
		Serial.println("Wakeup caused by timer");
		break;
	case ESP_SLEEP_WAKEUP_TOUCHPAD:
		Serial.println("Wakeup caused by touchpad");
		break;
	case ESP_SLEEP_WAKEUP_ULP:
		Serial.println("Wakeup caused by ULP program");
		break;
	default:
		Serial.printf("Wakeup was not caused by deep sleep: %d\n", wakeup_reason);
		break;
	}
}

void setup()
{
	Serial.begin(115200);
	delay(1000); // Take some time to open up the Serial Monitor

	// setCpuFrequencyMhz(80);//No hay diferencia en consumo hasta ahora al usar esta instrucción
	// Increment boot number and print it every reboot
	++bootCount;
	Serial.println("Boot number: " + String(bootCount));

	// Print the wakeup reason for ESP32
	print_wakeup_reason();

	// Set timer to 5 seconds //esta es otra opción
	/*esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH,ESP_PD_OPTION_OFF);
	esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_SLOW_MEM,ESP_PD_OPTION_OFF);
	esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_FAST_MEM,ESP_PD_OPTION_OFF);
	esp_sleep_enable_timer_wakeup(2000000);
	esp_deep_sleep_start();*/

	esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
	Serial.println("Setup ESP32 to sleep for every " + String(TIME_TO_SLEEP) +
				   " Seconds");

	Serial.println("Going to sleep now");
	delay(1000);
	Serial.flush();
	// Go to sleep now
	esp_deep_sleep_start();
	Serial.println("This will never be printed");
}

void loop() {}
