/**
 * IMP Project
 * Author: Jan Demel (xdemel01)
 * Originál - 22.12.2019
 */

#include <string.h>
#include "MK60D10.h"

#define SET_BIT(position, bit) bit<<position
#define CLEAR_PTA_PDOR() PTA->PDOR = (PTA->PDOR & 0xFFFFFA3F) | 0x3F000A00

#define SW2_BTN_MASK 0x400
#define SW3_BTN_MASK 0x1000
#define SW4_BTN_MASK 0x8000000
#define SW5_BTN_MASK 0x4000000

/**
 * Structure for handling time
 */
struct T_TIME{
	unsigned short seconds;
	unsigned short miliseconds;
};

/**
 * Addressing displays
 */
int display[4] = {
	SET_BIT(8, 1), // First
	SET_BIT(6, 1), // Second
	SET_BIT(7, 1), // Third
	SET_BIT(10, 1) // Fourth
};

/**
 * Numbers in 7seg display
 */
int digits[10] = {
	0b11010010111111111111010111111111, // 0
	0b11110110111111111111111111111111, // 1
	0b11010001111111111111011111111111, // 2
	0b11110000111111111111011111111111, // 3
	0b11110100111111111111110111111111, // 4
	0b11111000111111111111010111111111, // 5
	0b11011000111111111111010111111111, // 6
	0b11110110111111111111011111111111, // 7
	0b11010000111111111111010111111111, // 8
	0b11110000111111111111010111111111  // 9
};

// Holds currently displayed time
struct T_TIME current_time = {.seconds = 0, .miliseconds = 0};

// Array for holding recorded times
struct T_TIME times_memory[50];
int times_memory_max_index = 0;
int times_memory_current_index = 0;

// Is counting? 0 == false, 1 == true
int counting = 0;


/**
 * Delay function (active waiting)
 */
void delay(long long bound) {
	long long i;
	for(i=0;i<bound;i++);
}

/**
 * Initialize GPIO output pins
 */
void InitGPIOOutput() {
	PORTA->PCR[8] = PORT_PCR_MUX(0x01);
	PORTA->PCR[11] = PORT_PCR_MUX(0x01);
	PORTA->PCR[9] = PORT_PCR_MUX(0x01);
	PORTA->PCR[6] = PORT_PCR_MUX(0x01);
	PORTA->PCR[7] = PORT_PCR_MUX(0x01);
	PORTA->PCR[27] = PORT_PCR_MUX(0x01);
	PORTA->PCR[29] = PORT_PCR_MUX(0x01);
	PORTA->PCR[26] = PORT_PCR_MUX(0x01);
	PORTA->PCR[28] = PORT_PCR_MUX(0x01);
	PORTA->PCR[24] = PORT_PCR_MUX(0x01);
	PORTA->PCR[25] = PORT_PCR_MUX(0x01);
	PORTA->PCR[10] = PORT_PCR_MUX(0x01);

	PTA->PDDR = 0 | (
		SET_BIT(8, 1) |
		SET_BIT(11, 1) |
		SET_BIT(9, 1) |
		SET_BIT(6, 1) |
		SET_BIT(7, 1) |
		SET_BIT(27, 1) |
		SET_BIT(29, 1) |
		SET_BIT(26, 1) |
		SET_BIT(28, 1) |
		SET_BIT(24, 1) |
		SET_BIT(25, 1) |
		SET_BIT(10, 1)
	);
}

/**
 * Initialize input pin
 */
void InitGPIOInputPin(int pin_index) {
	PORTE->PCR[pin_index] = ( PORT_PCR_ISF(0x01)
					| PORT_PCR_IRQC(0x0A)
					| PORT_PCR_MUX(0x01)
					| PORT_PCR_PE(0x01)
					| PORT_PCR_PS(0x01));
}

/**
 * Initialize GPIO input pins
 */
void InitGPIOInput() {
	InitGPIOInputPin(10); // SW2
	InitGPIOInputPin(12); // SW3
	InitGPIOInputPin(26); // SW5
	InitGPIOInputPin(27); // SW4

	NVIC_EnableIRQ(PORTE_IRQn);
}

/**
 * Initialize hardware before code gets executed
 */
void InitPorts(){
	SIM->SCGC5 |= (SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTE_MASK );

	InitGPIOOutput();
	InitGPIOInput();
}

/**
 * Buttons handler
 */
