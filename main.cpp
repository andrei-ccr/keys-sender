/* MAIN.CPP
 *
 * Send Keys program to automatically type text. Runs on Windows x86/x64.
 * Created: 16 Dec 2018
 * Andrei Ciucur
 *
 */

#include <iostream>
#include <fstream> 

#define WINVER 0x0500
#include <windows.h>
#include <string>


#define DEFAULT_INIT_DELAY 2000
#define DEFAULT_INTER_DELAY 10

using namespace std;

WORD KeyToHex(char c) {
    switch(c) {
    case '1':
        return 0x02;
    case '2':
        return 0x03;
    case '3':
        return 0x04;
    case '4':
        return 0x05;
    case '5':
        return 0x06;
    case '6':
        return 0x07;
    case '7':
        return 0x08;
    case '8':
        return 0x09;
    case '9':
        return 0x0A;
    case '0':
        return 0x0B;
    case '-':
        return 0x0C;
    case '=':
        return 0x0D;
    case 'Q':
        return 0x10;

    }
}

WORD CharToVkey(char c) {
	c = tolower(c); //Make it lowercase because it's case insensitive
	switch(c) {
		case '0':
			return 0x30;
		case '1':
			return 0x31;
		case '2':
			return 0x32;
		case '3':
			return 0x33;
		case '4':
			return 0x34;
		case '5':
			return 0x35;
		case '6':
			return 0x36;
		case '7':
			return 0x37;
		case '8':
			return 0x38;
		case '9':
			return 0x39;
		case 'a':
			return 0x41;
		case 'b':
			return 0x42;
		case 'c':
			return 0x43;
		case 'd':
			return 0x44;
		case 'e':
			return 0x45;
		case 'f':
			return 0x46;
		case 'g':
			return 0x47;
		case 'h':
			return 0x48;
		case 'i':
			return 0x49;
		case 'j':
			return 0x4a;
		case 'k':
			return 0x4b;
		case 'l':
			return 0x4c;
		case 'm':
			return 0x4d;
		case 'n':
			return 0x4e;
		case 'o':
			return 0x4f;
		case 'p':
			return 0x50;
		case 'q':
			return 0x51;
		case 'r':
			return 0x52;
		case 's':
			return 0x53;
		case 't':
			return 0x54;
		case 'u':
			return 0x55;
		case 'v':
			return 0x56;
		case 'w':
			return 0x57;
		case 'x':
			return 0x58;
		case 'y':
			return 0x59;
		case 'z':
			return 0x5a;
		case '=':
			return VK_OEM_PLUS;
		case '-':
			return VK_OEM_MINUS;
		case '.':
			return VK_OEM_PERIOD;
		case ',':
			return VK_OEM_COMMA;
		case ';':
			return VK_OEM_1;
		case '/':
			return VK_OEM_2;
		case '[':
			return VK_OEM_4;
		case ']':
			return VK_OEM_6;
		case '\\':
			return VK_OEM_5;
		case '\'':
			return VK_OEM_7;
		case ' ':
			return VK_SPACE;
		case '\n':
			return VK_RETURN;
		case '*':
			return VK_MULTIPLY;
	}
}


