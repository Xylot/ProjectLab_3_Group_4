#include "msp430.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void sendConfirmation();
void sendError();
void sendPredefinedArray();
void sendRandArray();
void sendADCArray();
void sendADCValue();
void setupADC();
void setupUart();
void sampleADC();
void itoa2(long unsigned int value, char* result, int base);
void UARTSendArray(unsigned char * TxArray, unsigned char ArrayLength);


static volatile char data;
//char * data;

int adc[100] = {0};
unsigned int ADC_value=0;

//char *adcArray[100] = {"15","19","27","32","43","47","55","74","77","82","115","132","160","162","164","174","182","191","199","214","231","237","239","245","250","283","292","297","302","307","313","319","354","364","376","383","400","427","443","473","475","476","479","486","489","492","497","507","513","531","541","546","580","581","582","605","606","610","638","647","651","655","660","661","662","665","670","703","750","751","753","762","765","766","778","783","803","828","830","834","844","846","860","881","903","917","918","925","941","944","962","964","974","976","987","989","990","993","999","1017"};

//int ia[100] = {41, 17, 184, 875, 719, 349, 203, 658, 312, 889, 580, 470, 731, 427, 736, 491, 945, 667, 727, 311, 616, 254, 827, 153, 292, 82, 102, 266, 243, 420, 322, 201, 421, 263, 844, 437, 42, 674, 635, 669, 3, 236, 572, 608, 248, 564, 791, 536, 578, 718, 947, 994, 887, 982, 562, 559, 523, 516, 879, 778, 16, 985, 665, 817, 288, 381, 840, 742, 814, 98, 796, 230, 515, 579, 795, 100, 656, 351, 818, 473, 154, 323, 509, 479, 306, 565, 866, 201, 606, 683, 544, 664, 26, 48, 412, 13, 743, 32, 379, 141};
int ia[10] = {41, 17, 184, 875, 719, 349, 203, 658, 312, 889};
void main(void)
{
  WDTCTL = WDTPW + WDTHOLD; // Stop WDT

  P1DIR |= BIT0 + BIT3;
  P1OUT = BIT0; // Set P1.0

  P2DIR |= BIT3 + BIT4 + BIT5;
  P2OUT = BIT3;

 BCSCTL1 = CALBC1_1MHZ;          // Set range   DCOCTL = CALDCO_1MHZ;
//  BCSCTL2 &= ~(DIVS_3);           // SMCLK = DCO = 1MHz
//  P1SEL |= BIT5;
  DCOCTL = CALDCO_1MHZ; // Set DCO to 1MHz

  /* Configure hardware UART */
  readADC();
  setupUart();
  //readADC();

  //_BIS_SR(LPM0_bits +GIE);
  __bis_SR_register(LPM0_bits + GIE); // Enter LPM0, interrupts enabled

//  // ADC configuration,V+ref=3V,V-ref=0V,Channel=A0
//     ADC10CTL0  = ADC10ON + ADC10IE; // Vref Vr+=3v,Vr-=VSS,
//                       // S&Htime = 4 X ADCCLK,ADC10 on,ADC interrupts enabled
//     ADC10CTL1  = INCH_4; // INCH =0000->A0,ADCCLK src = ADC10CLK,
//                              // ADCCLK/8,Single Channel Single Conversion
//     ADC10AE0   |= 0x4; // channel A0
//
//     ADC10CTL0 |= ENC + ADC10SC; // Start Conversion

     //_BIS_SR(LPM0_bits +GIE);    // Go to LPM0,interrupts enabled

      while(1){

          setupUart();
//          char s[100];
//          UARTSendArray("[", 1);
//          itoa2(ADC_value, s, 10);
//          UARTSendArray(s, strlen(s));
//          UARTSendArray("]", 1);
      }

    // __bis_SR_register(GIE);

  //__enable_interrupt();

  //__bis_SR_register(LPM0_bits + GIE); // Enter LPM0, interrupts enabled

//  while(1) {
//      ADC_value = ADC10MEM;
//  }

  //setupADC();
//  while(1){
//      //sampleADC();
//      int i;
////      for(i=0;i<100;i++){
////          __delay_cycles(1000);               // Wait for ADC Ref to settle
////          ADC10CTL0 |= ENC + ADC10SC;         // Sampling and conversion start
////          __bis_SR_register(CPUOFF + GIE);    // Low Power Mode 0 with interrupts enabled
////          adc[i] = ADC10MEM;
////      }
//        __delay_cycles(1000);               // Wait for ADC Ref to settle
////        ADC10CTL0 |= ENC + ADC10SC;         // Sampling and conversion start
////        __bis_SR_register(CPUOFF + GIE);    // Low Power Mode 0 with interrupts enabled
//        ADC_value = ADC10MEM;               // Assigns the value held in ADC10MEM to the integer called ADC_value
//
//
//  }


}

void setupUart() {
    P1SEL = BIT1 + BIT2; // P1.1 = RXD, P1.2=TXD
      P1SEL2 = BIT1 + BIT2; // P1.1 = RXD, P1.2=TXD
      UCA0CTL1 |= UCSSEL_2; // Use SMCLK
      UCA0BR0 = 104; // Set baud rate to 9600 with 1MHz clock (Data Sheet 15.3.13)
      UCA0BR1 = 0; // Set baud rate to 9600 with 1MHz clock
      UCA0MCTL = UCBRS0; // Modulation UCBRSx = 1
      UCA0CTL1 &= ~UCSWRST; // Initialize USCI state machine
      IE2 |= UCA0RXIE; // Enable USCI_A0 RX interrupt
}

