#include "negativefilter.h"

NegativeFilter::NegativeFilter(QObject *parent) :
    AbstractImageFilter(parent)
{
}

QString NegativeFilter::name() const
{
    return "Negative";
}

void NegativeFilter::applyFilter(const QImage &origin)
{
    QImage newImage(origin);

    newImage.invertPixels();

    emit filterApplied(newImage);
}
