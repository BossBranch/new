#pragma once
#include <stack>
#include "mc/src-deps/renderer/Matrix.hpp"

class MatrixStack {
public:
    /* this + 0  */ std::stack<Matrix, std::deque<Matrix>> stack;
    /* this + 41 */ std::byte padding41[16];
    /* this + 56 */ bool _isDirty;
    /* this + 57 */ std::byte padding57[7];

    class MatrixStackRef {
    public:
        MatrixStack* stack;
        Matrix* mat;

        Matrix* operator->()
        {
            stack->_isDirty = true;
            return mat;
        }

        Matrix& operator*()
        {
            stack->_isDirty = true;
            return *mat;
        }
    };

    Matrix& getTop() {
        return stack.top();
    }

    const Matrix& getTop() const {
        return stack.top();
    }

    MatrixStackRef push(const Matrix& matrix) {
        stack.push(matrix);
        _isDirty = true;
		return { this, &stack.top() };
    }

	MatrixStack::MatrixStackRef push() {
		if (stack.empty()) {
			stack.push(Matrix());
		} else {
			stack.push(stack.top());
		}

		_isDirty = true;
		return { this, &stack.top() };
	}

	void pop() {
        if (!stack.empty()) {
            stack.pop();
            _isDirty = true;
        }
    }
};

static_assert(sizeof(MatrixStack) == 64);