// Copyright (c) 2022 Sri Lakshmi Kanthan P
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

// Header Guard
#ifndef SRILAKSHMIKANTHANP_LIBFIGLET_LIBFIGLET_HPP
#define SRILAKSHMIKANTHANP_LIBFIGLET_LIBFIGLET_HPP

// Copyright (c) 2022 Sri Lakshmi Kanthan P
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

// Header Guards
#ifndef SRILAKSHMIKANTHANP_LIBFIGLET_ABSTRACT_HPP
#define SRILAKSHMIKANTHANP_LIBFIGLET_ABSTRACT_HPP

// Copyright (c) 2022 Sri Lakshmi Kanthan P
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

// Header guard
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

#endif // SRILAKSHMIKANTHANP_TYPES_ENUMS_HPP

#include <algorithm>
#include <ostream>
#include <string>
#include <map>
#include <iomanip>
#include <regex>
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>

namespace srilakshmikanthanp
{
  namespace libfiglet
  {
    /**
     * @brief Base Font Type for Figlet
     */
    template <class string_type_t>
    struct basic_base_figlet_font
    {
    public:                                                               // public type definition
      using string_type      =   string_type_t;                           // String Type
      using char_type        =   typename string_type_t::value_type;      // Character Type
      using traits_type      =   typename string_type_t::traits_type;     // Traits Type
      using size_type        =   typename string_type_t::size_type;       // Size Type

      using fig_char_type    =   std::vector<string_type_t>;              // Figlet char
      using fig_str_type     =   std::vector<string_type_t>;              // Figlet String

    private:                                                              // private typedefs
      using sstream_type     =   std::basic_stringstream<char_type>;      // Sstream Type
      using ostream_type     =   std::basic_ostream<char_type>;           // Ostream Type
      using istream_type     =   std::basic_istream<char_type>;           // Istream Type
      using ifstream_type    =   std::basic_ifstream<char_type>;          // Ifstream Type
      using ofstream_type    =   std::basic_ofstream<char_type>;          // Ofstream Type

    public:                                                               // public methods

      /**
       * @brief Get the BasicFiglet character
       */
      virtual fig_char_type get_fig_char(char_type ch) const = 0;

      /**
       * @brief Get the Hard Blank character
       */
      virtual char_type get_hard_blank() const = 0;

      /**
       * @brief Get the Height of font
       */
      virtual size_type get_height() const = 0;

      /**
       * @brief Get the Shrink Level of font
       */
      virtual shrink_type get_shrink_level() const = 0;
    };

    /**
     * @brief Base Style Type for Figlet
     */
    template <class string_type_t>
    struct basic_base_figlet_style
    {
    public:                                                               // public type definition
      using string_type      =   string_type_t;                           // String Type
      using char_type        =   typename string_type_t::value_type;      // Character Type
      using traits_type      =   typename string_type_t::traits_type;     // Traits Type
      using size_type        =   typename string_type_t::size_type;       // Size Type

      using fig_char_type    =   std::vector<string_type_t>;              // Figlet char
      using fig_str_type     =   std::vector<string_type_t>;              // Figlet String

    private:                                                              // private typedefs
      using sstream_type     =   std::basic_stringstream<char_type>;      // Sstream Type
      using ostream_type     =   std::basic_ostream<char_type>;           // Ostream Type
      using istream_type     =   std::basic_istream<char_type>;           // Istream Type
      using ifstream_type    =   std::basic_ifstream<char_type>;          // Ifstream Type
      using ofstream_type    =   std::basic_ofstream<char_type>;          // Ofstream Type

    protected:                                                            // Protected Members
      char_type hard_blank;                                               // hard blank character of the Figlet
      size_type height;                                                   // height of the Figlet

    protected:                                                            // Protected Methods
      /**
       * @brief verify the height of the fig chars
       *
       * @param fig_chs fig characters
       */
      void verify_height(const std::vector<fig_char_type> &fig_chs) const
      {
        for(const auto &fig_ch: fig_chs)
        {
          if(fig_ch.size() != this->height)
          {
            throw std::runtime_error("Invalid Fig char Height");
          }
        }
      }

      /**
       * @brief removes hardblank from fig string
       *
       * @param figs fig string
       * @param hb hardblank
       */
      fig_str_type rm_hardblank(fig_str_type &figs) const
      {
        for (size_type i = 0; i < figs.size(); ++i)
        {
          std::replace(figs[i].begin(), figs[i].end(), this->hard_blank, traits_type::to_char_type(' '));
        }

        return figs;
      }

    public:
      basic_base_figlet_style(): hard_blank(' '), height(0) {}  // Default Constructor

      /**
       * @brief set the hard blank character of fig string
       */
      void set_hard_blank(char_type hb)
      {
        this->hard_blank = hb;
      }

      /**
       * @brief set the height of fig string
       */
      void set_height(size_type h)
      {
        this->height = h;
      }

      /**
       * @brief Get the Shrink Level
       */
      virtual shrink_type get_shrink_level() const = 0;

      /**
       * @brief Get the Fig string
       */
      virtual fig_str_type get_fig_str(std::vector<fig_char_type> fig_chs) const = 0;
    };
  }
}

#endif  // SRILAKSHMIKANTHANP_LIBFIGLET_ABSTRACT_HPP

// Copyright (c) 2022 Sri Lakshmi Kanthan P
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

// Header Guards
#ifndef SRILAKSHMIKANTHANP_LIBFIGLET_CONSTANTS_HPP
#define SRILAKSHMIKANTHANP_LIBFIGLET_CONSTANTS_HPP

#include <string>

namespace srilakshmikanthanp
{
  namespace libfiglet
  {
    const std::string LIBFIGLET_VERSION = "1.3.2";
  }
}

#endif // SRILAKSHMIKANTHANP_LIBFIGLET_CONSTANTS_HPP

// Copyright (c) 2022 Sri Lakshmi Kanthan P
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

// Header Guards
#ifndef SRILAKSHMIKANTHANP_LIBFIGLET_DRIVER_HPP
#define SRILAKSHMIKANTHANP_LIBFIGLET_DRIVER_HPP

