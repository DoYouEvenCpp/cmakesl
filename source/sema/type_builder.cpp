#include "sema/type_builder.hpp"
#include "sema/builtin_sema_function.hpp"
#include "sema/factories.hpp"
#include "sema/sema_context_impl.hpp"
#include "sema/user_sema_function.hpp"

namespace cmsl::sema {
type_builder::type_builder(sema_type_factory& type_factory,
                           sema_function_factory& function_factory,
                           sema_context_factory& context_factory,
                           sema_context& current_ctx,
                           ast::type_representation name)
  : m_type_factory{ type_factory }
  , m_function_factory{ function_factory }
  , m_context_factory{ context_factory }
  , m_current_ctx{ current_ctx }
  , m_type_ctx{ m_context_factory.create_class(&current_ctx) }
  , m_name{ std::move(name) }
{
}

type_builder& type_builder::with_member(const member_info& member)
{
  m_members.emplace_back(member);
  return *this;
}

type_builder& type_builder::with_user_function(const sema_type& return_type,
                                               function_signature s)
{
  const auto& function =
    m_function_factory.create_user(m_type_ctx, return_type, std::move(s));
  m_type_ctx.add_function(function);
  return *this;
}

type_builder& type_builder::with_builtin_function(const sema_type& return_type,
                                                  function_signature s,
                                                  builtin_function_kind kind)
{
  const auto& function = m_function_factory.create_builtin(
    m_type_ctx, return_type, std::move(s), kind);
  m_type_ctx.add_function(function);
  return *this;
}

const sema_type& type_builder::build_and_register_in_context()
{
  const auto& type =
    m_type_factory.create(m_type_ctx, m_name, std::move(m_members));
  const auto& reference_type = m_type_factory.create_reference(type);
  m_current_ctx.add_type(type);
  m_current_ctx.add_type(reference_type);
  return type;
}

const sema_type&
type_builder::build_homogeneous_generic_and_register_in_context(
  const sema_type& value_type)
{
  const auto& type =
    m_type_factory.create_homogeneous_generic(m_type_ctx, m_name, value_type);
  const auto& reference_type = m_type_factory.create_reference(type);
  m_current_ctx.add_type(type);
  m_current_ctx.add_type(reference_type);
  return type;
}

const sema_context& type_builder::context()
{
  return m_type_ctx;
}
}