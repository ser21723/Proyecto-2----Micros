#include <xc.h>

// CONFIGURACIÓN 1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits 
#pragma config WDTE = OFF       // Watchdog Timer Enable bit 
#pragma config PWRTE = OFF      // Power-up Timer Enable bit 
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit 
#pragma config CP = OFF         // Code Protection bit 
#pragma config CPD = OFF        // Data Code Protection bit 
#pragma config BOREN = OFF      // Brown Out Reset Selection bits 
#pragma config IESO = OFF       // Internal External Switchover bit 
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit 
#pragma config LVP = OFF        // Low Voltage Programming Enable bit 

// CONFIGACIÓN 2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit 
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits 

#define _XTAL_FREQ 8000000


//--------------------------------VARIABLES-------------------------------------
//POTENCIOMETROS 
unsigned char   POTM0;
unsigned char   POTM1;
unsigned char   POTM2;

//INSTRUCCIONES POTENCIOMETROS 
unsigned char   IPOTM0;
unsigned char   IPOTM1;
unsigned char   IPOTM2;

unsigned char   ENTM0Pot0;
unsigned char   ENTM0Pot1;
unsigned char   ENTM0Pot2;

//Mem eeprom contador timer 1
unsigned char   ConTMR1;
unsigned char   ConTEEPROM = 0;

////Matriz para memoria 
//unsigned char   ADD_POT0[5] = {0x04,0x05,0x06,0x07,0x08};
//unsigned char   ADD_POT1[5] = {0x09,0x0A,0x0B,0x0C,0x0D};
//unsigned char   ADD_POT2[5] = {0x0E,0x0F,0x10,0x11,0x12};
//unsigned char   ADD_POT3[5] = {0x13,0x14,0x15,0x16,0x17};
//unsigned char   DC1B1POT3[5] = {0x18,0x19,0x1A,0x1B,0x1C};
//unsigned char   RB0_old = 0;
//unsigned char   RB1_old = 0;
//unsigned char   RB2_old = 0;
//unsigned char   Reading = 0;
//unsigned char   PC_MN = 0;
//unsigned char   MENU = 0;
//unsigned char   Boolean = 0;
//char Instrucciones1 [] = "Instrucciones para controlar la garra";
//char Instrucciones2 [] = "Servo uno: q --> izquierda   w --> derecha";
//char Instrucciones3 [] = "Servo dos: a --> izquierda   s --> derecha";
//char Instrucciones4 [] = "Servo tres: z --> izquierda   x --> derecha";
//char despedida [] = {"UTILIZACION DE GARRA MANUAL"};
//
//
////---------------------------------FUNCIONES-----------------------------------
//
//void FUNCWRITEEEPROM(unsigned char data, unsigned char address){
//    EEADR = address;
//    EEDAT = data;
//    
//    EECON1bits.EEPGD = 0;           //SE ESCRIBE EN MEMORIA DE DATOS 
//    EECON1bits.WREN = 1;            //sE HABILITA LA EEPROM
//    INTCONbits.GIE = 0;             
//    
//    while(PIR2bits.EEIF==0);        //SE DESHABILITAN INTERRUPCIONES
//    PIR2bits.EEIF = 0;
//    
//    EECON2 = 0x55;                  
//    EECON2 = 0xAA;
//    EECON1bits.WR = 1;              //FUNCIÓN DE ESCRIBIR
//    
//    INTCONbits.GIE = 1;             //SE HABILITAN INTERRUPCIONES 
//    EECON1bits.WREN = 0;            //SE DESHABILITA LA EEPROM
//    return;
//}
//
//unsigned char   readFromEEPROM(unsigned char   address){
//    EEADR = address;        // direccion a leer
//    EECON1bits.EEPGD = 0;   // memoria de datos
//    EECON1bits.RD = 1;      // hace una lectura
//    unsigned char  data = EEDAT;   // guardar el dato leído de EEPROM
//    //__delay_ms(20);
//    return data;
//}

