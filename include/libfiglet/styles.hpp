// Copyright (c) 2022 Sri Lakshmi Kanthan P
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef SRILAKSHMIKANTHANP_LIBFIGLET_STYLES_HPP
#define SRILAKSHMIKANTHANP_LIBFIGLET_STYLES_HPP

#include "abstract.hpp"
#include "types.hpp"

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

        // Space character
        const char_type space = traits_type::to_char_type(' ');

        // count space
        for (size_type i = 0; i < fig_str.size(); ++i)
        {
          int l_count = 0, r_count = 0;

          for (auto itr = fig_str[i].rbegin(); itr != fig_str[i].rend(); ++itr)
          {
            if (*itr == space)
              ++l_count;
            else
              break;
          }

          for (auto itr = fig_chr[i].begin(); itr != fig_chr[i].end(); ++itr)
          {
            if (*itr == space)
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

          while (--siz > 0 && fig_str[i].back() == space)
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

    private:                                                         // Private smush parameters
      /**
       * @brief Smush Rules for the characters
       */
      bool smush_chars(char_type &current, char_type &next) const
      {
        // Smushing rules based on the Figlet specification
        // This is a simplified implementation; full implementation would have more rules

        const char_type space = traits_type::to_char_type(' ');

        // Rule 1: Equal characters smush to a single character
        if (current == next && current != space)
        {
          current = next;
          return true;
        }

        // Rule 2: One character is space, other is not
        if (current == space && next != space)
        {
          current = next;
          return true;
        }

        if (current != space && next == space)
        {
          return true;
        }

        return false;
      }

    protected:                                                       // protected methods
      /**
       * @brief Smush the figlet strings
       */
      void smush_fig_str_and_fig_char(fig_str_type &fig_str, fig_char_type &fig_chr) const
      {
        // For each line
        for (size_type i = 0; i < fig_str.size(); ++i)
        {
          // Get reference to current line strings
          string_type &str_line = fig_str[i];
          const string_type &chr_line = fig_chr[i];

          // Space character
          const char_type space = traits_type::to_char_type(' ');

          // Find overlapping position
          size_type str_len = str_line.length();
          size_type chr_len = chr_line.length();

          // Start from the end of str_line
          size_type overlap = 0;
          size_type max_overlap = std::min(str_len, chr_len);

          // Check for smushable overlap
          for (size_type i_ov = 0; i_ov < max_overlap; ++i_ov)
          {
            char_type str_char = str_line[str_len - max_overlap + i_ov];
            char_type chr_char = chr_line[i_ov];

            if (str_char != space && chr_char != space)
            {
              if (smush_chars(str_char, chr_char))
              {
                overlap = i_ov + 1;
                str_line[str_len - max_overlap + i_ov] = str_char;
              }
              else
              {
                break;
              }
            }
            else if (str_char == space || chr_char == space)
            {
              overlap = i_ov + 1;
            }
          }

          // Append the remaining part
          if (overlap < chr_len)
          {
            str_line += chr_line.substr(overlap);
          }
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
          this->smush_fig_str_and_fig_char(fig_str, fig_chr);
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
        return shrink_type::SMUSHED;
      }

    public:                                                           // static methods
      /**
       * @brief Make a smushed style as shared pointer
       */
      static auto make_shared()
      {
        return std::make_shared<basic_smushed_style>();
      }
    };
  }
}

#endif // SRILAKSHMIKANTHANP_LIBFIGLET_STYLES_HPP
