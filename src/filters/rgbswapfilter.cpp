#include "rgbswapfilter.h"

RGBSwapFilter::RGBSwapFilter(QObject *parent) :
    AbstractImageFilter(parent)
{
}

QString RGBSwapFilter::name() const
{
    return "RGB swap";
}

void RGBSwapFilter::applyFilter(const QImage &origin)
{
    emit filterApplied(origin.rgbSwapped());
}
