/*
 * Traffic Light System.c
 *
 * Created: 11/9/2024 12:25:25 PM
 * Author : 20155
 */ 

#define F_CPU 16000000UL  // Set CPU frequency to 16 MHz
#include <avr/io.h>
#include <util/delay.h>

#define VEHICLE_GREEN PORTB0
#define VEHICLE_YELLOW PORTB1
#define VEHICLE_RED PORTB2

#define	PED_GREEN PORTB3
#define PED_RED PORTB4

#define PED_BUTTON PORTD0
#define EMERGENCY_BUTTON PORTD1

void initialize_ports();
void normal_mode();
void pedestrian_mode();
void emergency_mode();


void initialize_ports()
	{
		DDRB |= (1 << VEHICLE_GREEN) | (1 << VEHICLE_YELLOW) | (1 << VEHICLE_RED) | (1 << PED_GREEN) | (1 << PED_RED) ;
		
		DDRD &= ~((1 << PED_BUTTON) | (1 << EMERGENCY_BUTTON));
		PORTD |= (1 << PED_BUTTON) | (1 << EMERGENCY_BUTTON); // Enable internal pull-ups	}
}
	void normal_mode() {
		// Car green, pedestrian red
				PORTB &= ~(1 << VEHICLE_RED);

		    PORTB |= (1 << VEHICLE_GREEN) | (1 << PED_RED);
		_delay_ms(500);

		// Car yellow
		PORTB &= ~(1 << VEHICLE_GREEN);
		PORTB |= (1 << VEHICLE_YELLOW);
		_delay_ms(200);

		// Car red, pedestrian green
		   PORTB &= ~(1 << VEHICLE_YELLOW | 1 << PED_RED);
		   PORTB |= (1 << VEHICLE_RED) | (1 << PED_GREEN);
		_delay_ms(500);

		// Pedestrian red
		PORTB &= ~(1 << PED_GREEN);
		PORTB |= (1 << PED_RED);
	}

	void pedestrian_mode()
	{
		 // Ensure cars are stopped
		 PORTB &= ~((1 << VEHICLE_GREEN) | (1 << VEHICLE_YELLOW));
		 PORTB |= (1 << VEHICLE_RED);

		 // Allow pedestrians to cross
		 PORTB &= ~(1 << PED_RED);
		 PORTB |= (1 << PED_GREEN);
		 _delay_ms(500);

		 // Reset lights
		 PORTB &= ~(1 << PED_GREEN);
		 PORTB |= (1 << PED_RED);
	 }
	void emergency_mode() {
							 PORTB &= ~((1 << VEHICLE_GREEN) | (1 << VEHICLE_YELLOW) | (1 << VEHICLE_RED) | (1 << PED_RED) | (1 << PED_GREEN));

		for (int i = 0; i < 10; i++) {

			PORTB ^= (1 << VEHICLE_RED) | (1 << VEHICLE_YELLOW) | (1 << VEHICLE_GREEN) |
			(1 << PED_RED) | (1 << PED_GREEN);
			_delay_ms(300);
		}
	}


int main(void)
{
    /* Replace with your application code */
	initialize_ports();
	
    while (1) 
    {
		if (!(PIND & (1 << EMERGENCY_BUTTON)))
		{
			emergency_mode();
		}
		
		else if (!(PIND & ( 1<< PED_BUTTON)))
		{
			pedestrian_mode();
		}
		
		else {
			normal_mode();
		}
		
    }
}

