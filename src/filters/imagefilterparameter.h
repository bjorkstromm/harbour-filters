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

#ifndef IMAGEFILTERPARAMETER_H
#define IMAGEFILTERPARAMETER_H

#include <QObject>

class ImageFilterParameter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(int min READ min NOTIFY minChanged)
    Q_PROPERTY(int max READ max NOTIFY maxChanged)
    Q_PROPERTY(int value READ value WRITE setValue NOTIFY valueChanged)

public:
    explicit ImageFilterParameter(QObject *parent = 0);
    ImageFilterParameter(const QString &name, int min, int max, QObject *parent = 0);

    QString name() const;
    void setName(const QString &name);

    int min() const;
    void setMin(int min);

    int max() const;
    void setMax(int max);

    int value() const;
    void setValue(int value);

signals:
    void nameChanged(QString);
    void minChanged(int);
    void maxChanged(int);
    void valueChanged(int);

public slots:

private:
    QString m_name;
    int m_min;
    int m_max;
    int m_value;

};

#endif // IMAGEFILTERPARAMETER_H
