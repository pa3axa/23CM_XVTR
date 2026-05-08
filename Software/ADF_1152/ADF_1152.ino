/* 
 ADF4351 PLL Frequency Init


 Connections for 23CM_XTVR
 ----------------------------------------------------------
 Please check the ADF4351 datasheet or use ADF4351 software
 to get PLL register values. ADF reference OCXO is 40 Mhz.

 
 PIN layout
   
 PA1 ADF4531 data (DATA)
 PA2 ADF4531 latch enable (LE)
 PA3 ADF4531 clock (CLK)   


 Set Speed for 1MHz

 ATtiny412 programming with megatinycore library

*/


// PLL registers
long int r0, r1, r2, r3, r4, r5;
 
/*------------------------------*/

void write2PLL(uint32_t PLLword) {              // clocks 32 bits word  directly to the STuW81300
                                                // msb (b31) first, lsb (b0) last

 noInterrupts();                                // disable interrupts to keep accurate timing. 
  
  for (byte i=32; i>0; i--) {                   // PLL word 32 bits
     
    (PLLword & 0x80000000? PORTA.OUTSET = PIN1_bm : PORTA.OUTCLR = PIN1_bm);   // data on PA1
                                                                               
    PORTA.OUTSET = PIN3_bm;                     // clock in bit on rising edge of CLK (PA3 = 1)
    PORTA.OUTCLR = PIN3_bm;                     // CLK (PA7 = 0)      
    (PLLword <<= 1);                            // rotate left for next bit
    }
    PORTA.OUTSET = PIN2_bm;                     // latch in PLL word on rising edge of LE (PA2 = 1)
    PORTA.OUTCLR = PIN2_bm;                     // LE (PA5 = 0)  

 interrupts();                                  // enable interrupts
   
} 



void setup () {


delay(1000); // Wait for ADF5341 to powerup

/* set PORTA bitwise to OUTPUT, for PA1, PA2 & PA3 */
  PORTA.DIR = 0b00001110;
  

/* Fout = 1152.000 MHz +5dBm  only RF port 40Mhz REF */
 r0 = 0x398008;  
 r1 = 0x8008029;
 r2 = 0x19004E42; 
 r3 = 0x4B3;
 r4 = 0x9A002C; // -1dBm , 0x9A003C = +5dBm; 
 r5 = 0x580005; 


 /* Fout = 1296.200 MHz +5dBm  only RF port 40Mhz REF
 r0 = 0x4080F8;
 r1 = 0x8008191;
 r2 = 0x19004E42; 
 r3 = 0x4B3;
 r4 = 0x9A003C;
 r5 = 0x580005; 
*/

 // write from r5 to r0
     write2PLL(r5); 
     write2PLL(r4); 
     write2PLL(r3);
     write2PLL(r2);
     write2PLL(r1);
     write2PLL(r0);  

} // End Setup



// main loop
//------------------------------------------------------------------------------------------------- 

void loop() {

  

}