unsigned char NumIteraciones (unsigned char ValorPot)
{
    if (ValorPot <19)
    {
        return 2;
    }
    else if (ValorPot < 40 && ValorPot > 18)
    {
        return 3;
    }
    else if (ValorPot < 61 && ValorPot > 39)
    {
        return 5;
    }
    else if (ValorPot < 82 && ValorPot > 60)
    {
        return 6;
    }
    else if (ValorPot < 103 && ValorPot > 81)
    {
        return 7;
    }
    else if (ValorPot < 131 && ValorPot > 102)
    {
        return 8;
    }
    else if (ValorPot < 152 && ValorPot > 130)
    {
        return 9;
    }
    else if (ValorPot < 173 && ValorPot > 151)
    {
        return 10;
    }
    else if (ValorPot < 194 && ValorPot > 172)
    {
        return 11;
    }
    else if (ValorPot < 215 && ValorPot > 193)
    {
        return 12;
    }
    else if (ValorPot < 236 && ValorPot > 214)
    {
        return 14;
    }
    else
    {
        return 15;
    }
}

//void readFromEEPROMPOTS(void){
//    ConTEEPROM = 0;
//    Reading = 1;
//    while (ConTEEPROM < 5){
//        switch(ConTEEPROM){
//            case 0:
//                CCPR1L = readFromEEPROM(ADD_POT3[0]);
//                CCP1CONbits.DC1B1 = readFromEEPROM(DC1B1POT3[0]) & 0b00100000;
//                CCP1CONbits.DC1B0 = readFromEEPROM(DC1B1POT3[0]) & 0b00010000;
//                POTM0 = readFromEEPROM(ADD_POT0[0]);
//                POTM1 = readFromEEPROM(ADD_POT1[0]);
//                POTM2 = readFromEEPROM(ADD_POT2[0]);
//                PORTDbits.RD3 = 1;
//                PORTDbits.RD4 = 0;
//                PORTDbits.RD5 = 0;
//                PORTDbits.RD6 = 0;
//                PORTDbits.RD7 = 0;
//                __delay_ms(100);
//                ConTEEPROM = 1;
//               break;
//
//            case 1:
//                CCPR1L = readFromEEPROM(ADD_POT3[1]);
//                CCP1CONbits.DC1B1 = readFromEEPROM(DC1B1POT3[1]) & 0b00100000;
//                CCP1CONbits.DC1B0 = readFromEEPROM(DC1B1POT3[1]) & 0b00010000;
//                POTM0 = readFromEEPROM(ADD_POT0[1]);
//                POTM1 = readFromEEPROM(ADD_POT1[1]);
//                POTM2 = readFromEEPROM(ADD_POT2[1]);
//                PORTDbits.RD4 = 1;
//                __delay_ms(100);
//                ConTEEPROM = 2;
//               break;
//
//            case 2:
//                CCPR1L = readFromEEPROM(ADD_POT3[2]);
//                CCP1CONbits.DC1B1 = readFromEEPROM(DC1B1POT3[2]) & 0b00100000;
//                CCP1CONbits.DC1B0 = readFromEEPROM(DC1B1POT3[2]) & 0b00010000;
//                POTM0 = readFromEEPROM(ADD_POT0[2]);
//                POTM1 = readFromEEPROM(ADD_POT1[2]);
//                POTM2 = readFromEEPROM(ADD_POT2[2]);
//                PORTDbits.RD5 = 1;
//                __delay_ms(100);
//                ConTEEPROM = 3;
//               break;
//            case 3:
//                CCPR1L = readFromEEPROM(ADD_POT3[3]);
//                CCP1CONbits.DC1B1 = readFromEEPROM(DC1B1POT3[3]) & 0b00100000;
//                CCP1CONbits.DC1B0 = readFromEEPROM(DC1B1POT3[3]) & 0b00010000;
//                POTM0 = readFromEEPROM(ADD_POT0[3]);
//                POTM1 = readFromEEPROM(ADD_POT1[3]);
//                POTM2 = readFromEEPROM(ADD_POT2[3]);
//                PORTDbits.RD6 = 1;
//                __delay_ms(100);
//                ConTEEPROM = 4;
//               break;
//
//            case 4:
//                CCPR1L = readFromEEPROM(ADD_POT3[4]);
//                CCP1CONbits.DC1B1 = readFromEEPROM(DC1B1POT3[4]) & 0b00100000;
//                CCP1CONbits.DC1B0 = readFromEEPROM(DC1B1POT3[4]) & 0b00010000;
//                POTM0 = readFromEEPROM(ADD_POT0[4]);
//                POTM1 = readFromEEPROM(ADD_POT1[4]);
//                POTM2 = readFromEEPROM(ADD_POT2[4]);
//                PORTDbits.RD7 = 1;
//                __delay_ms(100);
//                ConTEEPROM = 5;
//               break;
//        }
//    }
//    Reading = 0;
//    ConTEEPROM = 0;
//    return;
//}

