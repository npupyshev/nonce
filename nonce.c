#include <stdio.h>
#include <sys/types.h>
#include <CoreFoundation/CoreFoundation.h>

#define AM_MSG_CONNECTED 0

typedef void *AMRestorableDeviceRef;
extern CFDataRef AMRestorableDeviceCopyApNonce(AMRestorableDeviceRef device);
extern int AMRestorableDeviceRegisterForNotifications(void (*callback)(AMRestorableDeviceRef device, int messageType, void *unknown), void *unknown, CFErrorRef *error);
extern uint64_t AMRestorableDeviceGetECID(AMRestorableDeviceRef device);

void callback(AMRestorableDeviceRef device, int messageType, void *unknown) {
	if (messageType == AM_MSG_CONNECTED) {
		uint8_t *nonce = (uint8_t *)CFDataGetBytePtr(AMRestorableDeviceCopyApNonce(device));
		uint64_t ecid = AMRestorableDeviceGetECID(device);
		printf("ECID: %016llx NONCE: ", ecid);
		for (int i = 0; i < 20; i++) printf("%02x", *(nonce + i));
		puts("");
	}
}

int main(int argc, char *argv[]) {
	CFErrorRef error;
	if (AMRestorableDeviceRegisterForNotifications(&callback, NULL, &error) != 0) {
		CFRunLoopRun();
		return 0;
	} else {
		puts("Failed to register for device notifications!");
		return -1;
	}
}
