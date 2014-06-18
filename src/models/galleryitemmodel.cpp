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

#include "galleryitemmodel.h"

#include <QDirIterator>
#include <QStandardPaths>
#include <QDateTime>
#include <QTimer>

GalleryItemModel::GalleryItemModel(QObject *parent) :
    QAbstractListModel(parent)
{
    refresh();
}

int GalleryItemModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_imageFiles.count();
}

QVariant GalleryItemModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_imageFiles.count())
    {
        return QVariant();
    }

    switch (role) {
    case UrlRole:
        return m_imageFiles[index.row()].absoluteFilePath();
        break;
    case NameRole:
        return m_imageFiles[index.row()].fileName();
    default:
        return QVariant();
        break;
    }
}

void GalleryItemModel::refresh()
{
    foreach (QFileInfo fi, m_imageFiles)
    {
        if(!QFile::exists(fi.absoluteFilePath()))
        {
            int index = m_imageFiles.indexOf(fi);

            beginRemoveRows(QModelIndex(),index,index);
            m_imageFiles.removeAt(index);
            endRemoveRows();
        }
    }

    QDirIterator iter(QStandardPaths::writableLocation(QStandardPaths::PicturesLocation),
                      QStringList() << "*.png" << "*.jpg" << "*.jpeg",
                      QDir::NoFilter,
                      QDirIterator::Subdirectories);

    while(iter.hasNext())
    {
        iter.next();

        if (iter.fileInfo().isFile() && !m_imageFiles.contains(iter.fileInfo()))
        {
            AddImageFileSorted(iter.fileInfo(), 0, m_imageFiles.length() -1);
        }
    }
}

QHash<int, QByteArray> GalleryItemModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[UrlRole] = "url";
    roles[NameRole] = "name";

    return roles;
}

void GalleryItemModel::AddImageFileSorted(const QFileInfo &file, int min, int max)
{
    if (max < min)
    {
        beginInsertRows(QModelIndex(),min,min);
        m_imageFiles.insert(min,file);
        endInsertRows();
    }
    else
    {
        // calculate midpoint to cut set in half
        int mid = min + ((max - min) / 2);

        uint lastModified = file.lastModified().toTime_t();
        uint midLastModified = m_imageFiles[mid].lastModified().toTime_t();

        // three-way comparison
        if (midLastModified < lastModified)
        {
            // key is in lower subset
            AddImageFileSorted(file, min, mid-1);
        }
        else if (midLastModified > lastModified)
        {
            // key is in upper subset
            AddImageFileSorted(file, mid+1, max);
        }
        else
        {
            // key has been found
            beginInsertRows(QModelIndex(),mid,mid);
            m_imageFiles.insert(mid,file);
            endInsertRows();
        }
    }
}