void _SendKey(char k) {
	INPUT input;
	INPUT aux_input;
	
	bool aux_input_flag = false; //If the shift key was used, this will become true

	WORD vkey;

	switch(k) {
		case '{':
			vkey = CharToVkey('[');
			break;
		case '}':
			vkey = CharToVkey(']');
			break;
		case '_':
			vkey = CharToVkey('-');
			break;
		case '+':
		    vkey = CharToVkey('=');
			break;
		case ':':
		    vkey = CharToVkey(';');
			break;
		case '"':
			vkey = CharToVkey('\'');
			break;
		case '<':
			vkey = CharToVkey(',');
			break;
		case '>':
		    vkey = CharToVkey('.');
			break;
		case '?':
		    vkey = CharToVkey('/');
			break;
		case '|':
		    vkey = CharToVkey('\\');
			break;
		case '(':
			vkey = CharToVkey('9');
			break;
		case ')':
			vkey = CharToVkey('0');
			break;
		case '!':
		    vkey = CharToVkey('1');
			break;
		case '@':
		    vkey = CharToVkey('2');
			break;
		case '#':
		    vkey = CharToVkey('3');
			break;
		case '$':
		    vkey = CharToVkey('4');
			break;
		case '%':
		    vkey = CharToVkey('5');
			break;
		case '^':
		    vkey = CharToVkey('6');
			break;
		case '&':
		    vkey = CharToVkey('7');
			break;
		default:
			vkey = CharToVkey(k);
	}

	input.type = INPUT_KEYBOARD;
	input.ki.wScan = MapVirtualKey(vkey, 0);
	input.ki.time = 0;
	input.ki.dwExtraInfo = 0;
	input.ki.wVk = vkey;
	input.ki.dwFlags = 0; // there is no KEYEVENTF_KEYDOWN
	
	if((isupper(k)) || (k == '{') || (k == '}') || (k == ':') || (k == '"') || (k == '<') || (k == '>') || (k == '?') || (k == '|') || (k == '_') || (k == '+') || (k == '(') || (k == ')') || (k == '!')|| (k == '@')|| (k == '#')|| (k == '$')|| (k == '%')|| (k == '^')|| (k == '&')) {
		WORD vKeyAux = VK_SHIFT;
		aux_input.type = INPUT_KEYBOARD;
		aux_input.ki.wScan = MapVirtualKey(vKeyAux, 0);
		aux_input.ki.time = 0;
		aux_input.ki.dwExtraInfo = 0;
		aux_input.ki.wVk = vKeyAux;
		aux_input.ki.dwFlags = 0; // there is no KEYEVENTF_KEYDOWN
		SendInput(1, &aux_input, sizeof(INPUT));
		aux_input_flag = true;
	}
	
	SendInput(1, &input, sizeof(INPUT));
	
	//Send KEYUP events
	if(aux_input_flag) {
		aux_input.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &aux_input, sizeof(INPUT));
	}
	
	input.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &input, sizeof(INPUT));
	

}

void _SendKeys(const char *string, unsigned int firstDelayMs = DEFAULT_INIT_DELAY, unsigned int interDelayMs = DEFAULT_INTER_DELAY) {
	Sleep(firstDelayMs);
	int i=0;
	while ((string[i] != '\0') && (i<strlen(string)))   {  
		//std::cout << c;
		_SendKey(string[i]);
		Sleep(interDelayMs);
		i++;
	}
}

void _SendKeys(ifstream& fStream, unsigned int firstDelayMs = DEFAULT_INIT_DELAY, unsigned int interDelayMs = DEFAULT_INTER_DELAY) {
	Sleep(firstDelayMs);

	char c;
	while (fStream.get(c))   {  
		//std::cout << c;
		_SendKey(c);
		Sleep(interDelayMs);
	}
}

void PrintUsage(const char *appName) {
	cout<<"Usage:  "<<appName<< " (-f <filepath> | -s <string>) [opt]"<<endl;
	cout<<endl;
	cout<<"Required arguments:"<<endl;
	cout<<"   -f <filepath>  :  Point to a file containing text to type"<<endl;
	cout<<"   -s <string>    :  A string to type"<<endl;
	cout<<endl;
	cout<<"Optional arguments:"<<endl;
	cout<<"   -d <number>    :  Initial delay time in miliseconds before first type"<<endl;
	cout<<"   -D <number>    :  Delay time in miliseconds in-between typing two keys"<<endl;
	cout<<endl<<endl;
	cout<<"Made by A.C. 2018~2019"<<endl;
}

int main(int argc, char **argv) {
	
	bool file_mode = false;
	int d = DEFAULT_INIT_DELAY, D = DEFAULT_INTER_DELAY;
	
	if(argc>2) {
		//Check for file or string
		if(!strcmp(argv[1], "-f")) {
			file_mode = true;
		} else if(!strcmp(argv[1], "-s")) {
			file_mode = false;
		} else {
			PrintUsage(argv[0]);
			return 0;
		}
		
		//Check other options
		try {
			if(argc>4) {
				for(int i=3;i<argc;i++) {
					if(!strcmp(argv[i], "-d")) {
						d = stoi(argv[i+1]);
					} else if(!strcmp(argv[i], "-D")) {
						D = stoi(argv[i+1]);
					}
				}
			} else {
				PrintUsage(argv[0]);
				return 0;
			}
		} catch(exception e) {
			PrintUsage(argv[0]);
			return 0;
		}
	} else {
		PrintUsage(argv[0]);
		return 0;
	}
	
	if(file_mode) {
		ifstream is(argv[2]);
		_SendKeys(is, d, D);
		is.close();
	} else {
		_SendKeys(argv[2], d, D);
	}


    return 0;
}
