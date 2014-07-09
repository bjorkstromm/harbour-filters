#ifndef RGBSWAPFILTER_H
#define RGBSWAPFILTER_H

#include "abstractimagefilter.h"

class RGBSwapFilter : public AbstractImageFilter
{
    Q_OBJECT
public:
    explicit RGBSwapFilter(QObject *parent = 0);

    QString name() const;
    void applyFilter(const QImage &origin);

signals:

public slots:

};

#endif // RGBSWAPFILTER_H
