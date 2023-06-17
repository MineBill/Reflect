#pragma once

#include "Core/Util.h"
#include "TypeId.h"

#include <typeinfo>

namespace Reflect
{
    /// @brief A Type is a representation of a type. This would include the type name, type size and if it is a fundamental type or not. 
    /// This is Reflect's version of c++ typeid but with some additional data.
    class REFLECT_API Type
    {
    public:
        Type();
        Type(std::string_view typeName, uint64_t typeSize);
        ~Type();

        /// @brief Make a 'Type' from a template arguement.
        /// @tparam T 
        /// @return 
        template<typename T>
        static Type MakeType()
        {
            if constexpr (std::is_void_v<T>)
            {
                Type type("void", 0);
                return type;
            }
            else
            {
                Type type(Util::GetTypeName<T>(), sizeof(T));
                return type;
            }
        }

        operator bool() const;
        bool IsValid() const;

        const TypeId& GetTypeId() const;

        /// @brief Return TypeName with namespaces.
        /// @return std::string_view
        std::string_view GetTypeName() const;
        /// @brief Return TypeName without namespaces.
        /// @return std::string_view
        std::string_view GetPrettyTypeName() const;

        uint64_t GetTypeSize() const;

    private:
        TypeId m_typeId;

        /// @brief TypeName with no namespaces.
        std::string m_prettyTypeName;
        uint64_t m_typeSize = 0;
    };
}