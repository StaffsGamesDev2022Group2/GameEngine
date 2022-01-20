#pragma once
#include"..\Events\Event.h"
namespace Firelight::Events::Input {
	class KeyboardEvent: public Events::Event
	{
	public:
		enum class KeyEvent
		{
			press,
			release,
			Invalid

		};
		KeyboardEvent();
		KeyboardEvent(const KeyEvent type, const unsigned char key);

		bool isPressed() const;
		bool isReleased() const;
		bool isValid() const;
		unsigned char GetKeyCode() const;
		
		static constexpr DescriptorType sm_Description = "KeyboardEvent";

		virtual DescriptorType Type() const override
		{
			return sm_Description;
		}
	protected:
		KeyEvent m_Type;
		unsigned char m_Key;
	};


	class OnKeyPress : public KeyboardEvent
	{
	public:
		OnKeyPress();
		OnKeyPress(const KeyEvent type, const unsigned char key);
		~OnKeyPress();
		static constexpr DescriptorType sm_Description = "OnKeyPress";

		virtual DescriptorType Type() const override
		{
			return sm_Description;
		}
	private:

	};

	
	class OnKeyRelease : public KeyboardEvent
	{
	public:
		OnKeyRelease();
		OnKeyRelease(const KeyEvent type, const unsigned char key);
		~OnKeyRelease();

		static constexpr DescriptorType sm_Description = "OnKeyRelease";

		virtual DescriptorType Type() const override
		{
			return sm_Description;
		}
	private:

	};
}