// Copyright (c) 2022 Sri Lakshmi Kanthan P
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

// Header Guards
#ifndef SRILAKSHMIKANTHANP_LIBFIGLET_ABSTRACT_HPP
#define SRILAKSHMIKANTHANP_LIBFIGLET_ABSTRACT_HPP

// Copyright (c) 2022 Sri Lakshmi Kanthan P
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

// Header guard
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

#endif // SRILAKSHMIKANTHANP_TYPES_ENUMS_HPP

#include <algorithm>
#include <ostream>
#include <string>
#include <map>
#include <iomanip>
#include <regex>
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>

namespace srilakshmikanthanp
{
  namespace libfiglet
  {
    /**
     * @brief Base Font Type for Figlet
     */
    template <class string_type_t>
    struct basic_base_figlet_font
    {
    public:                                                               // public type definition
      using string_type      =   string_type_t;                           // String Type
      using char_type        =   typename string_type_t::value_type;      // Character Type
      using traits_type      =   typename string_type_t::traits_type;     // Traits Type
      using size_type        =   typename string_type_t::size_type;       // Size Type

      using fig_char_type    =   std::vector<string_type_t>;              // Figlet char
      using fig_str_type     =   std::vector<string_type_t>;              // Figlet String

    private:                                                              // private typedefs
      using sstream_type     =   std::basic_stringstream<char_type>;      // Sstream Type
      using ostream_type     =   std::basic_ostream<char_type>;           // Ostream Type
      using istream_type     =   std::basic_istream<char_type>;           // Istream Type
      using ifstream_type    =   std::basic_ifstream<char_type>;          // Ifstream Type
      using ofstream_type    =   std::basic_ofstream<char_type>;          // Ofstream Type

    public:                                                               // public methods

      /**
       * @brief Get the BasicFiglet character
       */
      virtual fig_char_type get_fig_char(char_type ch) const = 0;

      /**
       * @brief Get the Hard Blank character
       */
      virtual char_type get_hard_blank() const = 0;

      /**
       * @brief Get the Height of font
       */
      virtual size_type get_height() const = 0;

      /**
       * @brief Get the Shrink Level of font
       */
      virtual shrink_type get_shrink_level() const = 0;
    };

    /**
     * @brief Base Style Type for Figlet
     */
    template <class string_type_t>
    struct basic_base_figlet_style
    {
    public:                                                               // public type definition
      using string_type      =   string_type_t;                           // String Type
      using char_type        =   typename string_type_t::value_type;      // Character Type
      using traits_type      =   typename string_type_t::traits_type;     // Traits Type
      using size_type        =   typename string_type_t::size_type;       // Size Type

      using fig_char_type    =   std::vector<string_type_t>;              // Figlet char
      using fig_str_type     =   std::vector<string_type_t>;              // Figlet String

    private:                                                              // private typedefs
      using sstream_type     =   std::basic_stringstream<char_type>;      // Sstream Type
      using ostream_type     =   std::basic_ostream<char_type>;           // Ostream Type
      using istream_type     =   std::basic_istream<char_type>;           // Istream Type
      using ifstream_type    =   std::basic_ifstream<char_type>;          // Ifstream Type
      using ofstream_type    =   std::basic_ofstream<char_type>;          // Ofstream Type

    protected:                                                            // Protected Members
      char_type hard_blank;                                               // hard blank character of the Figlet
      size_type height;                                                   // height of the Figlet

    protected:                                                            // Protected Methods
      /**
       * @brief verify the height of the fig chars
       *
       * @param fig_chs fig characters
       */
      void verify_height(const std::vector<fig_char_type> &fig_chs) const
      {
        for(const auto &fig_ch: fig_chs)
        {
          if(fig_ch.size() != this->height)
          {
            throw std::runtime_error("Invalid Fig char Height");
          }
        }
      }

      /**
       * @brief removes hardblank from fig string
       *
       * @param figs fig string
       * @param hb hardblank
       */
      fig_str_type rm_hardblank(fig_str_type &figs) const
      {
        for (size_type i = 0; i < figs.size(); ++i)
        {
          std::replace(figs[i].begin(), figs[i].end(), this->hard_blank, traits_type::to_char_type(' '));
        }

        return figs;
      }

    public:
      basic_base_figlet_style(): hard_blank(' '), height(0) {}  // Default Constructor

      /**
       * @brief set the hard blank character of fig string
       */
      void set_hard_blank(char_type hb)
      {
        this->hard_blank = hb;
      }

      /**
       * @brief set the height of fig string
       */
      void set_height(size_type h)
      {
        this->height = h;
      }

      /**
       * @brief Get the Shrink Level
       */
      virtual shrink_type get_shrink_level() const = 0;

      /**
       * @brief Get the Fig string
       */
      virtual fig_str_type get_fig_str(std::vector<fig_char_type> fig_chs) const = 0;
    };
  }
}

#endif  // SRILAKSHMIKANTHANP_LIBFIGLET_ABSTRACT_HPP

// Copyright (c) 2022 Sri Lakshmi Kanthan P
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

// Header guard
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

#endif // SRILAKSHMIKANTHANP_TYPES_ENUMS_HPP

#include <algorithm>
#include <ostream>
#include <string>
#include <map>
#include <iomanip>
#include <regex>
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>

namespace srilakshmikanthanp
{
  namespace libfiglet
  {
    /**
     * @brief basic figlet class
     */
    template <class string_type_t>
    class basic_figlet
    {
    public:                                                               // public type definition
      using string_type      =   string_type_t;                           // String Type
      using char_type        =   typename string_type_t::value_type;      // Character Type
      using traits_type      =   typename string_type_t::traits_type;     // Traits Type
      using size_type        =   typename string_type_t::size_type;       // Size Type

      using fig_char_type    =   std::vector<string_type_t>;              // Figlet char
      using fig_str_type     =   std::vector<string_type_t>;              // Figlet String

