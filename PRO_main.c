#include "LIB\stdTypes.h"
#include "LIB\errorState.h"


#include "HAL\GRLCD\GRLCD_Int.h"
//#include "MCAL\EXTI2\EXTI_interface.h"
#include "MCAL\DIO\DIO_int.h"


#include "MCAL\EXTI\EXTI_int.h"

#include "MCAL\GIE\GIE_int.h"
#include "MCAL\TIMER0\TIMER0_int.h"
#define TIMSK	*((volatile u8*) 0x59)
#define TCCR0	*((volatile u8*) 0x53)
#define TCNT0	*((volatile u8*) 0x52)
#define OCR0	*((volatile u8*) 0x5c)


 u32 Counts=0;
 u8 Preload=0 ;
 u32 N_ISR=0;
 u32 N_OVF = 0 ;
int main()
{
	DIO_enuSetPinDirection(2,7,1);
	TCCR0 = 0b01101101;
	OCR0 = 8959;
	u32 Duty = (OCR0 + 1 ) / (256);
	//mode : fast PWM  pres : 1024  Non inverted 
    

	//Enable interrupt
	 //TIMSK |=(1<<1);
     //GIE_vidEnable();

	u32 Time = 500; //1 sec
	Counts = ((Time/1000)*16000000ul)/ (1024); //20000000
	//Preload = 256UL - (Counts % 256);
	//TCNT0 = Preload ;
	N_OVF = (Counts + 255)/256;
	N_ISR = N_OVF;
	OCR0 = 156;
	while(1);

}
void __vector_10(void)__attribute__((signal));
void __vector_10(void)
{
	
		DIO_enuTogglePinValue(2,7);

}


void __vector_11(void)__attribute__((signal));
void __vector_11(void)
{
	N_ISR = N_ISR-1;
	if(!N_ISR )
	{
		//TCNT0 = Preload;
		DIO_enuTogglePinValue(2,7);
		//DIO_enuSetPinValue(2,7,1);
		N_ISR = N_OVF ;
	}
}
