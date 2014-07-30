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

class Worker : public QObject
{
    Q_OBJECT

public slots:
    void doWork(const QImage &origin) {
        QImage newImage(origin.width(), origin.height(), QImage::Format_ARGB32);

        QRgb * line;

        for(int y = 0; y<newImage.height(); y++){
            line = (QRgb *)origin.scanLine(y);

            for(int x = 0; x<newImage.width(); x++){
                int average = (qRed(line[x]) + qGreen(line[x]) + qRed(line[x]))/3;
                newImage.setPixel(x,y, qRgb(average, average, average));
            }
        }

        emit resultReady(newImage);
    }

signals:
    void resultReady(const QImage &image);
};

GreyscaleFilter::GreyscaleFilter(QObject *parent) :
    AbstractImageFilter(parent)
{
}

GreyscaleFilter::~GreyscaleFilter()
{
    workerThread.quit();
    workerThread.wait();
}

QString GreyscaleFilter::name() const
{
    return QLatin1String("Greyscale");
}

void GreyscaleFilter::applyFilter(const QImage &origin)
{
    Worker *worker = new Worker;
    worker->moveToThread(&workerThread);

    connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
    //connect(&workerThread, &QThread::started, worker, &Worker::doWork);
    connect(worker, &Worker::resultReady, this, &GreyscaleFilter::handleResults);

    workerThread.start();

    QMetaObject::invokeMethod(worker,"doWork",Qt::QueuedConnection,Q_ARG(QImage, origin));
    //worker->doWork(origin);
}

void GreyscaleFilter::handleResults(const QImage &image)
{
    emit filterApplied(image);
}

#include "greyscalefilter.moc"
