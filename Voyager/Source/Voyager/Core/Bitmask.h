#ifndef VE_BITMASK_H
#define VE_BITMASK_H

#include <type_traits>

namespace VE 
{
    namespace Core 
    {
        // This bitmask can only be used with enums.
        template <class OptionType, 
            typename = typename std::enable_if<std::is_enum<OptionType>::value>::type> class Bitmask
        {
            // Value of bitmask should be the same as the enum underlying type.
            using EnumType = typename std::underlying_type<OptionType>::type;

            // Avoids having to explicitly set enum values to powers of two. 
            static constexpr EnumType maskValue(OptionType option)
            {
                return 1 << static_cast<EnumType>(option);
            }

            explicit constexpr Bitmask(EnumType option) : _mask(option) {}

        public:
            constexpr Bitmask() : _mask(0) {}

            constexpr Bitmask(OptionType option) : _mask(maskValue(option)) {}

            // Set the value bit to the given option.
            constexpr Bitmask operator|(OptionType option) 
            {
                return Bitmask(_mask | (maskValue(option)));
            }

            // Get the value bit of the given option.
            constexpr bool operator& (OptionType option) 
            {
                return _mask & maskValue(option);
            }

        private:
            EnumType _mask = 0;
        };
    }

    // Creates bitmask from two options.
    template <class OptionType,
        typename = typename std::enable_if<std::is_enum<OptionType>::value>::type>
        constexpr Core::Bitmask<OptionType> operator|(OptionType lhs, OptionType rhs)
    {
        return Core::Bitmask<OptionType>{lhs} | rhs;
    }
}

#endif