    private:                                                              // private typedefs
      using sstream_type     =   std::basic_stringstream<char_type>;      // Sstream Type
      using ostream_type     =   std::basic_ostream<char_type>;           // Ostream Type
      using istream_type     =   std::basic_istream<char_type>;           // Istream Type
      using ifstream_type    =   std::basic_ifstream<char_type>;          // Ifstream Type
      using ofstream_type    =   std::basic_ofstream<char_type>;          // Ofstream Type

    public:                                                               // Public types
      using base_figlet_style_ptr  =  std::shared_ptr<basic_base_figlet_style<string_type>>;
      using base_figlet_font_ptr   =  std::shared_ptr<basic_base_figlet_font<string_type>>;

    private:                                                              // Private members
      base_figlet_style_ptr style;                                        // Figlet Style
      base_figlet_font_ptr font;                                          // Figlet Font

    private:                                                              // private utilities
      /**
       * @brief Check the shrink level, set font and style
       */
      void set_font_and_style(base_figlet_font_ptr font, base_figlet_style_ptr style)
      {
        if (font->get_shrink_level() < style->get_shrink_level())
        {
          throw std::runtime_error("The Shrink Level of Font is less than Style");
        }

        this->style = style; // Set style
        this->font = font;   // Set font

        // Set the height of the style
        this->style->set_height(this->font->get_height());

        // Set the hard blank of the style
        this->style->set_hard_blank(this->font->get_hard_blank());
      }

    public:                                                             // Public members
      basic_figlet(const basic_figlet &) = default;                     // copy constructor
      basic_figlet(basic_figlet &&) = default;                          // move constructor
      basic_figlet() = delete;                                          // constructor

      /**
       * @brief Construct a new basic figlet object
       */
      basic_figlet(base_figlet_font_ptr font, base_figlet_style_ptr style)
      {
        this->set_font_and_style(font, style);
      }

      /**
       * @brief set the style
       */
      void set_style(base_figlet_style_ptr style)
      {
        this->set_font_and_style(this->font, style);
      }

      /**
       * @brief set the font
       */
      void set_font(base_figlet_font_ptr font)
      {
        this->set_font_and_style(font, this->style);
      }

      /**
       * @brief Get the style
       */
      base_figlet_style_ptr get_style() const
      {
        return this->style;
      }

      /**
       * @brief Get the font
       */
      base_figlet_font_ptr get_font() const
      {
        return this->font;
      }

      /**
       * @brief Get the figlet string
       */
      string_type operator()(const string_type &str) const
      {
        // Attributes for Transform
        std::vector<fig_char_type> fig_chs;
        const auto hard_blank = this->font->get_hard_blank();
        const auto height = this->font->get_height();

        // Transform to fig char
        std::transform(
          str.begin(), str.end(), std::back_inserter(fig_chs),
          [this](auto ch){
            return this->font->get_fig_char(ch);
          }
        );

        // Get the figlet string
        const auto fig_str = this->style->get_fig_str(fig_chs);

        // add with new line
        string_type value;

        for (const auto &fig : fig_str)
        {
          value += fig + traits_type::to_char_type('\n');
        }

        return value;
      }
    };
  } // namespace libfiglet
} // namespace srilakshmikanthanp

#endif

// Copyright (c) 2022 Sri Lakshmi Kanthan P
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

// Header Guard
#ifndef SRILAKSHMIKANTHANP_LIBFIGLET_FONTS_HPP
#define SRILAKSHMIKANTHANP_LIBFIGLET_FONTS_HPP

// Copyright (c) 2022 Sri Lakshmi Kanthan P
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

// Header Guards
#ifndef SRILAKSHMIKANTHANP_LIBFIGLET_ABSTRACT_HPP
#define SRILAKSHMIKANTHANP_LIBFIGLET_ABSTRACT_HPP

// Copyright (c) 2022 Sri Lakshmi Kanthan P
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

// Header guard
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

#endif // SRILAKSHMIKANTHANP_TYPES_ENUMS_HPP

#include <algorithm>
#include <ostream>
#include <string>
#include <map>
#include <iomanip>
#include <regex>
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>

namespace srilakshmikanthanp
{
  namespace libfiglet
  {
    /**
     * @brief Base Font Type for Figlet
     */
    template <class string_type_t>
    struct basic_base_figlet_font
    {
    public:                                                               // public type definition
      using string_type      =   string_type_t;                           // String Type
      using char_type        =   typename string_type_t::value_type;      // Character Type
      using traits_type      =   typename string_type_t::traits_type;     // Traits Type
      using size_type        =   typename string_type_t::size_type;       // Size Type

      using fig_char_type    =   std::vector<string_type_t>;              // Figlet char
      using fig_str_type     =   std::vector<string_type_t>;              // Figlet String

    private:                                                              // private typedefs
      using sstream_type     =   std::basic_stringstream<char_type>;      // Sstream Type
      using ostream_type     =   std::basic_ostream<char_type>;           // Ostream Type
      using istream_type     =   std::basic_istream<char_type>;           // Istream Type
      using ifstream_type    =   std::basic_ifstream<char_type>;          // Ifstream Type
      using ofstream_type    =   std::basic_ofstream<char_type>;          // Ofstream Type

    public:                                                               // public methods

      /**
       * @brief Get the BasicFiglet character
       */
      virtual fig_char_type get_fig_char(char_type ch) const = 0;

      /**
       * @brief Get the Hard Blank character
       */
      virtual char_type get_hard_blank() const = 0;

      /**
       * @brief Get the Height of font
       */
      virtual size_type get_height() const = 0;

      /**
       * @brief Get the Shrink Level of font
       */
      virtual shrink_type get_shrink_level() const = 0;
    };

    /**
     * @brief Base Style Type for Figlet
     */
    template <class string_type_t>
    struct basic_base_figlet_style
    {
    public:                                                               // public type definition
      using string_type      =   string_type_t;                           // String Type
      using char_type        =   typename string_type_t::value_type;      // Character Type
      using traits_type      =   typename string_type_t::traits_type;     // Traits Type
      using size_type        =   typename string_type_t::size_type;       // Size Type

