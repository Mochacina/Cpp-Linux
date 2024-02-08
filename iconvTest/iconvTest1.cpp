#include "./libiconv/inc/iconv.h"
#include <iostream>
#include <cstring>

int main() {
    // Input UTF-8 string
    const char* utf8String = "Your UTF-8 string here";

    // Output buffer for EUC-KR string
    char eucKrString[65000];

    // Create an iconv conversion descriptor
    iconv_t conversionDescriptor = iconv_open("EUC-KR", "UTF-8");
    if (conversionDescriptor == (iconv_t)-1) {
        std::cerr << "Failed to create iconv conversion descriptor" << std::endl;
        return 1;
    }

    // Perform the conversion
    size_t utf8Length = std::strlen(utf8String);
    size_t eucKrLength = sizeof(eucKrString);
    char* utf8Ptr = const_cast<char*>(utf8String);
    char* eucKrPtr = eucKrString;
    if (iconv(conversionDescriptor, &utf8Ptr, &utf8Length, &eucKrPtr, &eucKrLength) == (size_t)-1) {
        std::cerr << "Failed to convert UTF-8 to EUC-KR" << std::endl;
        iconv_close(conversionDescriptor);
        return 1;
    }

    // Null-terminate the EUC-KR string
    *eucKrPtr = '\0';

    // Close the iconv conversion descriptor
    iconv_close(conversionDescriptor);

    // Print the converted EUC-KR string
    std::cout << "EUC-KR string: " << eucKrString << std::endl;

    return 0;
}