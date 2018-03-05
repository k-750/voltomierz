#define F_CPU 1000000L
#include <avr/io.h>
#include <util/delay.h>

void teststartowy()
{
	int petla=0;
	while (petla<5)
	{
	PORTD |= (1<<petla);
	_delay_ms(200);
	PORTD &=~ (1<<petla);
	_delay_ms(200);
	petla++;
	}
}

void test2()
{
	int n=0;
	while (n<5)
	{
	PORTD |= (1<<n);
	n++;
	}
	_delay_ms(1000);
	n=0;
	while (n<5)
	{
	PORTD &=~ (1<<n);
	n++;
	}
}

int przycisk()
{
	int nrprzycisku=0;
	if (!(PINB&(1<<1))) nrprzycisku=1;
	return nrprzycisku;
}

void kontrolka(int nrprzycisku)
{
	if (nrprzycisku==1) PORTD |= (1<<0); else PORTD &=~ (1<<0);
}

void voltomierz()
{
	ADCSRA |= (1<<ADSC);	//URUCHOMIENIE POJEDYNCZEJ KONWERSJI
	while(ADCSRA & (1<<ADSC));	// czeka na zakończenie konwersji	
	if (ADC<500) PORTD &=~ (1<<0);
	if (ADC>499) PORTD |= (1<<0); else PORTD &=~ (1<<0);
	if (ADC>600) PORTD |= (1<<1); else PORTD &=~ (1<<1);
	if (ADC>700) PORTD |= (1<<2); else PORTD &=~ (1<<2);
	if (ADC>800) PORTD |= (1<<3); else PORTD &=~ (1<<3);
	if (ADC>900) PORTD |= (1<<4); else PORTD &=~ (1<<4);
	if (ADC>100) PORTD |= (1<<5); else PORTD &=~ (1<<5);
}

int main ()
{
int n=0;
while (n<5)
{
	DDRD |= (1<<n);		// port wyjściowy
	n++;
}
n=0;
DDRB &=~ (1<<1);	// port wejściowy przycisk
PORTB |= (1<<1);	// podciągnięcie do napięcia

DDRC =1;		// nieużywane porty C jako wyjścia 
DDRC &=~ (1<<5);		// wejscie analogowe
PORTC &=~ (1<<5);		// wejscie bez podciągnięcia do vcc

	ADCSRA = (1<<ADEN);	//uruchomienie przetwornika
	ADCSRA |= (1<<ADPS0);	//ustawienie preskalera na 128
	ADCSRA |= (1<<ADPS1);
	ADCSRA |= (1<<ADPS2);

	ADMUX = (1<<ADEN)	//REFS1:0: Reference Selection Bits   
         //Internal 2.56V Voltage Reference with external capacitor at AREF pin
		| (1<<MUX2) | (1<<MUX0);	//Input Channel Selections (ADC5 - Pin 5 )  

int nrprzycisku=0;
test2();
teststartowy();
while (1)
{
	//nrprzycisku=przycisk();
	//kontrolka(nrprzycisku);
	voltomierz();
	
}


return 0;
}