void setupADC() {
//  ADC10CTL1 = CONSEQ_2 + INCH_0;
//  ADC10CTL0 = ADC10SHT_2 + MSC + ADC10ON + ADC10IE;
//  ADC10DTC1 = 0x64;
//  ADC10AE0 |= BIT5;

//    ADC10CTL1 = INCH_3 + ADC10DIV_3 ;         // Channel 3, ADC10CLK/3
//    ADC10CTL0 = SREF_0 + ADC10SHT_3 + ADC10ON + ADC10IE;  // Vcc & Vss as reference, Sample and hold for 64 Clock cycles, ADC on, ADC interrupt enable
//    ADC10AE0 |= BIT5;
}

void sampleADC() {
//  ADC10CTL0 &= ~ENC;
//  while (ADC10CTL1 & BUSY);
//  ADC10SA = (int)adc;
//  ADC10CTL0 |= ENC + ADC10SC;
//  __bis_SR_register(CPUOFF + GIE);
}

// Echo back RXed character, confirm TX buffer is ready first
#pragma vector = USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void) {
    data = UCA0RXBUF;
    //         do {
    //             data = UCA0RXBUF;
    //         }
    //         while(!(data[0] == '\0'));
    //data = UCA0RXBUF;

    UCA0TXBUF = "";

    switch (data) {
    case 'p':
    {
     sendPredefinedArray();
    }
    break;
    case 'r':
    {
     //sendRandArray();
     sendADCArray();
    }
    break;
    case 'a':
    {
     readADC();
     sendADCValue();
    }
    break;
    default:
    {
     //sendError();
    }
    break;
    }


}

void readADC() {
    ADC10CTL0 = 0x00;
    ADC10CTL1 = INCH_4 | ADC10SSEL_3;  // Input Channel A0 and SMCLK
    ADC10AE0 = 0x04;
    ADC10CTL0 = ADC10ON | ENC;           // Turn on ADC and Enable Conversion
    ADC10CTL0 = ADC10CTL0 | ADC10SC;
    //while( ADC10CTL1 & ADC10BUSY );       // Wait until conversion is complete
    ADC_value = ADC10MEM;
    //UCA0CTL1 &= ~UCSWRST;
    //IE2 |= UCA0RXIE;
    //setupUart();
}

void sendRandArray() {
  char* c_array[100];
  int randArray[100];
  //srand(0);

  int j;
  for (j = 0; j < 100; j++) {
      srand(j);
    randArray[j] = (rand() % 1025);
  }

  char s[100];
  UARTSendArray("[", 1);
  int z;
  for(z = 0; z < 100; z++){
      itoa2(randArray[z], s, 10);
      UARTSendArray(s, strlen(s));
      UARTSendArray(",", 1);
  }
  UARTSendArray("]", 1);
}

void sendPredefinedArray() {
  char s[100];
  UARTSendArray("[", 1);
  int z;
  for(z = 0; z < 10.; z++){
      itoa2(ia[z], s, 10);
      UARTSendArray(s, strlen(s));
      UARTSendArray(",", 1);
  }
  UARTSendArray("]", 1);
}

void sendADCArray() {
    char s[100];
    UARTSendArray("[", 1);
    int z;
    for(z = 0; z < strlen(adc); z++){
      //itoa2(adc[z], s, 10);
      itoa2(adc[z], s, 10);
      UARTSendArray(s, strlen(s));
      UARTSendArray(",", 1);
    }
    UARTSendArray("]", 1);
}

void sendADCValue() {
    //readADC();
    char s[100];
    UARTSendArray("[", 1);
    itoa2(ADC10MEM, s, 10);
    UARTSendArray(s, strlen(s));
    UARTSendArray("]", 1);
}

void sendConfirmation() {
  UARTSendArray("Received command: ", 18);
  UARTSendArray( & data, 1);
  UARTSendArray("\n\r", 2);
}

void sendError() {
  UARTSendArray("ERROR: Command not found", 24);
  UARTSendArray( & data, 1);
  UARTSendArray("\n\r", 2);
}

void itoa2(long unsigned int value, char* result, int base) {
  // check that the base if valid
  if (base < 2 || base > 36) { *result = '\0'; }

  char* ptr = result, *ptr1 = result, tmp_char;
  int tmp_value;

  do {
    tmp_value = value;
    value /= base;
    *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + (tmp_value - value * base)];
  } while (value);

  // Apply negative sign
  if (tmp_value < 0) *ptr++ = '-';
  *ptr-- = '\0';
  while (ptr1 < ptr) {
    tmp_char = *ptr;
    *ptr-- = *ptr1;
    *ptr1++ = tmp_char;
  }
}

#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
    __bic_SR_register_on_exit(CPUOFF);
}

void UARTSendArray(unsigned char * TxArray, unsigned char ArrayLength) {
  while (ArrayLength--) {
    while (!(IFG2 & UCA0TXIFG));
    UCA0TXBUF = * TxArray;
    TxArray++;
  }
}

