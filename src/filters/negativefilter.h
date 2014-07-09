#ifndef NEGATIVEFILTER_H
#define NEGATIVEFILTER_H

#include "abstractimagefilter.h"

class NegativeFilter : public AbstractImageFilter
{
    Q_OBJECT
public:
    explicit NegativeFilter(QObject *parent = 0);

    QString name() const;
    void applyFilter(const QImage &origin);

signals:

public slots:

};

#endif // NEGATIVEFILTER_H
