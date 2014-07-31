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

#include "abstractimagefilter.h"
#include "imagefilterparameter.h"

#include <QThread>

AbstractImageFilter::AbstractImageFilter(QObject *parent) :
    QObject(parent)
{
}

QList<ImageFilterParameter *> AbstractImageFilter::parameterList()
{
    return QList<ImageFilterParameter *>();
}

void AbstractImageFilter::applyFilter(const QImage &origin)
{
    AbstractImageFilterWorker *worker = createWorker();

    if(worker)
    {
        QThread *workerThread = new QThread(this);
        worker->moveToThread(workerThread);

        connect(workerThread, SIGNAL(finished()), worker, SLOT(deleteLater()));
        connect(worker, SIGNAL(resultReady(QImage)), this, SLOT(handleResults(QImage)));

        workerThread->start();
        QMetaObject::invokeMethod(worker,"doWork",Qt::QueuedConnection,Q_ARG(QImage, origin));
    }
    else
    {
        emit filterApplied(origin);
    }
}

AbstractImageFilterWorker *AbstractImageFilter::createWorker()
{
    return 0;
}

void AbstractImageFilter::handleResults(const QImage &image)
{
    emit filterApplied(image);

    QThread *thread = sender()->thread();
    thread->quit();
    thread->wait();
    thread->deleteLater();
}
