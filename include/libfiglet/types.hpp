// Copyright (c) 2022 Sri Lakshmi Kanthan P
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef SRILAKSHMIKANTHANP_LIBFIGLET_TYPES_HPP
#define SRILAKSHMIKANTHANP_LIBFIGLET_TYPES_HPP

namespace srilakshmikanthanp
{
  namespace libfiglet
  {
    /**
     * @brief Font Shrinking Level
     */
    enum class shrink_type : int
    {
      FULL_WIDTH,     // Full Width
      KERNING,        // Kerning
      SMUSHED         // Smushed
    };
  }
}

#endif // SRILAKSHMIKANTHANP_LIBFIGLET_TYPES_HPP
