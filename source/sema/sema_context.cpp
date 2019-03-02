#include "sema/sema_context.hpp"
#include "sema/sema_function.hpp"
#include "sema_context.hpp"


namespace cmsl
{
    namespace sema
    {

        sema_context::sema_context(const sema_context_interface* parent, context_type context_type)
            : m_parent{ parent }
            , m_context_type{ context_type }
        {}

        void sema_context::add_function(const sema_function& function)
        {
            m_functions.push_back(&function);
        }

        void sema_context::add_type(const sema_type& type)
        {
            m_types.emplace_back(&type);
        }

        const sema_type* sema_context::find_type(cmsl::string_view name) const
        {
            if(auto found = find_type_in_this_scope(name))
            {
                return found;
            }

            return m_parent ? m_parent->find_type(name) : nullptr;
        }

        const sema_type* sema_context::find_type_in_this_scope(cmsl::string_view name) const
        {
            const auto pred = [name](const auto& type)
            {
                return name == type->name().str();
            };

            const auto found = std::find_if(std::cbegin(m_types), std::cend(m_types), pred);

            return found != std::cend(m_types) ? *found : nullptr;
        }

        const sema_function* sema_context::find_function(cmsl::string_view name) const
        {
            if(auto found = find_function_in_this_scope(name))
            {
                return found;
            }

            return m_parent ? m_parent->find_function(name) : nullptr;
        }

        const sema_function* sema_context::find_function_in_this_scope(cmsl::string_view name) const
        {
            const auto pred = [name](const auto& function)
            {
                return name == function->signature().name.str();
            };

            const auto found = std::find_if(std::cbegin(m_functions), std::cend(m_functions), pred);
            return found != std::cend(m_functions) ? *found : nullptr;
        }

        sema_context_interface::context_type sema_context::type() const
        {
            return m_context_type;
        }
    }
}
