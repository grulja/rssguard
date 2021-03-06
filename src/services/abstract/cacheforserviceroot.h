// This file is part of RSS Guard.

//
// Copyright (C) 2011-2017 by Martin Rotter <rotter.martinos@gmail.com>
//
// RSS Guard is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// RSS Guard is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with RSS Guard. If not, see <http://www.gnu.org/licenses/>.

#ifndef CACHEFORSERVICEROOT_H
#define CACHEFORSERVICEROOT_H

#include "services/abstract/serviceroot.h"

#include <QMap>
#include <QPair>
#include <QStringList>

class Mutex;

class CacheForServiceRoot {
  public:
    explicit CacheForServiceRoot();
    virtual ~CacheForServiceRoot();

    void addMessageStatesToCache(const QList<Message>& ids_of_messages, RootItem::Importance importance);
    void addMessageStatesToCache(const QStringList& ids_of_messages, RootItem::ReadStatus read);

    // Persistently saves/loads cached changes to/from file.
    // NOTE: The whole cache is cleared after save is done and before load is done.
    void saveCacheToFile(int acc_id);
    void loadCacheFromFile(int acc_id);

    virtual void saveAllCachedData(bool async = true) = 0;

  protected:
    QPair<QMap<RootItem::ReadStatus, QStringList>, QMap<RootItem::Importance, QList<Message>>> takeMessageCache();

    Mutex* m_cacheSaveMutex;

    QMap<RootItem::ReadStatus, QStringList> m_cachedStatesRead;
    QMap<RootItem::Importance, QList<Message>> m_cachedStatesImportant;

  private:
    bool isEmpty() const;
    void clearCache();
};

#endif // CACHEFORSERVICEROOT_H
