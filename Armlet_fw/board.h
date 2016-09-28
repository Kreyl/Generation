/*
 * board.h
 *
 *  Created on: 12 сент. 2015 г.
 *      Author: Kreyl
 */

#pragma once

#include <inttypes.h>

// ==== General ====
#define BOARD_NAME          "ArmletG"

#define DEBUG_OTK           0

// MCU type as defined in the ST header.
#define STM32L476xx

// Freq of external crystal if any. Leave it here even if not used.
#define CRYSTAL_FREQ_HZ 12000000

// OS timer settings
#define STM32_ST_IRQ_PRIORITY   2
#define STM32_ST_USE_TIMER      5
#define SYS_TIM_CLK             (Clk.APB1FreqHz)    // Timer 5 is clocked by APB1

//  Periphery
#define I2C1_ENABLED            TRUE
#define I2C2_ENABLED            TRUE
#define I2C3_ENABLED            TRUE

#define ADC_REQUIRED            TRUE
#define STM32_DMA_REQUIRED      TRUE    // Leave this macro name for OS

#if 1 // ========================== GPIO =======================================
// UART
#define UART_GPIO       GPIOA
#define UART_TX_PIN     2
#define UART_RX_PIN     3
#define UART_AF         AF7 // for all USARTs

// RGB LED
#define LED_RED_CH      { GPIOC, 6, TIM3, 1, invInverted, omPushPull, 255 }
#define LED_GREEN_CH    { GPIOC, 7, TIM3, 2, invInverted, omPushPull, 255 }
#define LED_BLUE_CH     { GPIOC, 8, TIM3, 3, invInverted, omPushPull, 255 }
// White LED
#define LED_WHITE       { GPIOC, 9, TIM3, 4 }
// IR LED
//#define LED_IR          { GPIOA, 4 }

// Vibro
#define VIBRO_TOP       100
#define VIBRO_PIN       { GPIOB, 14, TIM15, 1, invNotInverted, omPushPull, VIBRO_TOP }

// Beeper
#define BEEPER_TOP      22
#define BEEPER_PIN      { GPIOB, 9, TIM17, 1, invNotInverted, omPushPull, BEEPER_TOP }

// Mems
#define MEMS_PWR_GPIO   GPIOC
#define MEMS_PWR_PIN    12

// I2C
#define I2C1_GPIO       GPIOB
#define I2C1_SCL        6
#define I2C1_SDA        7
#define I2C2_GPIO       GPIOB
#define I2C2_SCL        10
#define I2C2_SDA        11
#define I2C3_GPIO       GPIOC
#define I2C3_SCL        0
#define I2C3_SDA        1
// I2C Alternate Function
#define I2C_AF          AF4

// Pill power
#define PILL_PWR_PIN    { GPIOB, 12, omPushPull }
// EE power
#define EE_PWR_PIN      { GPIOC, 2, omPushPull }

//  Battery measurement
#define BAT_GND_PIN     GPIOC, 4, omPushPull
#define BAT_INPUT_PIN   GPIOC, 5

// State pins
#define USB_DETECT_PIN  GPIOA, 9
#define CHARGE_PIN      GPIOB, 13

// Radio
#define CC_GPIO         GPIOA
#define CC_GDO2         NC
#define CC_GDO0         0
#define CC_SCK          5
#define CC_MISO         6
#define CC_MOSI         7
#define CC_CS           1
// Input pin
#define CC_GDO0_IRQ     { CC_GPIO, CC_GDO0, pudNone }

#endif // GPIO

#if 1 // ========================= Timer =======================================
//#define TMR_DAC_CHUNK               TIM6
//#define TMR_DAC_SMPL                TIM7
//#define TMR_DAC_CHUNK_IRQ           TIM6_IRQn
//#define TMR_DAC_CHUNK_IRQ_HANDLER   VectorEC
#endif // Timer

#if I2C_REQUIRED // ====================== I2C =================================

#endif

#if 1 // =========================== SPI =======================================
#define CC_SPI          SPI1
#define CC_SPI_AF       AF5
#endif

#if 1 // ========================== USART ======================================
#define PRINTF_FLOAT_EN TRUE
#define UART            USART2
#define UART_TX_REG     UART->TDR
#define UART_RX_REG     UART->RDR
#endif

#if ADC_REQUIRED // ======================= Inner ADC ==========================
// Clock divider: clock is generated from the APB2
#define ADC_CLK_DIVIDER		adcDiv2

// ADC channels
#define ADC_BATTERY_CHNL 	14
// ADC_VREFINT_CHNL
#define ADC_CHANNELS        { ADC_BATTERY_CHNL, ADC_VREFINT_CHNL }
#define ADC_CHANNEL_CNT     2   // Do not use countof(AdcChannels) as preprocessor does not know what is countof => cannot check
#define ADC_SAMPLE_TIME     ast24d5Cycles
#define ADC_OVERSAMPLING_RATIO  64   // 1 (no oversampling), 2, 4, 8, 16, 32, 64, 128, 256
#endif

#if 1 // =========================== DMA =======================================
// ==== Uart ====
// Remap is made automatically if required
#define UART_DMA_TX     STM32_DMA1_STREAM7
#define UART_DMA_RX     STM32_DMA1_STREAM6
#define UART_DMA_CHNL   2

// DAC
//#define DAC_DMA         STM32_DMA1_STREAM2

// ==== I2C ====
#define I2C1_DMA_TX     STM32_DMA2_STREAM7
#define I2C1_DMA_RX     STM32_DMA2_STREAM6
#define I2C1_DMA_CHNL   5
#define I2C2_DMA_TX     STM32_DMA1_STREAM4
#define I2C2_DMA_RX     STM32_DMA1_STREAM5
#define I2C2_DMA_CHNL   3
#define I2C3_DMA_TX     STM32_DMA1_STREAM2
#define I2C3_DMA_RX     STM32_DMA1_STREAM3
#define I2C3_DMA_CHNL   3

//#define STM32_I2C_I2C3_RX_DMA_STREAM   STM32_DMA_STREAM_ID(1, 3)
//#define STM32_I2C_I2C3_TX_DMA_STREAM   STM32_DMA_STREAM_ID(1, 2)


#if ADC_REQUIRED
#define ADC_DMA         STM32_DMA1_STREAM1
#define ADC_DMA_MODE    STM32_DMA_CR_CHSEL(0) |   /* DMA1 Stream1 Channel0 */ \
                        DMA_PRIORITY_LOW | \
                        STM32_DMA_CR_MSIZE_HWORD | \
                        STM32_DMA_CR_PSIZE_HWORD | \
                        STM32_DMA_CR_MINC |       /* Memory pointer increase */ \
                        STM32_DMA_CR_DIR_P2M |    /* Direction is peripheral to memory */ \
                        STM32_DMA_CR_TCIE         /* Enable Transmission Complete IRQ */
#endif // ADC

#endif // DMA
