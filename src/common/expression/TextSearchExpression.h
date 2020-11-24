/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License,
 * attached with Common Clause Condition 1.0, found in the LICENSES directory.
 */

#ifndef COMMON_EXPRESSION_TEXTSEARCHEXPRESSION_H_
#define COMMON_EXPRESSION_TEXTSEARCHEXPRESSION_H_

#include "common/base/Base.h"
#include "common/expression/Expression.h"

namespace nebula {

class TextSearchArgument final {
public:
    TextSearchArgument(std::string* from, std::string* prop, std::string* val) {
        from_.reset(from);
        prop_.reset(prop);
        val_.reset(val);
    }

    ~TextSearchArgument() = default;

    void setVal(std::string *val) {
        val_.reset(val);
    }

    const std::string* from() {
        return from_.get();
    }

    const std::string* prop() {
        return prop_.get();
    }

    const std::string* val() const {
        return val_.get();
    }

    void setOP(std::string *op) {
        op_.reset(op);
    }

    const std::string* op() const {
        return op_.get();
    }

    void setFuzziness(int32_t fuzz) {
        fuzziness_ = fuzz;
    }

    int32_t fuzziness() {
        return fuzziness_;
    }

    void setLimit(int32_t limit) {
        limit_ = limit;
    }

    int32_t limit() {
        return limit_;
    }

    void setTimeout(int32_t timeout) {
        timeout_ = timeout;
    }

    int32_t timeout() {
        return timeout_;
    }

    bool operator==(const TextSearchArgument& rhs) const;

    std::string toString() const;

private:
    std::unique_ptr<std::string>                from_{nullptr};
    std::unique_ptr<std::string>                prop_{nullptr};
    std::unique_ptr<std::string>                val_{nullptr};
    std::unique_ptr<std::string>                op_{nullptr};
    int32_t                                     fuzziness_{-2};
    int32_t                                     limit_{100};
    int32_t                                     timeout_{200};
};

class TextSearchExpression : public Expression {
    friend class Expression;

public:
    TextSearchExpression(Kind kind, TextSearchArgument* arg)
        : Expression(kind) {
        arg_.reset(arg);
    }

    bool operator==(const Expression& rhs) const override;

    const Value& eval(ExpressionContext&) override {
        LOG(FATAL) << "TextSearchExpression has to be rewritten";
    }

    void accept(ExprVisitor*) override {
        LOG(FATAL) << "TextSearchExpression has to be rewritten";
    }

    std::string toString() const override;

    std::unique_ptr<Expression> clone() const override {
        return std::make_unique<TextSearchExpression>(kind_, arg_.get());
    }

    const TextSearchArgument* arg() const {
        return arg_.get();
    }

    TextSearchArgument* arg() {
        return arg_.get();
    }

    void setArgs(TextSearchArgument* arg) {
        arg_.reset(arg);
    }

private:
    void writeTo(Encoder&) const override {
        LOG(FATAL) << "TextSearchExpression has to be rewritten";
    }

    void resetFrom(Decoder&) override {
        LOG(FATAL) << "TextSearchExpression has to be reset";
    }

private:
    std::unique_ptr<TextSearchArgument>   arg_;
};

}   // namespace nebula
#endif   // COMMON_EXPRESSION_TEXTSEARCHEXPRESSION_H_
