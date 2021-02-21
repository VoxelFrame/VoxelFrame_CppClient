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
        void bodyNotCompleteRec(uint32_t, uint16_t);
        void bodyCompleteRec();
        static RecStatRecorder *getInstance();

    private:
        RecStats curState = RecStats_NoHead;
        /* data */
        uint32_t bodyLen;
        uint16_t msgId;
        RecStatRecorder(/* args */);
        ~RecStatRecorder();

        // public:
    };

}

#endif // __RECSTATRECORDER_H__