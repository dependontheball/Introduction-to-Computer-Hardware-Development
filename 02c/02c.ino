#define ANALOG_PIN 6
#define RED_PIN     40
#define YELLOW_PIN  41
#define GREEN_PIN   42
#define PWM_FREQ    5000
#define PWM_RES     10

void setupPwm(int pin){
  ledcAttach(pin,PWM_FREQ,PWM_RES);
}

void setup() {
  analogSetAttenuation(ADC_11db);
  setupPwm(RED_PIN);
  setupPwm(YELLOW_PIN);
  setupPwm(GREEN_PIN);
}
int a,b,c;
// 1 -> 25%
// 4 -> 100%
void loop() {
  printf("%d\n",analogReadMilliVolts(ANALOG_PIN));
  delay(100);
  int val = analogReadMilliVolts(ANALOG_PIN);
  if (1400 < val && val < 1500){
    a = 2*256 - 1;
    b = 0;
    c = 0;
  }
  if (390 < val && val < 1400){
    a = 4*256 - 1;
    b = 0;
    c = 0;
  }
  if (350 < val && val < 390){
    a = 0;
    b = 2*256 - 1;
    c = 0;
  }
  if (200 < val && val < 340){
    a = 0;
    b = 4*256 - 1;
    c = 0;
  }
  if (100 < val && val < 200){
    a = 0;
    b = 0;
    c = 2*256 - 1;
  }
  if (val < 100){
    a = 0;
    b = 0;
    c = 4*256 - 1;
  }
  ledcWrite(RED_PIN, a);
  ledcWrite(YELLOW_PIN, b);
  ledcWrite(GREEN_PIN, c);
  delay(100);
}
