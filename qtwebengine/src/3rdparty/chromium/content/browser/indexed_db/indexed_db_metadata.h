// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_INDEXED_DB_INDEXED_DB_METADATA_H_
#define CONTENT_BROWSER_INDEXED_DB_INDEXED_DB_METADATA_H_

#include <stdint.h>

#include <map>

#include "base/strings/string16.h"
#include "content/common/indexed_db/indexed_db_key_path.h"

namespace content {

struct CONTENT_EXPORT IndexedDBIndexMetadata {
  static const int64_t kInvalidId = -1;

  IndexedDBIndexMetadata();
  IndexedDBIndexMetadata(const base::string16& name,
                         int64_t id,
                         const IndexedDBKeyPath& key_path,
                         bool unique,
                         bool multi_entry);
  IndexedDBIndexMetadata(const IndexedDBIndexMetadata& other);
  ~IndexedDBIndexMetadata();
  IndexedDBIndexMetadata& operator=(const IndexedDBIndexMetadata& other);

  base::string16 name;
  int64_t id;
  IndexedDBKeyPath key_path;
  bool unique;
  bool multi_entry;
};

struct CONTENT_EXPORT IndexedDBObjectStoreMetadata {
  typedef std::map<int64_t, IndexedDBIndexMetadata> IndexMap;

  static const int64_t kInvalidId = -1;

  IndexedDBObjectStoreMetadata();
  IndexedDBObjectStoreMetadata(const base::string16& name,
                               int64_t id,
                               const IndexedDBKeyPath& key_path,
                               bool auto_increment,
                               int64_t max_index_id);
  IndexedDBObjectStoreMetadata(const IndexedDBObjectStoreMetadata& other);
  ~IndexedDBObjectStoreMetadata();
  IndexedDBObjectStoreMetadata& operator=(
      const IndexedDBObjectStoreMetadata& other);

  base::string16 name;
  int64_t id;
  IndexedDBKeyPath key_path;
  bool auto_increment;
  int64_t max_index_id;

  IndexMap indexes;
};

struct CONTENT_EXPORT IndexedDBDatabaseMetadata {
  // TODO(jsbell): These can probably be collapsed into 0.
  enum {
    NO_INT_VERSION = -1,
    DEFAULT_INT_VERSION = 0
  };

  typedef std::map<int64_t, IndexedDBObjectStoreMetadata> ObjectStoreMap;

  IndexedDBDatabaseMetadata();
  IndexedDBDatabaseMetadata(const base::string16& name,
                            int64_t id,
                            const base::string16& version,
                            int64_t int_version,
                            int64_t max_object_store_id);
  IndexedDBDatabaseMetadata(const IndexedDBDatabaseMetadata& other);
  ~IndexedDBDatabaseMetadata();
  IndexedDBDatabaseMetadata& operator=(IndexedDBDatabaseMetadata& other);

  base::string16 name;
  int64_t id;
  base::string16 version;
  int64_t int_version;
  int64_t max_object_store_id;

  ObjectStoreMap object_stores;
};
}  // namespace content

#endif  // CONTENT_BROWSER_INDEXED_DB_INDEXED_DB_METADATA_H_
