#include <slib/core/platform_android.h>

#include "../../../../../src/app.h"

JNIEXPORT jint JNI_OnLoad(JavaVM* jvm, void* reserved)
{
	Android::initialize(jvm);
	ExampleFCMApp::main();
	return JNI_VERSION_1_4;
}
