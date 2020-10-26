#include "YRShell.h"
#include "utility/InterruptSliceable.h"
#include "utility/BufferedSerial_STM.h"
#include <stdio.h>

#include "appmain.h"

YRSmallShell shell1;
BufferedSerial BSerial2(usartHandler(2));
static CircularQ<uint32_t, 256> m_captureQ;
//static CircularQ<char, 16> debugInQ;
//static CircularQ<char, 1024> m_loggerQ;

void log(char *buf, uint16_t length) {
//	if( m_loggerQ.spaceAvailable( length) ) {
//		for( uint16_t i = 0; i < length; i++) {
//			m_loggerQ.put( buf[i]);
//		}
//	}
}

void appmainSlice(void) {

}

extern "C" void runApp( ) {

	//mainApp.setup();
	//setup( );
	//BootStatus::logBootStatus();

	BSerial2.begin(115200);
	BSerial2.init(shell1.getInq(), shell1.getOutq());
//	BSerial2.init(debugInQ, m_loggerQ);

	__HAL_RCC_TIM2_CLK_ENABLE();
	TIM_HandleTypeDef *timer = timHandler(2);
	HAL_TIM_Base_Start(timer);
	HAL_TIM_IC_Start_IT(timer, TIM_CHANNEL_2);

	while(true) {
		static uint32_t loopTimer = 0;
		//loop( );
		//mainApp.loop();
		Sliceable::sliceAll();

		if((HAL_GetTick() - loopTimer) > 1000) {
			loopTimer = HAL_GetTick();
			char temp[256];
			uint16_t used = m_captureQ.used();
			snprintf(temp, 256, "tick\r\n");
			log(temp, strlen(temp));
			if(used > 1) {
				snprintf(temp, 256, "Num captures %d\r\n", used);
				log(temp, strlen(temp));
				uint32_t total = 0;
				uint32_t count = 0;
				uint32_t discarded = 0;
				for(uint16_t i=0; i < used; i++) {
					uint32_t current = m_captureQ.get();
					if(current > 50) {
						total += current;
						count++;
					} else {
						discarded++;
					}

					snprintf(temp, 256, "%lu ", current);
					log(temp, strlen(temp));
				}
				uint32_t average = total/count;
//				for(uint16_t i=0; i < used; i++) {
//					total += m_captureQ.get();
//				}
//				uint32_t average = total/used;
				snprintf(temp, 256, "\r\ntotal %lu, average %lu, discarded %lu\r\n", total, average, discarded);
				log(temp, strlen(temp));
			}
		}
	}
}

// operating in a 1 millisecond interrupt, whatever is done here, be quick
extern "C" void sysTimerTick() {
	InterruptSliceable::sliceOne();
}
