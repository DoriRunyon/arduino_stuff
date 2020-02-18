#include <string>
int ledPin = 13;

std::string morseEncode(char x) {
    switch (x) {
    case 'a':
        return ".-";
    case 'b':
        return "-...";
    case 'c':
	    return "-.-.";
    case 'd':
	    return "-..";
    case 'e':
	    return ".";
    case 'f':
	    return "..-.";
    case 'g':
	    return "--.";
    case 'h':
	    return "....";
    case 'i':
	    return "..";
    case 'j':
	    return ".---";
    case 'k':
	    return "-.-";
    case 'l':
	    return ".-..";
    case 'm':
	    return "--";
    case 'n':
	    return "-.";
    case 'o':
	    return "---";
    case 'p':
	    return ".--.";
    case 'q':
	    return "--.-";
    case 'r':
	    return ".-.";
    case 's':
	    return "...";
    case 't':
	    return "-";
    case 'u':
	    return "..-";
    case 'v':
	    return "...-";
    case 'w':
	    return ".--";
    case 'x':
	    return "-..-";
    case 'y':
	    return "-.--";
    case 'z':
	    return "--..";
    }
    return "";
}

void strToBits(std::string morse, int bits[]) {
    int aryPos = 0;
    for (int i = morse.length()-1; i > -1; i--) {
        if (morse[i] == '.') {
            bits[aryPos++] = 1;
        }
        else if (morse[i] == '-') {
            bits[aryPos++] = 1;
            bits[aryPos++] = 1;
            bits[aryPos++] = 1;
        }
        bits[aryPos++] = 0;
    }
    bits[--aryPos] = -1;
}

long bitSchwifty(int bits[], long message) {
    for (int i = 0;; i++) {
        if (bits[i] < 0)
            break;
        if (bits[i]) {
            message = message<<1;
            message = message^1;
        }
        else {
            message = message<<1;
        }
    }
    message = message<<3;
    return message;
}

void setup() {
    pinMode(ledPin, OUTPUT);
}

void blinker(long message, const int unit) {
    while (message) {
        if (message & 1) {
            digitalWrite(ledPin, HIGH);
            delay(highTime);
        }
        else {
            digitalWrite(ledPin, LOW);
            delay(unit);
        }
        message = message>>1;
    }
}

void loop() {
    const int timeUnit = 200;
    std::string s = "dori";
    long message = 0;
    //int shift =0;
    for (int i = s.length()-1; i > -1; i--) {
        int bitBucket[13] = {0};
        std::string code = morseEncode(s[i]);
        if (code.length()) {
            strToBits(code, bitBucket);
        }
        else {
            if (i > 0) {
                bitBucket[1] = -1;
            }
        }
        message = bitSchwifty(bitBucket, message);
    }
    message = message>>3;
    for (;;) {
        blinker(message, timeUnit);
    }
}

int main(int argc, char **argv) {
    loop();
    return 0;
}
