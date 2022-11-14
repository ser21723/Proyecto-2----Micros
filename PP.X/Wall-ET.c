//******************************************************************************
//   UNIVERSIDAD DEL VALLE DE GUATEMALA
//   IE2023 PROGRAAMACIÓN DE MICROCONTROLADORES 
//   AUTOR: MICHELLE SERRANO
//   COMPILADOR: XC8 (v1.41), MPLAB X IDE (v6.00)
//   PROYECTO: PROYECTO 2 - WALL-E
//   HARDWARE: PIC16F887
//   CREADO: 09/11/2022
//   ÚLTIMA MODIFCACIÓN: 09/11/2022

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT
#pragma config WDTE = OFF       
#pragma config PWRTE = ON      
#pragma config MCLRE = OFF      
#pragma config CP = OFF        
#pragma config CPD = OFF        
#pragma config BOREN = OFF      
#pragma config IESO = OFF       
#pragma config FCMEN = OFF     
#pragma config LVP = OFF       

// CONFIG2
#pragma config BOR4V = BOR40V   
#pragma config WRT = OFF    

#include <xc.h>

#define _XTAL_FREQ 8000000 //8MHz 

void setup(void);
void setupINTOSC(void);
void setupADC(void);
void setupPWM(void);
void timer2(void);
void timer0(void);
void timer1(void);
void main(void);


//******************************************************************************
// Variables
//******************************************************************************

//POTENCIOMETROS 
unsigned char valor;
unsigned char pot3;

//******************************************************************************
// CÃ³digo Principal
//******************************************************************************
void main(void) {
    setup();
    setupINTOSC();
    setupADC();
    setupPWM();
    timer2();
    timer1();
    timer0();
    
        while(1){
           if (ADIF == 1) {                        //Interrupción ADC
              
            switch (ADCON0bits.CHS){
             
                case 0:
                
                CCPR1L = (ADRESH>>1)+124;       //180°
                CCP1CONbits.DC1B1 = ADRESH & 0b01; // presición 
                CCP1CONbits.DC1B0 = (ADRESL>>7);
                ADCON0bits.CHS = 1;     
                break;
                
                case 1:
                    
                CCPR2L = (ADRESH>>1)+124; //180°
                CCP2CONbits.DC2B1 = ADRESH & 0b01;//precision
                CCP2CONbits.DC2B0 = (ADRESL>>7);
                ADCON0bits.CHS = 2;       
                break;
                
                case 2:
                    
                pot3 = ADRESH;
                ADCON0bits.CHS = 0;
                break;
            }

            __delay_us(20);             //delay de 20 us
            PIR1bits.ADIF = 0;          
            ADCON0bits.GO = 1;          //inicio de conversión
            
            }

            if (T0IF == 1){                
                if (pot3 == TMR0){
                PORTCbits.RC3 = 1;
                __delay_ms(2);
                PORTCbits.RC3 = 1;
                TMR0 = 70; //0 grados
                INTCONbits.T0IF = 0;
                }
            }
                else {
                   PORTCbits.RC3 = 1;
                   __delay_ms(1);
                   PORTCbits.RC3 = 0;
                   TMR0 = 131;  //180 grados
                   INTCONbits.T0IF = 0;
                } 
                
        }
}   


