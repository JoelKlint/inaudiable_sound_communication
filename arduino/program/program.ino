/* 
 Parts required:
 speaker

 Created 21 May 2018
 by Joel Klint
*/

char MESSAGE[12] = "Joel Klint\n";

int speakerPin = 8;

const int LOW_FREQ = 19000;
const int MEDIUM_FREQ = 20000;
const int HIGH_FREQ = 21000;
unsigned int currentFreq = LOW_FREQ;

int toneDuration = 25;

void makeTone() {
  tone(speakerPin, currentFreq);
}

void sendPositiveBit() {
  switch (currentFreq) {
    case LOW_FREQ:
      currentFreq = HIGH_FREQ;
      break;
    case MEDIUM_FREQ:
      currentFreq = LOW_FREQ;
      break;
    case HIGH_FREQ:
      currentFreq = MEDIUM_FREQ;
      break;
  }

  Serial.print("1");
  Serial.print(" ");
  Serial.print(currentFreq);
  Serial.print(" ");
  makeTone();
}
void sendNegativeBit() {
  switch (currentFreq) {
    case LOW_FREQ:
      currentFreq = MEDIUM_FREQ;
      break;
    case MEDIUM_FREQ:
      currentFreq = HIGH_FREQ;
      break;
    case HIGH_FREQ:
      currentFreq = LOW_FREQ;
      break;
  }
  Serial.print("0");
  Serial.print(" ");
  Serial.print(currentFreq);
  Serial.print(" ");
  makeTone();
}

void setup() {

  Serial.begin(9600);
    
  // Start the sender
  for(int i=0; i < 50; i++){
    makeTone();
    delay(toneDuration); 
  }
}

void loop() {  
  
  // Loop over all chars
  for(int i=0; i < sizeof(MESSAGE); i++) {
    char send_char = MESSAGE[i];
    Serial.print("Will send char: ");
    Serial.println(send_char);

    // Loop over the bits in the char
    for(int j=7; j >= 0; j--) {

      delay(toneDuration);
      
      // Send the bit
      if(bitRead(send_char, j) == 1) {
        sendPositiveBit();
      } else {
        sendNegativeBit();
      }
    }
    Serial.println("");
  }
  
}

