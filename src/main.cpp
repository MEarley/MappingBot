#include <iostream>
#include <windows.h>

#define SERIAL_PORT "\\\\.\\COM6"

int main(){

    // Open serial port
    HANDLE serialHandle;

    serialHandle = CreateFileA(static_cast<LPCSTR>(SERIAL_PORT),
                                GENERIC_READ | GENERIC_WRITE,
                                0,
                                NULL,
                                OPEN_EXISTING,
                                FILE_ATTRIBUTE_NORMAL,
                                NULL);

    // Setting Parameters
    DCB serialParams = { 0 };
    serialParams.DCBlength = sizeof(serialParams);

    if (!GetCommState(serialHandle, &serialParams)) {
        std::cout<<"Error getting state"<<std::endl;
        std::cout<<(int)GetLastError()<<std::endl; 
        char lastError[1024];
        FormatMessage(
                    FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                    NULL,
                    GetLastError(),
                    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                    lastError,
                    1024,
                    NULL);
        std::cout<<lastError<<std::endl; 
        
    }

    GetCommState(serialHandle, &serialParams);
    serialParams.BaudRate = CBR_115200;
    serialParams.ByteSize = 8;
    serialParams.StopBits = TWOSTOPBITS;
    serialParams.Parity = NOPARITY;
    SetCommState(serialHandle, &serialParams);

    // Set timeouts
    COMMTIMEOUTS timeout = { 0 };
    timeout.ReadIntervalTimeout = 50;
    timeout.ReadTotalTimeoutConstant = 50;
    timeout.ReadTotalTimeoutMultiplier = 50;
    timeout.WriteTotalTimeoutConstant = 50;
    timeout.WriteTotalTimeoutMultiplier = 10;

    if(!SetCommTimeouts(serialHandle, &timeout)){
        std::cout<<"Error occured"<<std::endl;
    }

    SetCommTimeouts(serialHandle, &timeout);

    // Reading from the serial port
    char buffer[9] = {0};
    DWORD dwBytesRead = 0;

    if(!ReadFile(serialHandle, buffer, 8, &dwBytesRead, NULL)){
        std::cout<<"Error occured"<<std::endl;
    }
    std::cout<<"Output:"<<std::endl;
    std::cout<<buffer<<std::endl;
    CloseHandle(serialHandle);
}