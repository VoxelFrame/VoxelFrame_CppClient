#include "RecStatRecorder.h"
namespace NetSys
{

    RecStatRecorder::RecStatRecorder(/* args */)
    {
    }

    RecStatRecorder::~RecStatRecorder()
    {
    }

    void RecStatRecorder::bodyNotCompleteRec(uint32_t, uint16_t)
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