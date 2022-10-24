#pragma once

#include <sqlite3.h>

#include "entity.h"

#define SOMMELIER_DRIVE_N_TABLES 5
#define SOMMELIER_DRIVE_INITIALIZE_SQL 6
#define MAX_SIZE_SQL_PLANE_TEXT 1024

#define MAX_SIZE_SQL_CREATE_USER \
    MAX_SIZE_SQL_PLANE_TEXT + MAX_SIZE_PKE_CT + MAX_SIZE_PKSE_CT
#define MAX_SIZE_SQL_CREATE_SHARED_KEY MAX_SIZE_SQL_PLANE_TEXT + MAX_SIZE_PKE_CT

#define MAX_SIZE_SQL_READ_BY_ID MAX_SIZE_SQL_PLANE_TEXT

void InitalizeDatabase(sqlite3 *);

User *CreateUser(sqlite3 *, char *, char *);

User *ReadUser(sqlite3 *, uint64_t);

void IncrementUserNonce(sqlite3 *, User *);

// Path API cannot be used.
Path *CreatePath(sqlite3 *, uint64_t, char *, char *, char *);

// Path API cannot be used.
Path *ReadPath(sqlite3 *, uint64_t);

// Path API cannot be used.
PathVector *FilterByPermissionHash(sqlite3 *, char *);

// Path API cannot be used.
// depends on Sommelier-DB
PathVector *SearchEncryptedPath(sqlite3 *, uint64_t, char *);

SharedKey *CreateSharedKey(sqlite3 *, uint64_t, char *);

SharedKey *ReadSharedKey(sqlite3 *, uint64_t);

Content *CreateContent(sqlite3 *, char *, char *);

Content *ReadContent(sqlite3 *, uint64_t);

ContentVector *FilterBySharedKeyHash(sqlite3 *, char *);

WritePermission *CreateWritePermission(sqlite3 *, uint64_t, uint64_t);

WritePermission *ReadWritePermission(sqlite3 *, uint64_t);
