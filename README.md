# **CALIFORNIA STATE UNIVERSITY, NORTHRIDGE**

COLLEGE OF ENGINEERING AND COMPUTER SCIENCE

# Implantable-Motor-Controller with Wireless CommunicationImplantable

![image](https://user-images.githubusercontent.com/98668234/174352608-28c0adcf-a6dc-42e8-b1ac-e4b4233af9ce.png)


# ATTINY24A Pinout:

5V (Power Supply) VTG = Pin 1

GND (Power Supply) GND - Pin 14

MISO - Pin 8

MOSI - Pin 7

SCK (Clock used from program: default is 1 MHz) - Pin 9

RESET BAR - Pin 4



IMPORTANT: A Picture will be attached showing connections of ATTINY24A labeled PIC1



# PICKit 4 Pinout:

V (Power Supply) VTG = Pin 2

GND (Power Supply) GND - Pin 3

MISO - Pin 4

MOSI - Pin 5

SCK (Clock used from program: default is 1 MHz) - Pin 6

RESET BAR - Pin 7



IMPORTANT: PICKit has an arrow indicating which is the first pin. 
A picture will be supplied. It will be labeled PIC2. Just to ensure that connections
are made properly




After we set up these connections, we ensured that the program used was in MPLAB x IDE
with the latest compiler xc8 (v2.32)


# **To Begin Programming/Debugging:**

We used the PICKit in UART Module, and were able to program everything with the following Code:


#include <avr/io.h>

  int main (void){
  
      DDRB |= (1 << DDB2); //PB2 output
      OCR0A = 128; // 50% duty cycle (128/256) at 8 bit
      CLKPR = (1 << CLKPCE); //clock divider enable bit
      CLKPR = (1 << CLKPS2); //clock divide by 2
      
      TCCR0A |= (1 << COM0A1); //set Phase correct PWM mode
      TCCR0A |= (1 << WGM00) ; //set Phase correct PWM to upcount (0 to 255)
      TCCR0B |= (1 << CS01); //Pre-scaler set to 1 (used for frequency)
      
    while (1) {
        
	}//end while
    
}//end main




# How To Change PWM Output Using Specified Bits and Registers:

**Datasheet for ATTINY24A can be found here: https://ww1.microchip.com/downloads/en/DeviceDoc/ATtiny24A-44A-84A-DataSheet-DS40002269A.pdf**


<br>

Specifications to each bit set and its function will be explained with the following:

<ins>BEFORE STARTING, IT IS IMPORTANT TO NOTE THAT (1 << "") SETS THE BIT TO 1 IN C CODE</ins>

<ins>DDRB |= (1 << DDB2); //PB2 is set as the output</ins>


<br>


**OCR0A = 128; // OCR0A – Output Compare Register A**

// This uses 8 bits which we in turn will use to create the Duty Cycle

// Currently there is a 50% duty cycle (128/256) at 8 bit

<br>


![image](https://user-images.githubusercontent.com/98668234/174401785-219d8282-be8c-4bcf-b279-5609deb32a45.png)

This image can also be found on the ATTINY24A spec sheet, page 89


<br>


**CLKPR = (1 << CLKPCE); // Bit 7 – CLKPCE: Clock Prescaler Change Enable**

//CLKPR – Clock Prescale Register

//This is used to scale the clock which is set at 1MHz by default

<br>


![image](https://user-images.githubusercontent.com/98668234/174401847-a5787833-fca7-43cb-95bb-5e88a8e79058.png)

This image can also be found on the ATTINY24A spec sheet, page 37

<br>


**CLKPR = (1 << CLKPS0); //clock divide by 2**

//CLKPR – Clock Prescale Register

//Enabeling these bits determines the clock division factor


<br>

![image](https://user-images.githubusercontent.com/98668234/174401874-6f5e2cb9-6e60-4703-b03d-7575fb18883d.png)

This image can also be found on the ATTINY24A spec sheet, page 38

<br>


**TCCR0A |= (1 << COM0A1); //set Phase correct PWM**

//TCCR0A – Timer/Counter Control Register A

//Setting COM0A1 to 1, in Phase Correct Mode, has up-counting

//This means that going from 0-255 for OC0A will be 0 to 100% Duty Cycle respectively


<br>

![image](https://user-images.githubusercontent.com/98668234/174401920-4ecce6ac-006e-44bb-821f-c921d7057c67.png)

This image can also be found on the ATTINY24A spec sheet, page 86


<br>

**TCCR0A |= (1 << WGM00) ; //set Phase correct PWM mode**

//TCCR0A – Timer/Counter Control Register A

//Setting WGM00 to 1 guves us the Mode of Operation to PWM, Phase Correct

//With the Top being 0xFf (255), and OCRA is uodated at the TOP (resets)

<br>

![image](https://user-images.githubusercontent.com/98668234/174401953-3edb5592-a60b-4bec-acad-8d58edf56d0a.png)

This image can also be found on the ATTINY24A spec sheet, page 87

<br>

**TCCR0B |= (1 << CS01); //Pre-scaler set to 1**

//TCCR0B – Timer/Counter Control Register B

//Setting CS00 to 1 enables a clock prescaling of 1 (called no prescaling)


<br>
![image](https://user-images.githubusercontent.com/98668234/174401991-fa0819c8-b518-455e-bb23-3d9697a1811e.png)

This can also be found on the ATTINY24A spec sheet, page 88


