// +------------------------------------------------------------------+
// |             ____ _               _        __  __ _  __           |
// |            / ___| |__   ___  ___| | __   |  \/  | |/ /           |
// |           | |   | '_ \ / _ \/ __| |/ /   | |\/| | ' /            |
// |           | |___| | | |  __/ (__|   <    | |  | | . \            |
// |            \____|_| |_|\___|\___|_|\_\___|_|  |_|_|\_\           |
// |                                                                  |
// | Copyright Mathias Kettner 2014             mk@mathias-kettner.de |
// +------------------------------------------------------------------+
//
// This file is part of Check_MK.
// The official homepage is at http://mathias-kettner.de/check_mk.
//
// check_mk is free software;  you can redistribute it and/or modify it
// under the  terms of the  GNU General Public License  as published by
// the Free Software Foundation in version 2.  check_mk is  distributed
// in the hope that it will be useful, but WITHOUT ANY WARRANTY;  with-
// out even the implied warranty of  MERCHANTABILITY  or  FITNESS FOR A
// PARTICULAR PURPOSE. See the  GNU General Public License for more de-
// tails. You should have  received  a copy of the  GNU  General Public
// License along with GNU Make; see the file  COPYING.  If  not,  write
// to the Free Software Foundation, Inc., 51 Franklin St,  Fifth Floor,
// Boston, MA 02110-1301 USA.

#ifndef DownCommColumn_h
#define DownCommColumn_h

#include "config.h"  // IWYU pragma: keep
#include <memory>
#include <string>
#include <vector>
#include "ListColumn.h"
#include "contact_fwd.h"
class MonitoringCore;
class RowRenderer;
struct CommentData;
struct DowntimeData;

class DownCommColumn : public ListColumn {
    MonitoringCore *_mc;
    bool _is_downtime;
    bool _with_info;
    bool _is_service;
    bool _with_extra_info;

    std::vector<DowntimeData> downtimes_for_object(void *data) const;
    std::vector<CommentData> comments_for_object(void *data) const;

public:
    DownCommColumn(const std::string &name, const std::string &description,
                   MonitoringCore *mc, bool is_downtime, bool is_service,
                   bool with_info, bool with_extra_info, int indirect_offset,
                   int extra_offset, int extra_extra_offset)
        : ListColumn(name, description, indirect_offset, extra_offset,
                     extra_extra_offset)
        , _mc(mc)
        , _is_downtime(is_downtime)
        , _with_info(with_info)
        , _is_service(is_service)
        , _with_extra_info(with_extra_info) {}
    std::unique_ptr<Contains> makeContains(const std::string &name) override;
    void output(void *row, RowRenderer &r, contact *auth_user) override;
    bool isEmpty(void *data) override;
};

#endif  // DownCommColumn_h