      using fig_char_type    =   std::vector<string_type_t>;              // Figlet char
      using fig_str_type     =   std::vector<string_type_t>;              // Figlet String

    private:                                                              // private typedefs
      using sstream_type     =   std::basic_stringstream<char_type>;      // Sstream Type
      using ostream_type     =   std::basic_ostream<char_type>;           // Ostream Type
      using istream_type     =   std::basic_istream<char_type>;           // Istream Type
      using ifstream_type    =   std::basic_ifstream<char_type>;          // Ifstream Type
      using ofstream_type    =   std::basic_ofstream<char_type>;          // Ofstream Type

    protected:                                                            // Protected Members
      char_type hard_blank;                                               // hard blank character of the Figlet
      size_type height;                                                   // height of the Figlet

    protected:                                                            // Protected Methods
      /**
       * @brief verify the height of the fig chars
       *
       * @param fig_chs fig characters
       */
      void verify_height(const std::vector<fig_char_type> &fig_chs) const
      {
        for(const auto &fig_ch: fig_chs)
        {
          if(fig_ch.size() != this->height)
          {
            throw std::runtime_error("Invalid Fig char Height");
          }
        }
      }

      /**
       * @brief removes hardblank from fig string
       *
       * @param figs fig string
       * @param hb hardblank
       */
      fig_str_type rm_hardblank(fig_str_type &figs) const
      {
        for (size_type i = 0; i < figs.size(); ++i)
        {
          std::replace(figs[i].begin(), figs[i].end(), this->hard_blank, traits_type::to_char_type(' '));
        }

        return figs;
      }

    public:
      basic_base_figlet_style(): hard_blank(' '), height(0) {}  // Default Constructor

      /**
       * @brief set the hard blank character of fig string
       */
      void set_hard_blank(char_type hb)
      {
        this->hard_blank = hb;
      }

      /**
       * @brief set the height of fig string
       */
      void set_height(size_type h)
      {
        this->height = h;
      }

      /**
       * @brief Get the Shrink Level
       */
      virtual shrink_type get_shrink_level() const = 0;

      /**
       * @brief Get the Fig string
       */
      virtual fig_str_type get_fig_str(std::vector<fig_char_type> fig_chs) const = 0;
    };
  }
}

#endif  // SRILAKSHMIKANTHANP_LIBFIGLET_ABSTRACT_HPP

// Copyright (c) 2022 Sri Lakshmi Kanthan P
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef SRILAKSHMIKANTHANP_UTILITIES_FUNCTIONS_HPP
#define SRILAKSHMIKANTHANP_UTILITIES_FUNCTIONS_HPP

namespace srilakshmikanthanp
{
  namespace libfiglet
  {
    /**
     * @brief convert ascii string to string_type_t
     *
     * @param str string to convert
     * @return string_type_t string converted
     */
    template <class string_type_t>
    string_type_t cvt(const std::string str)
    {
      return string_type_t(str.begin(), str.end());
    }
  }
}

#endif

// Copyright (c) 2022 Sri Lakshmi Kanthan P
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

// Header guard
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

#endif // SRILAKSHMIKANTHANP_TYPES_ENUMS_HPP

#include <algorithm>
#include <ostream>
#include <string>
#include <map>
#include <iomanip>
#include <regex>
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>

namespace srilakshmikanthanp
{
  namespace libfiglet
  {
    /**
     * @brief Figlet flf Font Type
     */
    template <class string_type_t>
    class basic_flf_font : public basic_base_figlet_font<string_type_t>
    {
    public:                                                               // public type definition
      using string_type      =   string_type_t;                           // String Type
      using char_type        =   typename string_type_t::value_type;      // Character Type
      using traits_type      =   typename string_type_t::traits_type;     // Traits Type
      using size_type        =   typename string_type_t::size_type;       // Size Type

      using fig_char_type    =   std::vector<string_type_t>;              // Figlet char
      using fig_str_type     =   std::vector<string_type_t>;              // Figlet String

    private:                                                              // private typedefs
      using sstream_type     =   std::basic_stringstream<char_type>;      // Sstream Type
      using ostream_type     =   std::basic_ostream<char_type>;           // Ostream Type
      using istream_type     =   std::basic_istream<char_type>;           // Istream Type
      using ifstream_type    =   std::basic_ifstream<char_type>;          // Ifstream Type
      using ofstream_type    =   std::basic_ofstream<char_type>;          // Ofstream Type

    private:                                                              // Private types definition
      using map_type = std::map<char_type, fig_char_type>;
      using ibuff_it = std::istreambuf_iterator<char_type>;

    private:                                                              // Private configs
      char_type hard_blank;
      size_type height;
      shrink_type shrink;

    private:                                                              // Private characters
      map_type fig_chars;

    private:                                                              // Private utilities
      /**
       * @brief Read the Config from the stream
       */
      void read_config_and_remove_comments(istream_type &is)
      {
        // flf header line container
        string_type flf_config_line;

        // get the first line
        std::getline(is, flf_config_line);

        // string stream for the first line
        sstream_type ss(flf_config_line);

        // token
        string_type token;

        // Read header
        ss >> std::setw(5) >> token;

        // check
        if (token != cvt<string_type>("flf2a"))
        {
          throw std::runtime_error("Invalid flf2a header");
        }

        // Read hard blank
        ss >> this->hard_blank;

        // check stream
        if (ss.fail())
        {
          throw std::runtime_error("Invalid hard blank");
        }

        // Read height
        ss >> this->height;

        // check stream
        if (ss.fail())
        {
          throw std::runtime_error("Invalid height");
        }

        // Read baseline
        ss >> token;

        // check stream
        if (ss.fail())
        {
          throw std::runtime_error("Invalid baseline");
        }

        // Read max length
        ss >> token;

        // check stream
        if (ss.fail())
        {
          throw std::runtime_error("Invalid max length");
        }

        // Read old layout
        ss >> token;

        // check stream
        if (ss.fail())
        {
          throw std::runtime_error("Invalid old layout");
        }

        // set shrink level
        const auto old_layout = std::stoi(token);

        if (old_layout < 0) // less than 0 then FULL_WIDTH
        {
          this->shrink = shrink_type::FULL_WIDTH;
        }

        if (old_layout == 0) // equal to 0 then KERNING
        {
          this->shrink = shrink_type::KERNING;
        }

        if (old_layout > 0) // greater than 0 then SMUSHED
        {
          this->shrink = shrink_type::SMUSHED;
        }

        // Read comment lines
        ss >> token;

        // check stream
        if (ss.fail())
        {
          throw std::runtime_error("Invalid comment lines");
        }

        // check and set
        const auto comment_lines = std::stoi(token);

        // ignore comment lines
        for (auto i = 0; i < comment_lines; ++i)
        {
          std::getline(is, token);
        }
      }

