/*
 * evt_mask.h
 *
 *  Created on: Apr 12, 2013
 *      Author: g.kruglov
 */

#pragma once

// Event masks
#define EVT_USB_DATA_OUT        EVENT_MASK(3)
#define EVT_USB_READY           EVENT_MASK(10)
#define EVT_USB_SUSPEND         EVENT_MASK(11)

#define EVT_START_LISTEN        EVENT_MASK(15)
#define EVT_STOP_LISTEN         EVENT_MASK(16)


// Adc
#define EVT_SAMPLING            EVENT_MASK(24)
#define EVT_ADC_DONE            EVENT_MASK(25)

// Eternal
#define EVT_UART_NEW_CMD        EVENT_MASK(29)
#define EVT_RADIO               EVENT_MASK(30)
#define EVT_EVERY_SECOND        EVENT_MASK(31)
