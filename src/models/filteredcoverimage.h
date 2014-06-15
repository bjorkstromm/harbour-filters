#ifndef FILTEREDCOVERIMAGE_H
#define FILTEREDCOVERIMAGE_H

#include <QQuickPaintedItem>
#include <QImage>

class FilteredCoverImage : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QImage image READ image WRITE setImage NOTIFY imageChanged)
public:
    explicit FilteredCoverImage(QQuickItem *parent = 0);

    virtual void paint(QPainter *painter);

    QImage image() const;
    void setImage(const QImage &image);

signals:
    void imageChanged(QImage);

public slots:

private:
    QImage m_image;

};

#endif // FILTEREDCOVERIMAGE_H
