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

#include "brightnessfilter.h"

#include "imagefilterparameter.h"

class BrightnessFilterWorker : public AbstractImageFilterWorker
{
public:
    BrightnessFilterWorker(int brightness, int contrast)
    {
        m_brightness = brightness;
        m_contrast = (contrast + 100) / 100.0;
    }

    void doWork(const QImage &origin) {
        QImage newImage(origin);
        QRgb *bits = (QRgb *)newImage.bits();
        int contrastLookup[256];
        int pixel = 0;
        int width = newImage.width();
        int height = newImage.height();

        for(int i = 0; i < 256; i++)
        {
            contrastLookup[i] = qBound(0,(int)((((((qreal)i/255.0)-0.5)*m_contrast)+0.5)*255),255);
        }

        for(int y = 0; y<height; y++){
            for(int x = 0; x<width; x++)
            {
                pixel = (y*width)+x;
                bits[pixel] = qRgb(qBound(0, contrastLookup[qRed(bits[pixel])] + m_brightness, 255),
                                      qBound(0, contrastLookup[qGreen(bits[pixel])] + m_brightness, 255),
                                      qBound(0, contrastLookup[qBlue(bits[pixel])] + m_brightness, 255));
            }
        }

        emit resultReady(newImage);
    }

private:
    int m_brightness;
    qreal m_contrast;
};

BrightnessFilter::BrightnessFilter(QObject *parent) :
    AbstractImageFilter(parent)
{
    m_params << new ImageFilterParameter("Brightness", -100, 100, this)
             << new ImageFilterParameter("Contrast", -100, 100, this);

    resetParameters();
}

QString BrightnessFilter::name() const
{
    return QLatin1String("Brightness");
}

AbstractImageFilterWorker *BrightnessFilter::createWorker()
{
    return new BrightnessFilterWorker(m_params[0]->value(), m_params[1]->value());
}

QList<ImageFilterParameter *> BrightnessFilter::parameterList()
{
    return m_params;
}

void BrightnessFilter::resetParameters()
{
    m_params[0]->setValue(0);
    m_params[1]->setValue(0);
}
