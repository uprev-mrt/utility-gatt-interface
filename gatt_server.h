/**
 * @file gatt_server.h
 * @author Jason Berger
 * @brief Abstract/Generic Gatt server.  
 * @version 0.1
 * @date 2020-02-21
 * 
 * 
 */

#ifndef GATT_SERVER_H_
#define GATT_SERVER_H_
#ifdef __cplusplus
extern "C"
{
#endif

#define MRT_GATT_PROP_NONE                           0x00
#define MRT_GATT_PROP_BROADCAST                      0x01
#define MRT_GATT_PROP_READ                           0x02
#define MRT_GATT_PROP_WRITE_WITHOUT_RESP             0x04
#define MRT_GATT_PROP_WRITE                          0x08
#define MRT_GATT_PROP_NOTIFY                         0x10
#define MRT_GATT_PROP_INDICATE                       0x20
#define MRT_GATT_PROP_SIGNED_WRITE                   0x40
#define MRT_GATT_PROP_EXT                            0x80

/* Includes ------------------------------------------------------------------*/
#define MRT_GATT_MODULE_ENABLED
#include "Platforms/Common/mrt_platform.h"


/* Exported types ------------------------------------------------------------*/



typedef enum{
    e16Bit,
    e128Bit
}uuid_type_e;

typedef enum{
    GATT_EVT_CHAR_NONE     = 0x00,
    GATT_EVT_CHAR_WRITE    = 0x01,
    GATT_EVT_CHAR_READ     = 0x02,
    GATT_EVT_NOTIFY_ENABLE = 0x04,
    GATT_EVT_NOTIFY_DISABLE = 0x08
}mrt_gatt_evt_type_e;

/* UUID struct */
typedef struct{
    union {
        uint16_t m16Bit;            //16bit uuid
        uint8_t m128Bit[16];        //128bit uuid
    };
    uuid_type_e mType;              //type 16bit or 128bit
} mrt_gatt_uuid_t;


/* Forward Declare for self referencing function pointers */
typedef struct mrt_gatt_svc_t mrt_gatt_svc_t;                             //forward declare for self referencing callback
typedef struct mrt_gatt_char_t mrt_gatt_char_t;                             //forward declare for self referencing callback


/* gatt Event struct*/
typedef struct{
    mrt_gatt_evt_type_e mType;   /*Type of event*/
    mrt_gatt_char_t* mChar;      /*Characteristic for event*/
    struct{
        uint8_t* data;          /*ptr to data for writes (or notify on client)*/
        int len;                /* len of data in bytes*/
    }mData;
} mrt_gatt_evt_t;

typedef mrt_status_t (*mrt_gatt_svc_callback)(mrt_gatt_svc_t* svc, mrt_gatt_evt_t* event); 
typedef mrt_status_t (*mrt_gatt_char_callback)(mrt_gatt_evt_t* event); 

/* gatt characteristic descriptor */
struct mrt_gatt_char_t{
    mrt_gatt_uuid_t mUuid;          //UUID of Characteristic
    uint16_t mSize;                 //size of Characteristic
    mrt_gatt_chr_handle_t mHandle;      //Handle of Characteristic
    uint8_t mProps;                 //Permissions of characteristic
    bool mNotificationsEnable;      //Indicates if Notifications are enabled in CCCD
    mrt_gatt_svc_t* mSvc;
    mrt_gatt_char_callback cbEvent; //characteristic event callback
};

/* gatt Service descriptor */
struct mrt_gatt_svc_t{
    mrt_gatt_uuid_t mUuid;          //UUID of Service
    mrt_gatt_svc_handle_t  mHandle;
    mrt_gatt_char_t** mChars;         //Array of characteristics   
    uint16_t mCharCount;            //Number of characterestics
    uint16_t mMaxCharCount;          //max number of characteristics
    mrt_gatt_svc_callback cbEvent;   //Service event callback
};

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
mrt_status_t gatt_init_svc(mrt_gatt_svc_t* svc, uuid_type_e uuidType, const uint8_t* arrUuid, uint16_t charCount, mrt_gatt_svc_callback cbEvent);
mrt_status_t gatt_init_char(mrt_gatt_svc_t* svc, mrt_gatt_char_t* chr, uuid_type_e uuidType, const uint8_t* arrUuid, uint16_t size, uint8_t props, mrt_gatt_char_callback cbEvent );


#ifdef __cplusplus
}
#endif
#endif /*GATT_SERVER_H_*/
