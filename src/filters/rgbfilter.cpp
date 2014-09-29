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

#include "rgbfilter.h"
#include "imagefilterparameter.h"

class RgbFilterWorker : public AbstractImageFilterWorker
{
public:
    RgbFilterWorker(int red, int green, int blue)
    {
        m_red = red;
        m_green = green;
        m_blue = blue;
    }

    void doWork(const QImage &origin) {
        QImage newImage(origin);
        QRgb *bits = (QRgb *)newImage.bits();
        int pixels = newImage.height() * newImage.width();

        for(int i = 0; i<pixels; i++){
            bits[i] = qRgb(qBound(0, qRed(bits[i]) + m_red, 255),
                           qBound(0, qGreen(bits[i]) + m_green, 255),
                           qBound(0, qBlue(bits[i]) + m_blue, 255));
        }

        emit resultReady(newImage);
    }

private:
    int m_red;
    int m_green;
    int m_blue;
};


RGBFilter::RGBFilter(QObject *parent) :
    AbstractImageFilter(parent)
{
    m_params << new ImageFilterParameter("red", -100, 100, this)
             << new ImageFilterParameter("green", -100, 100, this)
             << new ImageFilterParameter("blue", -100, 100, this);

    resetParameters();
}

QString RGBFilter::name() const
{
    return QLatin1String("RGB");
}

QList<ImageFilterParameter *> RGBFilter::parameterList()
{
    return m_params;
}

void RGBFilter::resetParameters()
{
    m_params[0]->setValue(0);
    m_params[1]->setValue(0);
    m_params[2]->setValue(0);
}

AbstractImageFilterWorker *RGBFilter::createWorker()
{
    return new RgbFilterWorker(m_params[0]->value(),
                               m_params[1]->value(),
                               m_params[2]->value());
}
