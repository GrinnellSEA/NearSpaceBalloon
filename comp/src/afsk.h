/*
 * NEAR SPACE BALLOON PROJECT
 * FLIGHT COMPUTER CODE
 *
 * GRINNELL SPACE EXPLORATION AGENCY
 *
 * © 2017.  All Rights Reserved.
 */

#ifndef __AFSK_AVR_H__
#define __AFSK_AVR_H__

#include <avr/pgmspace.h>
#include "radio_config.h"

#define AFSK_ISR ISR(TIMER2_OVF_vect)

// Exported consts
extern const int MODEM_CLOCK_RATE;
extern const byte REST_DUTY;
extern const short TABLE_SIZE;
extern const int PLAYBACK_RATE;

// Exported vars
extern const byte afsk_sine_table[] PROGMEM;

// Inline functions (this saves precious cycles in the ISR)
#if AUDIO_PIN == 3
#  define OCR2 OCR2B
#endif
#if AUDIO_PIN == 11
#  define OCR2 OCR2A
#endif

inline byte afsk_read_sample(int phase) {
    return pgm_read_byte_near(afsk_sine_table + phase);
}

inline void afsk_output_sample(byte s) {
    OCR2 = s;
}

#ifdef DEBUG_MODEM
inline short afsk_timer_counter() {
    short t = TCNT2;
    if ((TIFR2 & _BV(TOV2)) && t < 128)
        t += 256;
    return t;
}

inline int afsk_isr_overrun() {
    return (TIFR2 & _BV(TOV2));
}
#endif


// Exported functions
void afsk_send(const byte *buffer, int len);
void afsk_start();
bool afsk_flush();
void afsk_isr();
void afsk_timer_setup();
void afsk_timer_start();
void afsk_timer_stop();
#ifdef DEBUG_MODEM
void afsk_debug();
#endif

#endif
