#include "string.h"

std::ostream& operator<<(std::ostream& out, const string& str) {
    for (char c : str)
        out << c;
    return out;
}

std::wostream& operator<<(std::wostream& out, const wstring& str) {
    for (wchar_t wc : str)
        out << wc;
    return out;
}