      /**
       * @brief Read the characters from the stream
       */
      void read_chars(istream_type &is)
      {
        // lambda function to convert the lines to fig char
        auto to_fig_char = [this](const std::vector<string_type> &lines) {
          // regex pattern to match
          std::basic_regex<char_type> pattern(cvt<string_type>("(.)\\1?\n"), std::regex::ECMAScript);

          // fig char container
          fig_char_type fig_char;

          // line
          string_type line;

          // read lines
          for (const auto &line : lines)
          {
            fig_char.push_back(std::regex_replace(line + cvt<string_type>("\n"), pattern, cvt<string_type>("")));
          }

          // check height
          if (fig_char.size() != this->height)
          {
            throw std::runtime_error("Height not match");
          }

          // return
          return fig_char;
        };

        // lambda function to read lines from the stream
        auto read_lines = [this](istream_type &is, size_type n) {
          // lines container
          std::vector<string_type> lines;

          // line
          string_type line;

          // read lines
          for (auto i = 0; i < n && std::getline(is, line); ++i)
          {
            lines.push_back(line);
          }

          // return
          return lines;
        };

        // read all the characters (ch <= '~' must be first)
        for (char_type ch = ' '; ch <= '~'; ++ch)
        {
          // get the fig char
          const auto fig_char = to_fig_char(read_lines(is, this->height));

          // if length less
          if (fig_char.size() < this->height)
          {
            throw std::runtime_error("Invalid fig char");
          }

          // insert the fig char
          this->fig_chars.insert({ch, fig_char});
        }
      }

      /**
       * @brief Init from the Stream
       */
      void init(istream_type &is)
      {
        // read config and remove comments
        this->read_config_and_remove_comments(is);

        // read characters
        this->read_chars(is);
      }

    public:                                                               // Public constructors
      basic_flf_font() = delete;                                          // default constructor
      basic_flf_font(const basic_flf_font &) = default;                   // copy constructor
      basic_flf_font(basic_flf_font &&) = default;                        // move constructor

      /**
       * @brief From istream
       */
      explicit basic_flf_font(istream_type &is)
      {
        this->init(is);
      }

      /**
       * @brief From file
       */
      explicit basic_flf_font(const std::string &file)
      {
        // file stream
        ifstream_type ifs(file);

        // check
        if (!ifs.is_open())
        {
          throw std::runtime_error("Cannot open font : " + file);
        }

        // read
        this->init(ifs);
      }

    public: // Public overrides
      /**
       * @brief Get the Hard Blank character
       */
      char_type get_hard_blank() const override
      {
        return this->hard_blank;
      }

      /**
       * @brief Get the height of the font
       */
      size_type get_height() const override
      {
        return this->height;
      }

      /**
       * @brief Get the shrink level
       */
      shrink_type get_shrink_level() const override
      {
        return this->shrink;
      }

      /**
       * @brief Get the fig char
       */
      fig_char_type get_fig_char(char_type ch) const override
      {
        // check
        if (ch < ' ' || ch > '~')
        {
          throw std::runtime_error("Invalid character : " + std::to_string(ch));
        }

        // return
        return this->fig_chars.at(ch);
      }

    public: // static methods
      /**
       * @brief Make a flf font type as shared pointer
       */
      static auto make_shared(const std::string &file)
      {
        return std::make_shared<basic_flf_font>(file);
      }

      /**
       * @brief Make a flf font type as shared pointer
       */
      static auto make_shared(istream_type &is)
      {
        return std::make_shared<basic_flf_font>(is);
      }
    };
  }
}

#endif // BASIC_FIGLET_FIG_FONT_HPP

// Copyright (c) 2022 Sri Lakshmi Kanthan P
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef SRILAKSHMIKANTHANP_LIBFIGLET_STYLES_HPP
#define SRILAKSHMIKANTHANP_LIBFIGLET_STYLES_HPP

// Copyright (c) 2022 Sri Lakshmi Kanthan P
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

// Header Guards
#ifndef SRILAKSHMIKANTHANP_LIBFIGLET_ABSTRACT_HPP
#define SRILAKSHMIKANTHANP_LIBFIGLET_ABSTRACT_HPP

// Copyright (c) 2022 Sri Lakshmi Kanthan P
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

// Header guard
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

#endif // SRILAKSHMIKANTHANP_TYPES_ENUMS_HPP

#include <algorithm>
#include <ostream>
#include <string>
#include <map>
#include <iomanip>
#include <regex>
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>

namespace srilakshmikanthanp
{
  namespace libfiglet
  {
    /**
     * @brief Base Font Type for Figlet
     */
    template <class string_type_t>
    struct basic_base_figlet_font
    {
    public:                                                               // public type definition
      using string_type      =   string_type_t;                           // String Type
      using char_type        =   typename string_type_t::value_type;      // Character Type
      using traits_type      =   typename string_type_t::traits_type;     // Traits Type
      using size_type        =   typename string_type_t::size_type;       // Size Type

      using fig_char_type    =   std::vector<string_type_t>;              // Figlet char
      using fig_str_type     =   std::vector<string_type_t>;              // Figlet String

