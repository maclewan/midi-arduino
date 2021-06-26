#include <MIDI.h>
#include "Controller.h"

/*************************************************************
  MIDI CONTROLLER

  by Notes and Volts
  www.notesandvolts.com

  Version 1.2 **Arduino UNO ONLY!**
 *************************************************************/

MIDI_CREATE_DEFAULT_INSTANCE();

//************************************************************
//***SET THE NUMBER OF CONTROLS USED**************************
//************************************************************
//---How many buttons are connected directly to pins?---------
byte NUMBER_BUTTONS = 6;
//---How many potentiometers are connected directly to pins?--
byte NUMBER_POTS = 1;

byte NUMBER_MUX_BUTTONS = 0;
byte NUMBER_MUX_POTS = 0;
//************************************************************
byte FREE_CHANNEL = 10;




//***DEFINE DIRECTLY CONNECTED POTENTIOMETERS************************
//Pot (Pin Number, Command, CC Control, Channel Number)
//**Command parameter is for future use**

Pot PO1(A0, 0, 1, FREE_CHANNEL);

Pot *POTS[] {&PO1};
//*******************************************************************


//***DEFINE DIRECTLY CONNECTED BUTTONS*******************************
//Button (Pin Number, Command, Note Number, Channel, Debounce Time)
//** Command parameter 0=NOTE  1=CC  2=Toggle CC **

Button BU1(2, 0, 51, FREE_CHANNEL, 5 );
Button BU2(3, 0, 52, FREE_CHANNEL, 5 );
Button BU3(4, 0, 53, FREE_CHANNEL, 5 );
Button BU4(5, 0, 54, FREE_CHANNEL, 5 );
Button BU5(6, 0, 55, FREE_CHANNEL, 5 );
Button BU6(7, 0, 56, FREE_CHANNEL, 5 );

Button *BUTTONS[] {&BU1, &BU2, &BU3, &BU4, &BU5, &BU6};
//*******************************************************************







void setup() {
  MIDI.begin(MIDI_CHANNEL_OFF);

  //midi in setup
  pinMode (9, OUTPUT);
  pinMode (10, OUTPUT);
  pinMode (11, OUTPUT);
  pinMode (12, OUTPUT);

  MIDI.begin(MIDI_CHANNEL_OMNI); // Initialize the Midi Library.
  // OMNI sets it to listen to all channels.. MIDI.begin(2) would set it 
  // to respond to notes on channel 2 only.
  MIDI.setHandleNoteOn(MyHandleNoteOn); // This is important!! This command
  // tells the Midi Library which function you want to call when a NOTE ON command
  // is received. In this case it's "MyHandleNoteOn".
  MIDI.setHandleNoteOff(MyHandleNoteOff); // This command tells the Midi Library 
  // to call "MyHandleNoteOff" when a NOTE OFF command is received.
}

void loop() {
  MIDI.read();
  
  if (NUMBER_BUTTONS != 0){
    updateButtons();
  }
  
  if (NUMBER_POTS != 0) updatePots();

}


//*****************************************************************
void updateButtons() {

  // Cycle through Button array
  for (int i = 0; i < NUMBER_BUTTONS; i = i + 1) {
    byte message = BUTTONS[i]->getValue();

    //  Button is pressed
    if (message == 0) {
      switch (BUTTONS[i]->Bcommand) {
        case 0: //Note
          //MIDI.sendNoteOn(BUTTONS[i]->Bvalue, 127, BUTTONS[i]->Bchannel);
          break;
      }
    }

    //  Button is not pressed
    if (message == 1) {
      switch (BUTTONS[i]->Bcommand) {
        case 0:
          MIDI.sendNoteOn(BUTTONS[i]->Bvalue, 127, BUTTONS[i]->Bchannel);
          //MIDI.sendNoteOff(BUTTONS[i]->Bvalue, 0, BUTTONS[i]->Bchannel);
          break;
        
      }
    }
  }
}
//*******************************************************************



/*OLD OLD OLD
 * //*****************************************************************
void updateOnOffButtons() {

  // Cycle through Button array
  for (int i = 4; i < NUMBER_BUTTONS; i = i + 1) {
    byte message = BUTTONS[i]->getValue();

    //  Button is pressed
    if (message == 0) { 
      MIDI.sendNoteOn(BUTTONS[i]->Bvalue, 127, BUTTONS[i]->Bchannel);   
    }

    //  Button is not pressed
    if (message == 1) {
      MIDI.sendNoteOff(BUTTONS[i]->Bvalue, 0, BUTTONS[i]->Bchannel);
    }
  }
}

void updateStateButtons() {

  // Cycle through Button array
  for (int i = 0; i < NUMBER_BUTTONS-2; i = i + 1) {
    byte message = BUTTONS[i]->getValue();
    byte pin = BUTTONS[i]->getPin();

    //  Button is not pressed
    if (message == 1) {
      if(digitalRead(pin+7)==HIGH){
        MIDI.sendNoteOff(BUTTONS[i]->Bvalue, 0, BUTTONS[i]->Bchannel);  
      }
      else{
        MIDI.sendNoteOn(BUTTONS[i]->Bvalue, 127, BUTTONS[i]->Bchannel);
      }
    
    }
  }
}
 */












//***********************************************************************
void updatePots() {
  for (int i = 0; i < NUMBER_POTS; i = i + 1) {
    byte potmessage = POTS[i]->getValue();
    if (potmessage != 255) MIDI.sendControlChange(POTS[i]->Pcontrol, potmessage, POTS[i]->Pchannel);
  }
}
//***********************************************************************






void MyHandleNoteOn(byte channel, byte pitch, byte velocity) { 
  if(pitch==1){
    digitalWrite(9,HIGH);
  }
  if(pitch==2){
    digitalWrite(10,HIGH);
  }
  if(pitch==3){
    digitalWrite(11,HIGH);
  }
  if(pitch==4){
    digitalWrite(12,HIGH);
  }
  
}


void MyHandleNoteOff(byte channel, byte pitch, byte velocity) { 
  
  if(pitch==1){
    digitalWrite(9,LOW);
  }
  if(pitch==2){
    digitalWrite(10,LOW);
  }
  if(pitch==3){
    digitalWrite(11,LOW);
  }
  if(pitch==4){
    digitalWrite(12,LOW);
  }
}
