#pragma once

#include <cmath>

namespace activation
{
    enum Function
    {
        Linear,
        Tanh,
        ReLU,
        LeakyReLU,
        Sigmoid
    };

    static float leak_factor = 0.001f;
    
    static float linear(float x)
    {
        return x;
    }

    static float linear_derivative(float x)
    {
        return 1.0f;
    }

    static float tanh(float x)
    {
        return ::tanh(x);
    }

    static float tanh_derivative(float x)
    {
        const float u = ::tanh(x);

        return 1.f - u * u;
    }

    static float relu(float x)
    {
        return x > 0.f ? x : 0.f;
    }

    static float relu_derivative(float x)
    {
        return x > 0.f ? 1.f : 0.f;
    }

    static float leaky_relu(float x)
    {
        return x > 0.f ? x : leak_factor * x;
    }

    static float leaky_relu_derivative(float x)
    {
        return x > 0.f ? 1.f : leak_factor;
    }

    static float sigmoid(float x)
    {
        return 1.f / (1.f + exp(-x));
    }

    static float sigmoid_derivative(float x)
    {
        const float u = sigmoid(x);

        return u * (1.f - u);
    }
}