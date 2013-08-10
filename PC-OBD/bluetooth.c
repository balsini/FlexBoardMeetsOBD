/*
 * bluetooth.c
 *
 *  Created on: Aug 10, 2013
 *      Author: alessio
 */

#include "bluetooth.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>

inquiry_info * ii = NULL;
int max_rsp, num_rsp;
int dev_id, sock, len, flags;
int status; // of the connection
int my_socket; // socket
int connectId;
char addr[19] = { 0 };
char name[248] = { 0 };
struct sockaddr_rc remote_addr = {0};
char buffer;

char EE_bluetooth_receive()
{
	return EE_bluetooth_receive_no_timeout();
}

char EE_bluetooth_receive_no_timeout()
{
	char buffer;
	read(my_socket, (void *)&buffer, 1);
	return buffer;
}

int EE_bluetooth_sendS(char * str)
{
	int status;
	status = write(my_socket, str, strlen(str)+1);
	return status;
}

void EE_bluetooth_init()
{
	printf("Searching device and opening socket\n");
	dev_id = hci_get_route(NULL);
	sock = hci_open_dev( dev_id );
	if (dev_id < 0 || sock < 0) {
		printf("error opening socket\n");
		exit(1);
	}
	my_socket = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

	len  = 8;
	max_rsp = 255;
	flags = IREQ_CACHE_FLUSH;
	ii = (inquiry_info*)malloc(max_rsp * sizeof(inquiry_info));
}

void EE_bluetooth_inquiry()
{
	int i;

	printf("Inquiry\n");
	num_rsp = hci_inquiry(dev_id, len, max_rsp, NULL, &ii, flags);
	if( num_rsp < 0 ) printf("hci_inquiry");

	for (i = 0; i < num_rsp; i++) {
		ba2str(&(ii+i)->bdaddr, addr);
		memset(name, 0, sizeof(name));
		if (hci_read_remote_name(sock, &(ii+i)->bdaddr, sizeof(name),
				name, 0) < 0)
			strcpy(name, "[unknown]");
		printf("%d) %s  %s\n", i, addr, name);
	}
}

void EE_bluetooth_connect()
{
	if (num_rsp > 1) {
		do {
			printf("Connect to? ");
			scanf("%d", &connectId);
		} while (!(connectId < num_rsp && connectId >= 0));
	} else {
		connectId = 0;
	}

	// set the connection parameters (who to connect to)
	ba2str(&(ii+connectId)->bdaddr, addr);
	remote_addr.rc_family = AF_BLUETOOTH;
	remote_addr.rc_channel = (uint8_t) 1;
	str2ba(addr, &remote_addr.rc_bdaddr);

	printf("Connecting...\n");

	status = connect(my_socket, (struct sockaddr *)&remote_addr, sizeof(remote_addr));
}

void EE_bluetooth_free()
{
	free(ii);
	close(my_socket);
	close(sock);
}
