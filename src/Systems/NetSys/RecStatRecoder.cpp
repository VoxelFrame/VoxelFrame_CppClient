#include "RecStatRecorder.h"
namespace NetSys
{

    RecStatRecorder::RecStatRecorder(/* args */)
    {

    }

    RecStatRecorder::~RecStatRecorder()
    {
    }

    void RecStatRecorder::bodyNotCompleteRec(uint32_t bodyLen, uint16_t msgId)
    {
    }

    void RecStatRecorder::bodyCompleteRec()
    {
    }
    RecStatRecorder *RecStatRecorder::getInstance()
    {
        static RecStatRecorder rsr;
        return &rsr;
    }
}