// apt-transport-droidian
// Copyright (C) 2024  Eugenio Paolantonio (g7) <eugenio@droidian.org>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <apt-pkg/configuration.h>
#include <apt-pkg/error.h>
#include <apt-pkg/strutl.h>

#include "transport.h"

#define TRANSPORT_PREFIX "droidian+"
#define DEFAULT_VERSION "current"
#define DEFAULT_VARIANT ""
#define DEFAULT_SNAPSHOT_PATH "/snapshots/"

std::string DroidianTransportMethod::Version;
std::string DroidianTransportMethod::Variant;
std::string DroidianTransportMethod::SnapshotSearchPath;

DroidianTransportMethod::DroidianTransportMethod()
: pkgAcqMethod("1.0", SingleInstance | SendConfig | NeedsCleanup)
{
    Version = "";
    Variant = "";
    SnapshotSearchPath = "";
}

bool DroidianTransportMethod::Configuration(std::string Message)
{
    if (!pkgAcqMethod::Configuration(Message))
    {
        _error->Error("Unable to do initial configuration");
        return false;
    }

    Version = _config->Find("Acquire::Droidian::Version", DEFAULT_VERSION);
    Variant = _config->Find("Acquire::Droidian::Variant", DEFAULT_VARIANT);
    SnapshotSearchPath = _config->Find("Acquire::Droidian::SnapshotSearchPath", DEFAULT_SNAPSHOT_PATH);

    return true;
}

bool DroidianTransportMethod::URIAcquire(std::string const &Message, FetchItem *Itm)
{
    std::unordered_map<std::string, std::string> fields;
    std::string current_repository = LookupTag(Message, "Target-Repo-URI");
    std::string file_path;

    if (APT::String::Endswith(current_repository, "/"))
    {
        current_repository.pop_back();
    }

    if (current_repository.empty() || Itm->Uri.length() <= current_repository.length())
    {
        return false;
    }

    file_path = Itm->Uri.substr(current_repository.length());
    current_repository.replace(0, sizeof(TRANSPORT_PREFIX)-1, "");

    fields.emplace("URI", Itm->Uri);
    fields.emplace("New-URI",
        current_repository +
        SnapshotSearchPath +
        Version +
        (Variant.empty() ? "" : "-" + Variant) +
        "/" +
        file_path);

    SendMessage("103 Redirect", std::move(fields));

    return true;
}
