/*$file${.::main.c} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
/*
* Model: TimeBomb.qm
* File:  ${.::main.c}
*
* This code has been generated by QM 5.2.5 <www.state-machine.com/qm>.
* DO NOT EDIT THIS FILE MANUALLY. All your changes will be lost.
*
* SPDX-License-Identifier: GPL-3.0-or-later
*
* This generated code is open source software: you can redistribute it under
* the terms of the GNU General Public License as published by the Free
* Software Foundation.
*
* This code is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
* more details.
*
* NOTE:
* Alternatively, this generated code may be distributed under the terms
* of Quantum Leaps commercial licenses, which expressly supersede the GNU
* General Public License and are specifically designed for licensees
* interested in retaining the proprietary status of their code.
*
* Contact information:
* <www.state-machine.com/licensing>
* <info@state-machine.com>
*/
/*$endhead${.::main.c} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/* TimeBomb/Button with QP/C framework */
#include "qpc.h"  /* QP/C API */
#include "bsp.h"

Q_DEFINE_THIS_MODULE("main") /* this module name for Q_ASSERT() */

/* The TimeBomb AO =======================================================*/
/*$declare${AOs::TimeBomb} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/

/*${AOs::TimeBomb} .........................................................*/
typedef struct {
/* protected: */
    QActive super;

/* private: */
    QTimeEvt te;
    uint32_t blink_ctr;
} TimeBomb;

/* public: */
static void TimeBomb_ctor(TimeBomb * const me);

/* protected: */
static QState TimeBomb_initial(TimeBomb * const me, void const * const par);
static QState TimeBomb_defused(TimeBomb * const me, QEvt const * const e);
static QState TimeBomb_armed(TimeBomb * const me, QEvt const * const e);
static QState TimeBomb_wait4button(TimeBomb * const me, QEvt const * const e);
static QState TimeBomb_blink(TimeBomb * const me, QEvt const * const e);
static QState TimeBomb_pause(TimeBomb * const me, QEvt const * const e);
static QState TimeBomb_boom(TimeBomb * const me, QEvt const * const e);
/*$enddecl${AOs::TimeBomb} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

/*$skip${QP_VERSION} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
/* Check for the minimum required QP version */
#if (QP_VERSION < 700U) || (QP_VERSION != ((QP_RELEASE^4294967295U) % 0x3E8U))
#error qpc version 7.0.0 or higher required
#endif
/*$endskip${QP_VERSION} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

/*$define${AOs::TimeBomb} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/

/*${AOs::TimeBomb} .........................................................*/

/*${AOs::TimeBomb::ctor} ...................................................*/
static void TimeBomb_ctor(TimeBomb * const me) {
    QActive_ctor(&me->super, (QStateHandler)&TimeBomb_initial);
    QTimeEvt_ctorX(&me->te, &me->super, TIMEOUT_SIG, 0U);
}

/*${AOs::TimeBomb::SM} .....................................................*/
static QState TimeBomb_initial(TimeBomb * const me, void const * const par) {
    /*${AOs::TimeBomb::SM::initial} */

    QS_FUN_DICTIONARY(&TimeBomb_defused);
    QS_FUN_DICTIONARY(&TimeBomb_armed);
    QS_FUN_DICTIONARY(&TimeBomb_wait4button);
    QS_FUN_DICTIONARY(&TimeBomb_blink);
    QS_FUN_DICTIONARY(&TimeBomb_pause);
    QS_FUN_DICTIONARY(&TimeBomb_boom);

    return Q_TRAN(&TimeBomb_wait4button);
}

/*${AOs::TimeBomb::SM::defused} ............................................*/
static QState TimeBomb_defused(TimeBomb * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /*${AOs::TimeBomb::SM::defused} */
        case Q_ENTRY_SIG: {
            BSP_ledBlueOn();
            status_ = Q_HANDLED();
            break;
        }
        /*${AOs::TimeBomb::SM::defused} */
        case Q_EXIT_SIG: {
            BSP_ledBlueOff();
            status_ = Q_HANDLED();
            break;
        }
        /*${AOs::TimeBomb::SM::defused::BUTTON2_PRESSED} */
        case BUTTON2_PRESSED_SIG: {
            status_ = Q_TRAN(&TimeBomb_armed);
            break;
        }
        /*${AOs::TimeBomb::SM::defused::BUTTON_PRESSED} */
        case BUTTON_PRESSED_SIG: {
            Q_ERROR_ID(100);
            status_ = Q_HANDLED();
            break;
        }
        default: {
            status_ = Q_SUPER(&QHsm_top);
            break;
        }
    }
    return status_;
}

