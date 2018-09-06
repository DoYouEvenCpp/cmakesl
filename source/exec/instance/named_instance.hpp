#pragma once

#include "ast/type.hpp"
#include "exec/instance/instance.hpp"

namespace cmsl
{
    namespace exec
    {
        class execution_context;

        namespace inst
        {
            class named_instance : public instance
            {
            public:
                named_instance(cmsl::string_view name,
                               execution_context &ctx);

                instance_value_t get_value() const override;
                instance_value_t& get_value_ref() override;
                void assign(instance_value_t val) override;
                std::unique_ptr<instance> copy() const override;
                instance* get_member(cmsl::string_view name) override;
                bool has_function(cmsl::string_view name) const override;
                const ast::function* get_function(cmsl::string_view name) const override;
                const ast::type& get_type() const override;

            private:
                cmsl::string_view m_name;
                execution_context &m_ctx;
                instance* m_instance;
            };
        }
    }
}
