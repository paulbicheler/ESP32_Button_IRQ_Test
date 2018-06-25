// Simple sketch to test the if the button press works.
// Tested on Wemos lolin32
// GPIOs 34-39 are input-only *and* do not have internal pull-up or pull-down circuitry. This is mentioned in Appendix C.1 of the datasheet, Number 2 in the table.

//
#define PUSH_PIN 18
// More info on volatile variables: https://www.arduino.cc/reference/en/language/variables/variable-scope--qualifiers/volatile/
volatile int buttonState = 0; // the current reading from the input pin
volatile boolean buttonEvent =  false;

void setup() {
   Serial.begin(115200);
  // put your setup code here, to run once:
  pinMode(PUSH_PIN, INPUT_PULLUP);// Pullup means that piun is HIGH form the start
  // Reference to attachInterrupt: https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
  // A quick press activates the button once. A long press is considered as two changes.
  attachInterrupt(digitalPinToInterrupt(PUSH_PIN), onButtonEvent, CHANGE );// trigger the interrupt whenever the pin changes value. LOW if pressed,HIGH if released. 
  // attachInterrupt(digitalPinToInterrupt(PUSH_PIN), onButtonEvent,  RISING );// triggers when the pin goes from low to high. Goes HIGH when released.
  // attachInterrupt(digitalPinToInterrupt(PUSH_PIN), onButtonEvent,  FALLING);// triggers when the pin goes from high to low. Goes LOW when pressed.
  //attachInterrupt(digitalPinToInterrupt(PUSH_PIN), onButtonEvent,  LOW);// trigger the interrupt whenever the pin is low. Does not work despite state being LOW?
}

/**Callback for rotary encoder push button interrupt */
void onButtonEvent() {
  buttonState = digitalRead(PUSH_PIN);
  buttonEvent = true;
}


void loop() {
    Serial.print("Button state: ");
    Serial.println(buttonState);

    noInterrupts();
    if (buttonEvent) {
      buttonEvent = false;     
      Serial.println("Button was pressed.");
    }
    interrupts();
    
    delay(1000);
}
