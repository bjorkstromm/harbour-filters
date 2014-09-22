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

#include "greyscalefilter.h"

class GreyscaleFilterWorker : public AbstractImageFilterWorker
{
public:
    void doWork(const QImage &origin) {
        QImage newImage(origin);
        QRgb *bits = (QRgb *)newImage.bits();
        int pixel = 0;
        int width = newImage.width();
        int height = newImage.height();
        int average = 0;

        for(int y = 0; y<height; y++){
            for(int x = 0; x<width; x++){
                pixel = (y*width)+x;
                average = (qRed(bits[pixel]) + qGreen(bits[pixel]) + qRed(bits[pixel]))/3;
                bits[pixel] = qRgb(average, average, average);
            }
        }

        emit resultReady(newImage);
    }
};

GreyscaleFilter::GreyscaleFilter(QObject *parent) :
    AbstractImageFilter(parent)
{
}

QString GreyscaleFilter::name() const
{
    return QLatin1String("Greyscale");
}

AbstractImageFilterWorker *GreyscaleFilter::createWorker()
{
    return new GreyscaleFilterWorker();
}
