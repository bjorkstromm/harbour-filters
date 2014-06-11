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

#include "imagefilterparameter.h"

ImageFilterParameter::ImageFilterParameter(QObject *parent) :
    QObject(parent)
{
}

ImageFilterParameter::ImageFilterParameter(const QString &name, int min, int max, QObject *parent) :
    QObject(parent)
{
    m_name = name;
    m_min = min;
    m_max = max;
}
QString ImageFilterParameter::name() const
{
    return m_name;
}

void ImageFilterParameter::setName(const QString &name)
{
    if(m_name != name)
    {
        m_name = name;
        emit nameChanged(m_name);
    }
}
int ImageFilterParameter::min() const
{
    return m_min;
}

void ImageFilterParameter::setMin(int min)
{
    if(m_min != min)
    {
        m_min = min;
        emit minChanged(m_min);
    }
}
int ImageFilterParameter::max() const
{
    return m_max;
}

void ImageFilterParameter::setMax(int max)
{
    if(m_max != max)
    {
        m_max = max;
        emit maxChanged(m_max);
    }
}
int ImageFilterParameter::value() const
{
    return m_value;
}

void ImageFilterParameter::setValue(int value)
{
    if(m_value != value)
    {
        m_value = value;
        emit valueChanged(m_value);
    }
}




