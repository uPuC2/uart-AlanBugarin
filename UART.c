#include <avr/io.h>

// Prototypes
// Initialization
UART_Ini(uint8_t com, uint32_t baudrate, uint8_t size, uint8_t parity, uint8_t stop);

// Send
void UART_puts(uint8_t com, char *str);
void UART_putchar(uint8_t com, char data);

// Received
uint8_t UART_available(uint8_t com);
char UART_getchar(uint8_t com );
void UART_gets(uint8_t com, char *str);

// Escape sequences
UART_clrscr( uint8_t com );
UART_setColor(uint8_t com, uint8_t color);
UART_gotoxy(uint8_t com, uint8_t x, uint8_t y);

// Utils
void itoa(uint16_t number, char* str, uint8_t base);
uint16_t atoi(char *str);

void UART_puts(uint8_t com, char *str){

	for(uint8_t i=0;i<sizeof(str);i++){
		UART_putchar(com,str[i]);
	}
}

void UART_putchar(uint8_t com,char data){

	switch(com){
		case 0:{
			while(!(UCSR0A & (1<<UDRE0))); //Cuando este vacio se rompe
			UDR0 =data; //pasamos el dato a UDR0
			break;
        }
		case 1:{
			while(!(UCSR1A & (1<<UDRE1))); //Cuando este vacio se rompe
			UDR1 =data; //pasamos el dato a UDR1
			break;
        }
		case 2:{
			while(!(UCSR2A & (1<<UDRE2))); //Cuando este vacio se rompe
			UDR2 =data; //pasamos el dato a UDR2
			break;
        }
		case 3:{
			(!(UCSR3A & (1<<UDRE3))); //Cuando este vacio se rompe
			UDR3 =data; //pasamos el dato a UDR3
			break;
        }
	}
}


uint8_t UART_available(uint8_t com){

}

char UART_getchar(uint8_t com){

}

void UART_gets(uint8_t com, char *str){

}

UART_clrscr(uint8_t com){

}

UART_setColor(uint8_t com, uint8_t color){

}

UART_gotoxy(uint8_t com, uint8_t x, uint8_t y){

}

void itoa(uint16_t number, char* str, uint8_t base){

}
uint16_t atoi(char *str){

}
