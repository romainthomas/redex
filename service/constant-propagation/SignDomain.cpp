/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "SignDomain.h"

#include "Debug.h"

namespace sign_domain {

/*
 *             ALL
 *            /    \
 *          LEZ    GEZ
 *         /  \   /   \
 *       LTZ   EQZ   GTZ
 *         \    |     /
 *            EMPTY
 */

Lattice lattice({Interval::EMPTY,
                 Interval::LTZ,
                 Interval::GTZ,
                 Interval::EQZ,
                 Interval::LEZ,
                 Interval::GEZ,
                 Interval::ALL},
                {{Interval::EMPTY, Interval::LTZ},
                 {Interval::EMPTY, Interval::GTZ},
                 {Interval::EMPTY, Interval::EQZ},
                 {Interval::LTZ, Interval::LEZ},
                 {Interval::EQZ, Interval::LEZ},
                 {Interval::GTZ, Interval::GEZ},
                 {Interval::EQZ, Interval::GEZ},
                 {Interval::LEZ, Interval::ALL},
                 {Interval::GEZ, Interval::ALL}});

std::ostream& operator<<(std::ostream& os, Interval interval) {
  switch (interval) {
  case Interval::EMPTY:
    os << "EMPTY";
    return os;
  case Interval::LTZ:
    os << "LTZ";
    return os;
  case Interval::GTZ:
    os << "GTZ";
    return os;
  case Interval::EQZ:
    os << "EQZ";
    return os;
  case Interval::GEZ:
    os << "GEZ";
    return os;
  case Interval::LEZ:
    os << "LEZ";
    return os;
  case Interval::ALL:
    os << "ALL";
    return os;
  case Interval::SIZE:
    not_reached();
  }
}

std::ostream& operator<<(std::ostream& os, Domain domain) {
  os << domain.element();
  return os;
}

Domain from_int(int64_t v) {
  if (v == 0) {
    return Domain(Interval::EQZ);
  } else if (v > 0) {
    return Domain(Interval::GTZ);
  } else /* v < 0 */ {
    return Domain(Interval::LTZ);
  }
}

bool contains(Interval interval, int64_t point) {
  switch (interval) {
  case Interval::EMPTY:
    return false;
  case Interval::EQZ:
    return point == 0;
  case Interval::LTZ:
    return point < 0;
  case Interval::GTZ:
    return point > 0;
  case Interval::LEZ:
    return point <= 0;
  case Interval::GEZ:
    return point >= 0;
  case Interval::ALL:
    return true;
  case Interval::SIZE:
    not_reached();
  }
}

} // namespace sign_domain