//void Envio_caracter (char a){
//    while (TXSTAbits.TRMT == 0){
//       
//    }
//    if (PIR1bits.TXIF){
//            TXREG = a;
//        }  
//    return;
//}
//
//void Envio_Cadena (char* cadena){
//    while (*cadena != 0){
//      Envio_caracter(*cadena);
//      cadena++;
//    }
//    if (PIR1bits.TXIF){
//            TXREG = 13;
//        } 
//    return;
//}

//**************************
//                              INTERRUPCIÓN
//**************************
void __interrupt() isr(void){    
    
    //Interrupción ADC
    if (ADIF == 1) {
        switch (ADCON0bits.CHS){
            case 0:
                POTM0 = NumIteraciones(ADRESH);          //Se guarda el valor del POTM1
                ADCON0bits.CHS = 1;     //cambio para el multiplexeo
                break;
        
            case 1:
                POTM1 = NumIteraciones(ADRESH);         //Se guarda el valor del POTM1
                ADCON0bits.CHS = 2;     //cambio para el multiplexeo
                break;
        
            case 2:
                POTM2 = NumIteraciones(ADRESH);          //Se guarda el valor del POTM1
                ADCON0bits.CHS = 3;     //cambio para el multiplexeo
                break;
            
           case 3:
                CCPR1L = (ADRESH>>1)+124;//habilita 180°
                CCP1CONbits.DC1B1 = ADRESH & 0b01; //añadir precision/resolucion
                CCP1CONbits.DC1B0 = (ADRESL>>7);
                ADCON0bits.CHS = 0;
                break;
        }
      }
        __delay_us(20);             //delay de 20 us
        PIR1bits.ADIF = 0;          //limpieza de bandera
        ADCON0bits.GO = 1;          //inicio de conversión
    }
    
   if (T0IF == 1){                
        TMR0 = 228;                 //reseteo de timer0
        if (IPOTM0 == POTM0){
            PORTCbits.RC1 = 0;
            IPOTM0 = 0;
            ENTM0Pot0 = 0;
        }
        if (IPOTM1 == POTM1){
            PORTCbits.RC2 = 0;
            IPOTM1 = 0;
            ENTM0Pot1 = 0;
        }
        if (IPOTM2 == POTM2){
            PORTCbits.RC3 = 0;
            IPOTM2 = 0;
            ENTM0Pot2 = 0;
        }
        if (ENTM0Pot0 == 1){
            IPOTM0++;
        }
        if (ENTM0Pot1 == 1){
            IPOTM1++;
        }
        if (ENTM0Pot2 == 1){
            IPOTM2++;
        }
        INTCONbits.T0IF = 0;        //limpieza de bandera
    }
    
    if (TMR1IF == 1){
        TMR1H = 255;
        TMR1L = 6;
        if (ConTMR1 == 1){
           ENTM0Pot0 = 1; 
           ENTM0Pot1 = 1; 
           ENTM0Pot2 = 1; 
        }   
        
        if (ConTMR1 == 20){
            ConTMR1 = 0;
            PORTCbits.RC1 = 1;
            PORTCbits.RC2 = 1;
            PORTCbits.RC3 = 1;
        }
        ConTMR1++;
        PIR1bits.TMR1IF = 0;       //limpieza de TMR1 
    }
}      


