# **CALIFORNIA STATE UNIVERSITY, NORTHRIDGE**

COLLEGE OF ENGINEERING AND COMPUTER SCIENCE

# Implantable-Motor-Controller with Wireless Communication

![image](https://user-images.githubusercontent.com/98668234/174352608-28c0adcf-a6dc-42e8-b1ac-e4b4233af9ce.png)



# Purpose: 

The general purpose within this project was to establish a wireless design designated to receive transmitted power which in turn would control a motor. This motor is intended to go within the heart in order to simulate a heartbeat, which is done by having the motor controller cause the motor to pump blood at a designated rate. In order to successfully implement said idea, we needed to use wireless power transmitter and receiver. The receiving system that was created consisted of an **internal resonator that was tuned for 6.78 MHz**, the lowest frequency allowed without interference from other medical devices. The receiver was coupled to the internal resonator, which produces an AC voltage. The AC voltage is then fed to a rectifier, the **CBRDFSH2-100 bridge rectifier**, which was meant to change the AC input into a DC output that would be then sent a voltage regulator that would prevent the overload. The **voltage regulator we chose was the TLV76760QWDRBRQ1 voltage
regulator**, which we chose for its size, which would fit into our PCB’s design parameters. The output of the voltage regulator was then fed into the motor controller, micro-controller, and to the voltagecontrolled switch. The respective components chosen were the **DRV8837 motor controller, the ATTINY20-MMHR micro-controller, and the TS5A4596 voltage switch**. These components were all chosen for their dimensions primarily, which needed to meet the specification in order to fit within the 5 mm margin, which was our designated PCB width.

<br>


# **Procedures/Imlementations:**

<br>

## Initial Testing Using ATTINY24A

### ATTINY24A Pinout:

5V (Power Supply) VTG = Pin 1

GND (Power Supply) GND - Pin 14

MISO - Pin 8

MOSI - Pin 7

SCK (Clock used from program: default is 1 MHz) - Pin 9

RESET BAR - Pin 4



IMPORTANT: A Picture will be attached showing connections of ATTINY24A labeled PIC1


<br>

### PICKit 4 Pinout:

V (Power Supply) VTG = Pin 2

GND (Power Supply) GND - Pin 3

MISO - Pin 4

MOSI - Pin 5

SCK (Clock used from program: default is 1 MHz) - Pin 6

RESET BAR - Pin 7



IMPORTANT: PICKit has an arrow indicating which is the first pin. 
A picture will be supplied. It will be labeled PIC2. Just to ensure that connections
are made properly

<br>


After we set up these connections, we ensured that the program used was in MPLAB x IDE
with the latest compiler xc8 (v2.32)


## **To Begin Programming/Debugging:**

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




## How To Change PWM Output Using Specified Bits and Registers:

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


## Second Testing Using ATTINY20-MMHR

Upon Successful implementation using the ATTINY24A micro controller, we determined that the same C language code may be utilized in order to successfully create the desired PWM. Once the code was set in stone, the only difference would be utilizing the ATTINY20-MMHR which consisted of a TPI protocol (different connections), so the following will address the connections and how proper programming was conducted.

<br>

**Datasheet and documention for TPI Protocol can be found in following links provided:**

**Datasheet: https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-8235-8-bit-AVR-Microcontroller-ATtiny20_Datasheet_Summary.pdf**

**TPI Protocol Information: https://ww1.microchip.com/downloads/en/Appnotes/doc8373.pdf**

<br>

### ATTINY20-MMHR Pinout:

5V (Power Supply) VTG = Pin 1

GND (Power Supply) GND - Pin 14

TPI CLK - Pin 11

TPI DATA - Pin 12

RESET BAR - Pin 13


<br>


### PICKit 4 Pinout:

V (Power Supply) VTG = Pin 2

GND (Power Supply) GND - Pin 3

TPI DATA - Pin 4

TPI CLK - Pin 5

RESET BAR - Pin 6





