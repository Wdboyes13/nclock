// Copyright (c) 2022 Sri Lakshmi Kanthan P
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef SRILAKSHMIKANTHANP_LIBFIGLET_HPP
#define SRILAKSHMIKANTHANP_LIBFIGLET_HPP

#include "libfiglet/types.hpp"
#include "libfiglet/abstract.hpp"
#include "libfiglet/driver.hpp"
#include "libfiglet/fonts.hpp"
#include "libfiglet/styles.hpp"
#include "libfiglet/constants.hpp"
#include "libfiglet/utilities.hpp"

namespace srilakshmikanthanp {
namespace libfiglet {

using Figlet = basic_figlet<std::string>;
using FlfFont = basic_flf_font<std::string>;
using FullWidth = basic_full_width_style<std::string>;
using Kerning = basic_kerning_style<std::string>;
using Smushed = basic_smushed_style<std::string>;

}} // namespace srilakshmikanthanp::libfiglet

#endif // SRILAKSHMIKANTHANP_LIBFIGLET_HPP