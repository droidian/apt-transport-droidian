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

#pragma once

#include <apt-pkg/acquire-method.h>

class DroidianTransportMethod : public pkgAcqMethod
{
  virtual bool Configuration(std::string Message) APT_OVERRIDE;
  virtual bool URIAcquire(std::string const &Message, FetchItem *Itm) APT_OVERRIDE;

  static std::string Version;
  static std::string Variant;
  static std::string SnapshotSearchPath;

  public:
  DroidianTransportMethod();
};
