#include <Windows.h>

class Macros {
public:
    Macros() {
        this->loopCount = 0;
        this->kArr = nullptr;
        this->arrSize = 0;
    }

    Macros(int loopCount) {
        this->kArr = nullptr;
        this->arrSize = 0;
        this->loopCount = loopCount;
    }

    ~Macros() {
        delete[] kArr;
    }
    void act_macros();

    void add_macros(const WCHAR& key, const int scanCode, const int& kTime, const int& kDelay);

private:

    class Keys {
    public:
        Keys() {
            this->key = NULL;
            this->kTime = NULL;
            this->kDelay = NULL;
            this->scanCode = NULL;
        }

        Keys(const WCHAR& key, const int& scanCode, const int& kTime, const int& kDelay) {
            this->key = key;
            this->kTime = kTime;
            this->kDelay = kDelay;
            this->scanCode = scanCode;
        }

        WCHAR key; // UNICODE key
        int kTime; // Key's pushing time for ScanCode
        int kDelay; // Key's pushing delay
        int scanCode; // ScanCode ID https://ru.wikipedia.org/wiki/Скан-код
    };

    Keys* kArr;
    int arrSize;
    int loopCount;
};

void Macros::add_macros(const WCHAR& key, const int scanCode, const int& kTime, const int& kDelay) {
    arrSize++;
    Keys* newKArr = new Keys[arrSize];

    Keys newKey(key, scanCode, kTime, kDelay);

    for (int i = 0; i < arrSize - 1; i++)
        newKArr[i] = kArr[i];

    newKArr[arrSize - 1] = newKey;

    kArr = new Keys[arrSize];

    for (int i = 0; i < arrSize; i++) {
        kArr[i] = newKArr[i];
    }
}

void Macros::act_macros() {

    for (int i = 0; i < loopCount; i++) {
        for (int j = 0; j < arrSize; j++) {
            keybd_event(kArr[j].key, kArr[j].scanCode, 0, 0); // push down

            if (kArr[j].scanCode == 0)
                keybd_event(kArr[j].key, kArr[j].scanCode + 128, KEYEVENTF_KEYUP, 0); // hold
            else
                keybd_event(kArr[j].key, kArr[j].scanCode, KEYEVENTF_KEYUP, 0); // hold

            Sleep(kArr[j].kTime); // holding time

            keybd_event(kArr[j].key, kArr[j].scanCode, KEYEVENTF_KEYUP, 0); // push up

            Sleep(kArr[j].kDelay); // stop time
        }
    }
}
