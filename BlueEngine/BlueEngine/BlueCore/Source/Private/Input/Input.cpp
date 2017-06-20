#include "Input/Input.h"
#include <memory>

namespace Blue
{
	Input Input::mInstance;
	Input::Input()
	{
		std::memset(mInstance.mKeys, 0, _countof(mInstance.mKeys));
		std::memset(mInstance.mMouseButton, 0, _countof(mInstance.mMouseButton));
		std::memset(mInstance.mHeldKeys, 0, _countof(mInstance.mHeldKeys));
		std::memset(mInstance.mHeldMouseButton, 0, _countof(mInstance.mHeldMouseButton));
	}
	Input::~Input()
	{

	}

	bool Input::GetKeyDown(const int aKeyCode)
	{
		return mInstance.mHeldKeys[aKeyCode];
	}

	bool Input::GetKeyPressed(const int aKeyCode)
	{
		return mInstance.mKeys[aKeyCode];
	}

	bool Input::IsKeyboardCaptured()
	{
		return mInstance.mKeyboardCapture;
	}

	bool Input::GetMouseButtonDown(const int aMouseButton)
	{
		return mInstance.mHeldMouseButton[aMouseButton];
	}

	bool Input::GetMouseButtonPressed(const int aMouseButton)
	{
		return mInstance.mMouseButton[aMouseButton];
	}

	void Input::GetMousePosition(float& a_x, float& aY)
	{
		a_x = mInstance.mMouseX;
		aY = mInstance.mMouseY;

	}

	void Input::GetMouseMove(float& aX, float& aY)
	{
		aX = mInstance.mMouseMoveX;
		aY = mInstance.mMouseMoveY;
	}

	bool Input::isMouseOverUI()
	{
		return mInstance.mMouseCapture;
	}

	void Input::Reset()
	{
		std::memset(mInstance.mKeys, 0, _countof(mInstance.mKeys));
		std::memset(mInstance.mMouseButton, 0, _countof(mInstance.mMouseButton));
	}

	void Input::OnKeyDown(const int aKeyCode)
	{
		mInstance.mHeldKeys[aKeyCode] = true;
		mInstance.mKeys[aKeyCode] = true;
	}

	void Input::OnKeyUp(const int aKeyCode)
	{
		mInstance.mHeldKeys[aKeyCode] = false;
	}

	void Input::OnMouseButtonDown(const int aMouseButton)
	{
		mInstance.mHeldMouseButton[aMouseButton] = true;
		mInstance.mMouseButton[aMouseButton] = true;
	}

	void Input::OnMouseButtonUp(const int aMouseButton)
	{
		mInstance.mHeldMouseButton[aMouseButton] = false;
	}

	void Input::OnMouseMove(const float a_x, const float aY)
	{
		mInstance.mMouseMoveX = a_x;
		mInstance.mMouseMoveY = aY;
	}

	void Input::OnMouseScroll(const float a_x, const float aY)
	{
		mInstance.mScrollX = a_x;
		mInstance.mScrollY = aY;
	}

	void Input::SetMousePosition(const float a_x, const float aY)
	{
		mInstance.mMouseX = a_x;
		mInstance.mMouseY = aY;
	}

	void Input::SetMouseCapture(const bool aCapture)
	{
		mInstance.mMouseCapture = aCapture;
	}

	void Input::SetKeyboardCapture(const bool aCapture)
	{
		mInstance.mKeyboardCapture = aCapture;
	}
}