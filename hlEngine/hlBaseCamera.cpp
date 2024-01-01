#include "hlBaseCamera.h"


Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch, float roll)

    : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(10.0f), MouseSensitivity(0.2f), Zoom(60.0f), Roll(0.0f) {
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch, float roll)

    : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(10.0f), MouseSensitivity(0.2f), Zoom(60.0f), Roll(0.0f) {
    Position = glm::vec3(posX, posY, posZ);
    WorldUp = glm::vec3(upX, upY, upZ);
    Yaw = yaw;
    Pitch = pitch;
    Roll = roll;
    MovementSpeed = 10.0f;
    updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix()
{

    return glm::lookAt(Position, Position + Front, Up);

}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{


    float velocity = MovementSpeed * deltaTime;
    if (CameraMode) {
        velocity *= 2.0f; // Увеличиваем скорость в режиме камеры
    }

    switch (direction) {
    case FORWARD:
        Position += Front * velocity;
        break;
    case BACKWARD:
        Position -= Front * velocity;
        break;
    case LEFT:
        Position -= Right * velocity;
        break;
    case RIGHT:
        Position += Right * velocity;
        break;
    }

}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{

    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    if (constrainPitch) {
        if (Pitch > 89.0f) {
            Pitch = 89.0f;
        }
        if (Pitch < -89.0f) {
            Pitch = -89.0f;
        }
    }

    updateCameraVectors();

}

void Camera::ProcessMouseScroll(float yoffset)
{

    if (Zoom >= 1.0f && Zoom <= 45.0f) {
        Zoom -= yoffset;
    }
    if (Zoom <= 1.0f) {
        Zoom = 1.0f;
    }
    if (Zoom >= 45.0f) {
        Zoom = 45.0f;
    }

}

void Camera::updateCameraVectors()
{

    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);

    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));

    // Поворот камеры вокруг своей оси (Roll)
    glm::mat4 rollMatrix = glm::mat4(1.0f);
    rollMatrix = glm::rotate(rollMatrix, glm::radians(Roll), Front);
    Right = glm::mat3(rollMatrix) * Right;
    Up = glm::mat3(rollMatrix) * Up;

}