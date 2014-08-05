/*
  Copyright (c) 2014, Martin Björkström
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this
    list of conditions and the following disclaimer.

  * Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef FILTEREDIMAGE_H
#define FILTEREDIMAGE_H

#include <QQuickItem>
#include <QImage>

class AbstractImageFilter;

class FilteredImage : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(QImage image READ image NOTIFY imageChanged)
    Q_PROPERTY(bool isApplyingFilter READ isApplyingFilter NOTIFY isApplyingFilterChanged)
public:
    explicit FilteredImage(QQuickItem *parent = 0);

    QString source() const;
    void setSource(const QString &source);

    bool isApplyingFilter();

    QImage image() const;

    Q_INVOKABLE void applyFilter(AbstractImageFilter *filter);
    Q_INVOKABLE void reApplyFilter();
    Q_INVOKABLE void applyCurrentFilter();
    Q_INVOKABLE void saveImage();

    //virtual void paint(QPainter *painter);
    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *);

signals:
    void sourceChanged(QString source);
    void imageChanged(QImage image);
    void imageSaved(QString fileName);
    void isApplyingFilterChanged(bool);

public slots:

private slots:
    void filterApplied(const QImage &image);

private:
    void setIsApplyingFilter(bool value);

    AbstractImageFilter* m_filter;
    QImage m_filteredImage;
    QImage m_image;
    QString m_source;
    bool m_imageChanged;
    bool m_isApplyingFilter;
};

#endif // FILTEREDIMAGE_H