/*${AOs::TimeBomb::SM::armed} ..............................................*/
static QState TimeBomb_armed(TimeBomb * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /*${AOs::TimeBomb::SM::armed} */
        case Q_EXIT_SIG: {
            BSP_ledRedOff();
            BSP_ledGreenOff();
            BSP_ledBlueOff();
            status_ = Q_HANDLED();
            break;
        }
        /*${AOs::TimeBomb::SM::armed::initial} */
        case Q_INIT_SIG: {
            status_ = Q_TRAN(&TimeBomb_wait4button);
            break;
        }
        /*${AOs::TimeBomb::SM::armed::BUTTON2_PRESSED} */
        case BUTTON2_PRESSED_SIG: {
            status_ = Q_TRAN(&TimeBomb_defused);
            break;
        }
        default: {
            status_ = Q_SUPER(&QHsm_top);
            break;
        }
    }
    return status_;
}

/*${AOs::TimeBomb::SM::armed::wait4button} .................................*/
static QState TimeBomb_wait4button(TimeBomb * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /*${AOs::TimeBomb::SM::armed::wait4button} */
        case Q_ENTRY_SIG: {
            BSP_ledGreenOn();
            status_ = Q_HANDLED();
            break;
        }
        /*${AOs::TimeBomb::SM::armed::wait4button} */
        case Q_EXIT_SIG: {
            BSP_ledGreenOff();
            status_ = Q_HANDLED();
            break;
        }
        /*${AOs::TimeBomb::SM::armed::wait4button::BUTTON_PRESSED} */
        case BUTTON_PRESSED_SIG: {
            me->blink_ctr = 5U;
            status_ = Q_TRAN(&TimeBomb_blink);
            break;
        }
        default: {
            status_ = Q_SUPER(&TimeBomb_armed);
            break;
        }
    }
    return status_;
}

/*${AOs::TimeBomb::SM::armed::blink} .......................................*/
static QState TimeBomb_blink(TimeBomb * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /*${AOs::TimeBomb::SM::armed::blink} */
        case Q_ENTRY_SIG: {
            BSP_ledRedOn();
            QTimeEvt_armX(&me->te, BSP_TICKS_PER_SEC/2, 0U);
            status_ = Q_HANDLED();
            break;
        }
        /*${AOs::TimeBomb::SM::armed::blink} */
        case Q_EXIT_SIG: {
            BSP_ledRedOff();
            status_ = Q_HANDLED();
            break;
        }
        /*${AOs::TimeBomb::SM::armed::blink::TIMEOUT} */
        case TIMEOUT_SIG: {
            status_ = Q_TRAN(&TimeBomb_pause);
            break;
        }
        default: {
            status_ = Q_SUPER(&TimeBomb_armed);
            break;
        }
    }
    return status_;
}

/*${AOs::TimeBomb::SM::armed::pause} .......................................*/
static QState TimeBomb_pause(TimeBomb * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /*${AOs::TimeBomb::SM::armed::pause} */
        case Q_ENTRY_SIG: {
            QTimeEvt_armX(&me->te, BSP_TICKS_PER_SEC/2, 0U);
            status_ = Q_HANDLED();
            break;
        }
        /*${AOs::TimeBomb::SM::armed::pause::TIMEOUT} */
        case TIMEOUT_SIG: {
            --me->blink_ctr;
            /*${AOs::TimeBomb::SM::armed::pause::TIMEOUT::[blink_ctr>0]} */
            if (me->blink_ctr > 0U) {
                status_ = Q_TRAN(&TimeBomb_blink);
            }
            /*${AOs::TimeBomb::SM::armed::pause::TIMEOUT::[else]} */
            else {
                status_ = Q_TRAN(&TimeBomb_boom);
            }
            break;
        }
        default: {
            status_ = Q_SUPER(&TimeBomb_armed);
            break;
        }
    }
    return status_;
}

/*${AOs::TimeBomb::SM::armed::boom} ........................................*/
static QState TimeBomb_boom(TimeBomb * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /*${AOs::TimeBomb::SM::armed::boom} */
        case Q_ENTRY_SIG: {
            BSP_ledRedOn();
            BSP_ledGreenOn();
            BSP_ledBlueOn();
            QS_BEGIN_ID(QS_USER, 0)
                QS_STR("*** Boom!!!");
            QS_END()
            status_ = Q_HANDLED();
            break;
        }
        default: {
            status_ = Q_SUPER(&TimeBomb_armed);
            break;
        }
    }
    return status_;
}
/*$enddef${AOs::TimeBomb} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

static QEvt const *timeBomb_queue[10];
static TimeBomb timeBomb;
QActive *AO_TimeBomb = &timeBomb.super;

/* the main function =========================================================*/
int main() {

    BSP_init(); /* initialize the BSP */
    QF_init();   /* initialize QP/C */

    /* create AO and start it */
    TimeBomb_ctor(&timeBomb);
    QACTIVE_START(AO_TimeBomb,
                 2U,
                 timeBomb_queue,
                 sizeof(timeBomb_queue)/sizeof(timeBomb_queue[0]),
                 (void *)0, 0U,
                 (void *)0);

    QF_run(); /* run QP/C... */
    return 0; /* NOTE: the scheduler does NOT return */
}

