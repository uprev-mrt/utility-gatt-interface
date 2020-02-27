/**
 * @file gatt_server.h
 * @author Jason Berger
 * @brief Abstract/Generic Gatt server.  
 * @version 0.1
 * @date 2020-02-21
 * 
 * 
 */
#pragma once
#ifdef __cplusplus
extern "C"
{
#endif

#define GATT_PERM_R    0x01
#define GATT_PERM_W    0x02
#define GATT_PERM_N    0x04
#define GATT_PERM_RW   0x03
#define GATT_PERM_RWN  0x07

/* Includes ------------------------------------------------------------------*/
#include "Platforms/Common/mrt_platform.h"

/* Exported types ------------------------------------------------------------*/



typedef enum{
    e16Bit,
    e128Bit
}uuid_type_e;

//BLE characteristic definition
typedef struct mrt_ble_char_t mrt_ble_char_t;                             //forward declare for self referencing callback
typedef mrt_ble_char_t (*mrt_ble_char_t)(mrt_ble_char_t* svc); 

//UUID struct
typedef struct{
    union {
        uint16_t m16Bit;            //16bit uuid
        uint8_t m128Bit[16];        //128bit uuid
    };
    uuid_type_e mType;              //type 16bit or 128bit
} mrt_ble_uuid_t;

//Ble Service definition
typedef struct mrt_ble_svc_t mrt_ble_svc_t;                             //forward declare for self referencing callback
typedef mrt_status_t (*mrt_ble_svc_callback)(mrt_ble_svc_t* svc); 

typedef mrt_ble_char_t{
    mrt_ble_uuid_t mUuid;           //UUID of Characteristic
    uint16_t mSize;                 //size of Characteristic
    void* mHandle;                  //Handle of Characteristic
    uint8_t mPerm;                  //Permissions of characteristic
} ;


typedef mrt_ble_svc_t{
    mrt_ble_char_t* mChars;         //Array of characteristics   
    uint16_t mCharCount;            //Number of characterestics
    mrt_ble_svc_callback cbWrite;   //characteristic write callback
} ;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */


#ifdef __cplusplus
}
#endif
