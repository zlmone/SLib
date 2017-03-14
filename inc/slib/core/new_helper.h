#ifndef CHECKHEADER_SLIB_CORE_NEW_HELPER
#define CHECKHEADER_SLIB_CORE_NEW_HELPER

#include "definition.h"

#include "base.h"

namespace slib
{
	
	template <class T>
	class NewHelper
	{
	public:
		static T* create();

		static T* create(sl_size count);

		template <class _T>
		static T* create(const _T* other);

		template <class _T>
		static T* create(const _T* other, sl_size count);

		static void free(T* data);

		static void free(T* data, sl_size count);

		static void constructor(T* data);

		static void constructor(T* data, sl_size count);

		template <class _T>
		static void constructor(T* data, const _T* other);

		template <class _T>
		static void constructor(T* data, const _T* other, sl_size count);

		static void destructor(T* data);

		static void destructor(T* data, sl_size count);

	};

}

#include "detail/new_helper.h"

#endif
