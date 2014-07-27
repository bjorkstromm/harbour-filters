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

#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include <QRect>
#include <QGuiApplication>
#include <QQuickView>
#include <QQmlContext>
#include <QQmlEngine>

#include <sailfishapp.h>
#include <QScopedPointer>


#include "src/models/galleryitemmodel.h"
#include "src/models/filteredimage.h"
#include "src/models/filteredcoverimage.h"
#include "src/models/filterlistmodel.h"
#include "src/models/filterparameterlistmodel.h"

#include "src/3rdparty/nemo-qml-plugin-thumbnailer/src/nemothumbnailprovider.h"
#include "src/3rdparty/nemo-qml-plugin-thumbnailer/src/nemothumbnailitem.h"

int main(int argc, char *argv[])
{
    qmlRegisterType<GalleryItemModel>("harbour.filters", 1, 0, "GalleryModel");
    qmlRegisterType<FilteredImage>("harbour.filters", 1, 0, "FilteredImage");
    qmlRegisterType<FilteredCoverImage>("harbour.filters", 1, 0, "FilteredCoverImage");
    qmlRegisterType<FilterListModel>("harbour.filters", 1, 0, "FilterListModel");
    qmlRegisterType<FilterParameterListModel>("harbour.filters", 1, 0, "FilterParameterListModel");
    qmlRegisterType<NemoThumbnailItem>("harbour.filters.nemoThumbnail", 1, 0, "Thumbnail");

    QScopedPointer<QGuiApplication> app(SailfishApp::application(argc,argv));
    QScopedPointer<QQuickView> view(SailfishApp::createView());

    view->engine()->addImageProvider(QLatin1String("nemoThumbnail"), new NemoThumbnailProvider);

    if (!NemoThumbnailLoader::instance) {
        NemoThumbnailLoader *loader = new NemoThumbnailLoader;
        loader->start(QThread::IdlePriority);
        qAddPostRoutine(NemoThumbnailLoader::shutdown);
    }

    view->setSource(SailfishApp::pathTo("qml/harbour-filters.qml"));

    view->show();

    return app->exec();
}

