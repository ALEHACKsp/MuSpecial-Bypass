# MuSpecial bypass
MHP-Bypass

Simple bypass preventing loading of module MHPClient.dll (does not have heartbeat).

The anticheat is usermode and does not detect opening handles to date this repository.

- Characteristics of a simple JMP

Prevents Call to LoadLibA (to load MHPClient.dll)

Bypass CRC detection

Prevents call to ExitProccess
