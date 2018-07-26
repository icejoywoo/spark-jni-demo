#include "Base64.h"
#include "base64_impl.h"

/*
 * Class:     Base64
 * Method:    encode
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_Base64_encode
  (JNIEnv *env, jclass clazz, jstring data) {
    int data_size = env->GetStringUTFLength(data);
    const char* data_ptr = env->GetStringUTFChars(data, 0);
    int output_size = Base64::EncodedLength(data_size);

    char* buf = new char[output_size + 1];
    if (!Base64::Encode(data_ptr, data_size, buf, output_size)) {
        printf("Failed to encode input string\n");
    }
    buf[output_size] = '\0';

    jstring ret = env->NewStringUTF(buf);
    delete[] buf;
    return ret;
}

/*
 * Class:     Base64
 * Method:    decode
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_Base64_decode
  (JNIEnv *env, jclass clazz, jstring data) {
    int data_size = env->GetStringUTFLength(data);
    const char* data_ptr = env->GetStringUTFChars(data, 0);
    int output_size = Base64::DecodedLength(data_ptr, data_size);

    char* buf = new char[output_size + 1];
    if (!Base64::Decode(data_ptr, data_size, buf, output_size)) {
        printf("Failed to decode input string\n");
    }
    buf[output_size] = '\0';

    jstring ret = env->NewStringUTF(buf);
    delete[] buf;
    return ret;
}

