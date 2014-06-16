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
    id: imagePage
    //allowedOrientations: Orientation.All
    property alias source: filteredImage.source

    DockedPanel {
        id: imageSavedPanel

        property string filename

        width: parent.width
        //height: Theme.itemSizeExtraLarge + Theme.paddingLarge

        dock: Dock.Bottom
        open: false

        Text {
            x: Theme.paddingLarge
            text: imageSavedPanel.filename + " saved"
            color: Theme.primaryColor
            font.pixelSize: Theme.fontSizeMedium
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

    Drawer {
        id: drawer
        anchors.fill: parent

        open: false

        background: SilicaListView {
            anchors.fill: parent

            header: PageHeader { title: "Filters" }

            PullDownMenu {
                MenuItem {
                    text: "About"
                    onClicked: {
                        pageStack.push(Qt.resolvedUrl("AboutPage.qml"))
                    }
                }
                MenuItem {
                    text: "Save"
                    onClicked: {
                        filteredImage.saveImage();
                    }
                }
//                MenuItem {
//                    text: "Redo"
//                }
//                MenuItem {
//                    text: "Undo"
//                }
                MenuItem {
                    text: "Apply"
                    enabled: filterComboBox.currentIndex !== 0
                    onClicked: {
                        filteredImage.applyCurrentFilter();
                        filterComboBox.currentIndex = 0;
                    }
                }
            }

            model: VisualItemModel {
                ComboBox {
                    id: filterComboBox
                    width: imagePage.width
                    label: "Filter"
                    currentIndex: 0

                    onCurrentIndexChanged: {
                        filteredImage.applyFilter(filterListModel.objectAt(currentIndex - 1));
                        filterParameterList.setFilter(filterListModel.objectAt(currentIndex - 1));
                    }

                    menu: ContextMenu {

                        MenuItem { text: "None" }

                        Repeater {
                            model: FilterListModel {
                                id: filterListModel
                            }

                            delegate: MenuItem {
                                text: name
                            }
                        }
                    }
                }

                Column {
                    width: parent.width

                    Repeater {
                        model: FilterParameterListModel {
                            id: filterParameterList
                        }

                        delegate: Slider {
                            value: model.value
                            minimumValue: model.min
                            maximumValue: model.max
                            stepSize: 1
                            width: imagePage.width
                            valueText: sliderValue
                            label: model.name

                            onDownChanged: {
                                if(!down && model.value !== sliderValue)
                                {
                                    model.value = sliderValue;
                                    filteredImage.reApplyFilter();
                                }
                            }
                        }
                    }
                }

//                Column {

//                    Repeater {
//                        id: filterParams
//                        model: 0

//                        delegate: Slider {
//                            value: model.modelData.value
//                            minimumValue: model.modelData.min
//                            maximumValue: model.modelData.max
//                            stepSize: 1
//                            width: imagePage.width
//                            valueText: model.modelData.value
//                            label: model.modelData.name
//                            onValueChanged: {
//                                filteredImage.reApplyFilter();
//                            }
//                        }
//                    }
//                }
            }

            VerticalScrollDecorator {}
        }

        SilicaFlickable {
            id: flickable
            anchors.fill: parent
            contentWidth: container.width
            contentHeight: container.height
//            contentWidth: filteredImage.contentsSize.width
//            contentHeight: filteredImage.contentsSize.height
            clip: true
            interactive: !drawer.open

            Item {
                id: container
                width: Math.max(filteredImage.width * filteredImage.scale, flickable.width)
                height: Math.max(filteredImage.height * filteredImage.scale, flickable.height)

                FilteredImage {
                    id: filteredImage

                    property real prevScale

                    anchors.centerIn: parent
                    smooth: !flickable.moving

                    function fitToScreen() {
                        scale = Math.min(flickable.width / width, flickable.height / height, 1)
                        pinchArea.pinch.minimumScale = scale
                        prevScale = scale
                    }

                    onScaleChanged: {
                        if ((width * scale) > flickable.width) {
                            var xoff = (flickable.width / 2 + flickable.contentX) * scale / prevScale;
                            flickable.contentX = xoff - flickable.width / 2
                        }
                        if ((height * scale) > flickable.height) {
                            var yoff = (flickable.height / 2 + flickable.contentY) * scale / prevScale;
                            flickable.contentY = yoff - flickable.height / 2
                        }
                        prevScale = scale
                    }

                    Component.onCompleted: {
                        fitToScreen();
                    }

                    onImageSaved: {
                        imageSavedPanel.filename = fileName;
                        imageSavedPanel.show();
                    }

//                    Component.onCompleted: {
//                        filteredImage.width = flickable.width;
//                        filteredImage.height = flickable.height;
//                    }
                }
            }

            PinchArea {
                id: pinchArea
                anchors.fill: parent
                enabled: !drawer.open
                pinch.target: filteredImage
                pinch.minimumScale: 1
                pinch.maximumScale: 2

                /*onPinchStarted: {
                    console.debug("Started pinch...");
                }*/

                onPinchFinished: {
                    //console.debug("Finished pinch...");
                    flickable.returnToBounds();
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: drawer.open = !drawer.open
                }
            }
        }
    }

    onStatusChanged: {
        if(status === PageStatus.Active)
        {
            mainWindow.cover = imgCover;
        }
    }

    Component {
        id: imgCover

        FilteredCoverImage {
            id: filteredCoverImage
            anchors.fill: parent
            image: filteredImage.image
        }
    }
}





