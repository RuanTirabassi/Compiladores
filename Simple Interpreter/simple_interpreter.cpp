#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <cctype>

enum TokenType
{
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,
    TOKEN_EOF
};

struct Token
{
    TokenType type;
    std::string value;
};

std::vector<Token> tokenize(const std::string &input)
{
    std::vector<Token> tokens;
    size_t i = 0;

    while (i < input.length())
    {
        if (std::isspace(input[i]))
        {
            i++;
            continue;
        }

        if (std::isdigit(input[i]))
        {
            std::string number;
            while (i < input.length() && std::isdigit(input[i]))
            {
                number += input[i];
                i++;
            }
            tokens.push_back({TOKEN_NUMBER, number});
            continue;
        }

        switch (input[i])
        {
        case '+':
            tokens.push_back({TOKEN_PLUS, "+"});
            break;
        case '-':
            tokens.push_back({TOKEN_MINUS, "-"});
            break;
        case '':
            tokens.push_back({TOKEN_STAR, ""});
            break;
        case '/':
            tokens.push_back({TOKEN_SLASH, "/"});
            break;
        default:
            std::cerr << "Unexpected character: " << input[i] << std::endl;
            exit(1);
        }
        i++;
    }

    tokens.push_back({TOKEN_EOF, ""});
    return tokens;
}

struct ASTNode
{
    virtual ~ASTNode() = default;
};

struct NumberNode : ASTNode
{
    int value;
    explicit NumberNode(int val) : value(val) {}
};

struct BinaryOpNode : ASTNode
{
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;
    TokenType op;

    BinaryOpNode(std::unique_ptr<ASTNode> left, TokenType op, std::unique_ptr<ASTNode> right)
        : left(std::move(left)), op(op), right(std::move(right)) {}
};

class Parser
{
    std::vector<Token> tokens;
    size_t current = 0;

    Token peek()
    {
        return tokens[current];
    }

    Token advance()
    {
        if (current < tokens.size())
        {
            current++;
        }
        return tokens[current - 1];
    }

    Token consume(TokenType type, const std::string &message)
    {
        if (peek().type == type)
        {
            return advance();
        }
        std::cerr << message << std::endl;
        exit(1);
    }

    std::unique_ptr<ASTNode> expression()
    {
        return term();
    }

    std::unique_ptr<ASTNode> term()
    {
        auto node = factor();
        while (peek().type == TOKEN_PLUS || peek().type == TOKEN_MINUS)
        {
            TokenType op = advance().type;
            auto right = factor();
            node = std::make_unique<BinaryOpNode>(std::move(node), op, std::move(right));
        }
        return node;
    }

    std::unique_ptr<ASTNode> factor()
    {
        auto node = primary();
        while (peek().type == TOKEN_STAR || peek().type == TOKEN_SLASH)
        {
            TokenType op = advance().type;
            auto right = primary();
            node = std::make_unique<BinaryOpNode>(std::move(node), op, std::move(right));
        }
        return node;
    }

    std::unique_ptr<ASTNode> primary()
    {
        if (peek().type == TOKEN_NUMBER)
        {
            int value = std::stoi(advance().value);
            return std::make_unique<NumberNode>(value);
        }
        std::cerr << "Expected number" << std::endl;
        exit(1);
    }

public:
    explicit Parser(const std::vector<Token> &tokens) : tokens(tokens) {}

    std::unique_ptr<ASTNode> parse()
    {
        return expression();
    }
};

int evaluate(const std::unique_ptr<ASTNode> &node)
{
    if (auto number = dynamic_cast<NumberNode *>(node.get()))
    {
        return number->value;
    }

    if (auto binOp = dynamic_cast<BinaryOpNode *>(node.get()))
    {
        int leftValue = evaluate(binOp->left);
        int rightValue = evaluate(binOp->right);
        switch (binOp->op)
        {
        case TOKEN_PLUS:
            return leftValue + rightValue;
        case TOKEN_MINUS:
            return leftValue - rightValue;
        case TOKEN_STAR:
            return leftValue * rightValue;
        case TOKEN_SLASH:
            return leftValue / rightValue;
        default:
            std::cerr << "Unknown operator" << std::endl;
            exit(1);
        }
    }

    std::cerr << "Unknown node type" << std::endl;
    exit(1);
}

int main()
{
    std::string input = "5 + 5 * 5";
    auto tokens = tokenize(input);

    Parser parser(tokens);
    auto ast = parser.parse();

    int result = evaluate(ast);
    std::cout << "Result: " << result << std::endl;

    return 0;
}