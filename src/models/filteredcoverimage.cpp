#include "filteredcoverimage.h"

#include <QPainter>

FilteredCoverImage::FilteredCoverImage(QQuickItem *parent) :
    QQuickPaintedItem(parent)
{
    connect(this,SIGNAL(imageChanged(QImage)),SLOT(update()));
}

void FilteredCoverImage::paint(QPainter *painter)
{
    QImage scaled;

    scaled = m_image.scaled(width(),height(),Qt::KeepAspectRatioByExpanding,Qt::SmoothTransformation);

    QRect rect = scaled.rect();
    rect.moveCenter(boundingRect().toAlignedRect().center());

    painter->drawImage(rect,scaled);
}
QImage FilteredCoverImage::image() const
{
    return m_image;
}

void FilteredCoverImage::setImage(const QImage &image)
{
    if(image != m_image)
    {
        m_image = image;
        emit imageChanged(image);
    }
}

