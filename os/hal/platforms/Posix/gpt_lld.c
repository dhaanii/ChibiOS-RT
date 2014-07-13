/*
    ChibiOS/RT - Copyright (C) 2006-2013 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/**
 * @file    templates/gpt_lld.c
 * @brief   GPT Driver subsystem low level driver source template.
 *
 * @addtogroup GPT
 * @{
 */

#include <time.h>
#include "ch.h"
#include "hal.h"

#if HAL_USE_GPT || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/**
 * @brief   GPTD1 driver identifier.
 */
#if POSIX_GPT_USE_GPT1 || defined(__DOXYGEN__)
  GPTDriver GPTD1;
#endif

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Driver interrupt handlers.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Low level GPT driver initialization.
 * @note    This function's high level  counter part is implicitly invoked by 
 *          @p halInit(), there is no need to explicitly initialize the driver.
 * @notapi
 */
void gpt_lld_init(void) {

#if POSIX_GPT_USE_TIM1
  /* Driver initialization.*/
  gptObjectInit(&GPTD1);
#endif
}

/**
 * @brief   Configures and activates the GPT peripheral.
 *
 * @param[in] gptp      pointer to the @p GPTDriver object
 *
 * @notapi
 */
void gpt_lld_start(GPTDriver *gptp) {
  uint16_t psc;

  if (gptp->state == GPT_STOP) {
    /* Enables the peripheral.*/
#if POSIX_GPT_USE_GPT1
    if (&GPTD1 == gptp) {
      /*Enable clock*/
      /*Reset clock*/
      /*Set priority of interrupt handler & enable it*/
      gptp->state = GPT_READY;
      timer_create(gptp->state, SIGEV_NONE, sigev_value.sival_int);
    }
#endif /* POSIX_GPT_USE_GPT1 */
  }
  /* Configures the peripheral.*/

}

/**
 * @brief   Deactivates the GPT peripheral.
 *
 * @param[in] gptp      pointer to the @p GPTDriver object
 *
 * @notapi
 */
void gpt_lld_stop(GPTDriver *gptp) {

  if (gptp->state == GPT_READY) {
    /* Resets the peripheral.*/
    gptp->state = GPT_STOP;
    

    /* Disables the peripheral.*/
#if POSIX_GPT_USE_GPT1
    if (&GPTD1 == gptp) {
      timersettime(gptp->state, 0, 0);
    }
#endif /* POSIX_GPT_USE_GPT1 */
  }
}

/**
 * @brief   Starts the timer in continuous mode.
 *
 * @param[in] gptp      pointer to the @p GPTDriver object
 * @param[in] interval  period in ticks
 *
 * @notapi
 */
void gpt_lld_start_timer(GPTDriver *gptp, gptcnt_t interval) {

  (void)gptp;
  (void)interval;
  timer_settime(gptp->state, TIME_ABSTIME, null, interval);

}

/**
 * @brief   Stops the timer.
 *
 * @param[in] gptp      pointer to the @p GPTDriver object
 *
 * @notapi
 */
void gpt_lld_stop_timer(GPTDriver *gptp) {

  (void)gptp;
  gptp->state = GPT_STOP; 

}

/**
 * @brief   Starts the timer in one shot mode and waits for completion.
 * @details This function specifically polls the timer waiting for completion
 *          in order to not have extra delays caused by interrupt servicing,
 *          this function is only recommended for short delays.
 *
 * @param[in] gptp      pointer to the @p GPTDriver object
 * @param[in] interval  time interval in ticks
 *
 * @notapi
 */
void gpt_lld_polled_delay(GPTDriver *gptp, gptcnt_t interval) {

  (void)gptp;
  (void)interval;
  

}

#endif /* HAL_USE_GPT */

/** @} */
