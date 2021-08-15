/*
 * Timer10msExactos.c
 *
 * Created: 15/8/2021 15:29:07
 * Author : Lauta
 */ 

#include <avr/io.h>
#define F_CPU	16000000L
#include <util/delay.h>
#include <avr/interrupt.h>

//. Prototipos
void initPort();
void initTimers();
//

//. Variables globales
volatile uint16_t timeOut1ms;
//

//. Interrupciones
ISR(TIMER1_COMPA_vect){
	timeOut1ms--;
	if (!timeOut1ms){
		timeOut1ms = 1000;
		//(1 << PORTB5 1) desplazado por B5 es igual a 00100000
		if(PORTB & (1 << PORTB5)) //desplazo al numero 1 cinco veces para que aparezca en la posicion 5
			PORTB &= ~(1 << PORTB5); //~ (1 << PORTB5) = 11011111 hago cero el bit 5 de PORTB5
		else
			PORTB |= (1 << PORTB5);
	}
	
}
//


//. Funciones
void initPort(){
	//Configuro Pin del LED como salida (PB5 Arduino uno)
	DDRB = (1 << DDB5);
	
	PORTB |= (1 << PORTB5);
}

void initTimers(){
	OCR1A = 0x7D0; 
	TCCR1A = 0x00;
	TCCR1B = 0x00; //reseteo registros
	TCNT1 = 0x00; //inicializo timer
	TIFR1 = TIFR1;
	TIMSK1 = (1 << OCIE1A); //activo flag interrupt cuando TCNT1 = OCR1A
	TCCR1B = (1 << WGM12) | (1 << CS11); //configuro prescaler 8 y modo CTC
	}

//

int main(void)
{
    /* Replace with your application code */
	timeOut1ms = 1000;
	initPort();
	initTimers();
	sei(); // pongo en 1 el bit 7 del Status
	
	
    while (1) 
    {
    }
}

