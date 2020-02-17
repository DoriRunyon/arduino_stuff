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

void morseCode(std::string s, int ary[]) {
    int aryPos = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == ' ') {
            ary[aryPos] = 7000;
            aryPos += 1;
        }
        else {
	        std::string m = morseEncode(s[i]);
            for (int j = 0; j < m.length(); j++) {
                int val = 0;
                if (m[j] == '.') {
                    val = 100;
                }
                else {
                    val = 300;
                }
                ary[aryPos] = val;
                aryPos += 1;
            }
            ary[aryPos] = 300;
            aryPos += 1;
        }
    }
    ary[aryPos] = '\0';
}

void setup() {
    pinMode(ledPin, OUTPUT);

}

void blinker(int highTime, int lowTime) {
    digitalWrite(ledPin, HIGH);
    delay(highTime);
    digitalWrite(ledPin, LOW);
    delay(lowTime);
}

void loop() {
    std::string s = "happy presidents day";
    int ary[255];
    morseCode(s, ary);
    for (int i = 0; i < s.length()*4; i++) {
        if (ary[i] == '\0') {
            break;
        }
        blinker(ary[i], 100);
    }

    // Happy 
    //blinker(300, 190);
    //blinker(300, 700);

    // Presidents 
    //blinker(300, 140);
    //blinker(300, 140);
    //blinker(300, 700);

    // Day
    //blinker(300, 3000);
}
