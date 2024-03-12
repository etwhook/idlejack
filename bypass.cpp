#include <iostream>
#include "bypass.h"
int main()
{
    debug::info("Starting Bypass..");
    auto PID = celestial::getRobloxPID();
    if (PID == NULL) {
        debug::err("Did not Find Roblox Process.");
        return -1;
    }
    auto hThread = celestial::getHijackableThread(PID);
    
    auto successPr = celestial::setPriority(hThread);
    
    if (successPr)
        debug::info("Set Thread Priority To Normal.");
    auto thrBuf = celestial::allocateRemoteMemory(PID);
    printf("Remote Buffer -> 0x%p\n", thrBuf);
    DWORD success = celestial::hijackThread(hThread, &thrBuf);
    
    if (success == -1)
        printf("[-] Failed to Hijack Thread.");
    else
        printf("[+] Hijacked Thread Successfully.");

    celestial::cleanup(hThread);
    return 0;
}
