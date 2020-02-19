#include <string.h>

const int ledPin = 13;

void morseEncode(char x, char *code) {
    switch (x) {
    case 'a':
        strcpy(code, ".-");
    case 'b':
        strcpy(code, "-...");
    case 'c':
	    strcpy(code, "-.-.");
    case 'd':
	    strcpy(code, "-..");
    case 'e':
	    strcpy(code, ".");
    case 'f':
	    strcpy(code, "..-.");
    case 'g':
	    strcpy(code, "--.");
    case 'h':
	    strcpy(code, "....");
    case 'i':
	    strcpy(code, "..");
    case 'j':
	    strcpy(code, ".---");
    case 'k':
	    strcpy(code, "-.-");
    case 'l':
	    strcpy(code, ".-..");
    case 'm':
	    strcpy(code, "--");
    case 'n':
	    strcpy(code, "-.");
    case 'o':
	    strcpy(code, "---");
    case 'p':
	    strcpy(code, ".--.");
    case 'q':
	    strcpy(code, "--.-");
    case 'r':
	    strcpy(code, ".-.");
    case 's':
	    strcpy(code, "...");
    case 't':
	    strcpy(code, "-");
    case 'u':
	    strcpy(code, "..-");
    case 'v':
	    strcpy(code, "...-");
    case 'w':
	    strcpy(code, ".--");
    case 'x':
	    strcpy(code, "-..-");
    case 'y':
	    strcpy(code, "-.--");
    case 'z':
	    strcpy(code, "--..");
    }
}

void strToBits(char *morse, int len, int bits[]) {
    int aryPos = 0;
    for (int i = len - 1; i > -1; i--) {
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
    //pinMode(ledPin, OUTPUT);
}

void blinker(long message, const int unit) {
    while (message) {
        if (message & 1) {
            digitalWrite(ledPin, HIGH);
            delay(unit);
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
    char *s = "dori";
    int slen = strlen(s);
    long message = 0;
    for (int i = slen-1; i > -1; i--, s++) {
        int bitBucket[14] = {0};
        char code[5] = {'\0'};
        morseEncode(*s, code);
        int len = strlen(code);
        if (len) {
            strToBits(code, len, bitBucket);
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
