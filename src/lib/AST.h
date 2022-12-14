#pragma once
#include <string>
#include <vector>

typedef enum ASTTypeID
{
    AST_ROOT,
    AST_BLOCK,
    AST_FUNC_DEF,
    AST_FUNC_CALL,
    AST_EXPRESSION,
    AST_BINARY,
    AST_LITERAL,
} ASTTypeID;

typedef enum ASTExpressionType
{
    AST_EXPR_RETURN,
    AST_EXPR_NO_RETURN,
    AST_EXPR_VAR_DEFINED,
    AST_EXPR_PRAM_LIST,
} ASTExpressionType;

typedef enum ASTDataType
{
    NOT_DETERMINED_DATA_TYPE,
    VOID_TYPE,
    INT8_TYPE,
    INT16_TYPE,
    INT32_TYPE,
    INT64_TYPE,
    UINT8_TYPE,
    UINT16_TYPE,
    UINT32_TYPE,
    UINT64_TYPE,
    FLOAT32_TYPE,
    FLOAT64_TYPE,
    FLOAT_ANY_TYPE,
    UINT_ANY_TYPE,
    INT_ANY_TYPE,
} ASTDataType;

typedef enum ASTOperatorType
{
    NOT_DETERMINED_OP_TYPE,
    ADD_TYPE,
    SUB_TYPE,
    DIV_TYPE,
    MUL_TYPE,
    AND_TYPE,
    OR_TYPE,
    XOR_TYPE,
    MOD_TYPE,
} ASTOperatorType;

struct ASTNode
{
  public:
    virtual ASTTypeID getTypeID() const noexcept = 0;
    virtual ~ASTNode() = default;
};

struct ASTRoot : public ASTNode
{
    std::string name;
    std::vector<const ASTNode *> children;
    ASTTypeID getTypeID() const noexcept override
    {
        return AST_ROOT;
    }

    constexpr ASTRoot(const std::string &name) noexcept
        : name(name)
    {
    }

    virtual ~ASTRoot()
    {
        children.clear();
    }
};

struct ASTExpression : public ASTNode
{
    std::vector<const ASTNode *> list;
    ASTExpressionType type;
    ASTDataType data_type = NOT_DETERMINED_DATA_TYPE;
    std::string extra_data = "";
    ASTTypeID getTypeID() const noexcept override
    {
        return AST_EXPRESSION;
    }

    virtual ~ASTExpression()
    {
        list.clear();
    }
};

struct ASTBlock : public ASTNode
{
    std::vector<const ASTExpression *> list;
    ASTTypeID getTypeID() const noexcept override
    {
        return AST_BLOCK;
    }
    virtual ~ASTBlock()
    {
        list.clear();
    }
};

struct ASTFuncDef : public ASTNode
{
    const std::string name = "";
    const bool is_public;
    const ASTExpression *args;
    ASTBlock *body;
    ASTDataType return_type = NOT_DETERMINED_DATA_TYPE;
    ASTTypeID getTypeID() const noexcept override
    {
        return AST_FUNC_DEF;
    }
    explicit ASTFuncDef(const std::string name_in, bool is_public)
        : name(name_in)
        , is_public(is_public)
    {
    }
    virtual ~ASTFuncDef()
    {
        if (args)
            delete args;
        if (body)
            delete body;
    }
};

struct ASTBinaryExpression : public ASTNode
{
    uint16_t precedence = 0;
    const ASTNode *right = nullptr;
    const ASTNode *left = nullptr;
    ASTOperatorType op = NOT_DETERMINED_OP_TYPE;
    ASTTypeID getTypeID() const noexcept override
    {
        return AST_BINARY;
    }
    virtual ~ASTBinaryExpression()
    {
        if (left)
            delete left;
        if (right)
            delete right;
    }
};

struct ASTLiteral : public ASTNode
{
    std::string value = "";
    ASTDataType data_type = NOT_DETERMINED_DATA_TYPE;
    ASTTypeID getTypeID() const noexcept override
    {
        return AST_LITERAL;
    }

    virtual ~ASTLiteral() = default;
};