//******************************************************************************
// FunciÃ³n para configurar puerto
//******************************************************************************
void setup(void){
    ANSELH = 0;
    TRISA = 0b00000111;  //RA0, RA1, RA2 como entradas
    PORTA = 0;          // limpiamos el puerto
    TRISC = 0;          // Puerto C como salida  
    PORTC = 0;          // limpiamos
    TRISE = 0;
    PORTE = 0;        
}
//******************************************************************************
// FunciÃ³n para configurar PWM
//******************************************************************************
void setupINTOSC(void){
    OSCCONbits.IRCF = 0b0111;       // 8 MHz
    OSCCONbits.SCS = 1;
}
//******************************************************************************
// FunciÃ³n para configurar ADC
//******************************************************************************
void setupADC(void){
    
    //TRISAbits.TRISA0 = 1;
    TRISA = TRISA | 0x01;
    ANSEL = ANSEL | 0x01;
    
    ADCON0bits.ADCS1 = 0;
    ADCON0bits.ADCS0 = 1;       // Fosc/ 8
    
    ADCON1bits.VCFG1 = 0;       // Ref VSS
    ADCON1bits.VCFG0 = 0;       // Ref VDD
    
    ADCON1bits.ADFM = 0;        // Justificado hacia izquierda
    
    ADCON0bits.CHS3 = 0;
    ADCON0bits.CHS2 = 0;
    ADCON0bits.CHS1 = 0;
    ADCON0bits.CHS0 = 0;        // Canal AN0
    
    ADCON0bits.ADON = 1;        // Habilitamos el ADC
    __delay_us(100);
    
    //interrupciones
    PIR1bits.ADIF = 0;
    PIE1bits.ADIE = 1;              //interrupción del  ADC
    INTCONbits.PEIE = 1;            
    INTCONbits.GIE  = 1;            
    ADCON0bits.GO = 1; 
    
}
//******************************************************************************
// FunciÃ³n para configurar PWM
//******************************************************************************
void setupPWM(void){
    
    TRISCbits.TRISC2 = 1;           //CCP1
    PR2 = 250;                      
    CCP1CONbits.P1M = 0;       
    CCP1CONbits.CCP1M = 0b1100;
    CCPR1L = 0x0f;                  //ciclo de trabajo inicial
    CCP1CONbits.DC1B = 0;
    TRISCbits.TRISC1 = 1;           //CCP2 
    CCP2CONbits.CCP2M = 0b1100;
    CCPR2L = 0x0f;                  //ciclo de trabajo inicial
    CCP2CONbits.DC2B1 = 0;
 
    }

//TMR2
// void timer2 (void) {
//     
//    PIR1bits.TMR2IF = 0;            //limpieza de bandera
//    T2CONbits.T2CKPS = 0b11;        //prescaler 1:16
//    T2CONbits.TMR2ON = 1;           
//    while(PIR1bits.TMR2IF == 0);    //esperar un ciclo de tmr2
//    PIR1bits.TMR2IF = 0;
//    TRISCbits.TRISC2 = 0;           
//    TRISCbits.TRISC1 = 0;   
   
// }
    
    //TMR0
 void timer0 (void) {
     
    OPTION_REGbits.T0CS = 0;    //Uso reloj interno
    OPTION_REGbits.PSA = 0;     //Uso pre-escaler
    OPTION_REGbits.PS = 0b111;  //PS = 111 / 1:256                
    TMR0 = 78;      //reseteo de timer0
//    OPTION_REGbits.T0CS = 0;
//    OPTION_REGbits.PSA  = 0;
//    OPTION_REGbits.PS2  = 0;
//    OPTION_REGbits.PS1  = 0;
//    OPTION_REGbits.PS0  = 0;        //prescaler a 2
//    TMR0 = 228;                      //reseteo TMR0
//    INTCONbits.T0IF = 0;  
 }   
    //TMR1
void timer1 (void) {

    T1CONbits.TMR1ON = 1;
    T1CONbits.TMR1CS = 0;
    T1CONbits.TMR1CS = 0;
    T1CONbits.T1CKPS1 = 1;
    T1CONbits.T1CKPS0 = 1;          //prescaler a 8
    TMR1H = 255;
    TMR1L = 6;
    PIR1bits.TMR1IF = 0;            //limpieza de la bandera
}
 void timer2 (void) {
    PIR1bits.TMR2IF = 0;            //limpieza de bandera
    T2CONbits.T2CKPS = 0b11;        //prescaler 1:16
    T2CONbits.TMR2ON = 1;   
    
    while(PIR1bits.TMR2IF == 0);    //esperar un ciclo de tmr2
    PIR1bits.TMR2IF = 0;
    TRISCbits.TRISC2 = 0;           
    TRISCbits.TRISC1 = 0;   
    
 }
// 
// void timer0 (void) {
//    INTCONbits.TMR0IE = 1;  
//    INTCONbits.TMR0IF = 0;            //limpieza de bandera
//    OPTION_REGbits.T0CS = 0;        
//    OPTION_REGbits.PSA = 0;   
//    OPTION_REGbits.PS = 0b011;        //prescaler 1:16
//    TMR0 = 255;
//
// }
