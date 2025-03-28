#include <avr/io.h>

// Prototypes
// Initialization
void UART_Ini(uint8_t com,uint32_t baudrate,uint8_t size,uint8_t parity,uint8_t stop);

// Send
void UART_puts(uint8_t com,char *str);
void UART_putchar(uint8_t com,char data);

// Received
uint8_t UART_available(uint8_t com);
char UART_getchar(uint8_t com );
void UART_gets(uint8_t com,char *str);

// Escape sequences
void UART_clrscr( uint8_t com );
void UART_setColor(uint8_t com,uint8_t color);
void UART_gotoxy(uint8_t com,uint8_t x,uint8_t y);

// Utils
void itoa(uint16_t number,char* str,uint8_t base);
uint16_t atoi(char *str);

void UART_Ini(uint8_t com,uint32_t baudrate,uint8_t size,uint8_t parity,uint8_t stop){
	
	uint16_t ubrr= 16000000/16/baudrate-1;

	switch(com){
		case 0:
				   // Configura baudrate
		    UBRR0H = (unsigned char)(ubrr >> 8);
		    UBRR0L = (unsigned char)ubrr;

			    // Activa la doble transimicion
		    UCSR1A = (1 << U2X0);
		
		    // Habilita transmisor y receptor
		    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
		
            // Configuracion para UCSR0C
            uint8_t config = 0;

            // Configuracion del tamano de size
            if (size == 5) {
                config |= 0; // 5 bits, no se configuran bits
            } else if (size == 6) {
                config |= (1 << UCSZ00); // 6 bits
            } else if (size == 7) {
                config |= (1 << UCSZ01); // 7 bits
            } else if (size == 8) {
                config |= (1 << UCSZ01) | (1 << UCSZ00); // 8 bits
            }

            // Configuracion de paridad
            if (parity == 1) {
                config |= (1 << UPM01); // Paridad par
            } else if (parity == 2) {
                config |= (1 << UPM01) | (1 << UPM00); // Paridad impar
            }

            // Configuracion de bits de parada
            if (stop == 2) {
                config |= (1 << USBS0); // 2 bits de parada
            }

            // Asignar el valor configurado a UCSR0C
            UCSR0C = config;   

			break;
		case 1:
				   // Configura baudrate
		    UBRR1H = (unsigned char)(ubrr >> 8);
		    UBRR1L = (unsigned char)ubrr;
		
		    // Activa la doble transmision
		    UCSR1A = (1 << U2X1);
		
		    // Habilita transmisor y receptor
		    UCSR1B = (1 << RXEN1) | (1 << TXEN1);
			
            // Configuracion para UCSR0C
            config = 0;

            // Configuracion del tamaño de size
            if (size == 5) {
                config |= 0; // 5 bits, no se configuran bits
            } else if (size == 6) {
                config |= (1 << UCSZ10); // 6 bits
            } else if (size == 7) {
                config |= (1 << UCSZ11); // 7 bits
            } else if (size == 8) {
                config |= (1 << UCSZ11) | (1 << UCSZ10); // 8 bits
            }

            // Configuracion de paridad
            if (parity == 1) {
                config |= (1 << UPM11); // Paridad par
            } else if (parity == 2) {
                config |= (1 << UPM11) | (1 << UPM10); // Paridad impar
            }

            // Configuracion de bits de parada
            if (stop == 2) {
                config |= (1 << USBS1); // 2 bits de parada
            }

            // Asignar el valor configurado a UCSR1C
            UCSR1C = config;
			break;
		case 2:
					   // Configura baudrate
		    UBRR2H = (unsigned char)(ubrr >> 8);
		    UBRR2L = (unsigned char)ubrr;
		
		    // Activa la doble transmision
		    UCSR2A = (1 << U2X2);
		
		    // Habilita transmisor y receptor
		    UCSR2B = (1 << RXEN2) | (1 << TXEN2);
		
		
            // Configuracion para UCSR0C
            config = 0;

            // Configuracion del size
            if (size == 5) {
                config |= 0; // 5 bits, no se configuran bits
            } else if (size == 6) {
                config |= (1 << UCSZ20); // 6 bits
            } else if (size == 7) {
                config |= (1 << UCSZ21); // 7 bits
            } else if (size == 8) {
                config |= (1 << UCSZ21) | (1 << UCSZ20); // 8 bits
            }

            // Configuracion de paridad
            if (parity == 1) {
                config |= (1 << UPM21); // Paridad par
            } else if (parity == 2) {
                config |= (1 << UPM21) | (1 << UPM20); // Paridad impar
            }

            // Configuracion de bits de parada
            if (stop == 2) {
                config |= (1 << USBS2); // 2 bits de parada
            }

            // Asignar el valor configurado a UCSR2C
            UCSR2C = config;
			break;
		case 3:
				   // Configura baudrate
		    UBRR3H = (unsigned char)(ubrr >> 8);
		    UBRR3L = (unsigned char)ubrr;
		
		    // Activa la doble transmision
		    UCSR3A = (1 << U2X3);
		
		    // Habilita transmisor y eceptor
		    UCSR3B = (1 << RXEN3) | (1 << TXEN3);
		
	                  // Configuracion para UCSR0C
            config = 0;

            // Configuracion del tamaño de datos
            if (size == 5) {
                config |= 0; // 5 bits, no se configuran bits
            } else if (size == 6) {
                config |= (1 << UCSZ30); // 6 bits
            } else if (size == 7) {
                config |= (1 << UCSZ31); // 7 bits
            } else if (size == 8) {
                config |= (1 << UCSZ31) | (1 << UCSZ30); // 8 bits
            }

            // Configuracion de paridad
            if (parity == 1) {
                config |= (1 << UPM31); // Paridad par
            } else if (parity == 2) {
                config |= (1 << UPM31) | (1 << UPM30); // Paridad impar
            }

            // Configuracion de bits de parada
            if (stop == 2) {
                config |= (1 << USBS3); // 2 bits de parada
            }

            // Asignar el valor configurado a UCSR3C
            UCSR3C = config;
			break;
	}
}


