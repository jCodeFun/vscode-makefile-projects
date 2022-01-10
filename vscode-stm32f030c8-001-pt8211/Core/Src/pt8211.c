/*
 PT8211 GPIO-DAC model

*/

#include "pt8211.h"

/*
 * Fast channel right output only
 */
void pcmMonoRightZero(void) {

  // Default right channel first, WS = Low
  POUT0 = (P_WS | P_SCK);
  POUT1 = P_SCK; POUT0 = P_SCK; // bit 15
}

void pcmMonoRight(uint16_t d) {
  POUT0 = (P_WS | P_DIN); // WS = Low
  if (d & BIT15) {POUT1 = P_DIN;}
  POUT1 = P_SCK; POUT0 = (P_SCK | P_DIN);

  if (d & BIT14) {POUT1 = P_DIN;}
  POUT1 = P_SCK; POUT0 = (P_SCK | P_DIN);

  if (d & BIT13) {POUT1 = P_DIN;}
  POUT1 = P_SCK; POUT0 = (P_SCK | P_DIN);

  if (d & BIT12) {POUT1 = P_DIN;}
  POUT1 = P_SCK; POUT0 = (P_SCK | P_DIN);

  if (d & BIT11) {POUT1 = P_DIN;}
  POUT1 = P_SCK; POUT0 = (P_SCK | P_DIN);

  if (d & BIT10) {POUT1 = P_DIN;}
  POUT1 = P_SCK; POUT0 = (P_SCK | P_DIN);

  if (d & BIT9) {POUT1 = P_DIN;}
  POUT1 = P_SCK; POUT0 = (P_SCK | P_DIN);

  if (d & BIT8) {POUT1 = P_DIN;}
  POUT1 = P_SCK; POUT0 = (P_SCK | P_DIN);

  if (d & BIT7) {POUT1 = P_DIN;}
  POUT1 = P_SCK; POUT0 = (P_SCK | P_DIN);

  if (d & BIT6) {POUT1 = P_DIN;}
  POUT1 = P_SCK; POUT0 = (P_SCK | P_DIN);

  if (d & BIT5) {POUT1 = P_DIN;}
  POUT1 = P_SCK; POUT0 = (P_SCK | P_DIN);

  if (d & BIT4) {POUT1 = P_DIN;}
  POUT1 = P_SCK; POUT0 = (P_SCK | P_DIN);

  if (d & BIT3) {POUT1 = P_DIN;}
  POUT1 = P_SCK; POUT0 = (P_SCK | P_DIN);

  if (d & BIT2) {POUT1 = P_DIN;}
  POUT1 = P_SCK; POUT0 = (P_SCK | P_DIN);

  if (d & BIT1) {POUT1 = P_DIN;}
  POUT1 = P_SCK; POUT0 = (P_SCK | P_DIN);

  if (d & BIT0) {POUT1 = P_DIN;}
  POUT1 = P_SCK; POUT0 = (P_SCK | P_DIN);
}

void pcmMonoLeft(uint16_t d) {
  POUT1 = P_WS; // WS = High
  POUT0 = P_DIN;
  if (d & BIT15) {POUT1 = P_DIN;}
  POUT1 = P_SCK; POUT0 = (P_SCK | P_DIN);

  if (d & BIT14) {POUT1 = P_DIN;}
  POUT1 = P_SCK; POUT0 = (P_SCK | P_DIN);

  if (d & BIT13) {POUT1 = P_DIN;}
  POUT1 = P_SCK; POUT0 = (P_SCK | P_DIN);

  if (d & BIT12) {POUT1 = P_DIN;}
  POUT1 = P_SCK; POUT0 = (P_SCK | P_DIN);

  if (d & BIT11) {POUT1 = P_DIN;}
  POUT1 = P_SCK; POUT0 = (P_SCK | P_DIN);

  if (d & BIT10) {POUT1 = P_DIN;}
  POUT1 = P_SCK; POUT0 = (P_SCK | P_DIN);

  if (d & BIT9) {POUT1 = P_DIN;}
  POUT1 = P_SCK; POUT0 = (P_SCK | P_DIN);

  if (d & BIT8) {POUT1 = P_DIN;}
  POUT1 = P_SCK; POUT0 = (P_SCK | P_DIN);

  if (d & BIT7) {POUT1 = P_DIN;}
  POUT1 = P_SCK; POUT0 = (P_SCK | P_DIN);

  if (d & BIT6) {POUT1 = P_DIN;}
  POUT1 = P_SCK; POUT0 = (P_SCK | P_DIN);

  if (d & BIT5) {POUT1 = P_DIN;}
  POUT1 = P_SCK; POUT0 = (P_SCK | P_DIN);

  if (d & BIT4) {POUT1 = P_DIN;}
  POUT1 = P_SCK; POUT0 = (P_SCK | P_DIN);

  if (d & BIT3) {POUT1 = P_DIN;}
  POUT1 = P_SCK; POUT0 = (P_SCK | P_DIN);

  if (d & BIT2) {POUT1 = P_DIN;}
  POUT1 = P_SCK; POUT0 = (P_SCK | P_DIN);

  if (d & BIT1) {POUT1 = P_DIN;}
  POUT1 = P_SCK; POUT0 = (P_SCK | P_DIN);

  if (d & BIT0) {POUT1 = P_DIN;}
  POUT1 = P_SCK; POUT0 = (P_SCK | P_DIN);
  POUT0 = P_WS;  // pull low all of pins
}

/*
 * Send out the mono PCM data only. (28us)
 */
void pt8211MonoOut (uint16_t left) {
  // Right channel must be first.
  pcmMonoRightZero(); // Right channel
  // Left channel.
  pcmMonoLeft(left); // Left channel
}

void pt8211StereoOut (uint16_t left, uint16_t right) {
  // Right channel first.
  pcmMonoRight(right); // Right channel
  // Left channel.
  pcmMonoLeft(left); // Left channel
}
/*
 * Initial the serial DAC hardware pins.
 */
void pt8211Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(DAC_PORT, DAC_SCK|DAC_WS|DAC_DIN, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA0 PA1 PA2 */
  GPIO_InitStruct.Pin = DAC_SCK|DAC_WS|DAC_DIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(DAC_PORT, &GPIO_InitStruct);

}
