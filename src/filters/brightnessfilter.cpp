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

BrightnessFilter::BrightnessFilter(QObject *parent) :
    AbstractImageFilter(parent)
{
    m_params << new ImageFilterParameter("Brightness", -100, 100, this)
             << new ImageFilterParameter("Contrast", -100, 100, this);

    m_params[0]->setValue(0);
    m_params[1]->setValue(0);
}

QString BrightnessFilter::name() const
{
    return QLatin1String("Brightness");
}

QList<ImageFilterParameter *> BrightnessFilter::parameterList()
{
    return m_params;
}

void BrightnessFilter::applyFilter(const QImage &origin)
{
    int contrastLookup[256];
    qreal contrast = (m_params[1]->value() + 100) / 100.0;

    for(int i = 0; i < 256; i++)
    {
        contrastLookup[i] = qBound(0,(int)((((((qreal)i/255.0)-0.5)*contrast)+0.5)*255),255);
    }

    int brightness = m_params[0]->value();

    QImage newImage(origin.width(), origin.height(), QImage::Format_ARGB32);

    QRgb * line;

    for(int y = 0; y<newImage.height(); y++){
        line = (QRgb *)origin.scanLine(y);

        for(int x = 0; x<newImage.width(); x++)
        {
            newImage.setPixel(x,y,qRgb(
                                   qBound(0, contrastLookup[qRed(line[x])] + brightness, 255),
                                   qBound(0, contrastLookup[qGreen(line[x])] + brightness, 255),
                                   qBound(0, contrastLookup[qBlue(line[x])] + brightness, 255)));
        }
    }

    emit filterApplied(newImage);
}
