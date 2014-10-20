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

#include "framefilter.h"
#include "imagefilterparameter.h"

#include <QPainter>

class FrameFilterWorker : public AbstractImageFilterWorker
{
public:
    FrameFilterWorker(int horizontal, int vertical)
    {
        m_horizontal = horizontal / 200.0;
        m_vertical = vertical / 200.0;
    }

    void doWork(const QImage &origin) {
        QImage newImage(origin);

        QPainter painter;

        QLinearGradient gradientLeft(0,0,(qreal)newImage.width(),0);
        gradientLeft.setColorAt(0, Qt::black);
        gradientLeft.setColorAt(m_horizontal, Qt::transparent);

        QLinearGradient gradientRight((qreal)newImage.width(),0,0,0);
        gradientRight.setColorAt(0, Qt::black);
        gradientRight.setColorAt(m_horizontal, Qt::transparent);

        QLinearGradient gradientTop(0,0,0,(qreal)newImage.height());
        gradientTop.setColorAt(0, Qt::black);
        gradientTop.setColorAt(m_vertical, Qt::transparent);

        QLinearGradient gradientBottom(0,(qreal)newImage.height(),0,0);
        gradientBottom.setColorAt(0, Qt::black);
        gradientBottom.setColorAt(m_vertical, Qt::transparent);

        painter.begin(&newImage);
        painter.fillRect(0,0,newImage.width(),newImage.height(),gradientLeft);
        painter.fillRect(0,0,newImage.width(),newImage.height(),gradientRight);
        painter.fillRect(0,0,newImage.width(),newImage.height(),gradientTop);
        painter.fillRect(0,0,newImage.width(),newImage.height(),gradientBottom);
        painter.end();

        emit resultReady(newImage);
    }

private:
    qreal m_horizontal;
    qreal m_vertical;
};

FrameFilter::FrameFilter(QObject *parent) :
    AbstractImageFilter(parent)
{
    m_params << new ImageFilterParameter("Horizontal", 0, 100, this)
             << new ImageFilterParameter("Vertical", 0, 100, this);

    resetParameters();
}

QString FrameFilter::name() const
{
    return QLatin1String("Frame");
}

AbstractImageFilterWorker *FrameFilter::createWorker()
{
    return new FrameFilterWorker(m_params[0]->value(), m_params[1]->value());
}

QList<ImageFilterParameter *> FrameFilter::parameterList()
{
    return m_params;
}

void FrameFilter::resetParameters()
{
    m_params[0]->setValue(0);
    m_params[1]->setValue(0);
}
