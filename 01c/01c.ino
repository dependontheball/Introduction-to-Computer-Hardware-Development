#define RED_PIN     40
#define YELLOW_PIN  41
#define GREEN_PIN   42
#define SW_PIN      1


void setup() {
 pinMode(RED_PIN, OUTPUT);
 pinMode(YELLOW_PIN, OUTPUT);
 pinMode(GREEN_PIN, OUTPUT);
 pinMode(SW_PIN, INPUT_PULLUP);
 digitalWrite(RED_PIN, 0);
 digitalWrite(YELLOW_PIN, 0);
 digitalWrite(GREEN_PIN, 0);
}

int count = 0;
int first = 0;
void loop() {

 if (digitalRead(SW_PIN) == 0) {
    while(digitalRead(SW_PIN) == 0){
      if(first == 0){
        count++;
        first++;
      }
      if(count%3 == 0){
        digitalWrite(RED_PIN, 0);
        digitalWrite(YELLOW_PIN, 0);
        digitalWrite(GREEN_PIN, 1);
      }
      if(count%3 == 1){
        digitalWrite(RED_PIN, 0);
        digitalWrite(YELLOW_PIN, 1);
        digitalWrite(GREEN_PIN, 0);
        }
      if(count%3 == 2){
        digitalWrite(RED_PIN, 1);
        digitalWrite(YELLOW_PIN, 0);
        digitalWrite(GREEN_PIN, 0);
      }
      printf("%d\n",count);
      delay(300);
    }
  } else {
    first = 0;
  }
}

