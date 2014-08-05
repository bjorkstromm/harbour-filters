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

#include "filterlistmodel.h"

#include "src/filters/abstractimagefilter.h"
#include "src/filters/sepiafilter.h"
#include "src/filters/greyscalefilter.h"
#include "src/filters/brightnessfilter.h"
//#include "src/filters/blurfilter.h"
//#include "src/filters/sharpenfilter.h"
#include "src/filters/rgbfilter.h"
#include "src/filters/negativefilter.h"
#include "src/filters/rgbswapfilter.h"

FilterListModel::FilterListModel(QObject *parent) :
    QAbstractListModel(parent)
{
    m_filters << new SepiaFilter(this)
              << new GreyscaleFilter(this)
              << new BrightnessFilter(this)
              //<< new BlurFilter(this)
              //<< new SharpenFilter(this)
              << new RGBFilter(this)
              << new NegativeFilter(this)
              << new RGBSwapFilter(this);
}

int FilterListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_filters.count();
}

QVariant FilterListModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_filters.count())
    {
        return QVariant();
    }

    switch (role) {
    case NameRole:
        return m_filters[index.row()]->name();
        break;
    case ObjectRole:
        return QVariant::fromValue(m_filters[index.row()]);
    default:
        return QVariant();
        break;
    }
}

QVariant FilterListModel::objectAt(int index) const
{
    if (index >= 0 && index < m_filters.count())
    {
        return QVariant::fromValue(m_filters[index]);
    }
    else
    {
        return 0;
    }
}

QHash<int, QByteArray> FilterListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[ObjectRole] = "object";

    return roles;
}

