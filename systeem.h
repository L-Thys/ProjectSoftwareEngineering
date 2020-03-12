//
// Created by lotte on 12.03.20.
//

#ifndef PSE_SYSTEEM_H
#define PSE_SYSTEEM_H

#include "Metronet.h"

Metronet* readFromXml(const char* file);
bool is_valid_String(const std::string& s);
bool is_Integer(const std::string& s);

#endif //PSE_SYSTEEM_H
