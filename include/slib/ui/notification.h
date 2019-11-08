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

#ifndef CHECKHEADER_SLIB_UI_NOTIFICATION
#define CHECKHEADER_SLIB_UI_NOTIFICATION

#include "definition.h"

#include "../service/push_notification.h"
#include "../core/function.h"

namespace slib
{

	class SLIB_EXPORT PushNotificationClient : public Object
	{
		SLIB_DECLARE_OBJECT
		
	public:
		PushNotificationClient();
		
		~PushNotificationClient();
		
	public:
		String getDeviceToken();
		
		void addTokenRefreshCallback(const Function<void(String)>& callback);
		
		void removeTokenRefreshCallback(const Function<void(String)>& callback);

		void addNotificationReceivedCallback(const Function<void(PushNotificationMessage&)>& callback);
		
		void removeNotificationReceivedCallback(const Function<void(PushNotificationMessage&)>& callback);
		
		void start();
		
	public:
		void dispatchTokenRefresh(const String& deviceToken);
		
		void dispatchNotificationReceived(PushNotificationMessage& message);
		
	protected:
		virtual void onStart();
		
	protected:
		sl_bool m_flagStarted;
		AtomicString m_deviceToken;
		AtomicFunction<void(String)> m_callbackTokenRefresh;
		AtomicFunction<void(PushNotificationMessage&)> m_callbackNotificationReceived;

	};
	
	// Apple Push Notification service
	class SLIB_EXPORT APNs : public PushNotificationClient
	{
		SLIB_DECLARE_OBJECT
		
	public:
		APNs();
		
		~APNs();
		
	protected:
		void onStart() override;
		
	public:
		static Ref<APNs> getInstance();
		
	};

	// Firebase Cloud Messaging
	class SLIB_EXPORT FCM : public PushNotificationClient
	{
		SLIB_DECLARE_OBJECT
		
	public:
		FCM();
		
		~FCM();
		
	public:
		void onStart() override;
		
	public:		
		static Ref<FCM> getInstance();
		
	};
	
}

#endif
