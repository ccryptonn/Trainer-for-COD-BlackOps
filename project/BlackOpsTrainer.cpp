#include <iostream>
#include "memory.h"
#include <thread>
#include <string>
#include <chrono> 
constexpr int COUNTFUNCS = 4;
void fly() noexcept;
void rapid() noexcept;
void infitity() noexcept;
void god() noexcept;
//void rofl() noexcept;
constexpr DWORD offJump = 0x1808B6C;
constexpr DWORD cords = 0x1808B64;
constexpr DWORD fierFlag = 0x01C08B7C;
constexpr DWORD ammos[5] = { 0x1C08F00 ,0x1C08F04,0x1C08F08,0x1C08F10,0x1C08F18 };
constexpr DWORD grenate = 0x1C08F18;
constexpr DWORD offHp = 0x01A7987C;
constexpr DWORD offMaxHp = 0x01A79880;
//constexpr DWORD offFlagKent = 0x180A7C0;
bool* flags[COUNTFUNCS]{ /*fly*/new bool(0), /*rapid*/new bool(0), /*infinity*/new bool(0), /*godmod*/new bool(0)};
memory mem;
//#define DEF
//#define DEF2
int main()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    setlocale(0, "RU");
#ifndef DEF
    mem.Attach(L"BlackOps.exe", PROCESS_ALL_ACCESS);
    std::cout << "Ссылка на игру https://itorrents-igruha.org/?do=download&id=28157\n"; 
    if (mem.pHandle == 0) {
        MessageBox(0, L"Братик колду открой", L"Ахтунг!1!", MB_ICONERROR);
        exit(0);
    };
    mem.GetModule(L"BlackOps.exe");
#endif 
    void(* funcs[COUNTFUNCS])() { fly, rapid, infitity, god};
#ifndef DEF2
    for (char a : "Trainer for BlackOps by crypton...") {
        std::cout << a;
        std::this_thread::sleep_for(std::chrono::milliseconds(15));
    }
    std::cout << std::endl;
#endif
    std::cout << "Модуль: " << mem._module <<  "\n";
    std::cout << "Все доступные функции: \n";
    std::cout << "F1 - fly hack \n";
    std::cout << "F2 - rapid hack \n";
    std::cout << "F3 - infinity ammo \n";
    std::cout << "F4 - god mod \n";
    //std::thread threads = std::thread(rofl); 
    //threads.detach();
    while (1) {
        if (GetAsyncKeyState(VK_F1)) {
            if (*flags[0] == 0) {
                std::thread threads = std::thread(funcs[0]);
                threads.detach();
                *flags[0] = 1;
            }
            else {
                *flags[0] = 0;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
        if (GetAsyncKeyState(VK_F2)) {
            if (*flags[1] == 0) {
                std::thread threads = std::thread(funcs[1]);
                threads.detach();
                *flags[1] = 1;
            }
            else {
                *flags[1] = 0;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
        if (GetAsyncKeyState(VK_F3)) {
            if (*flags[2] == 0) {
                std::thread threads = std::thread(funcs[2]);
                threads.detach();
                *flags[2] = 1;
            }
            else {
                *flags[2] = 0;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
        if (GetAsyncKeyState(VK_F4)) {
            if (*flags[3] == 0) {
                std::thread threads = std::thread(funcs[3]);
                threads.detach();
                *flags[3] = 1;
            }
            else {
                *flags[3] = 0;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
    return 0;
}
void fly() noexcept {
    Beep(1000, 300);
    float pos = 0;
    for (; *flags[0];) {
        pos = (float)mem.Read<float>(mem._module + offJump);
        for(;GetAsyncKeyState(VK_SPACE);) {
            mem.Write(mem._module + offJump, (pos += 0.01));
        }
        for(;GetAsyncKeyState(VK_CONTROL);) {
            mem.Write(mem._module + offJump, (pos -= 0.01));
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    Beep(400, 300);
}
void rapid() noexcept {
    Beep(1000, 300);
    for (; *flags[1];) {
        for (; mem.Read<int>(fierFlag) > 0;) {
            mem.Write(fierFlag, 0);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    Beep(400, 300);
}
void infitity() noexcept {
    Beep(1000, 300);
    for(; *flags[2];) {
        for (DWORD i : ammos) {
            mem.Write(i, 1000);
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10)); 
    }
    Beep(400, 300);
}
void god() noexcept {
    Beep(1000, 300);
    for (; *flags[3];) {
        if (mem.Read<int>(offHp) != 100000) {
            mem.Write(offMaxHp, 100000);
            mem.Write(offHp, 100000);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    mem.Write(offMaxHp, 100);
    mem.Write(offHp, 100);
    Beep(400, 300);
}
//void rofl() noexcept {
//    while (1) {
//        if (mem.Read<int>(mem._module + offFlagKent) != 0) {
//            mem.Write(mem._module + 0x2AED8B3, 1337);
//        }
//        std::this_thread::sleep_for(std::chrono::milliseconds(10));
//    }
//}
