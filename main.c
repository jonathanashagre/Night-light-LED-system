#define F_CPU 3333333
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include <avr/sleep.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
volatile uint16_t adc_result = 0;
ISR(ADC0_RESRDY_vect){ 
    adc_result = ADC0.RES;
    TCA0.SINGLE.CMP0BUF = (adc_result * TCA0.SINGLE.PER) / 2;
    ADC0.INTFLAGS = ADC_RESRDY_bm; 
}
int main(void) {
    PORTC.DIR |= PIN0_bm;
    PORTD.DIR &= ~PIN1_bm;
   
   
    
    PORTMUX.TCAROUTEA = PORTMUX_TCA0_PORTC_gc;
    
    ADC0.CTRLA |= ADC_ENABLE_bm | ADC_RESSEL_10BIT_gc | ADC_FREERUN_bm;
    ADC0.MUXPOS = ADC_MUXPOS_AIN1_gc;
    TCA0.SINGLE.CMP0 = 1388;
    TCA0.SINGLE.PER = 2776;
    ADC0.CTRLC = ADC_REFSEL_VDDREF_gc | ADC_PRESC_DIV4_gc;
    ADC0.INTCTRL = ADC_RESRDY_bm;
//    TCA0.SINGLE.CTRLA = TCA_SINGLE_CMP0EN_bm | TCA_SINGLE_WGMODE_SINGLESLOPE_gc;
//    TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV1_gc | TCA_SINGLE_ENABLE_bm;
    ADC0.COMMAND = ADC_STCONV_bm;
    PORTD.PIN1CTRL &= ~PORT_PULLUPEN_bm;
    PORTD.PIN1CTRL |= PORT_ISC_INPUT_DISABLE_gc;
//    TCA0.SINGLE.INTCTRL = TCA_SINGLE_OVF_bm | TCA_SINGLE_CMP0_bm;
    
    TCA0.SINGLE.PER = 2776;
    TCA0.SINGLE.CMP0BUF = adc_result * TCA0.SINGLE.PER / 2;
    TCA0.SINGLE.CTRLB = TCA_SINGLE_CMP0EN_bm | TCA_SINGLE_WGMODE_SINGLESLOPE_gc; 
    TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV1_gc | TCA_SINGLE_ENABLE_bm;
    sei();
    while(1){
        
    }