    private:                                                              // private typedefs
      using sstream_type     =   std::basic_stringstream<char_type>;      // Sstream Type
      using ostream_type     =   std::basic_ostream<char_type>;           // Ostream Type
      using istream_type     =   std::basic_istream<char_type>;           // Istream Type
      using ifstream_type    =   std::basic_ifstream<char_type>;          // Ifstream Type
      using ofstream_type    =   std::basic_ofstream<char_type>;          // Ofstream Type

    public:                                                               // public methods

      /**
       * @brief Get the BasicFiglet character
       */
      virtual fig_char_type get_fig_char(char_type ch) const = 0;

      /**
       * @brief Get the Hard Blank character
       */
      virtual char_type get_hard_blank() const = 0;

      /**
       * @brief Get the Height of font
       */
      virtual size_type get_height() const = 0;

      /**
       * @brief Get the Shrink Level of font
       */
      virtual shrink_type get_shrink_level() const = 0;
    };

    /**
     * @brief Base Style Type for Figlet
     */
    template <class string_type_t>
    struct basic_base_figlet_style
    {
    public:                                                               // public type definition
      using string_type      =   string_type_t;                           // String Type
      using char_type        =   typename string_type_t::value_type;      // Character Type
      using traits_type      =   typename string_type_t::traits_type;     // Traits Type
      using size_type        =   typename string_type_t::size_type;       // Size Type

      using fig_char_type    =   std::vector<string_type_t>;              // Figlet char
      using fig_str_type     =   std::vector<string_type_t>;              // Figlet String

    private:                                                              // private typedefs
      using sstream_type     =   std::basic_stringstream<char_type>;      // Sstream Type
      using ostream_type     =   std::basic_ostream<char_type>;           // Ostream Type
      using istream_type     =   std::basic_istream<char_type>;           // Istream Type
      using ifstream_type    =   std::basic_ifstream<char_type>;          // Ifstream Type
      using ofstream_type    =   std::basic_ofstream<char_type>;          // Ofstream Type

    protected:                                                            // Protected Members
      char_type hard_blank;                                               // hard blank character of the Figlet
      size_type height;                                                   // height of the Figlet

    protected:                                                            // Protected Methods
      /**
       * @brief verify the height of the fig chars
       *
       * @param fig_chs fig characters
       */
      void verify_height(const std::vector<fig_char_type> &fig_chs) const
      {
        for(const auto &fig_ch: fig_chs)
        {
          if(fig_ch.size() != this->height)
          {
            throw std::runtime_error("Invalid Fig char Height");
          }
        }
      }

      /**
       * @brief removes hardblank from fig string
       *
       * @param figs fig string
       * @param hb hardblank
       */
      fig_str_type rm_hardblank(fig_str_type &figs) const
      {
        for (size_type i = 0; i < figs.size(); ++i)
        {
          std::replace(figs[i].begin(), figs[i].end(), this->hard_blank, traits_type::to_char_type(' '));
        }

        return figs;
      }

    public:
      basic_base_figlet_style(): hard_blank(' '), height(0) {}  // Default Constructor

      /**
       * @brief set the hard blank character of fig string
       */
      void set_hard_blank(char_type hb)
      {
        this->hard_blank = hb;
      }

      /**
       * @brief set the height of fig string
       */
      void set_height(size_type h)
      {
        this->height = h;
      }

      /**
       * @brief Get the Shrink Level
       */
      virtual shrink_type get_shrink_level() const = 0;

      /**
       * @brief Get the Fig string
       */
      virtual fig_str_type get_fig_str(std::vector<fig_char_type> fig_chs) const = 0;
    };
  }
}

#endif  // SRILAKSHMIKANTHANP_LIBFIGLET_ABSTRACT_HPP

// Copyright (c) 2022 Sri Lakshmi Kanthan P
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef SRILAKSHMIKANTHANP_UTILITIES_FUNCTIONS_HPP
#define SRILAKSHMIKANTHANP_UTILITIES_FUNCTIONS_HPP

namespace srilakshmikanthanp
{
  namespace libfiglet
  {
    /**
     * @brief convert ascii string to string_type_t
     *
     * @param str string to convert
     * @return string_type_t string converted
     */
    template <class string_type_t>
    string_type_t cvt(const std::string str)
    {
      return string_type_t(str.begin(), str.end());
    }
  }
}

#endif

// Copyright (c) 2022 Sri Lakshmi Kanthan P
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

// Header guard
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

#endif // SRILAKSHMIKANTHANP_TYPES_ENUMS_HPP

#include <algorithm>
#include <ostream>
#include <string>
#include <map>
#include <iomanip>
#include <regex>
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>

namespace srilakshmikanthanp
{
  namespace libfiglet
  {
    /**
     * @brief Figlet full width style
     */
    template <typename string_type_t>
    struct basic_full_width_style : public basic_base_figlet_style<string_type_t>
    {
    public:                                                         // public type definition
      using string_type   = string_type_t;                          // String Type
      using char_type     = typename string_type_t::value_type;     // Character Type
      using traits_type   = typename string_type_t::traits_type;    // Traits Type
      using size_type     = typename string_type_t::size_type;      // Size Type

      using fig_char_type = std::vector<string_type_t>;             // Figlet char
      using fig_str_type  = std::vector<string_type_t>;             // Figlet String

    private:                                                        // private typedefs
      using sstream_type  = std::basic_stringstream<char_type>;     // Sstream Type
      using ostream_type  = std::basic_ostream<char_type>;          // Ostream Type
      using istream_type  = std::basic_istream<char_type>;          // Istream Type
      using ifstream_type = std::basic_ifstream<char_type>;         // Ifstream Type
      using ofstream_type = std::basic_ofstream<char_type>;         // Ofstream Type

    protected:                                                      // Protected methods
      /**
       * @brief Add the Fig String and the Figlet Char
       */
      void add_fig_str_and_fig_char(fig_str_type& fig_str, const fig_char_type& fig_char) const
      {
        for (size_type i = 0; i < fig_char.size(); ++i)
        {
          fig_str[i] += fig_char[i];
        }
      }

