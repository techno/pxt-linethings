/**
  * Class definition for the custom MicroBit Temperature Service.
  * Provides a BLE service to remotely read the silicon temperature of the nRF51822.
  */
#include "MicroBitConfig.h"
#include "ble/UUID.h"

#include "LineThingsService.h"

/**
  * Constructor.
  * Create a representation of the TemperatureService
  * @param _ble The instance of a BLE device that we're running on.
  */
LineThingsService::LineThingsService(BLEDevice &_ble, const uint8_t *serviceUuid) :
        ble(_ble)
{
    // Create the data structures that represent each of our characteristics in Soft Device.
    GattCharacteristic  psdiCharacteristic(LineThingsPSDICharacteristicUUID, (uint8_t *)psdiBuffer, 0,
    sizeof(psdiBuffer), GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_READ);

    // Initialise our characteristic values.
    BLEProtocol::AddressType_t type;
    ble.getAddress(&type, psdiBuffer);

    // Set default security requirements
    psdiCharacteristic.requireSecurity(SecurityManager::MICROBIT_BLE_SECURITY_LEVEL);

    GattCharacteristic *characteristics[] = { &psdiCharacteristic };
    GattService         service(LineThingsPSDICharacteristicUUID, characteristics, sizeof(characteristics) / sizeof(GattCharacteristic *));

    ble.addService(service);

    psdiCharacteristicHandle = psdiCharacteristic.getValueHandle();

    ble.gattServer().write(psdiCharacteristicHandle,(uint8_t *)psdiBuffer, sizeof(psdiBuffer));

    // Start advertising user service UUID
    ble.accumulateAdvertisingPayload(GapAdvertisingData::INCOMPLETE_LIST_128BIT_SERVICE_IDS, serviceUuid, sizeof(serviceUuid));
}

const uint8_t  LineThingsPSDIServiceUUID[] = {
    0xe6, 0x25, 0x60, 0x1e, 0x9e, 0x55, 0x45, 0x97, 0xa5, 0x98, 0x76, 0x01, 0x8a, 0x0d, 0x29, 0x3d
};

const uint8_t  LineThingsPSDICharacteristicUUID[] = {
    0x26, 0xe2, 0xb1, 0x2b, 0x85, 0xf0, 0x4f, 0x3f, 0x9f, 0xdd, 0x91, 0xd1, 0x14, 0x27, 0x0e, 0x6e
};
