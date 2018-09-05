#include "lexer/lexer.hpp"
#include "exec/source_executor.hpp"

#include <iostream>

int main()
{
    const auto source =
        "int main()"
        "{"
        "    list<int> l;"
        "    return l.size();"
        "}";

    cmsl::exec::source_executor exec;
    auto ret = exec.execute(source);
    std::cout << ret << '\n';
}
