#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Vec3;

class Matrix {
public:
	glm::mat4x4 _m;

public:
    static Matrix IDENTITY;

    Matrix() : _m(1.0f) {};
    Matrix(const glm::mat4& other) : _m(other) {};

	void translate(const Vec3& vec);
	void translate(float x, float y, float z);

	void scale(float allAxis);
	void scale(const Vec3& scale);
    void scale(float scaleX, float scaleY, float scaleZ);

    void rotate(float angleDeg, float x, float y, float z);
	void rotateRad(float angleRad, float x, float y, float z);

    void rotateXDegrees(float angle);
    void rotateYDegrees(float angle);
    void rotateZDegrees(float angle);

    void rotateXRadians(float angleRad);
    void rotateYRadians(float angleRad);
    void rotateZRadians(float angleRad);
};