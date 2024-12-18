﻿#include "../exercise.h"
#include <cmath>
#include <type_traits>

enum class DataType {
    Float,
    Double,
};

/// @brief Tagged union 即标签化联合体，是联合体的一种常见应用。
///        Rust enum 在实现上就是标签化联合体。
struct TaggedUnion {
    DataType type;
    // NOTICE: struct/union 可以相互任意嵌套。
    union {
        float f;
        double d;
    };
    TaggedUnion(DataType t) : type(t) {}
};

// TODO: 将这个函数模板化用于 sigmoid_dyn
template<typename T>
T sigmoid(T x) {
    return static_cast<T>(1) / (static_cast<T>(1) + std::exp(-x));
}
template<typename T>
TaggedUnion sigmoid_dyn(const TaggedUnion& x) {
    TaggedUnion ans(x.type);
    if (x.type == DataType::Float) {
        ans.f = sigmoid(x.f);
    } else if (x.type == DataType::Double) {
        ans.d = sigmoid(x.d);
    }
    return ans;
}
TaggedUnion sigmoid_dyn(TaggedUnion x) {
    if (x.type == DataType::Float) {
        x.f = sigmoid(x.f);
    } else if (x.type == DataType::Double) {
        x.d = sigmoid(x.d);
    }
    return x;
}

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    TaggedUnion xf{DataType::Float};
    xf.f = 5.f;
    auto yf = sigmoid_dyn(xf);
    ASSERT(yf.type == DataType::Float, "type mismatch");
    ASSERT(yf.f == 1 / (1 + std::exp(-5.f)), "sigmoid float");

    TaggedUnion xd{DataType::Double};
    xd.d = 5.0;
    auto yd = sigmoid_dyn(xd);
    ASSERT(yd.type == DataType::Double, "type mismatch");
    ASSERT(yd.d == 1 / (1 + std::exp(-5.0)), "sigmoid double");
    return 0;
}