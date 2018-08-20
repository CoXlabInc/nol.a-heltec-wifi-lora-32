#include <cox.h>

#define LED_PIN    25
#define BUTTON_PIN 0

Timer timerHello;
Timer timerHello2;

static void taskHello(void *) {
  struct timeval t;
  gettimeofday(&t, NULL);

  Serial.printf(
    "Hello every 1sec. This is Serial. gettimeofday:%u.%06u,", t.tv_sec, t.tv_usec
  );

  digitalToggle(LED_PIN);
  Serial.printf(" Button:%d, LED:%d\n", digitalRead(BUTTON_PIN), digitalRead(LED_PIN));
}

static void taskHello2(void *) {
  struct timeval t;
  gettimeofday(&t, NULL);

  Serial.printf(
    "Hello every 5sec. This is Serial. gettimeofday:%u.%06u\n", t.tv_sec, t.tv_usec
  );
}

static void eventKeyPressed() {
  Serial.printf("* Button is pressed!\n");
}

static void eventSerialRx(SerialPort &p) {
  while (p.available() > 0) {
    char c = p.read();
    p.write(c); //echo
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("*** [Heltec WiFi-LoRa-32 Kit Basic ***");
  Serial.onReceive(eventSerialRx);
  Serial.listen();

  timerHello.onFired(taskHello, NULL);
  timerHello.startPeriodic(1000);

  timerHello2.onFired(taskHello2, NULL);
  timerHello2.startPeriodic(5000);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);

  pinMode(BUTTON_PIN, INPUT);
  attachInterrupt(BUTTON_PIN, eventKeyPressed, FALLING);
}
