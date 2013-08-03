#ifndef FSM_H_
#define FSM_H_

#include "ee_bluetooth.h"
#include "buttons.h"

typedef enum Status_ {WELCOME, INIT, WAIT} Status;
typedef enum Signal_ {ABSENT, B1, B2, B3, B4} Signal;

Signal FSM_getSignals();
void FSM_init();
void FSM_tran_(Status dest);
void FSM_dispatch();

#endif /* FSM_H_ */
