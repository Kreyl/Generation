/*****************************************************************************
* Model: generation_light_biotics.qm
* File:  ./generation_light.h
*
* This code has been generated by QM tool (see state-machine.com/qm).
* DO NOT EDIT THIS FILE MANUALLY. All your changes will be lost.
*
* This program is open source software: you can redistribute it and/or
* modify it under the terms of the GNU General Public License as published
* by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
* or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
* for more details.
*****************************************************************************/
/*${.::generation_light.h} .................................................*/
#ifndef generation_light_h
#define generation_light_h
#ifdef __cplusplus
extern "C" {
#endif

#include "qpc.h"    /* include own framework */

#define BSP_TICKS_PER_SEC 100

enum PlayerSignals {
    TICK_SEC_SIG  = Q_USER_SIG,

    CHARGE_SIG,
    FIRST_ABILITY,
    THROW_SIG = FIRST_ABILITY,
    PUNCH_SIG,
    LIFT_SIG,
    WARP_SIG,
    BARRIER_SIG,
    CLEANSE_SIG,
    SINGULAR_SIG,
    SONG_SIG,
    LAST_ABILITY = SONG_SIG,
    RELEASE_SIG,
    PWR_RELEASE_SIG,

    PUNCH_PILL_SIG,
    PUNCH_PWR_PILL_SIG,
    LIFT_PILL_SIG,
    LIFT_PWR_PILL_SIG,
    WARP_PILL_SIG,
    WARP_PWR_PILL_SIG,
    CLEANSE_PILL_SIG,
    BARRIER_PILL_SIG,
    SINGULARITY_PILL_SIG,
    SONG_PILL_SIG,
    DEFAULT_PILL_SIG,
    MAX_PILL_SIG,

    LAST_USER_SIG = MAX_PILL_SIG
};

extern QHsm * const the_biotics; /* opaque pointer to the biotics HSM */

/*${SMs::Biotics_ctor} .....................................................*/
void Biotics_ctor(void);


extern QHsm * const the_hand; /* opaque pointer to the hand HSM */

/*${SMs::Hand_ctor} ........................................................*/
void Hand_ctor(void);


#ifdef __cplusplus
}
#endif
#endif /* generation_light_h */
