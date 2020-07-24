/**
 * @file gatt_server.c
 * @author Jason Berger
 * @brief Abstract/Generic Gatt server.  
 * @version 0.1
 * @date 2020-02-21
 * 
 * 
 */


/* Includes ------------------------------------------------------------------*/
#include <stdlib.h>
#include <string.h>
#include "gatt_server.h"


mrt_status_t gatt_init_svc(mrt_gatt_svc_t* svc, uuid_type_e uuidType, const uint8_t* arrUuid, uint16_t charCount, mrt_gatt_svc_callback cbEvent)
{
     /* Set UUID */
    svc->mUuid.mType = uuidType;
    if(uuidType == e16Bit)
    {   
        memcpy((uint8_t*)&svc->mUuid.m16Bit, arrUuid, 2);
    }
    else
    {
        memcpy((uint8_t*)&svc->mUuid.m128Bit, arrUuid, 16);
    }

    /* malloc memory for characteristic descriptors */
    svc->mCharCount = 0;
    svc->mMaxCharCount = charCount;
    svc->mChars = (mrt_gatt_char_t**)malloc(sizeof(mrt_gatt_char_t*) * charCount);
    svc->cbEvent = cbEvent;
    svc->mSecurity = MRT_GATT_SECURITY_NONE;    //Default to no security
    

    return MRT_STATUS_OK;
}

mrt_status_t gatt_init_char(mrt_gatt_svc_t* svc, mrt_gatt_char_t* chr, uuid_type_e uuidType, const uint8_t* arrUuid, uint16_t size, uint8_t props, mrt_gatt_char_callback cbEvent  )
{
    if(svc->mCharCount < svc->mMaxCharCount)
    {
        /* Set UUID */
        chr->mUuid.mType = uuidType;
        if(uuidType == e16Bit)
        {   
            memcpy((uint8_t*)&chr->mUuid.m16Bit, arrUuid, 2);
        }
        else
        {
            memcpy((uint8_t*)&chr->mUuid.m128Bit, arrUuid, 16);
        }

        chr->mSize = size;
        chr->mSecurity = MRT_GATT_SECURITY_NONE;    //Default to no security
        chr->mProps = props;
        chr->cbEvent = cbEvent;
        chr->mNotificationsEnable = false;
        chr->mSvc = svc;
        svc->mChars[svc->mCharCount++] = chr;   /*Add ptr to list for looping through*/
    }
    else 
    {
        return MRT_STATUS_ERROR; //tried to add more characteristics than max
    }


    return MRT_STATUS_OK;
}



