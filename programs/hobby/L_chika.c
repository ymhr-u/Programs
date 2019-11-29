#include <wiringPi.h>
  
#define GPIO17 17
  
int main(void) {
  int i;
  if(wiringPiSetupGpio() == -1) return 1;
  
  pinMode(GPIO17, OUTPUT);
  
  for(i=0; i<10; i++){
    digitalWrite(GPIO17, 0);
    delay(500);
    digitalWrite(GPIO17, 1);
    delay(50);
  }
  digitalWrite(GPIO17, 0);
  
  return 0;
}
