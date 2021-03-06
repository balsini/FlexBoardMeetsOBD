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

#include "LCD.h"

/**
 * Inquiry result is a matrix of maximum 9 rows, where
 * each element is like:
 * <BT addr>,<BT name>,<COD>
 */

typedef struct inquiry_result_t_ {
	char addr[13];
	char name[17];
	char cod[7];
} inquiry_result_t;

/**
 * Initializes the UART to make Bluetooth available.
 * baud defines the UART channel
 * @param baud Bluetooth UART baud rate.
 * @param byteformat The UART configuragion for the Bluetooth
 * communication.
 * @param mode The UART flow control for the Bluetooth
 * communication.
 * @return 1 if everything worked fine.
 */

int EE_bluetooth_init(EE_UINT32 baud,
		EE_UINT16 byteformat,
		EE_UINT16 mode);

/**
 * Brings Bluetooth module to Master mode
 * @return 1 if everything worked fine.
 */

int EE_bluetooth_set_master();

/**
 * Brings Bluetooth module to Slave mode
 * @return 1 if everything worked fine.
 */

int EE_bluetooth_set_slave();

/**
 * Brings Bluetooth module to Pairing mode
 * @return 1 if everything worked fine.
 */

int EE_bluetooth_set_pairing();

/**
 * Checks if Bluetooth module is alive.
 * @return 1 if Bluetooth module is alive.
 */

int EE_bluetooth_alive();

/**
 * Connects to the Bluetooth remote device with
 * given address.
 * @param remote_addr The remote address to which
 * the connection will be established.
 * @return 1 if everything worked fine.
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
 * @param name Bluetooth module name chosen.
 * @return 1 if everything worked fine.
 */

int EE_bluetooth_set_name(char * name);

/**
 * Sets the Bluetooth module's PIN value
 * for remote device authentication.
 * Default value: "1234"
 * @param pin Bluetooth module pin chosen.
 * @return 1 if everything worked fine.
 */

int EE_bluetooth_set_pin(char * pin);

/**
 * Sends a string via Bluetooth.
 * @param string The string to be sent.
 */

void EE_bluetooth_sendS(char * string);

/**
 * Receives a char via Bluetooth.
 * This function returns after a timeout.
 * @return The char received.
 * @return 0xFF if timeout has expired.
 */

unsigned char EE_bluetooth_receive();

/**
 * Receives a char via Bluetooth.
 * This function can wait forever.
 * @return The char received.
 */

unsigned char EE_bluetooth_receive_no_timeout();

/**
 * Resets the device.
 * This function is needed to update some device
 * properties, like device name.
 */

int EE_bluetooth_reboot();

/**
 * Makes a Bluetooth inquiry, scanning for
 * other devices.
 * @param dest Results of the inquiry are stored in
 * this container.
 * @return The number of devices found.
 */

int EE_bluetooth_inquiry(inquiry_result_t * dest);

/**
 * Acquires mutual exclusion on the BT resource.
 */

void EE_bluetooth_acquire();

/**
 * Releases mutual exclusion on the BT resource.
 */

void EE_bluetooth_release();

#endif /* EE_BLUETOOTH_H_ */
