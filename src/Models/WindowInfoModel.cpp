#include "WindowInfoModel.h"
WindowInfoModel &WindowInfoModel::getInstance()
{
    static WindowInfoModel *wim;
    if (!wim)
    {
        wim = new WindowInfoModel();
    }
    return *wim;
}

WindowInfoModel::WindowInfoModel()
{
    Width = 800;
    Height = 600;
}
