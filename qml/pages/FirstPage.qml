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

import QtQuick 2.0
import Sailfish.Silica 1.0

import harbour.filters 1.0

Page {
    id: page

    SilicaGridView {
        id: grid
        header: PageHeader { title: "Images" }

        cellWidth: width / 3
        cellHeight: width / 3

        anchors.fill: parent

        model: GalleryModel {
            id: galleryModel
        }

        delegate: Image {
            asynchronous: true
            // From org.nemomobile.thumbnailer
            source:  "image://nemoThumbnail/" + url
            sourceSize.width: grid.cellWidth
            sourceSize.height: grid.cellHeight

            MouseArea {
                anchors.fill: parent
                onClicked: pageStack.push(Qt.resolvedUrl("SecondPage.qml"),
                                          {source: url} )
            }
        }
        ScrollDecorator {}
    }

//    // To enable PullDownMenu, place our content in a SilicaFlickable
//    SilicaFlickable {
//        anchors.fill: parent

//        // PullDownMenu and PushUpMenu must be declared in SilicaFlickable, SilicaListView or SilicaGridView
//        PullDownMenu {
//            MenuItem {
//                text: qsTr("Show Page 2")
//                onClicked: pageStack.push(Qt.resolvedUrl("SecondPage.qml"))
//            }
//        }

//        // Tell SilicaFlickable the height of its content.
//        contentHeight: column.height

//        // Place our content in a Column.  The PageHeader is always placed at the top
//        // of the page, followed by our content.
//        Column {
//            id: column

//            width: page.width
//            spacing: Theme.paddingLarge
//            PageHeader {
//                title: qsTr("UI Template")
//            }
//            Label {
//                x: Theme.paddingLarge
//                text: qsTr("Hello Sailors")
//                color: Theme.secondaryHighlightColor
//                font.pixelSize: Theme.fontSizeExtraLarge
//            }
//        }
//    }
}


