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

#include "hslfilter.h"

#include "imagefilterparameter.h"

#include <QColor>
#include <QDebug>

/* Algorithma from Paul Bourke
 * http://paulbourke.net/libraries/paulslib.h
 * http://paulbourke.net/libraries/paulslib.c
 */
extern "C" {

    #ifndef MIN
    #define MIN(x,y) (x < y ? x : y)
    #endif
    #ifndef MAX
    #define MAX(x,y) (x > y ? x : y)
    #endif

    typedef struct {
       double r,g,b;
    } COLOUR;

    typedef struct {
        double h,s,l;
    } HSL;

    /*
       Calculate HSL from RGB
       Hue is in degrees
       Lightness is betweeen 0 and 1
       Saturation is between 0 and 1
    */
    HSL RGB2HSL(COLOUR c1)
    {
       double themin,themax,delta;
       HSL c2;

       themin = MIN(c1.r,MIN(c1.g,c1.b));
       themax = MAX(c1.r,MAX(c1.g,c1.b));
       delta = themax - themin;
       c2.l = (themin + themax) / 2;
       c2.s = 0;
       if (c2.l > 0 && c2.l < 1)
          c2.s = delta / (c2.l < 0.5 ? (2*c2.l) : (2-2*c2.l));
       c2.h = 0;
       if (delta > 0) {
          if (themax == c1.r && themax != c1.g)
             c2.h += (c1.g - c1.b) / delta;
          if (themax == c1.g && themax != c1.b)
             c2.h += (2 + (c1.b - c1.r) / delta);
          if (themax == c1.b && themax != c1.r)
             c2.h += (4 + (c1.r - c1.g) / delta);
          c2.h *= 60;
            if (c2.h < 0)
                c2.h += 360;
       }
       return(c2);
    }

    /*
       Calculate RGB from HSL, reverse of RGB2HSL()
       Hue is in degrees
       Lightness is between 0 and 1
       Saturation is between 0 and 1
    */
    COLOUR HSL2RGB(HSL c1)
    {
       COLOUR c2,sat,ctmp;

       while (c1.h < 0)
          c1.h += 360;
       while (c1.h > 360)
          c1.h -= 360;

       if (c1.h < 120) {
          sat.r = (120 - c1.h) / 60.0;
          sat.g = c1.h / 60.0;
          sat.b = 0;
       } else if (c1.h < 240) {
          sat.r = 0;
          sat.g = (240 - c1.h) / 60.0;
          sat.b = (c1.h - 120) / 60.0;
       } else {
          sat.r = (c1.h - 240) / 60.0;
          sat.g = 0;
          sat.b = (360 - c1.h) / 60.0;
       }
       sat.r = MIN(sat.r,1);
       sat.g = MIN(sat.g,1);
       sat.b = MIN(sat.b,1);

       ctmp.r = 2 * c1.s * sat.r + (1 - c1.s);
       ctmp.g = 2 * c1.s * sat.g + (1 - c1.s);
       ctmp.b = 2 * c1.s * sat.b + (1 - c1.s);

       if (c1.l < 0.5) {
          c2.r = c1.l * ctmp.r;
          c2.g = c1.l * ctmp.g;
          c2.b = c1.l * ctmp.b;
       } else {
          c2.r = (1 - c1.l) * ctmp.r + 2 * c1.l - 1;
          c2.g = (1 - c1.l) * ctmp.g + 2 * c1.l - 1;
          c2.b = (1 - c1.l) * ctmp.b + 2 * c1.l - 1;
       }

       return(c2);
    }
}

class HslFilterWorker : public AbstractImageFilterWorker
{
public:
    HslFilterWorker(int hue, int saturation, int lightness)
    {
        m_hue = (double)hue;
        m_saturation = ((saturation + 100) / 100.0) - 1.0;
        m_lightness = ((lightness + 100) / 400.0) - 0.25;
    }

    void doWork(const QImage &origin) {
        QImage newImage(origin.width(), origin.height(), QImage::Format_ARGB32);

        const QRgb * line;
        COLOUR rgb;
        HSL hsl;

        for(int y = 0; y<newImage.height(); y++){
            line = (QRgb *)origin.constScanLine(y);

            for(int x = 0; x<newImage.width(); x++)
            {
                rgb = {qRed(line[x]) / 255.0,
                              qGreen(line[x]) / 255.0,
                              qBlue(line[x]) / 255.0 };

                hsl = RGB2HSL(rgb);

                hsl.h = hsl.h + m_hue;
                hsl.s = qBound(0.0,hsl.s+m_saturation,1.0);
                hsl.l = qBound(0.0,hsl.l+m_lightness,1.0);

                rgb = HSL2RGB(hsl);

                newImage.setPixel(x,y,qRgb(rgb.r * 255,rgb.g * 255,rgb.b * 255));
            }
        }

        emit resultReady(newImage);
    }

private:
    int m_hue;
    double m_saturation;
    double m_lightness;
};

HSLFilter::HSLFilter(QObject *parent) :
    AbstractImageFilter(parent)
{
    m_params << new ImageFilterParameter("hue", -180, 180, this)
             << new ImageFilterParameter("saturation", -100, 100, this)
             << new ImageFilterParameter("lightness", -100, 100, this);

    m_params[0]->setValue(0);
    m_params[1]->setValue(0);
    m_params[2]->setValue(0);
}

QString HSLFilter::name() const
{
    return QLatin1String("HSL");
}

QList<ImageFilterParameter *> HSLFilter::parameterList()
{
    return m_params;
}

AbstractImageFilterWorker *HSLFilter::createWorker()
{
    qDebug() << m_params[0]->value() << " " << m_params[1]->value() << " " << m_params[2]->value();
    return new HslFilterWorker(m_params[0]->value(),
                               m_params[1]->value(),
                               m_params[2]->value());
}