    public:                                                         // public methods
      /**
       * @brief get the fig str
       */
      fig_str_type get_fig_str(std::vector<fig_char_type> fig_chrs) const override
      {
        // fig str container type
        fig_str_type fig_str(this->height);

        // verify height
        this->verify_height(fig_chrs);

        // for each fig char
        for (auto &fig_chr : fig_chrs)
        {
          this->add_fig_str_and_fig_char(fig_str, fig_chr);
        }

        // return
        return this->rm_hardblank(fig_str);
       }

       /**
        * @brief get shrink level
        */
       shrink_type get_shrink_level() const override
       {
         return shrink_type::FULL_WIDTH;
       }

     public:                                                        // static methods
      /**
       * @brief Make a full width style as shared pointer
       */
       static auto make_shared()
       {
         return std::make_shared<basic_full_width_style>();
       }
    };

    /**
      * @brief Figlet kerning style
      */
    template <typename string_type_t>
    struct basic_kerning_style : public basic_full_width_style<string_type_t>
    {
    public:                                                          // public type definition
      using string_type   = string_type_t;                           // String Type
      using char_type     = typename string_type_t::value_type;      // Character Type
      using traits_type   = typename string_type_t::traits_type;     // Traits Type
      using size_type     = typename string_type_t::size_type;       // Size Type

      using fig_char_type = std::vector<string_type_t>;              // Figlet char
      using fig_str_type  = std::vector<string_type_t>;              // Figlet String

    private:                                                         // private typedefs
      using sstream_type  = std::basic_stringstream<char_type>;      // Sstream Type
      using ostream_type  = std::basic_ostream<char_type>;           // Ostream Type
      using istream_type  = std::basic_istream<char_type>;           // Istream Type
      using ifstream_type = std::basic_ifstream<char_type>;          // Ifstream Type
      using ofstream_type = std::basic_ofstream<char_type>;          // Ofstream Type

    protected:                                                       // protected methods
      /**
       * @brief Trim deep the figlet string and char
       */
      void trim_fig_str_and_fig_char(fig_str_type &fig_str, fig_char_type &fig_chr) const
      {
        // left spaces and right spaces
        std::vector<size_type> elem;

        // count space
        for (size_type i = 0; i < fig_str.size(); ++i)
        {
          int l_count = 0, r_count = 0;

          for (auto itr = fig_str[i].rbegin(); itr != fig_str[i].rend(); ++itr)
          {
            if (*itr == ' ')
              ++l_count;
            else
              break;
          }

          for (auto itr = fig_chr[i].begin(); itr != fig_chr[i].end(); ++itr)
          {
            if (*itr == ' ')
              ++r_count;
            else
              break;
          }

          elem.push_back(l_count + r_count);
        }

        // minimum
        const auto min = *std::min_element(elem.begin(), elem.end());

        // for each line
        for (size_type i = 0; i < fig_str.size(); ++i)
        {
          size_type siz = min + 1;

          while (--siz > 0 && fig_str[i].back() == ' ')
          {
            fig_str[i].pop_back();
          }

          fig_chr[i].erase(0, siz);
        }
      }

    public:                                                          // Public overrides
      /**
       * @brief get the fig str
       */
      fig_str_type get_fig_str(std::vector<fig_char_type> fig_chrs) const override
      {
        // fig str container type
        fig_str_type fig_str(this->height);

        // verify height
        this->verify_height(fig_chrs);

        // for each fig char
        for (auto &fig_chr : fig_chrs)
        {
          this->trim_fig_str_and_fig_char(fig_str, fig_chr);
          this->add_fig_str_and_fig_char(fig_str, fig_chr);
        }

        // return
        return this->rm_hardblank(fig_str);
      }

      /**
       * @brief get shrink level
       */
      shrink_type get_shrink_level() const override
      {
        return shrink_type::KERNING;
      }

    public:                                                           // static methods
      /**
       * @brief Make a kerning style as shared pointer
       */
      static auto make_shared()
      {
        return std::make_shared<basic_kerning_style>();
      }
    };

    /**
     * @brief Figlet smushed style
     */
    template <typename string_type_t>
    struct basic_smushed_style : public basic_kerning_style<string_type_t>
    {
    public:                                                          // public type definition
      using string_type   = string_type_t;                           // String Type
      using char_type     = typename string_type_t::value_type;      // Character Type
      using traits_type   = typename string_type_t::traits_type;     // Traits Type
      using size_type     = typename string_type_t::size_type;       // Size Type

      using fig_char_type = std::vector<string_type_t>;              // Figlet char
      using fig_str_type  = std::vector<string_type_t>;              // Figlet String

    private:                                                         // private typedefs
      using sstream_type  = std::basic_stringstream<char_type>;      // Sstream Type
      using ostream_type  = std::basic_ostream<char_type>;           // Ostream Type
      using istream_type  = std::basic_istream<char_type>;           // Istream Type
      using ifstream_type = std::basic_ifstream<char_type>;          // Ifstream Type
      using ofstream_type = std::basic_ofstream<char_type>;          // Ofstream Type

