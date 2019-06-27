#include "pxt.h"
#include "LineThingsService.h"

//% color="#00c300" weight=100 icon="\uf294" block="LINE Things"
namespace linethings {
    LineThingsService* _pService = NULL;

    void HexStringToBytes(StringData *strData, uint8_t *data) {
        ManagedString m(strData);
        int16_t len = m.length();
        for (int16_t i=0; i<len; i+=2) {
            unsigned int x;
            
            sscanf(m.substring(i,2).toCharArray(), "%02x", &x);
            data[i/2] = (uint8_t) x;
        }
    }

    /**
    * Starts a LINE Things service.
    */
    //% blockId=linethings_start block="LINE Things Service UUID %serviceUuID"
    void start(StringData *serviceUuid) {
        if (NULL != _pService) return;

        uint8_t serviceUuidBytes[16];
        HexStringToBytes(serviceUuid, serviceUuidBytes);

        _pService = new LineThingsService(*uBit.ble, serviceUuidBytes);
    }
}
