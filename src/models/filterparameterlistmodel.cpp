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

#include "filterparameterlistmodel.h"

#include "src/filters/abstractimagefilter.h"
#include "src/filters/imagefilterparameter.h"

FilterParameterListModel::FilterParameterListModel(QObject *parent) :
    QAbstractListModel(parent)
{
    m_filter = 0;
}

int FilterParameterListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    if(m_filter != 0)
    {
        return m_filter->parameterList().count();
    }
    else
    {
        return 0;
    }
}

QVariant FilterParameterListModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_filter->parameterList().count())
    {
        return QVariant();
    }

    switch (role) {
    case NameRole:
        return m_filter->parameterList()[index.row()]->name();
    case MinRole:
        return m_filter->parameterList()[index.row()]->min();
    case MaxRole:
        return m_filter->parameterList()[index.row()]->max();
    case ValueRole:
        return m_filter->parameterList()[index.row()]->value();
    default:
        return QVariant();
    }
}

bool FilterParameterListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.row() < 0 || index.row() >= m_filter->parameterList().count())
    {
        return false;
    }

    switch(role) {
    case ValueRole:
        m_filter->parameterList()[index.row()]->setValue(value.toInt());
        emit dataChanged(index,index,QVector<int>() << role);
        return true;
    default:
        return false;
    }
}

Qt::ItemFlags FilterParameterListModel::flags(const QModelIndex &index) const
{
    return QAbstractListModel::flags(index) | Qt::ItemIsEditable;
}

void FilterParameterListModel::setFilter(AbstractImageFilter *filter)
{
    beginResetModel();
    m_filter = filter;
    endResetModel();
}

QHash<int, QByteArray> FilterParameterListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[MinRole] = "min";
    roles[MaxRole] = "max";
    roles[ValueRole] = "value";

    return roles;
}
