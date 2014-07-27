#include "negativefilter.h"

NegativeFilter::NegativeFilter(QObject *parent) :
    AbstractImageFilter(parent)
{
}

QString NegativeFilter::name() const
{
    return QLatin1String("Negative");
}

void NegativeFilter::applyFilter(const QImage &origin)
{
    QImage newImage(origin);

    newImage.invertPixels();

    emit filterApplied(newImage);
}
