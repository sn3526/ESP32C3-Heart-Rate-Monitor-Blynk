
#define BLYNK_TEMPLATE_ID "TMPL33ssmvBRN"
#define BLYNK_TEMPLATE_NAME "HR Monitor"
#define BLYNK_AUTH_TOKEN "aOv4_b6nO5Yo6Cq04h8G1wNt9MxUxtjI"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

const char* ssid = "Saran";
const char* password = "12345678";

const int PULSE_PIN = 2; 
const int LOW_BPM_LIMIT = 60;
const int HIGH_BPM_LIMIT = 100;

BlynkTimer timer;

int bpm = 0;
int signalValue = 0;
int previousSignal = 0;
int threshold = 2000;

bool beatDetected = false;
unsigned long lastBeatTime = 0;
unsigned long abnormalSince = 0;
unsigned long lastAlertTime = 0;

const unsigned long MIN_BEAT_INTERVAL = 300;
const unsigned long MAX_BEAT_INTERVAL = 2000;
const unsigned long ABNORMAL_DELAY = 5000;
const unsigned long ALERT_REPEAT_DELAY = 60000;

void readPulseSensor() {
  signalValue = analogRead(PULSE_PIN);

  if (signalValue > threshold &&
      previousSignal <= threshold &&
      !beatDetected) {

    unsigned long now = millis();
    unsigned long interval = now - lastBeatTime;

    if (lastBeatTime != 0 &&
        interval >= MIN_BEAT_INTERVAL &&
        interval <= MAX_BEAT_INTERVAL) {
      int newBPM = 60000 / interval;

      if (newBPM >= 30 && newBPM <= 200) {
        bpm = newBPM;
      }
    }

    lastBeatTime = now;
    beatDetected = true;
  }

  if (signalValue < threshold - 100) {
    beatDetected = false;
  }

  previousSignal = signalValue;
}

void sendToCloud() {
  if (!Blynk.connected()) return;

  Blynk.virtualWrite(V0, bpm);
  Blynk.virtualWrite(V1, signalValue);

  Serial.print("Pulse signal: ");
  Serial.print(signalValue);
  Serial.print(" | Heart rate: ");
  Serial.print(bpm);
  Serial.println(" BPM");
}

void checkHeartRateAlert() {
  if (!Blynk.connected()) return;

  if (lastBeatTime == 0 || bpm == 0) {
    abnormalSince = 0;
    return;
  }

  bool abnormal = (bpm < LOW_BPM_LIMIT ||
                   bpm > HIGH_BPM_LIMIT);

  if (!abnormal) {
    abnormalSince = 0;
    return;
  }

  if (abnormalSince == 0) {
    abnormalSince = millis();
    return;
  }

  if (millis() - abnormalSince >= ABNORMAL_DELAY &&
      (lastAlertTime == 0 ||
       millis() - lastAlertTime >= ALERT_REPEAT_DELAY)) {

    String message = "Heart rate reading: " +
                     String(bpm) + " BPM";

    Blynk.logEvent("heart_rate_alert", message);
    Serial.println("Cloud alert event sent.");

    lastAlertTime = millis();
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  analogReadResolution(12);
  pinMode(PULSE_PIN, INPUT);

  Serial.println("Starting heart-rate monitor...");

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);

  Serial.println("Connected to Blynk Cloud.");

  timer.setInterval(10L, readPulseSensor);
  timer.setInterval(2000L, sendToCloud);
  timer.setInterval(1000L, checkHeartRateAlert);
}

void loop() {
  Blynk.run();
  timer.run();
}
