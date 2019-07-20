/*
 *   Copyright (c) 2008-2018 SLIBIO <https://github.com/SLIBIO>
 *
 *   Permission is hereby granted, free of charge, to any person obtaining a copy
 *   of this software and associated documentation files (the "Software"), to deal
 *   in the Software without restriction, including without limitation the rights
 *   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *   copies of the Software, and to permit persons to whom the Software is
 *   furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in
 *   all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *   THE SOFTWARE.
 */

#include "slib/core/definition.h"

#if defined(SLIB_UI_IS_WIN32)

#include "slib/ui/date_picker.h"

#include "view_win32.h"

#include <commctrl.h>

namespace slib
{

	namespace priv
	{
		namespace date_picker
		{
			class DatePickerInstance : public Win32_ViewInstance
			{
			public:
				sl_bool processCommand(SHORT code, LRESULT& result) override
				{
					if (code == BN_CLICKED) {
						onClick();
						return sl_true;
					}
					return sl_false;
				}
			};
		}
	}

	using namespace priv::date_picker;

	Ref<ViewInstance> DatePicker::createNativeWidget(ViewInstance* parent)
	{
		Win32_UI_Shared* shared = Win32_UI_Shared::get();
		if (!shared) {
			return sl_null;
		}
		DWORD style = 0;
		Ref<DatePickerInstance> ret = Win32_ViewInstance::create<DatePickerInstance>(this, parent, L"SysDateTimePick32", L"DateTime", style, 0);
		if (ret.isNotNull()) {
			HWND handle = ret->getHandle();
			Ref<Font> font = getFont();
			HFONT hFont = GraphicsPlatform::getGdiFont(font.get());
			if (hFont) {
				SendMessageW(handle, WM_SETFONT, (WPARAM)hFont, TRUE);
			}
			SYSTEMTIME st;
			m_date.get_SYSTEMTIME(&st, sl_false);
			SendMessageW(handle, DTM_SETSYSTEMTIME, GDT_VALID, (LPARAM)&st);
		}
		return ret;
	}

	void DatePicker::_getDate_NW()
	{
		HWND handle = UIPlatform::getViewHandle(this);
		if (handle) {
			SYSTEMTIME st;
			if (GDT_VALID == SendMessageW(handle, DTM_GETSYSTEMTIME, 0, (LPARAM)&st)) {
				m_date.set_SYSTEMTIME(&st, sl_false);
			}
		}
	}

	void DatePicker::_setDate_NW(const Time& time)
	{
		HWND handle = UIPlatform::getViewHandle(this);
		if (handle) {
			SYSTEMTIME st;
			time.get_SYSTEMTIME(&st, sl_false);
			SendMessageW(handle, DTM_SETSYSTEMTIME, GDT_VALID, (LPARAM)&st);
		}
	}

	sl_bool DatePicker::_measureSize_NW(UISize& _out)
	{
		HWND handle = UIPlatform::getViewHandle(this);
		if (handle) {
			SIZE size = { 0, 0 };
			SendMessageW(handle, DTM_GETIDEALSIZE, 0, (LPARAM)&size);
			_out.x = (sl_ui_len)(size.cx);
			_out.y = (sl_ui_len)(size.cy);
			return sl_true;
		}
		return sl_false;
	}

	void DatePicker::_setFont_NW(const Ref<Font>& font)
	{
		HWND handle = UIPlatform::getViewHandle(this);
		if (handle) {
			HFONT hFont = GraphicsPlatform::getGdiFont(font.get());
			if (hFont) {
				::SendMessageW(handle, WM_SETFONT, (WPARAM)hFont, TRUE);
			}
		}
	}

}

#endif
