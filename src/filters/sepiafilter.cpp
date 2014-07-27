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

#include "sepiafilter.h"

SepiaFilter::SepiaFilter(QObject *parent) :
    AbstractImageFilter(parent)
{
}

QString SepiaFilter::name() const
{
    return QLatin1String("Sepia");
}

void SepiaFilter::applyFilter(const QImage &origin)
{
    QImage newImage(origin.width(), origin.height(), QImage::Format_ARGB32);

    QRgb * line;

    for(int y = 0; y<newImage.height(); y++){
        line = (QRgb *)origin.scanLine(y);

        for(int x = 0; x<newImage.width(); x++){
            int r = qBound(0,(int)((qRed(line[x]) * .393) + (qGreen(line[x]) *.769) + (qRed(line[x]) * .189)),255);
            int g = qBound(0,(int)((qRed(line[x]) * .349) + (qGreen(line[x]) *.686) + (qRed(line[x]) * .168)),255);
            int b = qBound(0,(int)((qRed(line[x]) * .272) + (qGreen(line[x]) *.534) + (qRed(line[x]) * .131)),255);

            newImage.setPixel(x,y, qRgb(r, g, b));
        }
    }

    emit filterApplied(newImage);
}