    protected:                                                       // protected methods
      /**
       * @brief Smush Rules for the characters
       */
      auto smush_rules(char_type lc, char_type rc) const
      {
        //()
        if (lc == traits_type::to_char_type(' '))
        {
          return rc;
        }

        if (rc == traits_type::to_char_type(' '))
        {
          return lc;
        }

        //(Equal character smush)
        if (lc == rc)
        {
          return rc;
        }

        //(Underscores smush)
        if (lc == traits_type::to_char_type('_') && cvt<string_type>("|/\\[]{}()<>").find(rc) != string_type::npos)
        {
          return rc;
        }

        if (rc == traits_type::to_char_type('_') && cvt<string_type>("|/\\[]{}()<>").find(lc) != string_type::npos)
        {
          return lc;
        }

        //(Hierarchy Smushing)
        auto find_class = [](char_type ch)
        {
          if (ch == traits_type::to_char_type('|'))
          {
            return 1;
          }

          if (ch == traits_type::to_char_type('/') || ch == traits_type::to_char_type('\\'))
          {
            return 3;
          }

          if (ch == traits_type::to_char_type('[') || ch == traits_type::to_char_type(']'))
          {
            return 4;
          }

          if (ch == traits_type::to_char_type('{') || ch == traits_type::to_char_type('}'))
          {
            return 5;
          }

          if (ch == traits_type::to_char_type('(') || ch == traits_type::to_char_type(')'))
          {
            return 6;
          }

          return 0;
        };

        size_type c_lc = find_class(lc);
        size_type c_rc = find_class(rc);

        if (c_lc > c_rc)
        {
          return lc;
        }

        if (c_rc > c_lc)
        {
          return rc;
        }

        //(Opposite smush)
        if (lc == traits_type::to_char_type('[')  &&  rc == traits_type::to_char_type(']'))
        {
          return traits_type::to_char_type('|');
        }

        if (lc == traits_type::to_char_type(']')  &&  rc == traits_type::to_char_type('['))
        {
          return traits_type::to_char_type('|');
        }

        if (lc == traits_type::to_char_type('{')  &&  rc == traits_type::to_char_type('}'))
        {
          return traits_type::to_char_type('|');
        }

        if (lc == traits_type::to_char_type('}')  &&  rc == traits_type::to_char_type('{'))
        {
          return traits_type::to_char_type('|');
        }

        if (lc == traits_type::to_char_type('(')  &&  rc == traits_type::to_char_type(')'))
        {
          return traits_type::to_char_type('|');
        }

        if (lc == traits_type::to_char_type(')')  &&  rc == traits_type::to_char_type('('))
        {
          return traits_type::to_char_type('|');
        }

        //(Big X smush)
        if (lc == traits_type::to_char_type('/')  &&  rc == traits_type::to_char_type('\\'))
        {
          return traits_type::to_char_type('|');
        }

        if (lc == traits_type::to_char_type('\\') &&  rc == traits_type::to_char_type('/'))
        {
          return traits_type::to_char_type('Y');
        }

        if (lc == traits_type::to_char_type('>')  &&  rc == traits_type::to_char_type('<'))
        {
          return traits_type::to_char_type('X');
        }

        //(universal smush)
        return lc;
      }

      /**
       * @brief smush algorithm on kerned Fig string and character
       */
      void smush_fig_str_and_fig_char(fig_str_type &fig_str, fig_char_type fig_chr) const
      {
        // determine if smushable if not the just add and return
        for (size_type i = 0; i < this->height; ++i)
        {
          if ((fig_str[i].back() == this->hard_blank) && !(fig_chr[i].front() == this->hard_blank))
          {
            return this->add_fig_str_and_fig_char(fig_str, fig_chr);
          }
          else if (fig_str[i].size() == 0 || fig_str[i].size() == 0)
          {
            return this->add_fig_str_and_fig_char(fig_str, fig_chr);
          }
        }

        // smush the fig str and fig char
        for (size_type i = 0; i < fig_str.size(); ++i)
        {
          fig_str[i].back() = this->smush_rules(fig_str[i].back(), fig_chr[i].front());
          fig_chr[i].erase(fig_chr[i].begin());
        }

        // Add the fig char to the fig str
        this->add_fig_str_and_fig_char(fig_str, fig_chr);
      }

    public:                                                            // public methods
      /**
       * @brief Get the Fig string
       */
      fig_str_type get_fig_str(std::vector<fig_char_type> fig_chrs) const
      {
        // fig str container type
        fig_str_type fig_str(this->height);

        // verify the height
        this->verify_height(fig_chrs);

        // smush the chars
        for (auto &fig_char : fig_chrs)
        {
          this->trim_fig_str_and_fig_char(fig_str, fig_char);
          this->smush_fig_str_and_fig_char(fig_str, fig_char);
        }

        // remove hardblank
        return this->rm_hardblank(fig_str);
      }

      /**
       * @brief Get the shrink level
       */
      shrink_type get_shrink_level() const override
      {
        return shrink_type::SMUSHED;
      }

    public:                                                                // static methods
      /**
       * @brief Make a kerning style as shared pointer
       */
      static auto make_shared()
      {
        return std::make_shared<basic_smushed_style>();
      }
    };
  }
}

#endif // SRILAKSHMIKANTHANP_LIBFIGLET_STYLES_HPP

// Copyright (c) 2022 Sri Lakshmi Kanthan P
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

// Header guard
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

#endif // SRILAKSHMIKANTHANP_TYPES_ENUMS_HPP

// Copyright (c) 2022 Sri Lakshmi Kanthan P
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef SRILAKSHMIKANTHANP_UTILITIES_FUNCTIONS_HPP
#define SRILAKSHMIKANTHANP_UTILITIES_FUNCTIONS_HPP

namespace srilakshmikanthanp
{
  namespace libfiglet
  {
    /**
     * @brief convert ascii string to string_type_t
     *
     * @param str string to convert
     * @return string_type_t string converted
     */
    template <class string_type_t>
    string_type_t cvt(const std::string str)
    {
      return string_type_t(str.begin(), str.end());
    }
  }
}

#endif

namespace srilakshmikanthanp
{
  namespace libfiglet
  {
    // Styles for the Figlet using std::string
    using full_width  =   basic_full_width_style<std::string>;
    using kerning     =   basic_kerning_style<std::string>;
    using smushed     =   basic_smushed_style<std::string>;

    // flf Font Parser using std::string
    using flf_font    =   basic_flf_font<std::string>;

    // Figlet Driver using std::string
    using figlet      =   basic_figlet<std::string>;

    // Styles for the Figlet using std::wstring
    using wfull_width =   basic_full_width_style<std::wstring>;
    using wkerning    =   basic_kerning_style<std::wstring>;
    using wsmushed    =   basic_smushed_style<std::wstring>;

    // flf Font Parser using std::wstring
    using wflf_font   =   basic_flf_font<std::wstring>;

    // Figlet Driver using std::wstring
    using wfiglet     =   basic_figlet<std::wstring>;
  }
}

#endif // SRILAKSHMIKANTHANP_LIBFIGLET_LIBFIGLET_HPP