void main(void) {
//**************************
//                              CONFIGURACIONES
//**************************
    
    //RELOJ
    OSCCONbits.IRCF = 0b0111;       //Reloj a 8 MHz
    OSCCONbits.SCS   = 1;
    
    
    //INPUTS/OUTPUTS
    ANSELH = 0;                     
    ANSELbits.ANS0  = 1;            //RA: 0,1,2,3 entradas analogas
    ANSELbits.ANS1  = 1;
    ANSELbits.ANS2  = 1;
    ANSELbits.ANS3  = 1;
    TRISA  = 0b11111111;            //PORTA inputs
    TRISC  = 0; 
    TRISD = 0; //PORTD salidas
    TRISE  = 0;                     //PORTD salidas
    TRISB  = 0b111111;              //PORTD salidas
    OPTION_REGbits.nRBPU = 0;
    WPUBbits.WPUB0 = 1;             //habilitar pull-ups
    WPUBbits.WPUB1 = 1;
    WPUBbits.WPUB2 = 1;
    PORTA  = 0;                     //limpieza de puertos
    PORTD  = 0;
    PORTE  = 0;
    PORTC = 0;
    IPOTM0 = 0;
    IPOTM1 = 0;
    IPOTM2 = 0;
    POTM0 = 0;
    POTM1 = 0;
    POTM2 = 0;
    ConTMR1 = 0;
    
    
    //ADC
    ADCON0bits.ADCS  =   2;         //Fosc/32 
    ADCON0bits.CHS0  =   0;         //se selecciona el canal AN0
    ADCON1bits.VCFG1 =   0;         //voltajes referencia default
    ADCON1bits.VCFG0 =   0;           
    ADCON1bits.ADFM  =   0;         //justificación izquierda
    ADCON0bits.ADON  =   1;            
    __delay_us(20);                 //delay de 20 us
    
    
    //PWM
    TRISCbits.TRISC2 = 1;           //CCP1 como entrada;
    PR2 = 250;                      //valor para que el periodo pwm sea 2 ms 
    CCP1CONbits.P1M = 0;       
    CCP1CONbits.CCP1M = 0b1100;
    CCPR1L = 0x0f;                  //ciclo de trabajo inicial
    CCP1CONbits.DC1B = 0;
    
    
    //TMR2
    PIR1bits.TMR2IF = 0;            //limpieza de bandera
    T2CONbits.T2CKPS = 0b11;        //prescaler 1:16
    T2CONbits.TMR2ON = 1;           
    while(PIR1bits.TMR2IF == 0);    //esperar un ciclo de tmr2
    PIR1bits.TMR2IF = 0;
    TRISCbits.TRISC2 = 0;           
    TRISCbits.TRISC1 = 0;   
    
    
    //TMR0
    OPTION_REGbits.T0CS = 0;
    OPTION_REGbits.PSA  = 0;
    OPTION_REGbits.PS2  = 0;
    OPTION_REGbits.PS1  = 0;
    OPTION_REGbits.PS0  = 0;        //prescaler a 2
    TMR0 = 228;                      //reseteo TMR0
    INTCONbits.T0IF = 0;
    
    
    //TMR1
    T1CONbits.TMR1ON = 1;
    T1CONbits.TMR1CS = 0;
    T1CONbits.TMR1CS = 0;
    T1CONbits.T1CKPS1 = 1;
    T1CONbits.T1CKPS0 = 1;          //prescaler a 8
    TMR1H = 255;
    TMR1L = 6;
    PIR1bits.TMR1IF = 0;            //limpieza de la bandera
    
    
    //TX y RX
    TXSTAbits.SYNC = 0;
    TXSTAbits.BRGH = 1;
    
    BAUDCTLbits.BRG16 = 1;
    
    SPBRG = 207;
    SPBRGH = 0;
    
    RCSTAbits.SPEN = 1;
    RCSTAbits.RX9 = 0;
    RCSTAbits.CREN = 1;
    
    TXSTAbits.TXEN = 1;
    

    //INTERRUPCIONES
    PIR1bits.ADIF = 0;
    PIE1bits.ADIE = 1;              //interrupción ADC
    INTCONbits.PEIE = 1;            
    INTCONbits.GIE  = 1; 
    INTCONbits.T0IE  = 1;           //interrupción del TMR0
    PIE1bits.TMR1IE = 1;            //interrupcion del TMR1
    ADCON0bits.GO = 1; 
    
    while (1){
        
        if (PC_MN == 1 && RCIF == 1){
            switch (RCREG){
                case 119:                    //w
                    if (POTM0 < 16){
                        POTM0 = POTM0 + 3;
                    }
                    else{
                        POTM0 = 18;
                    }
                    break;

                case 113:                    //q
                    if (POTM0 > 3){
                        POTM0 = POTM0 - 3;
                    }
                    else{
                        POTM0 = 0;
                    }
                    break;
                    
                case 115:                    //s
                    if (POTM1 < 16){
                        POTM1 = POTM1 + 3;
                    }
                    else{
                        POTM1 = 18;
                    }
                    break;

                case 97:                    //a
                    if (POTM1 > 3){
                        POTM1 = POTM1 - 3;
                    }
                    else{
                        POTM1 = 0;
                    }
                    break;
                    
                case 120:                    //x
                    if (POTM2 < 16){
                        POTM2 = POTM2 + 3;
                    }
                    else{
                        POTM2 = 18;
                    }
                    break;

                case 122:                    //z
                    if (POTM2 > 3){
                        POTM2 = POTM2 - 3;
                    }
                    else{
                        POTM2 = 0;
                    }
                    break;

            }
        }
        
        if (RB0 == 0 && PC_MN == 0)
            RB0_old = 1;
        
        if (RB1 == 0 && PC_MN == 0)
            RB1_old = 1;
        
        if (RB2 == 0)
            RB2_old = 1;
        
        if (RB0 == 1 && RB0_old == 1 && PC_MN == 0 ){
            switch(ConTEEPROM){
                case 0:
                   FUNCWRITEEEPROM(CCPR1L,ADD_POT3[0]);
                   FUNCWRITEEEPROM(CCP1CON,DC1B1POT3[0]);
                   FUNCWRITEEEPROM(POTM0,ADD_POT0[0]); 
                   FUNCWRITEEEPROM(POTM1,ADD_POT1[0]); 
                   FUNCWRITEEEPROM(POTM2,ADD_POT2[0]); 
                   ConTEEPROM = 1;
                   PORTCbits.RC3 = 1;
                   PORTCbits.RC4 = 0;
                   PORTCbits.RC5 = 0;
                   PORTCbits.RC6 = 0;
                   PORTCbits.RC7 = 0;
                   break;
                
                case 1:
                   FUNCWRITEEEPROM(CCPR1L,ADD_POT3[1]);
                   FUNCWRITEEEPROM(CCP1CON,DC1B1POT3[1]);
                   FUNCWRITEEEPROM(POTM0,ADD_POT0[1]); 
                   FUNCWRITEEEPROM(POTM1,ADD_POT1[1]); 
                   FUNCWRITEEEPROM(POTM2,ADD_POT2[1]); 
                   ConTEEPROM = 2;
                   PORTCbits.RC4 = 1;
                   break;
                
                case 2:
                   FUNCWRITEEEPROM(CCPR1L,ADD_POT3[2]);
                   FUNCWRITEEEPROM(CCP1CON,DC1B1POT3[2]);
                   FUNCWRITEEEPROM(POTM0,ADD_POT0[2]); 
                   FUNCWRITEEEPROM(POTM1,ADD_POT1[2]); 
                   FUNCWRITEEEPROM(POTM2,ADD_POT2[2]); 
                   ConTEEPROM = 3;
                   PORTCbits.RC5 = 1;
                   break;
                
                case 3:
                   FUNCWRITEEEPROM(CCPR1L,ADD_POT3[3]);
                   FUNCWRITEEEPROM(CCP1CON,DC1B1POT3[3]);
                   FUNCWRITEEEPROM(POTM0,ADD_POT0[3]); 
                   FUNCWRITEEEPROM(POTM1,ADD_POT1[3]); 
                   FUNCWRITEEEPROM(POTM2,ADD_POT2[3]); 
                   ConTEEPROM = 4;
                   PORTCbits.RC6 = 1;
                   break;
                
                case 4:
                   FUNCWRITEEEPROM(CCPR1L,ADD_POT3[4]);
                   FUNCWRITEEEPROM(CCP1CON,DC1B1POT3[4]);
                   FUNCWRITEEEPROM(POTM0,ADD_POT0[4]); 
                   FUNCWRITEEEPROM(POTM1,ADD_POT1[4]); 
                   FUNCWRITEEEPROM(POTM2,ADD_POT2[4]); 
                   ConTEEPROM = 0;
                   PORTCbits.RC7 = 1;
                   break;  
            }
            RB0_old = 0;
            }
        
        if (RB1 == 1 && RB1_old == 1 && PC_MN == 0){
            readFromEEPROMPOTS();
            RB1_old = 0;
        }
        
        if (RB2 == 1 && RB2_old == 1){
           if (PC_MN == 1){
               PC_MN = 0;
               PORTEbits.RE0 = 0;
               if (PIR1bits.TXIF){
                   TXREG = 13;
                } 
               __delay_ms(5);
               Envio_Cadena(despedida);
           }
           else{
               PC_MN = 1;
               if (PIR1bits.TXIF){
                   TXREG = 13;
                } 
               __delay_ms(5);
               Envio_Cadena(Instrucciones1);
               Envio_Cadena(Instrucciones2);
               Envio_Cadena(Instrucciones3);
               Envio_Cadena(Instrucciones4);
               PORTEbits.RE0 = 1;
           }
           RB2_old = 0;
        }
    }      
}