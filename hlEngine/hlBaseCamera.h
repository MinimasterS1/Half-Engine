#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include "Common.hpp"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class ENGINE_API Camera {
public:



    bool CameraMode = false;

    float MovementSpeed = 10.0f;
    float MouseSensitivity = 0.2f;
    float Zoom = 60.0f;
    float Roll = 0.0f;

    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    glm::mat4 projection;

    Camera(glm::vec3 position = glm::vec3(1.0f, 5.0f, 5.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f, float roll = 0.0f);
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch, float roll);



    glm::mat4 GetViewMatrix();

    void ProcessKeyboard(Camera_Movement direction, float deltaTime);

    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

    void ProcessMouseScroll(float yoffset);

    void SetSpeed(float speed) {
        MovementSpeed = speed;
        updateCameraVectors();
    }

    float GetSpeed() const {
        return MovementSpeed;
    }

    void SetPosition(glm::vec3 newPosition) {
        Position = newPosition;
        updateCameraVectors();
    }

    void SetPosition(float x, float y, float z) {
        Position = glm::vec3(x, y, z);
        updateCameraVectors();
    }

    void SetRoll(float roll) {
        Roll = roll;
        updateCameraVectors();
    }

    void SetMouseSensitivity(float sensitivity) {
        MouseSensitivity = sensitivity;
        updateCameraVectors();
    }

private:
    float Yaw;
    float Pitch;

    void updateCameraVectors();
};

#endif