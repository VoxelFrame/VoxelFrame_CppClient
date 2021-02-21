#ifndef __RECSTATRECORDER_H__
#define __RECSTATRECORDER_H__

#include "stdint.h"

namespace NetSys
{
    class RecStatRecorder
    {
    public:
        enum RecStats
        {
            RecStats_ReceivedHead,
            RecStats_NoHead
        };

    private:
        RecStats curState;
        /* data */
        uint32_t bodyLen;
        uint16_t msgId;
        RecStatRecorder(/* args */);
        ~RecStatRecorder();

    public:
        void bodyNotCompleteRec(uint32_t, uint16_t);
        void bodyCompleteRec();
        RecStatRecorder *getInstance();
    };

}

#endif // __RECSTATRECORDER_H__