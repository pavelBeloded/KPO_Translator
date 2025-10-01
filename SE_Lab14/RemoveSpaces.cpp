#include "RemoveSpaces.h"
#include "stdafx.h"

void In::RemoveExtraSpaces(IN& in) {
    if (!in.text || in.size == 0) return;

    int writePos = 0;
    bool lastWasSpace = false;

    for (int readPos = 0; readPos < in.size; readPos++) {
        unsigned char c = in.text[readPos];

        if (c == ' ' || c == '\t') {
            if (!lastWasSpace) {
                in.text[writePos++] = ' ';
                lastWasSpace = true;
            }
        }
        else {
            in.text[writePos++] = c;
            lastWasSpace = false;
        }
    }

    if (writePos > 0 && in.text[writePos - 1] == ' ')
        writePos--;

    in.size = writePos;
    in.text[in.size] = '\0';
}
