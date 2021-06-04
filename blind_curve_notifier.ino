// Including the required Arduino libraries
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

// Uncomment according to your hardware type
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
//#define HARDWARE_TYPE MD_MAX72XX::GENERIC_HW

// Defining size, and output pins
#define MAX_DEVICES 16
#define CS_PIN 53

// Create a new instance of the MD_Parola class with hardware SPI connection
MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

boolean setOnce = false;
boolean setOnceLow = false;
long previousMillis = 0;
boolean displayChange = true;

void setup() {
  // Intialize the object

  Serial.begin(9600);
  pinMode(2, INPUT);
  
  myDisplay.begin();

  // Set the intensity (brightness) of the display (0-15)
  myDisplay.setIntensity(0);

  // Clear the display
  myDisplay.displayClear();

}

void loop() {



  if(digitalRead(2) == HIGH){
    displayChange = false;  
    previousMillis = millis();
 
    if(!setOnce){
       myDisplay.displayClear();
       myDisplay.displayScroll("VEHICLE APPROACHING!!!", PA_CENTER, PA_SCROLL_LEFT, 50);
       setOnce = true;
       setOnceLow = false;
    }
  }else{
     if(millis() - previousMillis > 20000 && !displayChange){
        displayChange = true;  
     }
     
    if(!setOnceLow && displayChange){
       myDisplay.displayClear();
       myDisplay.displayScroll("SLOW DOWN!!!", PA_CENTER, PA_SCROLL_LEFT, 50);
       setOnceLow = true;
       setOnce = false;
    }
  }
  
  if (myDisplay.displayAnimate()) {
    myDisplay.displayReset();
  }
}
