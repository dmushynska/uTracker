#pragma once

#include <QString>
#include <sstream>
#include "openssl/sha.h"
#include <openssl/bio.h>
#include <openssl/evp.h>

QString mx_hash(const QString& pass, const QString& salt = nullptr);
