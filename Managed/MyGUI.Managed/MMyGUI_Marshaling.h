/*!
	@file
	@author		Albert Semenov
	@date		01/2009
	@module
*/
#pragma once

#include <MyGUI.h>

#include "MMyGUI_Macros.h"
#include "MMyGUI_Utility.h"

namespace MyGUI
{
	namespace Managed
	{

		class ObjectHolder
		{
		public:
			ObjectHolder() : object() { }
			ObjectHolder(System::Object ^ _obj) : object(_obj) { }
			~ObjectHolder() { }
			System::Object ^ toObject() { return object; }
		private:
			gcroot<System::Object^> object;
		};


		// ������� ������� ��� ����������� ���������� � �����
		template <typename T> struct Convert
		{
			typedef T Type;
			static inline Type To(T _value) { return _value; }
			static inline T From(Type _value) { return _value; }
		};

		// ���������� ��� ������� �����
		template <> struct Convert<size_t>
		{
			typedef System::UInt32 Type;
			inline static System::UInt32 To(size_t _value) { return System::UInt32(_value); }
			inline static size_t From(System::UInt32 _value) { return size_t(_value); }
		};
		template <> struct Convert<bool&>
		{
			typedef bool% Type;
			inline static bool% To(bool& _value)
			{
				return reinterpret_cast<bool&>(_value);
			}
		};

		// ���������� ��� �����
		template <> struct Convert<const std::string&>
		{
			typedef System::String^ Type;
			inline static System::String^ To(const std::string& _value) { return string_utility::utf8_to_managed(_value); }
			inline static std::string From(System::String^ _value) { return string_utility::managed_to_utf8(_value); }
		};
		template <> struct Convert<const Ogre::UTFString&>
		{
			typedef System::String^ Type;
			inline static System::String^ To(const Ogre::UTFString& _value) { return string_utility::utf16_to_managed(_value); }
			inline static Ogre::UTFString From(System::String^ _value) { return string_utility::managed_to_utf16(_value); }
		};
		template <> struct Convert<Ogre::UTFString>
		{
			typedef System::String^ Type;
			inline static System::String^ To(const Ogre::UTFString& _value) { return string_utility::utf16_to_managed(_value); }
			inline static Ogre::UTFString From(System::String^ _value) { return string_utility::managed_to_utf16(_value); }
		};

		// ��������� ��� Any
		template <> struct Convert<MyGUI::Any>
		{
			typedef System::Object^ Type;
			inline static System::Object^ To(MyGUI::Any _value)
			{
				ObjectHolder * obj = _value.castType< ObjectHolder >(false);
				return obj ? obj->toObject() : nullptr;
			}
			inline static MyGUI::Any From(System::Object^ _value)
			{
				ObjectHolder obj = _value;
				return obj;
			}
		};

		template <> struct Convert<const MyGUI::Guid&>
		{
			typedef System::Guid Type;
			inline static const System::Guid& To(const MyGUI::Guid& _value)
			{
				return reinterpret_cast<const System::Guid&>(_value);
			}
			inline static const MyGUI::Guid& From(System::Guid& _value)
			{
				return reinterpret_cast<const MyGUI::Guid&>(_value);
			}
		};

	} // namespace Managed
} // namespace MyGUI
