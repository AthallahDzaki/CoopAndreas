#include "stdafx.h"

void PatchPlayers()
{
    // i think this patches are useless
    
    // increase player count 
    // we dont use first two players because
    // 0 - you
    // 1 - local-coop player
    //patch::SetUChar(0x84E98B, MAX_SERVER_PLAYERS + 2); // _vector_constructor
    //patch::SetUChar(0x856506, MAX_SERVER_PLAYERS + 2); // _vector_destructor

    // increase pad count
    // same situation
    //patch::SetUChar(0x84E1FB, MAX_SERVER_PLAYERS + 2); // _vector_constructor
    //patch::SetUChar(0x856466, MAX_SERVER_PLAYERS + 2); // _vector_destructor
}

#ifdef _DEV
void PatchConsole()
{
    // disable gta sa`s printfs
    
    // random floats
    patch::Nop(0x745997, 5);

    // soundmanager
    patch::Nop(0x5B97C9, 5);
}
#endif

void PatchStreaming()
{
    // increase available streaming memory (memory512.cs full analog) 
    patch::SetUInt(0x8A5A80, 536870912); // 512 megabytes
    patch::SetUInt(0x5B8E6A, 536870912); // hardcoded value

    // increase max fps
    RsGlobal.maxFPS = 100;
    patch::SetUChar(0x619626, 0x64); // hardcoded value

    // patch game freezeing if inactive
    //patch::Nop(0x561AF0, 7);
    //patch::Nop(0x745BC9, 2);
    patch::SetUChar(0x747FB6, 1);
    patch::SetUChar(0x74805A, 1);
    patch::Nop(0x74542B, 8);
    patch::Nop(0x53EA88, 6);

    // fix cutscene crash
    patch::Nop(0x40EC56, 5);

    // fix crash after death
    //patch::Nop(0x441481, 6);
}


void PatchPools()
{
    //Inc task pool
    patch::SetUChar(0x551140, 0xFF);

    //Inc ped pool pool
    patch::SetUChar(0x550FF2, (unsigned char)1000);

    //Inc intelligence pool
    patch::SetUChar(0x551283, 210);

    //Inc event pool
    patch::SetUChar(0x551178, 0x01);

    //Inc matrices pool
    patch::SetUChar(0x54F3A2, 0x10);

    //Inc ccolmodel pool
    patch::SetUChar(0x551108, 0x77);

    //Inc dummies pool
    patch::SetUChar(0x5510D0, 0x0F);

    //Inc objects pool
    patch::SetUChar(0x551098, 0x02);
}

void FixCrashes()
{
    // Anim crash in CPlayerPed::ProcessControl
    patch::Nop(0x609C08, 39);

    // No DirectPlay dependency
    // Increase compatibility for Windows 8+
    patch::SetUChar(0x74754A, 0xB8);
    patch::SetUInt(0x74754B, 0x900);

    // Don't create a ped group on player creation (Fixes a crash)
    patch::Nop(0x60D64D, 1);
    patch::SetUChar(0x60D64E, 0xE9);

    // Disable the call to FxSystem_c::GetCompositeMatrix in CAEFireAudioEntity::UpdateParameters
    // Which was causing a crash. The crash happens if you create 40 or
    // so vehicles that catch fire (upside down) then delete them, repeating a few times.
    patch::Nop(0x4DCF87, 6);

    // Fixed a crash (race condition triggered when jacking a vehicle)
    patch::Nop(0x6485AC, 6);

    // Fix mirror crash
    patch::SetUChar(0x7271CB + 0, 0x85); // test eax, eax
    patch::SetUChar(0x7271CB + 1, 0xC0);
    patch::SetUChar(0x7271CB + 2, 0x74); // je 0x727203
    patch::SetUChar(0x7271CB + 3, 0x34);
    patch::SetUChar(0x7271CB + 4, 0x83); // add esp, 04
    patch::SetUChar(0x7271CB + 5, 0xC4);
    patch::SetUChar(0x7271CB + 6, 0x04);
    patch::SetUChar(0x7271CB + 7, 0xC6); // mov byte ptr [00C7C728],01

    // No FxMemoryPool_c::Optimize (causes heap corruption)
    patch::Nop(0x5C25D3, 5);

    // Satchel charge crash fix
    patch::Nop(0x738F3A, 83);

    // Removes the FindPlayerInfoForThisPlayerPed at these locations.

    patch::Nop(0x5E63A6, 19);
    patch::Nop(0x621AEA, 12);
    patch::Nop(0x62D331, 11);
    patch::Nop(0x741FFF, 27);

    // fixes unknown crash from CWorld::ClearScanCodes(), testing
    patch::PutRetn(0x563470);

    // PlayerInfo checks in CPlayerPed::ProcessControl
    patch::Nop(0x60F2C4, 25);

    // fix CPhysical dctor caused by realtime shadow
    patch::Nop(0x705B3B, 10);

    // nop ped destroying when player enters interior
    patch::Nop(0x4407B7, 5);
    patch::Nop(0x61648C, 5);

    // fix spawning with bottles and cigars
    patch::Nop(0x4217F4, 21);
    patch::Nop(0x4218D8, 17);
    patch::Nop(0x5F80C0, 10);
    patch::Nop(0x5FBA47, 10);

    // disable vehicle audio (controls manualy from hooks)
    patch::Nop(0x6B18F1, 5);
    patch::Nop(0x6B9298, 5);
    patch::Nop(0x6F1793, 5);
    patch::Nop(0x6F86B6, 5);
}

void CPatch::ApplyPatches()
{
    // this comment fixes a lot of crashes :D
    //PatchPools(); 
    
    PatchPlayers();
    PatchStreaming();
    FixCrashes();
#ifdef _DEV
    PatchConsole();
#endif
}