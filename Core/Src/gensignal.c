/*
 * gensignal.h
 *
 *  Created on: 16 mar 2023
 *      Author: Federico
 */

#include "gensignal.h"
#include "stdio.h"

step Fase[6][5]={


	// RESET
	{{.dac_signal[0]=0, .dac_signal[1]=0, .dac_signal[2]=0,
	.next_step=1, .cont=CONTINUE},

	{.dac_signal[0]=0, .dac_signal[1]=0, .dac_signal[2]=0,
	.next_step=1, .cont=END_PHASE}},


	//FASE1
	{{.dac_signal[0]=2.9, .dac_signal[1]=0, .dac_signal[2]=0,
	.next_step=1, .cont=CONTINUE},

	{.dac_signal[0]=2.9, .dac_signal[1]=0, .dac_signal[2]=0,
	.next_step=1, .cont=END_PHASE}},


	// FASE2
	{{.dac_signal[0]=0, .dac_signal[1]=0, .dac_signal[2]=0,
	.next_step=3, .cont=CONTINUE},

	{.dac_signal[0]=0, .dac_signal[1]=2.7, .dac_signal[2]=0,
	.next_step=1, .cont=CONTINUE},

	{.dac_signal[0]=0, .dac_signal[1]=2.7, .dac_signal[2]=0,
	.next_step=1, .cont=END_PHASE}},


	// FASE3
	{{.dac_signal[0]=0, .dac_signal[1]=0, .dac_signal[2]=0,
	.next_step=3, .cont=CONTINUE},

	{.dac_signal[0]=0, .dac_signal[1]=0, .dac_signal[2]=2.7,
	.next_step=1, .cont=CONTINUE},

	{.dac_signal[0]=0, .dac_signal[1]=0, .dac_signal[2]=2.7,
	.next_step=1, .cont=END_PHASE}},


	// FASE4
	{{.dac_signal[0]=0,
	.dac_signal[1]=0,
	.dac_signal[2]=0,
	.next_step=3,
	.cont=CONTINUE},

	{.dac_signal[0]=2.9,
	.dac_signal[1]=0,
	.dac_signal[2]=0,
	.next_step=3,
	.cont=CONTINUE},

	{.dac_signal[0]=2.9,
	.dac_signal[1]=2.7,
	.dac_signal[2]=0,
	.next_step=1,
	.cont=CONTINUE},

	{.dac_signal[0]=2.9,
	.dac_signal[1]=2.7,
	.dac_signal[2]=0,
	.next_step=1,
	.cont=END_PHASE}},


	// FASE5
	{{.dac_signal[0]=0,
	.dac_signal[1]=0,
	.dac_signal[2]=0,
	.next_step=36,
	.cont=CONTINUE},

	{.dac_signal[0]=2.9,
	.dac_signal[1]=0,
	.dac_signal[2]=0,
	.next_step=3,
	.cont=CONTINUE},

	{.dac_signal[0]=2.9,
	.dac_signal[1]=2.7,
	.dac_signal[2]=0,
	.next_step=1,
	.cont=CONTINUE},

	{.dac_signal[0]=0,
	.dac_signal[1]=0,
	.dac_signal[2]=0,
	.next_step=1,
	.cont=CONTINUE},

	{.dac_signal[0]=0,
	.dac_signal[1]=0,
	.dac_signal[2]=0,
	.next_step=1,
	.cont=END_PHASE}}
};


void PlayStep(uint8_t fase, uint8_t *step_fase, uint8_t *nextStep){

	//printf("PlayStep: step=%u\r\n", *step_fase);

	if(Fase[fase][*step_fase].cont==END_PHASE){
		printf("-Fase%u ENDPHASE\r\n\n", fase);
		//*nextStep=Fase[fase][*step_fase].next_step;
		*nextStep=1;
		return;
	}


	// SIG1 con DAC1
	uint32_t val1 = (uint32_t)(Fase[fase][*step_fase].dac_signal[0]*4096)/3.3;
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, val1);

	// SIG2 con DAC2
	uint32_t val2 = (uint32_t)(Fase[fase][*step_fase].dac_signal[1]*4096)/3.3;
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_2, DAC_ALIGN_12B_R, val2);

	// SIG3 con PWM
	uint16_t val3 = (((Fase[fase][*step_fase].dac_signal[2])/3.3) * 1023);
	TIM1->CCR1 = val3;

	printf("gensignal.c  next_step=%d\r\n\n", Fase[fase][*step_fase].next_step);
	*nextStep=Fase[fase][*step_fase].next_step;
	*step_fase+=1;

	return;
}

