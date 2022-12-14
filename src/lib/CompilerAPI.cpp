#include "front/Parser.h"
#include <cstring>
#include <liblunascript/Compiler.h>

struct Compiler_T
{
    LunaScript::compiler::front::Parser *parser;
};

losResult compileAST(Compiler *compiler, const char *src, const data_size_t src_size, const char *filename, const data_size_t filename_size)
{
    if ((*compiler))
    {
        *compiler = new Compiler_T();
        (*compiler)->parser = new LunaScript::compiler::front::Parser(std::string(src,0,src_size), std::string(filename,0,filename_size));
        if ((*compiler)->parser->hasErrors())
            return LOS_ERROR_MALFORMED_DATA;
    }
    return LOS_SUCCESS;
}

uint8_t hasErrorOnStack(Compiler compiler)
{
    return compiler->parser->hasErrors();
}

void getErrorOffStack(Compiler compiler, char **str, data_size_t *str_size)
{
    std::string err = compiler->parser->popErrorOffStack();
    (*str) = new char[(*str_size = err.size())];
    memmove(*str,err.data(),*str_size);
}

void astToString(Compiler compiler, char **str, data_size_t *str_size)
{
    std::string err = compiler->parser->asString(true);
    (*str) = new char[(*str_size = err.size())];
    memmove(*str,err.data(),*str_size);
}

void freeCompiler(Compiler compiler)
{
    delete compiler->parser;
    delete compiler;
}