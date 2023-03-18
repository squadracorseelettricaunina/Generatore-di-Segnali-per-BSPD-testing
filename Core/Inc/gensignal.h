/*
 * gensignal.h
 *
 *  Created on: 16 mar 2023
 *      Author: Federico
 */

#ifndef GENSIG_H_
#define GENSIG_H_

#include "dac.h"
#include <stdint.h>


enum FASI {GS_RESET=0, FASE1=1, FASE2=2, FASE3=3, FASE4=4, FASE5=5};
enum PHASE_PROGRESS {CONTINUE = 0, END_PHASE = 1};
enum STEP_MUTEX {WAIT=0, PLAY=1};


typedef struct steps{
	float dac_signal[3];
	uint8_t next_step;
	enum PHASE_PROGRESS cont;
} step;

//step Fase[0]={step1, step2, step3};
//Fase[0][0]={step1};


void PlayStep(uint8_t fase, uint8_t *step_fase, uint8_t *nextStep); //nel main bisogna creare un puntatore che punta a next_step



#endif //GENSIG_H_
