#include <includeAll.h>
#include "../Robot1/fonctions.h"
int main(){
	//DDRC = 0xFF;
	//enableConversion();
	PWM(125, 125, 2);
    _delay_ms(1150);
    avancer(0);
    _delay_ms(500);
	for(;;){
	}
}