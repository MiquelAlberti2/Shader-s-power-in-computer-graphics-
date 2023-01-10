#include "Camera.hpp"

#include "glm/gtx/transform.hpp"

#include <iostream>

Camera& Camera::Instance(){
    static Camera* instance = new Camera();
    return *instance;
}

void Camera::MouseLook(int mouseX, int mouseY){
    // TODO: Which vector are you modifying?
	// *hint* not the eye...
    glm::vec2 new_position = glm::vec2(mouseX, mouseY);
    glm::vec2 movement_vector = glm::vec2(-new_position.x + m_oldMousePosition.x,
                                          -new_position.y + m_oldMousePosition.y);
    
    //look 'right to left'
    m_viewDirection=glm::rotate(m_viewDirection,
                                movement_vector.x * MOUSE_SPEED,
                                m_upVector);

    //we need a new axis of rotation to look up and down
    glm::vec3 right = glm::cross(m_viewDirection, m_upVector);

    //look 'up and down'
    m_viewDirection=glm::rotate(m_viewDirection,
                                movement_vector.y * MOUSE_SPEED,
                                right);

    m_oldMousePosition = new_position;
}

void Camera::MoveForward(float speed){
    // TODO: Which vector are you modifying?
    m_eyePosition += m_viewDirection * speed;
}

void Camera::MoveBackward(float speed){
    // TODO: Which vector are you modifying?
    m_eyePosition -= m_viewDirection * speed;
}

void Camera::MoveLeft(float speed){
    // TODO: Which vector are you modifying?
    glm::vec3 right = glm::cross(m_viewDirection, m_upVector);
    m_eyePosition -= right * speed;
}

void Camera::MoveRight(float speed){
    // TODO: Which vector are you modifying?
    glm::vec3 right = glm::cross(m_viewDirection, m_upVector);
    m_eyePosition += right * speed;
}

void Camera::MoveUp(float speed){
    // TODO: Which vector are you modifying?
    m_eyePosition += m_upVector * speed;
}

void Camera::MoveDown(float speed){
    // TODO: Which vector are you modifying?
    m_eyePosition -= m_upVector * speed;
}

float Camera::GetEyeXPosition(){
    return m_eyePosition.x;
}

float Camera::GetEyeYPosition(){
    return m_eyePosition.y;
}

float Camera::GetEyeZPosition(){
    return m_eyePosition.z;
}

float Camera::GetViewXDirection(){
    return m_viewDirection.x;
}

float Camera::GetViewYDirection(){
    return m_viewDirection.y;
}

float Camera::GetViewZDirection(){
    return m_viewDirection.z;
}

Camera::Camera(){
    std::cout << "Created a Single Camera!\n";
	// Position us at the origin.
    m_eyePosition = glm::vec3(0.0f,0.0f, 0.0f);
	// Looking down along the z-axis initially.
	// Remember, this is negative because we are looking 'into' the scene.
    m_viewDirection = glm::vec3(0.0f,0.0f, -1.0f);
	// For now--our upVector always points up along the y-axis
    m_upVector = glm::vec3(0.0f, 1.0f, 0.0f);
}

// Set the position for the camera
void Camera::SetCameraEyePosition(float x, float y, float z){
    m_eyePosition.x = x;
    m_eyePosition.y = y;
    m_eyePosition.z = z;
}

glm::mat4 Camera::GetWorldToViewmatrix() const{
    // Think about the second argument and why that is
    // setup as it is.
    return glm::lookAt( m_eyePosition,
                        m_eyePosition + m_viewDirection,
                        m_upVector);
}