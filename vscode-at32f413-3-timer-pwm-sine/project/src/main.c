/**
  **************************************************************************
  * @file     main.c
  * @version  v2.0.5
  * @date     2022-05-20
  * @brief    main program
  **************************************************************************
  *                       Copyright notice & Disclaimer
  *
  * The software Board Support Package (BSP) that is made available to
  * download from Artery official website is the copyrighted work of Artery.
  * Artery authorizes customers to use, copy, and distribute the BSP
  * software and its related documentation for the purpose of design and
  * development in conjunction with Artery microcontrollers. Use of the
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */

#include "at32f413_board.h"
#include "at32f413_clock.h"
#include "math.h"

#define PWM_FREQ     1000000 // 1MHz
#define TMR_DMA_SIZE 1000    // 1MHz/1000 = 1KHz

/** @addtogroup AT32F413_periph_examples
  * @{
  */

/** @addtogroup 413_TMR_dma TMR_dma
  * @{
  */

gpio_init_type gpio_init_struct = {0};
tmr_output_config_type tmr_output_struct;
dma_init_type dma_init_struct = {0};
crm_clocks_freq_type crm_clocks_freq_struct = {0};

uint16_t timer_period = 0;
uint16_t src_buffer[TMR_DMA_SIZE];

/**
  * @brief  main function.
  * @param  none
  * @retval none
  */
int main(void)
{
  system_clock_config();

  at32_board_init();

  /* get system clock */
  crm_clocks_freq_get(&crm_clocks_freq_struct);

  /* turn led2/led3/led4 on */
  at32_led_on(LED2);
  at32_led_on(LED3);
  at32_led_on(LED4);

  /* enable tmr1/gpioa/gpiob/dma clock */
  crm_periph_clock_enable(CRM_TMR1_PERIPH_CLOCK, TRUE);
  crm_periph_clock_enable(CRM_DMA1_PERIPH_CLOCK, TRUE);
  crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);

  /* timer1 output pin Configuration */
  gpio_init_struct.gpio_pins = GPIO_PINS_10;
  gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
  gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init(GPIOA, &gpio_init_struct);

  /* tmr1 dma transfer example
  /* compute the value to be set in arr regiter to generate signal frequency at 17.57 khz */
  timer_period = (crm_clocks_freq_struct.sclk_freq / PWM_FREQ) - 1;

  /*  Set Sine wave data to buffer. */
  for(int i=0; i< TMR_DMA_SIZE; i++) {
    src_buffer[i] = sin(i*2*M_PI/TMR_DMA_SIZE)*(timer_period/2)+(timer_period/2);
  }

  /* Enable TMR1 */
  tmr_base_init(TMR1, timer_period, 0);
  tmr_cnt_dir_set(TMR1, TMR_COUNT_UP);

  /* channel 3 configuration in output mode */
  tmr_output_default_para_init(&tmr_output_struct);
  tmr_output_struct.oc_mode = TMR_OUTPUT_CONTROL_PWM_MODE_B;
  tmr_output_struct.oc_output_state = TRUE;
  tmr_output_struct.oc_polarity = TMR_OUTPUT_ACTIVE_LOW;
  tmr_output_struct.oc_idle_state = TRUE;
  tmr_output_struct.occ_output_state = TRUE;
  tmr_output_struct.occ_polarity = TMR_OUTPUT_ACTIVE_LOW;
  tmr_output_struct.occ_idle_state = FALSE;
  /* channel 3 */
  tmr_output_channel_config(TMR1, TMR_SELECT_CHANNEL_3, &tmr_output_struct);
  tmr_channel_value_set(TMR1, TMR_SELECT_CHANNEL_3, src_buffer[0]);

  /* enable tmr1 overflow dma request */
  tmr_dma_request_enable(TMR1, TMR_OVERFLOW_DMA_REQUEST, TRUE);

  /* dma config for tmr1 overflow dma request */
  /* dma1 channel5 configuration */
  dma_reset(DMA1_CHANNEL5);
  dma_init_struct.buffer_size = TMR_DMA_SIZE;
  dma_init_struct.direction = DMA_DIR_MEMORY_TO_PERIPHERAL;
  dma_init_struct.memory_base_addr = (uint32_t)src_buffer;
  dma_init_struct.memory_data_width = DMA_MEMORY_DATA_WIDTH_HALFWORD;
  dma_init_struct.memory_inc_enable = TRUE;
  dma_init_struct.peripheral_base_addr = (uint32_t)0x40012C3C;
  dma_init_struct.peripheral_data_width = DMA_PERIPHERAL_DATA_WIDTH_HALFWORD;
  dma_init_struct.peripheral_inc_enable = FALSE;
  dma_init_struct.priority = DMA_PRIORITY_MEDIUM;
  dma_init_struct.loop_mode_enable = TRUE;
  dma_init(DMA1_CHANNEL5, &dma_init_struct);

  dma_channel_enable(DMA1_CHANNEL5, TRUE);

  /* output enable */
  tmr_output_enable(TMR1, TRUE);
  /* enable tmr1 */
  tmr_counter_enable(TMR1, TRUE);

  while(1)
  {
  }
}

/**
  * @}
  */

/**
  * @}
  */
