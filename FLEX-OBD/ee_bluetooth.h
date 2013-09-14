/*
 * ee_bluetooth.h
 *
 *  Created on: 26/mar/2013
 *      Author: Alessio
 */

#ifndef EE_BLUETOOTH_H_
#define EE_BLUETOOTH_H_

#include "ee.h"
#include "eeuart.h"
#include "constants.h"

/**
 * Each element returned by inquiry comprehends three
 * fields:
 *
 * [BT addr],[BT name],[COD]
 *
 * Inquiry results are stored in vector of this type.
 */

typedef struct inquiry_result_t_ {
	char addr[13];
	char name[17];
	char cod[7];
} inquiry_result_t;

/**
 * Initializes the UART to make Bluetooth available.
 *
 * \param baud Baudrate of Bluetooth device.
 * \param byteformat Bluetooth UART parameters.
 * \param mode Bluetooth UART flow control.
 */

int EE_bluetooth_init(EE_UINT32 baud,
		EE_UINT16 byteformat,
		EE_UINT16 mode);

/**
 * Brings Bluetooth module to Master mode.
 * \return 0 if something went wrong.
 */

int EE_bluetooth_set_master();

/**
 * Brings Bluetooth module to Slave mode.
 * \return 0 if something went wrong.
 */

int EE_bluetooth_set_slave();

/**
 * Brings Bluetooth module to Pairing mode.
 * \return 0 if something went wrong.
 */

int EE_bluetooth_set_pairing();

/**
 * Checks if Bluetooth module is alive.
 * \return 1 if Bluetooth module is alive.
 */

int EE_bluetooth_alive();

/**
 * Connects to the Bluetooth remote device.
 * \param remote_addr String containing remote
 * device's address to which establish connection. 
 */

int EE_bluetooth_connect(char * remote_addr);

/**
 * Sets authentication:
 *
 * 0: Open mode. With this mode, the module uses
 *   Bluetooth version 2.0 with NO encryption
 *   (open mode). This mode is useful for legacy
 *   devices that do not need security. This
 *   mode is the same as in firmware version 4.77.
 *
 * 1: SSP keyboard I/O mode (default). If this
 *   option is set, the remote host receives a
 *   prompt; reply yes to pair. For Android devices,
 *   the user is prompted with a 6-digit code and
 *   is asked to verify that the code matches on
 *   the module. The module always responds yes.
 *   Because the module cannot display a code,
 *   simply press OK or Yes on the remote device
 *   to authenticate.
 *
 * 2: SSP "just works" mode. This mode works with
 *   iOS device and newer PCs. You can use this
 *   mode with Droid devices if the application
 *   connects using unsecure mode (which was the
 *   default on Droid version 3.3). This mode also
 *   works with new PC stacks.
 *
 * 4: Pin code. Forces pin code mode authentication
 *   (Bluetooth version 2.0), which requires the
 *   host device to enter a pin code that matches
 *   the stored pin code. The functionality is
 *   similar to firmware version 4.77.
 *
 * Default value: 1
 *
 * @param value The desired authentication type.
 * @return 1 if everything worked fine.
 */

int EE_bluetooth_set_authentication(unsigned char value);

/**
 * Sets the Bluetooth module's name.
 * @param name String containing Bluetooth name
 *   to be assigned.
 * @return 1 if everything worked fine.
 */

int EE_bluetooth_set_name(char * name);

/**
 * Sets the Bluetooth module's PIN value
 * for remote device authentication.
 * \param pin String containing pin. Default
 *   value: "1234"
 * @return 1 if everything worked fine.
 */

int EE_bluetooth_set_pin(char * pin);

/**
 * Sends a string via Bluetooth
 * \param str String to be sent. The string
 * termination character will not be sent.
 */

void EE_bluetooth_sendS(char * str);

/**
 * Receives a char via Bluetooth. This function has
 * a timeout.
 * \return The character received via Bluetooth. If
 *   no data is received, then 0xFF value is returned.
 */

unsigned char EE_bluetooth_receive();

/**
 * Receives a char via Bluetooth. This function has
 * no timeout, so it can wait forever if no data is
 * transmitted.
 * \return The character received via Bluetooth.
 */
 
unsigned char EE_bluetooth_receive_no_timeout();

/**
 * Resets the device.
 * This function is needed to update some device
 * properties, like device name.
 * @return 1 if everything worked fine.
 */

int EE_bluetooth_reboot();

/**
 * Makes a Bluetooth inquiry, scanning for
 * other devices.
 * \param dest Containter in where results of the
 *   inquiry will be stored.
 * \return Number of devices found during the inquiry.
 */

int EE_bluetooth_inquiry(inquiry_result_t * dest);

/**
 * Acquires the mutual exclusion on the BT resource.
 * @return 1 if everything worked fine.
 */
 
void EE_bluetooth_acquire();

/**
 * Releases the mutual exclusion on the BT resource.
 */

void EE_bluetooth_release();

#endif /* EE_BLUETOOTH_H_ */