void UART_puts(uint8_t com, char *str){
	while(*str){
		UART_putchar(com,*str++);
	}
}

void UART_putchar(uint8_t com,char data){
	switch(com){
		case 0:
			while(!(UCSR0A & (1<<UDRE0))); //Cuando este vacio se rompe
			UDR0 =data; //pasamos el dato a UDR0
			break;
		case 1:
			while(!(UCSR1A & (1<<UDRE1))); //Cuando este vacio se rompe
			UDR1 =data; //pasamos el dato a UDR1
			break;
		case 2:
			while(!(UCSR2A & (1<<UDRE2))); //Cuando este vacio se rompe
			UDR2 =data; //pasamos el dato a UDR2
			break;
		case 3:
			(!(UCSR3A & (1<<UDRE3))); //Cuando este vacio se rompe
			UDR3 =data; //pasamos el dato a UDR3
			break;
	}
}

uint8_t UART_available(uint8_t com){
	uint8_t estado=0;
	switch(com){ //en espera de bit disponible
		case 0:{
			while(!(UCSR0A & (1<<RXC0)));
			estado=1;
			break;
		}
		case 1:{
			while(!(UCSR1A & (1<<RXC1)));
			estado=1;
			break;
		}
		case 2:{
			while(!(UCSR2A & (1<<RXC2)));
			estado=1;
			break;
		}
		case 3:{
			while(!(UCSR3A & (1<<RXC3)));
			estado=1;
			break;
		}
	}
	return estado;
}

char UART_getchar(uint8_t com){
	char data;
	while(!UART_available(com));
		switch(com){
			case 0:{
				data=UDR0;
				break;
			}
			case 1:{
				data=UDR1;
				break;
			}
			case 2:{
				data=UDR2;
				break;
			}
			case 3:{
				data=UDR3;
				break;
			}
		}
		return data;
}

void UART_gets(uint8_t com,char *str){
	char caracter;
	uint8_t idx=0;
	while(1){
		caracter=UART_getchar(com); //obtenemos el carac
		if(caracter==13){ //si es un enter se rompe
			break;
		}else{
			str[idx]=caracter; //coloca el caracter en la posicion actual
			idx++;	//avanza el indice
		}
	}

}

void UART_clrscr(uint8_t com){
	UART_puts(com,"\x1b[2J");
}

void UART_setColor(uint8_t com,uint8_t color){
	char comandoColor[16];
	itoa(color,comandoColor,10);
	
	UART_puts(com,"\033["); //poner el color en  uart
	UART_puts(com,comandoColor);
	UART_puts(com,"m");

}

void UART_gotoxy(uint8_t com,uint8_t x,uint8_t y){
	char buffer[10];
	// Formar la secuencia de escape ANSI
    UART_puts(com,"\x1b[");  // Secuencia de escape inicial
    // Convertir la coordenada Y (fila) a cadena
    itoa(y,buffer, 10);
    UART_puts(com,buffer);           // Enviar el valor de Y
    UART_puts(com,";");  // Separador entre coordenadas
    // Convertir la coordenada X (columna) a cadena
    itoa(x,buffer, 10);
    UART_puts(com,buffer);           // Enviar el valor de X
	UART_puts(com,"H");  // Final de la secuencia

}

void itoa(uint16_t number,char* str,uint8_t base){
int i = 0;
	int copia=i; //paa inverti la cadena
	    //en caso de que el numero sea cero, solo se agrega el carc nulo y se agrega el carac de cero
    if (number == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }
	  do {
	    int residuo = number % base;  //Obtenemos el residuo
	    if (residuo <= 9) {
		    str[i++] = residuo + '0'; // Si el residuo es menor o igual a 9, es un digito
	    } else {
		    str[i++] = residuo - 10 + 'A'; // Si el residuo es mayor que 9, es una letra
	    }
	    number = number/ base;     //Obtenemos el entero
	  } while (number != 0);
	  
	    // Colocamos el  caracter nulo
  		str[i] = '\0';
		//invertimos la cadena resuttante
		int end = i - 1;
	    while (copia < end) {
	        char temp = str[copia];
	        str[copia] = str[end];
	        str[end] = temp;
	        copia++;
	        end--;
	    }
}

uint16_t atoi(char *str){
	uint16_t dato=0;
   
    while (*str >= '0' && *str <= '9') { //Mientras sea un digito
        dato = dato * 10 + (*str - '0'); //lo convertimos a numeo
        str++;   //avanzamos al siguiente caracter
    }
	return dato;
}