void PORTE_IRQHandler(void) {
	if((PORTE_ISFR & SW3_BTN_MASK) && !(PTE->PDIR & SW3_BTN_MASK)){
		if(counting == 0){
			counting = 1;
		} else {
			times_memory[times_memory_current_index++] = current_time;
			times_memory_max_index++;
		}


		PORTE_ISFR |= SW3_BTN_MASK;
	} else if((PORTE_ISFR & SW5_BTN_MASK) && !(PTE->PDIR & SW5_BTN_MASK)){
		if(counting == 0){
			current_time.seconds = 0;
			current_time.miliseconds = 0;

			memset(times_memory, 0, sizeof(times_memory));
			times_memory_max_index = 0;
			times_memory_current_index = 0;
		} else {
			counting = 0;
		}

		PORTE_ISFR |= SW5_BTN_MASK;

	} else if((PORTE_ISFR & SW4_BTN_MASK) && !(PTE->PDIR & SW4_BTN_MASK)){
		if(counting == 0 && times_memory_current_index - 1 >= 0){
			current_time = times_memory[--times_memory_current_index];
		}

		PORTE_ISFR |= SW4_BTN_MASK;
	} else if((PORTE_ISFR & SW2_BTN_MASK) && !(PTE->PDIR & SW2_BTN_MASK)){
		if(counting == 0 && times_memory_current_index + 1 <= times_memory_max_index){
			current_time = times_memory[times_memory_current_index++];
		}

		PORTE_ISFR |= SW2_BTN_MASK;
	}
}

/**
 * Init clock
 */
void InitMCU() {
  MCG_C4 |= ( MCG_C4_DMX32_MASK | MCG_C4_DRST_DRS(0x01) );
  SIM_CLKDIV1 |= SIM_CLKDIV1_OUTDIV1(0x00);
  WDOG_STCTRLH &= ~WDOG_STCTRLH_WDOGEN_MASK;
}

/**
 * Timer interrupt handler
 */
void LPTMR0_IRQHandler() {
  LPTMR0_CSR |=  LPTMR_CSR_TCF_MASK;   // Clean interrupt flag

  if(counting == 1){
    current_time.miliseconds++;
  }

  if(current_time.miliseconds == 100){
    current_time.seconds++;
    current_time.miliseconds = 0;
  }

  if(current_time.seconds == 100){
    current_time.seconds = 0;
  }
}

/**
 * Timer setup
 */
void LPTMR0Init() {
	SIM->SCGC5 |= SIM_SCGC5_LPTIMER_MASK;

  LPTMR0->CSR &= ~LPTMR_CSR_TEN_MASK;
  LPTMR0->PSR = ( LPTMR_PSR_PRESCALE(0)
                | LPTMR_PSR_PBYP_MASK
                | LPTMR_PSR_PCS(1));
  LPTMR0->CMR = 9;
  LPTMR0->CSR =(  LPTMR_CSR_TCF_MASK
                | LPTMR_CSR_TIE_MASK
              );

  NVIC_EnableIRQ(LPTMR0_IRQn);
  LPTMR0->CSR |= LPTMR_CSR_TEN_MASK;
}

/**
 * Show certain number on certain display
 */
void ShowDigit(unsigned short display_index, unsigned short digit) {
	CLEAR_PTA_PDOR(); // Clear display
	PTA->PDOR |= display[display_index]; // Choose display
	PTA->PDOR &= digits[digit]; // Set digit
	if(display_index == 1) PTA->PDOR &= 0xEFFFFFFF; // Show dot (.)
}

/**
 * Main rendering time loop
 * Responsible for displaying time
 * info on display
 */
void RenderTimeLoop(){
	unsigned short tick = 0;
	while(1){
		switch(tick){
			case 0:
				ShowDigit(tick, (unsigned short) (current_time.seconds / 10));
			break;
			case 1:
				ShowDigit(tick, (unsigned short) (current_time.seconds % 10));
			break;
			case 2:
				ShowDigit(tick, (unsigned short) (current_time.miliseconds / 10));
			break;
			case 3:
				ShowDigit(tick, (unsigned short) (current_time.miliseconds % 10));
			break;
		}

		tick++;
		tick = tick % 4;
		delay(2000);
	}
}

int main(void)
{
	InitMCU();
	InitPorts();
	LPTMR0Init();
	RenderTimeLoop();

  return 0;
}
