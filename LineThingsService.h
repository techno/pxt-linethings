#ifndef BLUETOOTH_LINE_THINGS_SERVICE_H
#define BLUETOOTH_LINE_THINGS_SERVICE_H

#include "MicroBitConfig.h"
#include "ble/BLE.h"
#include "MicroBitThermometer.h"
#include "EventModel.h"

// UUIDs for our service and characteristics
extern const uint8_t  LineThingsPSDIServiceUUID[];
extern const uint8_t  LineThingsPSDICharacteristicUUID[];

/**
  * Class definition for the custom MicroBit Temperature Service.
  * Provides a BLE service to beam any temperature
  */
class LineThingsService
{
    public:

    /**
      * Constructor.
      * Create a representation of the LineThingsService
      * @param _ble The instance of a BLE device that we're running on.
      */
    LineThingsService(BLEDevice &_ble, const uint8_t *serviceUuid);

   private:

    // Bluetooth stack we're running on.
    BLEDevice           	&ble;

    // memory for our 8 bit temperature characteristic.
    BLEProtocol::AddressBytes_t psdiBuffer;

    // Handles to access each characteristic when they are held by Soft Device.
    GattAttribute::Handle_t psdiCharacteristicHandle;
};


#endif
