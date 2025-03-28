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

typedef struct{
	union{
		uint8_t UCSRA;
		struct{
			uint8_t mpcm:1;
			uint8_t u2x:1;
			uint8_t upe:1;
			uint8_t dor:1;
			uint8_t fe:1;
			uint8_t udre:1;
			uint8_t txc:1;
			uint8_t rxc:1;
		};
	};
	union{
		uint8_t UCSRB;
		struct{
			uint8_t txb8:1;
			uint8_t rxb8:1;
			uint8_t ucsz2:1;
			uint8_t txen:1;
			uint8_t rxen:1;
			uint8_t udrie:1;
			uint8_t txcie:1;
			uint8_t rxcie:1;			
		};
	};
	union{
		uint8_t UCSRC;
		struct{
			uint8_t ucpol:1;
			uint8_t ucsz0:1;
			uint8_t ucsz1:1;
			uint8_t usbs:1;
			uint8_t upm0:1;
			uint8_t upm1:1;
			uint8_t umsel0:1;
			uint8_t umsel1:1;			
		};
	};
	union{
		uint8_t res;
	};
	union{
		uint16_t UBRR;
		struct{
			uint8_t ubrrl:8;
			uint8_t ubrrh:8;
		};
	};
	
}UART_Regs_t;


UART_Regs_t *uart_offsets[]={
	&UCSR0A,
	&UCSR1A,
	&UCSR2A,
	&UCSR3A	
};

void UART_Ini(uint8_t com,uint32_t baudrate,uint8_t size,uint8_t parity,uint8_t stop)
{
	UART_Regs_t *myUart = uart_offsets[com];
	
	//Calculo para sacar baudaje normal
	uint16_t velNormal=16000000/16/baudrate-1;
	uint16_t baudNormal=16000000/16/(velNormal+1);

	//calculo para sacar baudaje Doble velocidad
	uint16_t velDoble=16000000/8/baudrate-1;
	uint16_t baudDoble=16000000/8/(velDoble+1);

	//Sacamos el error
	uint16_t errorNormal = ((baudNormal - baudrate) * 100) / baudrate;
    uint16_t errorDoble = ((baudDoble - baudrate) * 100) / baudrate;
		

	
	//Registro A	
	if(errorDoble<errorNormal){
		myUart->u2x=1;
		myUart->ubrrh=(unsigned char)(velDoble>>8);
		myUart->ubrrl=(unsigned char)velDoble;
	}else{
		myUart->ubrrh=(unsigned char)(velNormal>>8);
		myUart->ubrrl=(unsigned char)velNormal;	
	}

	//Registro B
	myUart->txen=1;
	myUart->rxen=1;

	//Registro C
	if(size==6){ //para el tamano de los bits
		myUart->ucsz0=1;	
	}else if(size==7){
		myUart->ucsz1=1;
	}else if(size==8){
		myUart->ucsz0=1;
		myUart->ucsz1=1;
	}
	if(parity==1){ //configuracion de paridad
		myUart->upm1=1;
	}else if(parity==2){
		myUart->upm1=1;
		myUart->upm0=1;
	}
	if(stop==2){
		myUart->usbs=1;
	}
	
}


void UART_puts(uint8_t com, char *str){
	while(*str){
		UART_putchar(com,*str);
		str++;
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
			while(!(UCSR3A & (1<<UDRE3))); //Cuando este vacio se rompe
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
	    while(!UART_available(com));
		switch(com){
			case 0:{
				return UDR0;
				break;
			}
			case 1:{
				return UDR1;
				break;
			}
			case 2:{
				return UDR2;
				break;
			}
			case 3:{
				return UDR3;
				break;
			}
		}
}

void UART_gets(uint8_t com,char *str){
	char caracter=0;
	uint16_t idx=0;
	while(1){
		caracter=UART_getchar(com); //obtenemos el carac

		if(caracter>='0' && caracter<='9'){
			str[idx]=caracter;
			idx++;
		}else if(caracter==13){ //enter
			str[idx]='\0';
			idx++;
			break;
		}else if(caracter==8 || caracter == 127){ //backspace
			if(idx>0){
				idx--;
				str[idx]='\0';
			}
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
    uint16_t i = 0;
	uint16_t copia=i; //paa inverti la cadena
	    //en caso de que el numero sea cero, solo se agrega el carc nulo y se agrega el carac de cero
    if (number == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }
	  do {
	    uint16_t residuo = number % base;  //Obtenemos el residuo
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
		uint16_t end = i - 1;
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

