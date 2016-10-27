#include "Input.h"
#include <memory>

namespace BlueGengine
{
	Input Input::m_instance;
	Input::Input()
	{

		std::memset(m_instance.m_keys, 0, _countof(m_instance.m_keys));
		std::memset(m_instance.m_mouseButton, 0, _countof(m_instance.m_mouseButton));
		std::memset(m_instance.m_heldKeys, 0, _countof(m_instance.m_heldKeys));
		std::memset(m_instance.m_heldMouseButton, 0, _countof(m_instance.m_heldMouseButton));
	}
	Input::~Input()
	{

	}

	bool Input::GetKeyDown(const int a_keyCode)
	{
		return m_instance.m_heldKeys[a_keyCode];
	}

	bool Input::GetKeyPressed(const int a_keyCode)
	{
		return m_instance.m_keys[a_keyCode];
	}

	bool Input::IsKeyboardCaptured()
	{
		return m_instance.m_keyboardCapture;
	}

	bool Input::GetMouseButtonDown(const int a_mouseButton)
	{
		return m_instance.m_heldMouseButton[a_mouseButton];
	}

	bool Input::GetMouseButtonPressed(const int a_mouseButton)
	{
		return m_instance.m_mouseButton[a_mouseButton];
	}

	void Input::GetMousePosition(float& a_x, float& a_y)
	{
		a_x = m_instance.m_mouseX;
		a_y = m_instance.m_mouseY;

	}

	void Input::GetMouseMove(float& a_x, float& a_y)
	{
		a_x = m_instance.m_mouseMoveX;
		a_y = m_instance.m_mouseMoveY;

	}

	bool Input::isMouseOverUI()
	{
		return m_instance.m_mouseCapture;
	}

	void Input::Reset()
	{
		std::memset(m_instance.m_keys, 0, _countof(m_instance.m_keys));
		std::memset(m_instance.m_mouseButton, 0, _countof(m_instance.m_mouseButton));
		m_instance.m_mouseMoveX = 0;
		m_instance.m_mouseMoveY = 0;
	}

	void Input::OnKeyDown(const int a_keyCode)
	{
		m_instance.m_heldKeys[a_keyCode] = true;
		m_instance.m_keys[a_keyCode] = true;

	}

	void Input::OnKeyUp(const int a_keyCode)
	{
		m_instance.m_heldKeys[a_keyCode] = false;
	}

	void Input::OnMouseButtonDown(const int a_mouseButton)
	{
		m_instance.m_heldMouseButton[a_mouseButton] = true;
		m_instance.m_mouseButton[a_mouseButton] = true;
	}

	void Input::OnMouseButtonUp(const int a_mouseButton)
	{
		m_instance.m_heldMouseButton[a_mouseButton] = false;
	}

	void Input::OnMouseMove(const float a_x, const float a_y)
	{
		m_instance.m_mouseMoveX = a_x;
		m_instance.m_mouseMoveY = a_y;
	}

	void Input::OnMouseScroll(const float a_x, const float a_y)
	{
		m_instance.m_scrollX = a_x;
		m_instance.m_scrollY = a_y;
	}

	void Input::SetMousePosition(const float a_x, const float a_y)
	{
		m_instance.m_mouseX = a_x;
		m_instance.m_mouseY = a_y;
	}

	void Input::SetMouseCapture(const bool a_capture)
	{
		m_instance.m_mouseCapture = a_capture;
	}

	void Input::SetKeyboardCapture(const bool a_capture)
	{
		m_instance.m_keyboardCapture = a_capture;
	}

}