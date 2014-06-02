/****************************************
Scrolling Sound Meter Sketch for the 
Adafruit Microphone Amplifier
****************************************/
#include <stdint.h>
#include <ffft.h>

#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"
 
// Include the Matrix code for display
Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix();
 
const int maxScale = 8;
const int redZone = 5;

const int myChannel = 1; // Set the channel
const int micInput = 0;
unsigned int timer = 0;
unsigned int timerMax = 1500;
unsigned int eqLevel = 0;
 
#define  IR_AUDIO  0 // ADC channel to capture

volatile  byte  position = 0;
volatile  long  zero = 0;

int16_t capture[FFT_N];			/* Wave captureing buffer */
complex_t bfly_buff[FFT_N];		/* FFT buffer */
uint16_t spektrum[FFT_N/2];		/* Spectrum output buffer */ 
 
void setup() 
{
   Serial.begin(57600);
   adcInit();
   adcCalb();
   matrix.begin(0x70);  // pass in the address
}
  
void loop() 
{
  unsigned int level = 0;
  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;
  
  if (position == FFT_N)
    {
      fft_input(capture, bfly_buff);
      fft_execute(bfly_buff);
      fft_output(bfly_buff, spektrum);
      level = spektrum[20] + spektrum[30] * 50; // instead of looping thru the spektrum (0 - 63); find 1 bin
      position = 0;
    }  
   
   if (level > 0) {
     eqLevel = level;
   }
   
   timer++;
   
   if (timer > timerMax) {
     
     Serial.println(myChannel);
     Serial.println(eqLevel);
     
     // map 1v p-p level to the max scale of the display
     int displayPeak = map(eqLevel, 0, 1023, 0, maxScale);
   
     // Update the display:
     for (int i = 0; i < 7; i++)  // shift the display left
     {
        matrix.displaybuffer[i] = matrix.displaybuffer[i+1];
     }
   
     // draw the new sample
     for (int i = 0; i <= maxScale; i++)
     {
        if (i >= displayPeak)  // blank these pixels
        {
           matrix.drawPixel(i, 7, 0);
        }
        else if (i < redZone) // draw in green
        {
           matrix.drawPixel(i, 7, LED_GREEN);
        }
        else // Red Alert!  Red Alert!
        {
           matrix.drawPixel(i, 7, LED_RED);
        }
     }
     matrix.writeDisplay();  // write the changes we just made to the display
     timer = 0;
   }

}

// free running ADC fills capture buffer
ISR(ADC_vect)
{
  if (position >= FFT_N)
    return;
  
  capture[position] = ADC + zero;
  if (capture[position] == -1 || capture[position] == 1)
    capture[position] = 0;

  position++;
}
void adcInit(){
  /*  REFS0 : VCC use as a ref, IR_AUDIO : channel selection, ADEN : ADC Enable, ADSC : ADC Start, ADATE : ADC Auto Trigger Enable, ADIE : ADC Interrupt Enable,  ADPS : ADC Prescaler  */
  // free running ADC mode, f = ( 16MHz / prescaler ) / 13 cycles per conversion 
  ADMUX = _BV(REFS0) | IR_AUDIO; // | _BV(ADLAR); 
  //ADCSRA = _BV(ADSC) | _BV(ADEN) | _BV(ADATE) | _BV(ADIE) | _BV(ADPS2) | _BV(ADPS1); //prescaler 64 : 19231 Hz - 300Hz per 64 divisions
  ADCSRA = _BV(ADSC) | _BV(ADEN) | _BV(ADATE) | _BV(ADIE) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0); // prescaler 128 : 9615 Hz - 150 Hz per 64 divisions, better for most music
  sei();
}
void adcCalb(){
  Serial.println("Start to calc zero");
  long midl = 0;
  // get 2 meashurment at 2 sec
  // on ADC input must be NO SIGNAL!!!
  for (byte i = 0; i < 2; i++)
  {
    position = 0;
    delay(100);
    midl += capture[0];
    delay(900);
  }
  zero = -midl/2;
  Serial.println("Done.");
}
