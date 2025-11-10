#include "mc/src-deps/renderer/Matrix.hpp"
#include "Matrix.hpp"
#include <mc/src/common/world/phys/Vec3.hpp>

Matrix Matrix::IDENTITY = Matrix();

void Matrix::translate(const Vec3& vec) 
{
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(vec.x, vec.y, vec.z));
    _m = _m * translationMatrix;
}

void Matrix::translate(float x, float y, float z) 
{
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
    _m = _m * translationMatrix;
}

void Matrix::scale(float allAxis) {
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(allAxis, allAxis, allAxis));
	_m = _m * scaleMatrix;
}

void Matrix::scale(const Vec3& scale) {
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(scale.x, scale.y, scale.z));
	_m = _m * scaleMatrix;
}

void Matrix::scale(float scaleX, float scaleY, float scaleZ)
{
    glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(scaleX, scaleY, scaleZ));
    _m = _m * scaleMatrix;
}

void Matrix::rotate(float angle, float x, float y, float z)
{
    // note: it IS accurate that mc takes angle in degrees, not radians
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(x, y, z));
    _m = _m * rotationMatrix;
}

void Matrix::rotateRad(float angleRad, float x, float y, float z) {
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), angleRad, glm::vec3(x, y, z));
    _m = _m * rotationMatrix;
}

void Matrix::rotateXDegrees(float angle) {
    rotate(angle, 1.0f, 0.0f, 0.0f);
}

void Matrix::rotateYDegrees(float angle) {
    rotate(angle, 0.0f, 1.0f, 0.0f);
}

void Matrix::rotateZDegrees(float angle) {
    rotate(angle, 0.0f, 0.0f, 1.0f);
}

void Matrix::rotateXRadians(float angleRad) {
    rotateRad(angleRad, 1.0f, 0.0f, 0.0f);
}

void Matrix::rotateYRadians(float angleRad) {
    rotateRad(angleRad, 0.0f, 1.0f, 0.0f);
}

void Matrix::rotateZRadians(float angleRad) {
    rotateRad(angleRad, 0.0f, 0.0f, 1.0f);
}