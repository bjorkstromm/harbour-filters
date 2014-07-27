#include "rgbswapfilter.h"

RGBSwapFilter::RGBSwapFilter(QObject *parent) :
    AbstractImageFilter(parent)
{
}

QString RGBSwapFilter::name() const
{
    return QLatin1String("RGB swap");
}

void RGBSwapFilter::applyFilter(const QImage &origin)
{
    emit filterApplied(origin.rgbSwapped());
}
