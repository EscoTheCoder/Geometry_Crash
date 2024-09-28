#include "Player.h"
#include "GameState.h"
#include "util.h"
#include <sgg/graphics.h>
#include <iostream>

Player::Player(const std::string& name) :
    GameObject(name)
{
    m_width = 0.4f;
    m_height = 0.4f;
}

void Player::init() {
    m_pos_x = m_state->getCanvasDimensions().first / 4.0f;  // Starting position (left side)
    m_pos_y = m_state->getCanvasDimensions().second / 2.0f;
    m_velocity_y = 0.0f;

    m_initial_pos_x = m_pos_x;
    m_initial_pos_y = m_pos_y;

    m_brush_player.fill_opacity = 1.0f;
    m_brush_player.outline_opacity = 0.0f;
    m_brush_player.texture = m_state->getFullAssetPath("blob.png");

    m_brush_player_debug.fill_opacity = 0.1f;
    SETCOLOR(m_brush_player_debug.fill_color, 1.0f, 0.0f, 0.0f);
    SETCOLOR(m_brush_player_debug.outline_color, 0.0f, 0.0f, 1.0f);
}

void Player::reset() {
    // ��������� ��� ����� ��� ������ ���� ������ ���������
    m_pos_x = m_initial_pos_x;
    m_pos_y = m_initial_pos_y;
    m_velocity_y = 0.0f; // ��������� ��� ���������
    // �������� �� ����������� ����� �����������, ���� � ����������, �� ����������
}




void Player::movePlayer(float dt) {
    float delta_time = dt / 1000.0f; // Convert milliseconds to seconds

    // Jumping logic
    graphics::MouseState mouse;
    graphics::getMouseState(mouse);

    if (m_velocity_y == 0) {
        m_velocity_y -= (graphics::getKeyState(graphics::SCANCODE_SPACE) || mouse.button_left_pressed) ? m_jump_force : 0;
    }

    // Apply gravity
    m_velocity_y += m_gravity * delta_time;

    // Update vertical position based on velocity
    m_pos_y += m_velocity_y * delta_time;

}



void Player::update(float dt) {
    movePlayer(dt);
}

void Player::draw() {
    graphics::drawRect(m_pos_x, m_pos_y, m_width, m_height, m_brush_player);
    debugDraw();
}

void Player::debugDraw() {
    if (m_state->m_debugging) {
        graphics::drawRect(m_pos_x, m_pos_y, m_width, m_height, m_brush_player_debug);

        char s[20];
        sprintf_s(s, "(%5.2f, %5.2f)", m_pos_x, m_pos_y);
        graphics::drawText(m_pos_x - 0.4f, m_pos_y - 0.6f, 0.15f, s, m_brush_player_debug);
    }
}

float Player::getPosX() const { return m_pos_x; }
float Player::getPosY() const { return m_pos_y; }
float Player::getWidth() const { return m_width; }
float Player::getHeight() const { return m_height; }
float Player::getVelocityY() const { return m_velocity_y; }