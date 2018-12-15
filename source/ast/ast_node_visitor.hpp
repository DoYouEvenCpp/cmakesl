#pragma once

namespace cmsl
{
    namespace ast
    {
        class block_node;
        class class_node2;
        class conditional_node;
        class if_else_node;
        class binary_operator_node;
        class class_member_access_node;
        class function_call_node;
        class member_function_call_node;
        class bool_value_node;
        class int_value_node;
        class double_value_node;
        class string_value_node;
        class id_node;
        class return_node;
        class translation_unit_node;
        class user_function_node2;
        class variable_declaration_node;
        class while_node;

        class ast_node_visitor
        {
        public:
            virtual ~ast_node_visitor() = default;

            virtual void visit(block_node& node) = 0;
            virtual void visit(class_node2& node) = 0;
            virtual void visit(conditional_node& node) = 0;
            virtual void visit(if_else_node& node) = 0;
            virtual void visit(binary_operator_node& node) = 0;
            virtual void visit(class_member_access_node& node) = 0;
            virtual void visit(function_call_node& node) = 0;
            virtual void visit(member_function_call_node& node) = 0;
            virtual void visit(bool_value_node& node) = 0;
            virtual void visit(int_value_node& node) = 0;
            virtual void visit(double_value_node& node) = 0;
            virtual void visit(string_value_node& node) = 0;
            virtual void visit(id_node& node) = 0;
            virtual void visit(return_node& node) = 0;
            virtual void visit(translation_unit_node& node) = 0;
            virtual void visit(user_function_node2& node) = 0;
            virtual void visit(variable_declaration_node& node) = 0;
            virtual void visit(while_node& node) = 0;
        };
    }
}
