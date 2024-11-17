#include <windows.h>
#include <stdio.h>
#include "hook_macro.h"

HINSTANCE mHinst = 0, mHinstDLL = 0;

UINT_PTR mProcs[193] = {0};

LPCSTR mImportNames[] = {
  "CloseDriver",
  "DefDriverProc",
  "DriverCallback",
  "DrvGetModuleHandle",
  "GetDriverModuleHandle",
  "NotifyCallbackData",
  "OpenDriver",
  "PlaySound",
  "PlaySoundA",
  "PlaySoundW",
  "SendDriverMessage",
  "WOW32DriverCallback",
  "WOW32ResolveMultiMediaHandle",
  "WOWAppExit",
  "aux32Message",
  "auxGetDevCapsA",
  "auxGetDevCapsW",
  "auxGetNumDevs",
  "auxGetVolume",
  "auxOutMessage",
  "auxSetVolume",
  "joy32Message",
  "joyConfigChanged",
  "joyGetDevCapsA",
  "joyGetDevCapsW",
  "joyGetNumDevs",
  "joyGetPos",
  "joyGetPosEx",
  "joyGetThreshold",
  "joyReleaseCapture",
  "joySetCapture",
  "joySetThreshold",
  "mci32Message",
  "mciDriverNotify",
  "mciDriverYield",
  "mciExecute",
  "mciFreeCommandResource",
  "mciGetCreatorTask",
  "mciGetDeviceIDA",
  "mciGetDeviceIDFromElementIDA",
  "mciGetDeviceIDFromElementIDW",
  "mciGetDeviceIDW",
  "mciGetDriverData",
  "mciGetErrorStringA",
  "mciGetErrorStringW",
  "mciGetYieldProc",
  "mciLoadCommandResource",
  "mciSendCommandA",
  "mciSendCommandW",
  "mciSendStringA",
  "mciSendStringW",
  "mciSetDriverData",
  "mciSetYieldProc",
  "mid32Message",
  "midiConnect",
  "midiDisconnect",
  "midiInAddBuffer",
  "midiInClose",
  "midiInGetDevCapsA",
  "midiInGetDevCapsW",
  "midiInGetErrorTextA",
  "midiInGetErrorTextW",
  "midiInGetID",
  "midiInGetNumDevs",
  "midiInMessage",
  "midiInOpen",
  "midiInPrepareHeader",
  "midiInReset",
  "midiInStart",
  "midiInStop",
  "midiInUnprepareHeader",
  "midiOutCacheDrumPatches",
  "midiOutCachePatches",
  "midiOutClose",
  "midiOutGetDevCapsA",
  "midiOutGetDevCapsW",
  "midiOutGetErrorTextA",
  "midiOutGetErrorTextW",
  "midiOutGetID",
  "midiOutGetNumDevs",
  "midiOutGetVolume",
  "midiOutLongMsg",
  "midiOutMessage",
  "midiOutOpen",
  "midiOutPrepareHeader",
  "midiOutReset",
  "midiOutSetVolume",
  "midiOutShortMsg",
  "midiOutUnprepareHeader",
  "midiStreamClose",
  "midiStreamOpen",
  "midiStreamOut",
  "midiStreamPause",
  "midiStreamPosition",
  "midiStreamProperty",
  "midiStreamRestart",
  "midiStreamStop",
  "mixerClose",
  "mixerGetControlDetailsA",
  "mixerGetControlDetailsW",
  "mixerGetDevCapsA",
  "mixerGetDevCapsW",
  "mixerGetID",
  "mixerGetLineControlsA",
  "mixerGetLineControlsW",
  "mixerGetLineInfoA",
  "mixerGetLineInfoW",
  "mixerGetNumDevs",
  "mixerMessage",
  "mixerOpen",
  "mixerSetControlDetails",
  "mmDrvInstall",
  "mmGetCurrentTask",
  "mmTaskBlock",
  "mmTaskCreate",
  "mmTaskSignal",
  "mmTaskYield",
  "mmioAdvance",
  "mmioAscend",
  "mmioClose",
  "mmioCreateChunk",
  "mmioDescend",
  "mmioFlush",
  "mmioGetInfo",
  "mmioInstallIOProcA",
  "mmioInstallIOProcW",
  "mmioOpenA",
  "mmioOpenW",
  "mmioRead",
  "mmioRenameA",
  "mmioRenameW",
  "mmioSeek",
  "mmioSendMessage",
  "mmioSetBuffer",
  "mmioSetInfo",
  "mmioStringToFOURCCA",
  "mmioStringToFOURCCW",
  "mmioWrite",
  "mmsystemGetVersion",
  "mod32Message",
  "mxd32Message",
  "sndPlaySoundA",
  "sndPlaySoundW",
  "tid32Message",
  "timeBeginPeriod",
  "timeEndPeriod",
  "timeGetDevCaps",
  "timeGetSystemTime",
  "timeGetTime",
  "timeKillEvent",
  "timeSetEvent",
  "waveInAddBuffer",
  "waveInClose",
  "waveInGetDevCapsA",
  "waveInGetDevCapsW",
  "waveInGetErrorTextA",
  "waveInGetErrorTextW",
  "waveInGetID",
  "waveInGetNumDevs",
  "waveInGetPosition",
  "waveInMessage",
  "waveInOpen",
  "waveInPrepareHeader",
  "waveInReset",
  "waveInStart",
  "waveInStop",
  "waveInUnprepareHeader",
  "waveOutBreakLoop",
  "waveOutClose",
  "waveOutGetDevCapsA",
  "waveOutGetDevCapsW",
  "waveOutGetErrorTextA",
  "waveOutGetErrorTextW",
  "waveOutGetID",
  "waveOutGetNumDevs",
  "waveOutGetPitch",
  "waveOutGetPlaybackRate",
  "waveOutGetPosition",
  "waveOutGetVolume",
  "waveOutMessage",
  "waveOutOpen",
  "waveOutPause",
  "waveOutPrepareHeader",
  "waveOutReset",
  "waveOutRestart",
  "waveOutSetPitch",
  "waveOutSetPlaybackRate",
  "waveOutSetVolume",
  "waveOutUnprepareHeader",
  "waveOutWrite",
  "wid32Message",
  "wod32Message",
  (LPCSTR)2,
};

#ifndef _DEBUG
inline void log_info(const char* info) {
}
#else
FILE* debug;
inline void log_info(const char* info) {
  fprintf(debug, "%s\n", info);
  fflush(debug);
}
#endif

#include "empty.h"

inline void _hook_setup() {
#ifdef CLOSEDRIVER
  CloseDriver_real = (CloseDriver_ptr)mProcs[0];
  mProcs[0] = (UINT_PTR)&CloseDriver_fake;
#endif
#ifdef DEFDRIVERPROC
  DefDriverProc_real = (DefDriverProc_ptr)mProcs[1];
  mProcs[1] = (UINT_PTR)&DefDriverProc_fake;
#endif
#ifdef DRIVERCALLBACK
  DriverCallback_real = (DriverCallback_ptr)mProcs[2];
  mProcs[2] = (UINT_PTR)&DriverCallback_fake;
#endif
#ifdef DRVGETMODULEHANDLE
  DrvGetModuleHandle_real = (DrvGetModuleHandle_ptr)mProcs[3];
  mProcs[3] = (UINT_PTR)&DrvGetModuleHandle_fake;
#endif
#ifdef GETDRIVERMODULEHANDLE
  GetDriverModuleHandle_real = (GetDriverModuleHandle_ptr)mProcs[4];
  mProcs[4] = (UINT_PTR)&GetDriverModuleHandle_fake;
#endif
#ifdef NOTIFYCALLBACKDATA
  NotifyCallbackData_real = (NotifyCallbackData_ptr)mProcs[5];
  mProcs[5] = (UINT_PTR)&NotifyCallbackData_fake;
#endif
#ifdef OPENDRIVER
  OpenDriver_real = (OpenDriver_ptr)mProcs[6];
  mProcs[6] = (UINT_PTR)&OpenDriver_fake;
#endif
#ifdef PLAYSOUND
  PlaySound_real = (PlaySound_ptr)mProcs[7];
  mProcs[7] = (UINT_PTR)&PlaySound_fake;
#endif
#ifdef PLAYSOUNDA
  PlaySoundA_real = (PlaySoundA_ptr)mProcs[8];
  mProcs[8] = (UINT_PTR)&PlaySoundA_fake;
#endif
#ifdef PLAYSOUNDW
  PlaySoundW_real = (PlaySoundW_ptr)mProcs[9];
  mProcs[9] = (UINT_PTR)&PlaySoundW_fake;
#endif
#ifdef SENDDRIVERMESSAGE
  SendDriverMessage_real = (SendDriverMessage_ptr)mProcs[10];
  mProcs[10] = (UINT_PTR)&SendDriverMessage_fake;
#endif
#ifdef WOW32DRIVERCALLBACK
  WOW32DriverCallback_real = (WOW32DriverCallback_ptr)mProcs[11];
  mProcs[11] = (UINT_PTR)&WOW32DriverCallback_fake;
#endif
#ifdef WOW32RESOLVEMULTIMEDIAHANDLE
  WOW32ResolveMultiMediaHandle_real = (WOW32ResolveMultiMediaHandle_ptr)mProcs[12];
  mProcs[12] = (UINT_PTR)&WOW32ResolveMultiMediaHandle_fake;
#endif
#ifdef WOWAPPEXIT
  WOWAppExit_real = (WOWAppExit_ptr)mProcs[13];
  mProcs[13] = (UINT_PTR)&WOWAppExit_fake;
#endif
#ifdef AUX32MESSAGE
  aux32Message_real = (aux32Message_ptr)mProcs[14];
  mProcs[14] = (UINT_PTR)&aux32Message_fake;
#endif
#ifdef AUXGETDEVCAPSA
  auxGetDevCapsA_real = (auxGetDevCapsA_ptr)mProcs[15];
  mProcs[15] = (UINT_PTR)&auxGetDevCapsA_fake;
#endif
#ifdef AUXGETDEVCAPSW
  auxGetDevCapsW_real = (auxGetDevCapsW_ptr)mProcs[16];
  mProcs[16] = (UINT_PTR)&auxGetDevCapsW_fake;
#endif
#ifdef AUXGETNUMDEVS
  auxGetNumDevs_real = (auxGetNumDevs_ptr)mProcs[17];
  mProcs[17] = (UINT_PTR)&auxGetNumDevs_fake;
#endif
#ifdef AUXGETVOLUME
  auxGetVolume_real = (auxGetVolume_ptr)mProcs[18];
  mProcs[18] = (UINT_PTR)&auxGetVolume_fake;
#endif
#ifdef AUXOUTMESSAGE
  auxOutMessage_real = (auxOutMessage_ptr)mProcs[19];
  mProcs[19] = (UINT_PTR)&auxOutMessage_fake;
#endif
#ifdef AUXSETVOLUME
  auxSetVolume_real = (auxSetVolume_ptr)mProcs[20];
  mProcs[20] = (UINT_PTR)&auxSetVolume_fake;
#endif
#ifdef JOY32MESSAGE
  joy32Message_real = (joy32Message_ptr)mProcs[21];
  mProcs[21] = (UINT_PTR)&joy32Message_fake;
#endif
#ifdef JOYCONFIGCHANGED
  joyConfigChanged_real = (joyConfigChanged_ptr)mProcs[22];
  mProcs[22] = (UINT_PTR)&joyConfigChanged_fake;
#endif
#ifdef JOYGETDEVCAPSA
  joyGetDevCapsA_real = (joyGetDevCapsA_ptr)mProcs[23];
  mProcs[23] = (UINT_PTR)&joyGetDevCapsA_fake;
#endif
#ifdef JOYGETDEVCAPSW
  joyGetDevCapsW_real = (joyGetDevCapsW_ptr)mProcs[24];
  mProcs[24] = (UINT_PTR)&joyGetDevCapsW_fake;
#endif
#ifdef JOYGETNUMDEVS
  joyGetNumDevs_real = (joyGetNumDevs_ptr)mProcs[25];
  mProcs[25] = (UINT_PTR)&joyGetNumDevs_fake;
#endif
#ifdef JOYGETPOS
  joyGetPos_real = (joyGetPos_ptr)mProcs[26];
  mProcs[26] = (UINT_PTR)&joyGetPos_fake;
#endif
#ifdef JOYGETPOSEX
  joyGetPosEx_real = (joyGetPosEx_ptr)mProcs[27];
  mProcs[27] = (UINT_PTR)&joyGetPosEx_fake;
#endif
#ifdef JOYGETTHRESHOLD
  joyGetThreshold_real = (joyGetThreshold_ptr)mProcs[28];
  mProcs[28] = (UINT_PTR)&joyGetThreshold_fake;
#endif
#ifdef JOYRELEASECAPTURE
  joyReleaseCapture_real = (joyReleaseCapture_ptr)mProcs[29];
  mProcs[29] = (UINT_PTR)&joyReleaseCapture_fake;
#endif
#ifdef JOYSETCAPTURE
  joySetCapture_real = (joySetCapture_ptr)mProcs[30];
  mProcs[30] = (UINT_PTR)&joySetCapture_fake;
#endif
#ifdef JOYSETTHRESHOLD
  joySetThreshold_real = (joySetThreshold_ptr)mProcs[31];
  mProcs[31] = (UINT_PTR)&joySetThreshold_fake;
#endif
#ifdef MCI32MESSAGE
  mci32Message_real = (mci32Message_ptr)mProcs[32];
  mProcs[32] = (UINT_PTR)&mci32Message_fake;
#endif
#ifdef MCIDRIVERNOTIFY
  mciDriverNotify_real = (mciDriverNotify_ptr)mProcs[33];
  mProcs[33] = (UINT_PTR)&mciDriverNotify_fake;
#endif
#ifdef MCIDRIVERYIELD
  mciDriverYield_real = (mciDriverYield_ptr)mProcs[34];
  mProcs[34] = (UINT_PTR)&mciDriverYield_fake;
#endif
#ifdef MCIEXECUTE
  mciExecute_real = (mciExecute_ptr)mProcs[35];
  mProcs[35] = (UINT_PTR)&mciExecute_fake;
#endif
#ifdef MCIFREECOMMANDRESOURCE
  mciFreeCommandResource_real = (mciFreeCommandResource_ptr)mProcs[36];
  mProcs[36] = (UINT_PTR)&mciFreeCommandResource_fake;
#endif
#ifdef MCIGETCREATORTASK
  mciGetCreatorTask_real = (mciGetCreatorTask_ptr)mProcs[37];
  mProcs[37] = (UINT_PTR)&mciGetCreatorTask_fake;
#endif
#ifdef MCIGETDEVICEIDA
  mciGetDeviceIDA_real = (mciGetDeviceIDA_ptr)mProcs[38];
  mProcs[38] = (UINT_PTR)&mciGetDeviceIDA_fake;
#endif
#ifdef MCIGETDEVICEIDFROMELEMENTIDA
  mciGetDeviceIDFromElementIDA_real = (mciGetDeviceIDFromElementIDA_ptr)mProcs[39];
  mProcs[39] = (UINT_PTR)&mciGetDeviceIDFromElementIDA_fake;
#endif
#ifdef MCIGETDEVICEIDFROMELEMENTIDW
  mciGetDeviceIDFromElementIDW_real = (mciGetDeviceIDFromElementIDW_ptr)mProcs[40];
  mProcs[40] = (UINT_PTR)&mciGetDeviceIDFromElementIDW_fake;
#endif
#ifdef MCIGETDEVICEIDW
  mciGetDeviceIDW_real = (mciGetDeviceIDW_ptr)mProcs[41];
  mProcs[41] = (UINT_PTR)&mciGetDeviceIDW_fake;
#endif
#ifdef MCIGETDRIVERDATA
  mciGetDriverData_real = (mciGetDriverData_ptr)mProcs[42];
  mProcs[42] = (UINT_PTR)&mciGetDriverData_fake;
#endif
#ifdef MCIGETERRORSTRINGA
  mciGetErrorStringA_real = (mciGetErrorStringA_ptr)mProcs[43];
  mProcs[43] = (UINT_PTR)&mciGetErrorStringA_fake;
#endif
#ifdef MCIGETERRORSTRINGW
  mciGetErrorStringW_real = (mciGetErrorStringW_ptr)mProcs[44];
  mProcs[44] = (UINT_PTR)&mciGetErrorStringW_fake;
#endif
#ifdef MCIGETYIELDPROC
  mciGetYieldProc_real = (mciGetYieldProc_ptr)mProcs[45];
  mProcs[45] = (UINT_PTR)&mciGetYieldProc_fake;
#endif
#ifdef MCILOADCOMMANDRESOURCE
  mciLoadCommandResource_real = (mciLoadCommandResource_ptr)mProcs[46];
  mProcs[46] = (UINT_PTR)&mciLoadCommandResource_fake;
#endif
#ifdef MCISENDCOMMANDA
  mciSendCommandA_real = (mciSendCommandA_ptr)mProcs[47];
  mProcs[47] = (UINT_PTR)&mciSendCommandA_fake;
#endif
#ifdef MCISENDCOMMANDW
  mciSendCommandW_real = (mciSendCommandW_ptr)mProcs[48];
  mProcs[48] = (UINT_PTR)&mciSendCommandW_fake;
#endif
#ifdef MCISENDSTRINGA
  mciSendStringA_real = (mciSendStringA_ptr)mProcs[49];
  mProcs[49] = (UINT_PTR)&mciSendStringA_fake;
#endif
#ifdef MCISENDSTRINGW
  mciSendStringW_real = (mciSendStringW_ptr)mProcs[50];
  mProcs[50] = (UINT_PTR)&mciSendStringW_fake;
#endif
#ifdef MCISETDRIVERDATA
  mciSetDriverData_real = (mciSetDriverData_ptr)mProcs[51];
  mProcs[51] = (UINT_PTR)&mciSetDriverData_fake;
#endif
#ifdef MCISETYIELDPROC
  mciSetYieldProc_real = (mciSetYieldProc_ptr)mProcs[52];
  mProcs[52] = (UINT_PTR)&mciSetYieldProc_fake;
#endif
#ifdef MID32MESSAGE
  mid32Message_real = (mid32Message_ptr)mProcs[53];
  mProcs[53] = (UINT_PTR)&mid32Message_fake;
#endif
#ifdef MIDICONNECT
  midiConnect_real = (midiConnect_ptr)mProcs[54];
  mProcs[54] = (UINT_PTR)&midiConnect_fake;
#endif
#ifdef MIDIDISCONNECT
  midiDisconnect_real = (midiDisconnect_ptr)mProcs[55];
  mProcs[55] = (UINT_PTR)&midiDisconnect_fake;
#endif
#ifdef MIDIINADDBUFFER
  midiInAddBuffer_real = (midiInAddBuffer_ptr)mProcs[56];
  mProcs[56] = (UINT_PTR)&midiInAddBuffer_fake;
#endif
#ifdef MIDIINCLOSE
  midiInClose_real = (midiInClose_ptr)mProcs[57];
  mProcs[57] = (UINT_PTR)&midiInClose_fake;
#endif
#ifdef MIDIINGETDEVCAPSA
  midiInGetDevCapsA_real = (midiInGetDevCapsA_ptr)mProcs[58];
  mProcs[58] = (UINT_PTR)&midiInGetDevCapsA_fake;
#endif
#ifdef MIDIINGETDEVCAPSW
  midiInGetDevCapsW_real = (midiInGetDevCapsW_ptr)mProcs[59];
  mProcs[59] = (UINT_PTR)&midiInGetDevCapsW_fake;
#endif
#ifdef MIDIINGETERRORTEXTA
  midiInGetErrorTextA_real = (midiInGetErrorTextA_ptr)mProcs[60];
  mProcs[60] = (UINT_PTR)&midiInGetErrorTextA_fake;
#endif
#ifdef MIDIINGETERRORTEXTW
  midiInGetErrorTextW_real = (midiInGetErrorTextW_ptr)mProcs[61];
  mProcs[61] = (UINT_PTR)&midiInGetErrorTextW_fake;
#endif
#ifdef MIDIINGETID
  midiInGetID_real = (midiInGetID_ptr)mProcs[62];
  mProcs[62] = (UINT_PTR)&midiInGetID_fake;
#endif
#ifdef MIDIINGETNUMDEVS
  midiInGetNumDevs_real = (midiInGetNumDevs_ptr)mProcs[63];
  mProcs[63] = (UINT_PTR)&midiInGetNumDevs_fake;
#endif
#ifdef MIDIINMESSAGE
  midiInMessage_real = (midiInMessage_ptr)mProcs[64];
  mProcs[64] = (UINT_PTR)&midiInMessage_fake;
#endif
#ifdef MIDIINOPEN
  midiInOpen_real = (midiInOpen_ptr)mProcs[65];
  mProcs[65] = (UINT_PTR)&midiInOpen_fake;
#endif
#ifdef MIDIINPREPAREHEADER
  midiInPrepareHeader_real = (midiInPrepareHeader_ptr)mProcs[66];
  mProcs[66] = (UINT_PTR)&midiInPrepareHeader_fake;
#endif
#ifdef MIDIINRESET
  midiInReset_real = (midiInReset_ptr)mProcs[67];
  mProcs[67] = (UINT_PTR)&midiInReset_fake;
#endif
#ifdef MIDIINSTART
  midiInStart_real = (midiInStart_ptr)mProcs[68];
  mProcs[68] = (UINT_PTR)&midiInStart_fake;
#endif
#ifdef MIDIINSTOP
  midiInStop_real = (midiInStop_ptr)mProcs[69];
  mProcs[69] = (UINT_PTR)&midiInStop_fake;
#endif
#ifdef MIDIINUNPREPAREHEADER
  midiInUnprepareHeader_real = (midiInUnprepareHeader_ptr)mProcs[70];
  mProcs[70] = (UINT_PTR)&midiInUnprepareHeader_fake;
#endif
#ifdef MIDIOUTCACHEDRUMPATCHES
  midiOutCacheDrumPatches_real = (midiOutCacheDrumPatches_ptr)mProcs[71];
  mProcs[71] = (UINT_PTR)&midiOutCacheDrumPatches_fake;
#endif
#ifdef MIDIOUTCACHEPATCHES
  midiOutCachePatches_real = (midiOutCachePatches_ptr)mProcs[72];
  mProcs[72] = (UINT_PTR)&midiOutCachePatches_fake;
#endif
#ifdef MIDIOUTCLOSE
  midiOutClose_real = (midiOutClose_ptr)mProcs[73];
  mProcs[73] = (UINT_PTR)&midiOutClose_fake;
#endif
#ifdef MIDIOUTGETDEVCAPSA
  midiOutGetDevCapsA_real = (midiOutGetDevCapsA_ptr)mProcs[74];
  mProcs[74] = (UINT_PTR)&midiOutGetDevCapsA_fake;
#endif
#ifdef MIDIOUTGETDEVCAPSW
  midiOutGetDevCapsW_real = (midiOutGetDevCapsW_ptr)mProcs[75];
  mProcs[75] = (UINT_PTR)&midiOutGetDevCapsW_fake;
#endif
#ifdef MIDIOUTGETERRORTEXTA
  midiOutGetErrorTextA_real = (midiOutGetErrorTextA_ptr)mProcs[76];
  mProcs[76] = (UINT_PTR)&midiOutGetErrorTextA_fake;
#endif
#ifdef MIDIOUTGETERRORTEXTW
  midiOutGetErrorTextW_real = (midiOutGetErrorTextW_ptr)mProcs[77];
  mProcs[77] = (UINT_PTR)&midiOutGetErrorTextW_fake;
#endif
#ifdef MIDIOUTGETID
  midiOutGetID_real = (midiOutGetID_ptr)mProcs[78];
  mProcs[78] = (UINT_PTR)&midiOutGetID_fake;
#endif
#ifdef MIDIOUTGETNUMDEVS
  midiOutGetNumDevs_real = (midiOutGetNumDevs_ptr)mProcs[79];
  mProcs[79] = (UINT_PTR)&midiOutGetNumDevs_fake;
#endif
#ifdef MIDIOUTGETVOLUME
  midiOutGetVolume_real = (midiOutGetVolume_ptr)mProcs[80];
  mProcs[80] = (UINT_PTR)&midiOutGetVolume_fake;
#endif
#ifdef MIDIOUTLONGMSG
  midiOutLongMsg_real = (midiOutLongMsg_ptr)mProcs[81];
  mProcs[81] = (UINT_PTR)&midiOutLongMsg_fake;
#endif
#ifdef MIDIOUTMESSAGE
  midiOutMessage_real = (midiOutMessage_ptr)mProcs[82];
  mProcs[82] = (UINT_PTR)&midiOutMessage_fake;
#endif
#ifdef MIDIOUTOPEN
  midiOutOpen_real = (midiOutOpen_ptr)mProcs[83];
  mProcs[83] = (UINT_PTR)&midiOutOpen_fake;
#endif
#ifdef MIDIOUTPREPAREHEADER
  midiOutPrepareHeader_real = (midiOutPrepareHeader_ptr)mProcs[84];
  mProcs[84] = (UINT_PTR)&midiOutPrepareHeader_fake;
#endif
#ifdef MIDIOUTRESET
  midiOutReset_real = (midiOutReset_ptr)mProcs[85];
  mProcs[85] = (UINT_PTR)&midiOutReset_fake;
#endif
#ifdef MIDIOUTSETVOLUME
  midiOutSetVolume_real = (midiOutSetVolume_ptr)mProcs[86];
  mProcs[86] = (UINT_PTR)&midiOutSetVolume_fake;
#endif
#ifdef MIDIOUTSHORTMSG
  midiOutShortMsg_real = (midiOutShortMsg_ptr)mProcs[87];
  mProcs[87] = (UINT_PTR)&midiOutShortMsg_fake;
#endif
#ifdef MIDIOUTUNPREPAREHEADER
  midiOutUnprepareHeader_real = (midiOutUnprepareHeader_ptr)mProcs[88];
  mProcs[88] = (UINT_PTR)&midiOutUnprepareHeader_fake;
#endif
#ifdef MIDISTREAMCLOSE
  midiStreamClose_real = (midiStreamClose_ptr)mProcs[89];
  mProcs[89] = (UINT_PTR)&midiStreamClose_fake;
#endif
#ifdef MIDISTREAMOPEN
  midiStreamOpen_real = (midiStreamOpen_ptr)mProcs[90];
  mProcs[90] = (UINT_PTR)&midiStreamOpen_fake;
#endif
#ifdef MIDISTREAMOUT
  midiStreamOut_real = (midiStreamOut_ptr)mProcs[91];
  mProcs[91] = (UINT_PTR)&midiStreamOut_fake;
#endif
#ifdef MIDISTREAMPAUSE
  midiStreamPause_real = (midiStreamPause_ptr)mProcs[92];
  mProcs[92] = (UINT_PTR)&midiStreamPause_fake;
#endif
#ifdef MIDISTREAMPOSITION
  midiStreamPosition_real = (midiStreamPosition_ptr)mProcs[93];
  mProcs[93] = (UINT_PTR)&midiStreamPosition_fake;
#endif
#ifdef MIDISTREAMPROPERTY
  midiStreamProperty_real = (midiStreamProperty_ptr)mProcs[94];
  mProcs[94] = (UINT_PTR)&midiStreamProperty_fake;
#endif
#ifdef MIDISTREAMRESTART
  midiStreamRestart_real = (midiStreamRestart_ptr)mProcs[95];
  mProcs[95] = (UINT_PTR)&midiStreamRestart_fake;
#endif
#ifdef MIDISTREAMSTOP
  midiStreamStop_real = (midiStreamStop_ptr)mProcs[96];
  mProcs[96] = (UINT_PTR)&midiStreamStop_fake;
#endif
#ifdef MIXERCLOSE
  mixerClose_real = (mixerClose_ptr)mProcs[97];
  mProcs[97] = (UINT_PTR)&mixerClose_fake;
#endif
#ifdef MIXERGETCONTROLDETAILSA
  mixerGetControlDetailsA_real = (mixerGetControlDetailsA_ptr)mProcs[98];
  mProcs[98] = (UINT_PTR)&mixerGetControlDetailsA_fake;
#endif
#ifdef MIXERGETCONTROLDETAILSW
  mixerGetControlDetailsW_real = (mixerGetControlDetailsW_ptr)mProcs[99];
  mProcs[99] = (UINT_PTR)&mixerGetControlDetailsW_fake;
#endif
#ifdef MIXERGETDEVCAPSA
  mixerGetDevCapsA_real = (mixerGetDevCapsA_ptr)mProcs[100];
  mProcs[100] = (UINT_PTR)&mixerGetDevCapsA_fake;
#endif
#ifdef MIXERGETDEVCAPSW
  mixerGetDevCapsW_real = (mixerGetDevCapsW_ptr)mProcs[101];
  mProcs[101] = (UINT_PTR)&mixerGetDevCapsW_fake;
#endif
#ifdef MIXERGETID
  mixerGetID_real = (mixerGetID_ptr)mProcs[102];
  mProcs[102] = (UINT_PTR)&mixerGetID_fake;
#endif
#ifdef MIXERGETLINECONTROLSA
  mixerGetLineControlsA_real = (mixerGetLineControlsA_ptr)mProcs[103];
  mProcs[103] = (UINT_PTR)&mixerGetLineControlsA_fake;
#endif
#ifdef MIXERGETLINECONTROLSW
  mixerGetLineControlsW_real = (mixerGetLineControlsW_ptr)mProcs[104];
  mProcs[104] = (UINT_PTR)&mixerGetLineControlsW_fake;
#endif
#ifdef MIXERGETLINEINFOA
  mixerGetLineInfoA_real = (mixerGetLineInfoA_ptr)mProcs[105];
  mProcs[105] = (UINT_PTR)&mixerGetLineInfoA_fake;
#endif
#ifdef MIXERGETLINEINFOW
  mixerGetLineInfoW_real = (mixerGetLineInfoW_ptr)mProcs[106];
  mProcs[106] = (UINT_PTR)&mixerGetLineInfoW_fake;
#endif
#ifdef MIXERGETNUMDEVS
  mixerGetNumDevs_real = (mixerGetNumDevs_ptr)mProcs[107];
  mProcs[107] = (UINT_PTR)&mixerGetNumDevs_fake;
#endif
#ifdef MIXERMESSAGE
  mixerMessage_real = (mixerMessage_ptr)mProcs[108];
  mProcs[108] = (UINT_PTR)&mixerMessage_fake;
#endif
#ifdef MIXEROPEN
  mixerOpen_real = (mixerOpen_ptr)mProcs[109];
  mProcs[109] = (UINT_PTR)&mixerOpen_fake;
#endif
#ifdef MIXERSETCONTROLDETAILS
  mixerSetControlDetails_real = (mixerSetControlDetails_ptr)mProcs[110];
  mProcs[110] = (UINT_PTR)&mixerSetControlDetails_fake;
#endif
#ifdef MMDRVINSTALL
  mmDrvInstall_real = (mmDrvInstall_ptr)mProcs[111];
  mProcs[111] = (UINT_PTR)&mmDrvInstall_fake;
#endif
#ifdef MMGETCURRENTTASK
  mmGetCurrentTask_real = (mmGetCurrentTask_ptr)mProcs[112];
  mProcs[112] = (UINT_PTR)&mmGetCurrentTask_fake;
#endif
#ifdef MMTASKBLOCK
  mmTaskBlock_real = (mmTaskBlock_ptr)mProcs[113];
  mProcs[113] = (UINT_PTR)&mmTaskBlock_fake;
#endif
#ifdef MMTASKCREATE
  mmTaskCreate_real = (mmTaskCreate_ptr)mProcs[114];
  mProcs[114] = (UINT_PTR)&mmTaskCreate_fake;
#endif
#ifdef MMTASKSIGNAL
  mmTaskSignal_real = (mmTaskSignal_ptr)mProcs[115];
  mProcs[115] = (UINT_PTR)&mmTaskSignal_fake;
#endif
#ifdef MMTASKYIELD
  mmTaskYield_real = (mmTaskYield_ptr)mProcs[116];
  mProcs[116] = (UINT_PTR)&mmTaskYield_fake;
#endif
#ifdef MMIOADVANCE
  mmioAdvance_real = (mmioAdvance_ptr)mProcs[117];
  mProcs[117] = (UINT_PTR)&mmioAdvance_fake;
#endif
#ifdef MMIOASCEND
  mmioAscend_real = (mmioAscend_ptr)mProcs[118];
  mProcs[118] = (UINT_PTR)&mmioAscend_fake;
#endif
#ifdef MMIOCLOSE
  mmioClose_real = (mmioClose_ptr)mProcs[119];
  mProcs[119] = (UINT_PTR)&mmioClose_fake;
#endif
#ifdef MMIOCREATECHUNK
  mmioCreateChunk_real = (mmioCreateChunk_ptr)mProcs[120];
  mProcs[120] = (UINT_PTR)&mmioCreateChunk_fake;
#endif
#ifdef MMIODESCEND
  mmioDescend_real = (mmioDescend_ptr)mProcs[121];
  mProcs[121] = (UINT_PTR)&mmioDescend_fake;
#endif
#ifdef MMIOFLUSH
  mmioFlush_real = (mmioFlush_ptr)mProcs[122];
  mProcs[122] = (UINT_PTR)&mmioFlush_fake;
#endif
#ifdef MMIOGETINFO
  mmioGetInfo_real = (mmioGetInfo_ptr)mProcs[123];
  mProcs[123] = (UINT_PTR)&mmioGetInfo_fake;
#endif
#ifdef MMIOINSTALLIOPROCA
  mmioInstallIOProcA_real = (mmioInstallIOProcA_ptr)mProcs[124];
  mProcs[124] = (UINT_PTR)&mmioInstallIOProcA_fake;
#endif
#ifdef MMIOINSTALLIOPROCW
  mmioInstallIOProcW_real = (mmioInstallIOProcW_ptr)mProcs[125];
  mProcs[125] = (UINT_PTR)&mmioInstallIOProcW_fake;
#endif
#ifdef MMIOOPENA
  mmioOpenA_real = (mmioOpenA_ptr)mProcs[126];
  mProcs[126] = (UINT_PTR)&mmioOpenA_fake;
#endif
#ifdef MMIOOPENW
  mmioOpenW_real = (mmioOpenW_ptr)mProcs[127];
  mProcs[127] = (UINT_PTR)&mmioOpenW_fake;
#endif
#ifdef MMIOREAD
  mmioRead_real = (mmioRead_ptr)mProcs[128];
  mProcs[128] = (UINT_PTR)&mmioRead_fake;
#endif
#ifdef MMIORENAMEA
  mmioRenameA_real = (mmioRenameA_ptr)mProcs[129];
  mProcs[129] = (UINT_PTR)&mmioRenameA_fake;
#endif
#ifdef MMIORENAMEW
  mmioRenameW_real = (mmioRenameW_ptr)mProcs[130];
  mProcs[130] = (UINT_PTR)&mmioRenameW_fake;
#endif
#ifdef MMIOSEEK
  mmioSeek_real = (mmioSeek_ptr)mProcs[131];
  mProcs[131] = (UINT_PTR)&mmioSeek_fake;
#endif
#ifdef MMIOSENDMESSAGE
  mmioSendMessage_real = (mmioSendMessage_ptr)mProcs[132];
  mProcs[132] = (UINT_PTR)&mmioSendMessage_fake;
#endif
#ifdef MMIOSETBUFFER
  mmioSetBuffer_real = (mmioSetBuffer_ptr)mProcs[133];
  mProcs[133] = (UINT_PTR)&mmioSetBuffer_fake;
#endif
#ifdef MMIOSETINFO
  mmioSetInfo_real = (mmioSetInfo_ptr)mProcs[134];
  mProcs[134] = (UINT_PTR)&mmioSetInfo_fake;
#endif
#ifdef MMIOSTRINGTOFOURCCA
  mmioStringToFOURCCA_real = (mmioStringToFOURCCA_ptr)mProcs[135];
  mProcs[135] = (UINT_PTR)&mmioStringToFOURCCA_fake;
#endif
#ifdef MMIOSTRINGTOFOURCCW
  mmioStringToFOURCCW_real = (mmioStringToFOURCCW_ptr)mProcs[136];
  mProcs[136] = (UINT_PTR)&mmioStringToFOURCCW_fake;
#endif
#ifdef MMIOWRITE
  mmioWrite_real = (mmioWrite_ptr)mProcs[137];
  mProcs[137] = (UINT_PTR)&mmioWrite_fake;
#endif
#ifdef MMSYSTEMGETVERSION
  mmsystemGetVersion_real = (mmsystemGetVersion_ptr)mProcs[138];
  mProcs[138] = (UINT_PTR)&mmsystemGetVersion_fake;
#endif
#ifdef MOD32MESSAGE
  mod32Message_real = (mod32Message_ptr)mProcs[139];
  mProcs[139] = (UINT_PTR)&mod32Message_fake;
#endif
#ifdef MXD32MESSAGE
  mxd32Message_real = (mxd32Message_ptr)mProcs[140];
  mProcs[140] = (UINT_PTR)&mxd32Message_fake;
#endif
#ifdef SNDPLAYSOUNDA
  sndPlaySoundA_real = (sndPlaySoundA_ptr)mProcs[141];
  mProcs[141] = (UINT_PTR)&sndPlaySoundA_fake;
#endif
#ifdef SNDPLAYSOUNDW
  sndPlaySoundW_real = (sndPlaySoundW_ptr)mProcs[142];
  mProcs[142] = (UINT_PTR)&sndPlaySoundW_fake;
#endif
#ifdef TID32MESSAGE
  tid32Message_real = (tid32Message_ptr)mProcs[143];
  mProcs[143] = (UINT_PTR)&tid32Message_fake;
#endif
#ifdef TIMEBEGINPERIOD
  timeBeginPeriod_real = (timeBeginPeriod_ptr)mProcs[144];
  mProcs[144] = (UINT_PTR)&timeBeginPeriod_fake;
#endif
#ifdef TIMEENDPERIOD
  timeEndPeriod_real = (timeEndPeriod_ptr)mProcs[145];
  mProcs[145] = (UINT_PTR)&timeEndPeriod_fake;
#endif
#ifdef TIMEGETDEVCAPS
  timeGetDevCaps_real = (timeGetDevCaps_ptr)mProcs[146];
  mProcs[146] = (UINT_PTR)&timeGetDevCaps_fake;
#endif
#ifdef TIMEGETSYSTEMTIME
  timeGetSystemTime_real = (timeGetSystemTime_ptr)mProcs[147];
  mProcs[147] = (UINT_PTR)&timeGetSystemTime_fake;
#endif
#ifdef TIMEGETTIME
  timeGetTime_real = (timeGetTime_ptr)mProcs[148];
  mProcs[148] = (UINT_PTR)&timeGetTime_fake;
#endif
#ifdef TIMEKILLEVENT
  timeKillEvent_real = (timeKillEvent_ptr)mProcs[149];
  mProcs[149] = (UINT_PTR)&timeKillEvent_fake;
#endif
#ifdef TIMESETEVENT
  timeSetEvent_real = (timeSetEvent_ptr)mProcs[150];
  mProcs[150] = (UINT_PTR)&timeSetEvent_fake;
#endif
#ifdef WAVEINADDBUFFER
  waveInAddBuffer_real = (waveInAddBuffer_ptr)mProcs[151];
  mProcs[151] = (UINT_PTR)&waveInAddBuffer_fake;
#endif
#ifdef WAVEINCLOSE
  waveInClose_real = (waveInClose_ptr)mProcs[152];
  mProcs[152] = (UINT_PTR)&waveInClose_fake;
#endif
#ifdef WAVEINGETDEVCAPSA
  waveInGetDevCapsA_real = (waveInGetDevCapsA_ptr)mProcs[153];
  mProcs[153] = (UINT_PTR)&waveInGetDevCapsA_fake;
#endif
#ifdef WAVEINGETDEVCAPSW
  waveInGetDevCapsW_real = (waveInGetDevCapsW_ptr)mProcs[154];
  mProcs[154] = (UINT_PTR)&waveInGetDevCapsW_fake;
#endif
#ifdef WAVEINGETERRORTEXTA
  waveInGetErrorTextA_real = (waveInGetErrorTextA_ptr)mProcs[155];
  mProcs[155] = (UINT_PTR)&waveInGetErrorTextA_fake;
#endif
#ifdef WAVEINGETERRORTEXTW
  waveInGetErrorTextW_real = (waveInGetErrorTextW_ptr)mProcs[156];
  mProcs[156] = (UINT_PTR)&waveInGetErrorTextW_fake;
#endif
#ifdef WAVEINGETID
  waveInGetID_real = (waveInGetID_ptr)mProcs[157];
  mProcs[157] = (UINT_PTR)&waveInGetID_fake;
#endif
#ifdef WAVEINGETNUMDEVS
  waveInGetNumDevs_real = (waveInGetNumDevs_ptr)mProcs[158];
  mProcs[158] = (UINT_PTR)&waveInGetNumDevs_fake;
#endif
#ifdef WAVEINGETPOSITION
  waveInGetPosition_real = (waveInGetPosition_ptr)mProcs[159];
  mProcs[159] = (UINT_PTR)&waveInGetPosition_fake;
#endif
#ifdef WAVEINMESSAGE
  waveInMessage_real = (waveInMessage_ptr)mProcs[160];
  mProcs[160] = (UINT_PTR)&waveInMessage_fake;
#endif
#ifdef WAVEINOPEN
  waveInOpen_real = (waveInOpen_ptr)mProcs[161];
  mProcs[161] = (UINT_PTR)&waveInOpen_fake;
#endif
#ifdef WAVEINPREPAREHEADER
  waveInPrepareHeader_real = (waveInPrepareHeader_ptr)mProcs[162];
  mProcs[162] = (UINT_PTR)&waveInPrepareHeader_fake;
#endif
#ifdef WAVEINRESET
  waveInReset_real = (waveInReset_ptr)mProcs[163];
  mProcs[163] = (UINT_PTR)&waveInReset_fake;
#endif
#ifdef WAVEINSTART
  waveInStart_real = (waveInStart_ptr)mProcs[164];
  mProcs[164] = (UINT_PTR)&waveInStart_fake;
#endif
#ifdef WAVEINSTOP
  waveInStop_real = (waveInStop_ptr)mProcs[165];
  mProcs[165] = (UINT_PTR)&waveInStop_fake;
#endif
#ifdef WAVEINUNPREPAREHEADER
  waveInUnprepareHeader_real = (waveInUnprepareHeader_ptr)mProcs[166];
  mProcs[166] = (UINT_PTR)&waveInUnprepareHeader_fake;
#endif
#ifdef WAVEOUTBREAKLOOP
  waveOutBreakLoop_real = (waveOutBreakLoop_ptr)mProcs[167];
  mProcs[167] = (UINT_PTR)&waveOutBreakLoop_fake;
#endif
#ifdef WAVEOUTCLOSE
  waveOutClose_real = (waveOutClose_ptr)mProcs[168];
  mProcs[168] = (UINT_PTR)&waveOutClose_fake;
#endif
#ifdef WAVEOUTGETDEVCAPSA
  waveOutGetDevCapsA_real = (waveOutGetDevCapsA_ptr)mProcs[169];
  mProcs[169] = (UINT_PTR)&waveOutGetDevCapsA_fake;
#endif
#ifdef WAVEOUTGETDEVCAPSW
  waveOutGetDevCapsW_real = (waveOutGetDevCapsW_ptr)mProcs[170];
  mProcs[170] = (UINT_PTR)&waveOutGetDevCapsW_fake;
#endif
#ifdef WAVEOUTGETERRORTEXTA
  waveOutGetErrorTextA_real = (waveOutGetErrorTextA_ptr)mProcs[171];
  mProcs[171] = (UINT_PTR)&waveOutGetErrorTextA_fake;
#endif
#ifdef WAVEOUTGETERRORTEXTW
  waveOutGetErrorTextW_real = (waveOutGetErrorTextW_ptr)mProcs[172];
  mProcs[172] = (UINT_PTR)&waveOutGetErrorTextW_fake;
#endif
#ifdef WAVEOUTGETID
  waveOutGetID_real = (waveOutGetID_ptr)mProcs[173];
  mProcs[173] = (UINT_PTR)&waveOutGetID_fake;
#endif
#ifdef WAVEOUTGETNUMDEVS
  waveOutGetNumDevs_real = (waveOutGetNumDevs_ptr)mProcs[174];
  mProcs[174] = (UINT_PTR)&waveOutGetNumDevs_fake;
#endif
#ifdef WAVEOUTGETPITCH
  waveOutGetPitch_real = (waveOutGetPitch_ptr)mProcs[175];
  mProcs[175] = (UINT_PTR)&waveOutGetPitch_fake;
#endif
#ifdef WAVEOUTGETPLAYBACKRATE
  waveOutGetPlaybackRate_real = (waveOutGetPlaybackRate_ptr)mProcs[176];
  mProcs[176] = (UINT_PTR)&waveOutGetPlaybackRate_fake;
#endif
#ifdef WAVEOUTGETPOSITION
  waveOutGetPosition_real = (waveOutGetPosition_ptr)mProcs[177];
  mProcs[177] = (UINT_PTR)&waveOutGetPosition_fake;
#endif
#ifdef WAVEOUTGETVOLUME
  waveOutGetVolume_real = (waveOutGetVolume_ptr)mProcs[178];
  mProcs[178] = (UINT_PTR)&waveOutGetVolume_fake;
#endif
#ifdef WAVEOUTMESSAGE
  waveOutMessage_real = (waveOutMessage_ptr)mProcs[179];
  mProcs[179] = (UINT_PTR)&waveOutMessage_fake;
#endif
#ifdef WAVEOUTOPEN
  waveOutOpen_real = (waveOutOpen_ptr)mProcs[180];
  mProcs[180] = (UINT_PTR)&waveOutOpen_fake;
#endif
#ifdef WAVEOUTPAUSE
  waveOutPause_real = (waveOutPause_ptr)mProcs[181];
  mProcs[181] = (UINT_PTR)&waveOutPause_fake;
#endif
#ifdef WAVEOUTPREPAREHEADER
  waveOutPrepareHeader_real = (waveOutPrepareHeader_ptr)mProcs[182];
  mProcs[182] = (UINT_PTR)&waveOutPrepareHeader_fake;
#endif
#ifdef WAVEOUTRESET
  waveOutReset_real = (waveOutReset_ptr)mProcs[183];
  mProcs[183] = (UINT_PTR)&waveOutReset_fake;
#endif
#ifdef WAVEOUTRESTART
  waveOutRestart_real = (waveOutRestart_ptr)mProcs[184];
  mProcs[184] = (UINT_PTR)&waveOutRestart_fake;
#endif
#ifdef WAVEOUTSETPITCH
  waveOutSetPitch_real = (waveOutSetPitch_ptr)mProcs[185];
  mProcs[185] = (UINT_PTR)&waveOutSetPitch_fake;
#endif
#ifdef WAVEOUTSETPLAYBACKRATE
  waveOutSetPlaybackRate_real = (waveOutSetPlaybackRate_ptr)mProcs[186];
  mProcs[186] = (UINT_PTR)&waveOutSetPlaybackRate_fake;
#endif
#ifdef WAVEOUTSETVOLUME
  waveOutSetVolume_real = (waveOutSetVolume_ptr)mProcs[187];
  mProcs[187] = (UINT_PTR)&waveOutSetVolume_fake;
#endif
#ifdef WAVEOUTUNPREPAREHEADER
  waveOutUnprepareHeader_real = (waveOutUnprepareHeader_ptr)mProcs[188];
  mProcs[188] = (UINT_PTR)&waveOutUnprepareHeader_fake;
#endif
#ifdef WAVEOUTWRITE
  waveOutWrite_real = (waveOutWrite_ptr)mProcs[189];
  mProcs[189] = (UINT_PTR)&waveOutWrite_fake;
#endif
#ifdef WID32MESSAGE
  wid32Message_real = (wid32Message_ptr)mProcs[190];
  mProcs[190] = (UINT_PTR)&wid32Message_fake;
#endif
#ifdef WOD32MESSAGE
  wod32Message_real = (wod32Message_ptr)mProcs[191];
  mProcs[191] = (UINT_PTR)&wod32Message_fake;
#endif
#ifdef _NONAME_
   _NONAME__real = (_NONAME__ptr)mProcs[192];
   mProcs[192] = (UINT_PTR)&_NONAME__fake;
#endif
}

extern DECLSPEC void SDLCALL SDL_Quit(void);

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
  mHinst = hinstDLL;
  if (fdwReason == DLL_PROCESS_ATTACH) {
    mHinstDLL = LoadLibrary("real_winmm.dll");
    if (!mHinstDLL) {
      return FALSE;
    }
    for (int i = 0; i < 193; ++i) {
      mProcs[i] = (UINT_PTR)GetProcAddress(mHinstDLL, mImportNames[i]);
    }

    //SDL Initialization
    if (SDL_Init(SDL_INIT_AUDIO) != 0) {
      fprintf(stderr, "ERROR: Cannot init SDL: %s\n", SDL_GetError());
      return -1;
    }

    _hook_setup();
#ifdef _DEBUG
    debug = fopen("./debug.log", "a");
#endif
  } else if (fdwReason == DLL_PROCESS_DETACH) {
    SDL_Quit();
#ifdef _DEBUG
    fclose(debug);
#endif
    FreeLibrary(mHinstDLL);
  }
  return TRUE;
}

extern "C" __declspec(naked) void __stdcall CloseDriver_wrapper(){
#ifdef _DEBUG
  log_info("calling CloseDriver");
#endif
  __asm{jmp mProcs[0 * 4]}
}
extern "C" __declspec(naked) void __stdcall DefDriverProc_wrapper(){
#ifdef _DEBUG
  log_info("calling DefDriverProc");
#endif
  __asm{jmp mProcs[1 * 4]}
}
extern "C" __declspec(naked) void __stdcall DriverCallback_wrapper(){
#ifdef _DEBUG
  log_info("calling DriverCallback");
#endif
  __asm{jmp mProcs[2 * 4]}
}
extern "C" __declspec(naked) void __stdcall DrvGetModuleHandle_wrapper(){
#ifdef _DEBUG
  log_info("calling DrvGetModuleHandle");
#endif
  __asm{jmp mProcs[3 * 4]}
}
extern "C" __declspec(naked) void __stdcall GetDriverModuleHandle_wrapper(){
#ifdef _DEBUG
  log_info("calling GetDriverModuleHandle");
#endif
  __asm{jmp mProcs[4 * 4]}
}
extern "C" __declspec(naked) void __stdcall NotifyCallbackData_wrapper(){
#ifdef _DEBUG
  log_info("calling NotifyCallbackData");
#endif
  __asm{jmp mProcs[5 * 4]}
}
extern "C" __declspec(naked) void __stdcall OpenDriver_wrapper(){
#ifdef _DEBUG
  log_info("calling OpenDriver");
#endif
  __asm{jmp mProcs[6 * 4]}
}
extern "C" __declspec(naked) void __stdcall PlaySound_wrapper(){
#ifdef _DEBUG
  log_info("calling PlaySound");
#endif
  __asm{jmp mProcs[7 * 4]}
}
extern "C" __declspec(naked) void __stdcall PlaySoundA_wrapper(){
#ifdef _DEBUG
  log_info("calling PlaySoundA");
#endif
  __asm{jmp mProcs[8 * 4]}
}
extern "C" __declspec(naked) void __stdcall PlaySoundW_wrapper(){
#ifdef _DEBUG
  log_info("calling PlaySoundW");
#endif
  __asm{jmp mProcs[9 * 4]}
}
extern "C" __declspec(naked) void __stdcall SendDriverMessage_wrapper(){
#ifdef _DEBUG
  log_info("calling SendDriverMessage");
#endif
  __asm{jmp mProcs[10 * 4]}
}
extern "C" __declspec(naked) void __stdcall WOW32DriverCallback_wrapper(){
#ifdef _DEBUG
  log_info("calling WOW32DriverCallback");
#endif
  __asm{jmp mProcs[11 * 4]}
}
extern "C" __declspec(naked) void __stdcall WOW32ResolveMultiMediaHandle_wrapper(){
#ifdef _DEBUG
  log_info("calling WOW32ResolveMultiMediaHandle");
#endif
  __asm{jmp mProcs[12 * 4]}
}
extern "C" __declspec(naked) void __stdcall WOWAppExit_wrapper(){
#ifdef _DEBUG
  log_info("calling WOWAppExit");
#endif
  __asm{jmp mProcs[13 * 4]}
}
extern "C" __declspec(naked) void __stdcall aux32Message_wrapper(){
#ifdef _DEBUG
  log_info("calling aux32Message");
#endif
  __asm{jmp mProcs[14 * 4]}
}
extern "C" __declspec(naked) void __stdcall auxGetDevCapsA_wrapper(){
#ifdef _DEBUG
  log_info("calling auxGetDevCapsA");
#endif
  __asm{jmp mProcs[15 * 4]}
}
extern "C" __declspec(naked) void __stdcall auxGetDevCapsW_wrapper(){
#ifdef _DEBUG
  log_info("calling auxGetDevCapsW");
#endif
  __asm{jmp mProcs[16 * 4]}
}
extern "C" __declspec(naked) void __stdcall auxGetNumDevs_wrapper(){
#ifdef _DEBUG
  log_info("calling auxGetNumDevs");
#endif
  __asm{jmp mProcs[17 * 4]}
}
extern "C" __declspec(naked) void __stdcall auxGetVolume_wrapper(){
#ifdef _DEBUG
  log_info("calling auxGetVolume");
#endif
  __asm{jmp mProcs[18 * 4]}
}
extern "C" __declspec(naked) void __stdcall auxOutMessage_wrapper(){
#ifdef _DEBUG
  log_info("calling auxOutMessage");
#endif
  __asm{jmp mProcs[19 * 4]}
}
extern "C" __declspec(naked) void __stdcall auxSetVolume_wrapper(){
#ifdef _DEBUG
  log_info("calling auxSetVolume");
#endif
  __asm{jmp mProcs[20 * 4]}
}
extern "C" __declspec(naked) void __stdcall joy32Message_wrapper(){
#ifdef _DEBUG
  log_info("calling joy32Message");
#endif
  __asm{jmp mProcs[21 * 4]}
}
extern "C" __declspec(naked) void __stdcall joyConfigChanged_wrapper(){
#ifdef _DEBUG
  log_info("calling joyConfigChanged");
#endif
  __asm{jmp mProcs[22 * 4]}
}
extern "C" __declspec(naked) void __stdcall joyGetDevCapsA_wrapper(){
#ifdef _DEBUG
  log_info("calling joyGetDevCapsA");
#endif
  __asm{jmp mProcs[23 * 4]}
}
extern "C" __declspec(naked) void __stdcall joyGetDevCapsW_wrapper(){
#ifdef _DEBUG
  log_info("calling joyGetDevCapsW");
#endif
  __asm{jmp mProcs[24 * 4]}
}
extern "C" __declspec(naked) void __stdcall joyGetNumDevs_wrapper(){
#ifdef _DEBUG
  log_info("calling joyGetNumDevs");
#endif
  __asm{jmp mProcs[25 * 4]}
}
extern "C" __declspec(naked) void __stdcall joyGetPos_wrapper(){
#ifdef _DEBUG
  log_info("calling joyGetPos");
#endif
  __asm{jmp mProcs[26 * 4]}
}
extern "C" __declspec(naked) void __stdcall joyGetPosEx_wrapper(){
#ifdef _DEBUG
  log_info("calling joyGetPosEx");
#endif
  __asm{jmp mProcs[27 * 4]}
}
extern "C" __declspec(naked) void __stdcall joyGetThreshold_wrapper(){
#ifdef _DEBUG
  log_info("calling joyGetThreshold");
#endif
  __asm{jmp mProcs[28 * 4]}
}
extern "C" __declspec(naked) void __stdcall joyReleaseCapture_wrapper(){
#ifdef _DEBUG
  log_info("calling joyReleaseCapture");
#endif
  __asm{jmp mProcs[29 * 4]}
}
extern "C" __declspec(naked) void __stdcall joySetCapture_wrapper(){
#ifdef _DEBUG
  log_info("calling joySetCapture");
#endif
  __asm{jmp mProcs[30 * 4]}
}
extern "C" __declspec(naked) void __stdcall joySetThreshold_wrapper(){
#ifdef _DEBUG
  log_info("calling joySetThreshold");
#endif
  __asm{jmp mProcs[31 * 4]}
}
extern "C" __declspec(naked) void __stdcall mci32Message_wrapper(){
#ifdef _DEBUG
  log_info("calling mci32Message");
#endif
  __asm{jmp mProcs[32 * 4]}
}
extern "C" __declspec(naked) void __stdcall mciDriverNotify_wrapper(){
#ifdef _DEBUG
  log_info("calling mciDriverNotify");
#endif
  __asm{jmp mProcs[33 * 4]}
}
extern "C" __declspec(naked) void __stdcall mciDriverYield_wrapper(){
#ifdef _DEBUG
  log_info("calling mciDriverYield");
#endif
  __asm{jmp mProcs[34 * 4]}
}
extern "C" __declspec(naked) void __stdcall mciExecute_wrapper(){
#ifdef _DEBUG
  log_info("calling mciExecute");
#endif
  __asm{jmp mProcs[35 * 4]}
}
extern "C" __declspec(naked) void __stdcall mciFreeCommandResource_wrapper(){
#ifdef _DEBUG
  log_info("calling mciFreeCommandResource");
#endif
  __asm{jmp mProcs[36 * 4]}
}
extern "C" __declspec(naked) void __stdcall mciGetCreatorTask_wrapper(){
#ifdef _DEBUG
  log_info("calling mciGetCreatorTask");
#endif
  __asm{jmp mProcs[37 * 4]}
}
extern "C" __declspec(naked) void __stdcall mciGetDeviceIDA_wrapper(){
#ifdef _DEBUG
  log_info("calling mciGetDeviceIDA");
#endif
  __asm{jmp mProcs[38 * 4]}
}
extern "C" __declspec(naked) void __stdcall mciGetDeviceIDFromElementIDA_wrapper(){
#ifdef _DEBUG
  log_info("calling mciGetDeviceIDFromElementIDA");
#endif
  __asm{jmp mProcs[39 * 4]}
}
extern "C" __declspec(naked) void __stdcall mciGetDeviceIDFromElementIDW_wrapper(){
#ifdef _DEBUG
  log_info("calling mciGetDeviceIDFromElementIDW");
#endif
  __asm{jmp mProcs[40 * 4]}
}
extern "C" __declspec(naked) void __stdcall mciGetDeviceIDW_wrapper(){
#ifdef _DEBUG
  log_info("calling mciGetDeviceIDW");
#endif
  __asm{jmp mProcs[41 * 4]}
}
extern "C" __declspec(naked) void __stdcall mciGetDriverData_wrapper(){
#ifdef _DEBUG
  log_info("calling mciGetDriverData");
#endif
  __asm{jmp mProcs[42 * 4]}
}
extern "C" __declspec(naked) void __stdcall mciGetErrorStringA_wrapper(){
#ifdef _DEBUG
  log_info("calling mciGetErrorStringA");
#endif
  __asm{jmp mProcs[43 * 4]}
}
extern "C" __declspec(naked) void __stdcall mciGetErrorStringW_wrapper(){
#ifdef _DEBUG
  log_info("calling mciGetErrorStringW");
#endif
  __asm{jmp mProcs[44 * 4]}
}
extern "C" __declspec(naked) void __stdcall mciGetYieldProc_wrapper(){
#ifdef _DEBUG
  log_info("calling mciGetYieldProc");
#endif
  __asm{jmp mProcs[45 * 4]}
}
extern "C" __declspec(naked) void __stdcall mciLoadCommandResource_wrapper(){
#ifdef _DEBUG
  log_info("calling mciLoadCommandResource");
#endif
  __asm{jmp mProcs[46 * 4]}
}
extern "C" __declspec(naked) void __stdcall mciSendCommandA_wrapper(){
#ifdef _DEBUG
  log_info("calling mciSendCommandA");
#endif
  __asm{jmp mProcs[47 * 4]}
}
extern "C" __declspec(naked) void __stdcall mciSendCommandW_wrapper(){
#ifdef _DEBUG
  log_info("calling mciSendCommandW");
#endif
  __asm{jmp mProcs[48 * 4]}
}
extern "C" __declspec(naked) void __stdcall mciSendStringA_wrapper(){
#ifdef _DEBUG
  log_info("calling mciSendStringA");
#endif
  __asm{jmp mProcs[49 * 4]}
}
extern "C" __declspec(naked) void __stdcall mciSendStringW_wrapper(){
#ifdef _DEBUG
  log_info("calling mciSendStringW");
#endif
  __asm{jmp mProcs[50 * 4]}
}
extern "C" __declspec(naked) void __stdcall mciSetDriverData_wrapper(){
#ifdef _DEBUG
  log_info("calling mciSetDriverData");
#endif
  __asm{jmp mProcs[51 * 4]}
}
extern "C" __declspec(naked) void __stdcall mciSetYieldProc_wrapper(){
#ifdef _DEBUG
  log_info("calling mciSetYieldProc");
#endif
  __asm{jmp mProcs[52 * 4]}
}
extern "C" __declspec(naked) void __stdcall mid32Message_wrapper(){
#ifdef _DEBUG
  log_info("calling mid32Message");
#endif
  __asm{jmp mProcs[53 * 4]}
}
extern "C" __declspec(naked) void __stdcall midiConnect_wrapper(){
#ifdef _DEBUG
  log_info("calling midiConnect");
#endif
  __asm{jmp mProcs[54 * 4]}
}
extern "C" __declspec(naked) void __stdcall midiDisconnect_wrapper(){
#ifdef _DEBUG
  log_info("calling midiDisconnect");
#endif
  __asm{jmp mProcs[55 * 4]}
}
extern "C" __declspec(naked) void __stdcall midiInAddBuffer_wrapper(){
#ifdef _DEBUG
  log_info("calling midiInAddBuffer");
#endif
  __asm{jmp mProcs[56 * 4]}
}
extern "C" __declspec(naked) void __stdcall midiInClose_wrapper(){
#ifdef _DEBUG
  log_info("calling midiInClose");
#endif
  __asm{jmp mProcs[57 * 4]}
}
extern "C" __declspec(naked) void __stdcall midiInGetDevCapsA_wrapper(){
#ifdef _DEBUG
  log_info("calling midiInGetDevCapsA");
#endif
  __asm{jmp mProcs[58 * 4]}
}
extern "C" __declspec(naked) void __stdcall midiInGetDevCapsW_wrapper(){
#ifdef _DEBUG
  log_info("calling midiInGetDevCapsW");
#endif
  __asm{jmp mProcs[59 * 4]}
}
extern "C" __declspec(naked) void __stdcall midiInGetErrorTextA_wrapper(){
#ifdef _DEBUG
  log_info("calling midiInGetErrorTextA");
#endif
  __asm{jmp mProcs[60 * 4]}
}
extern "C" __declspec(naked) void __stdcall midiInGetErrorTextW_wrapper(){
#ifdef _DEBUG
  log_info("calling midiInGetErrorTextW");
#endif
  __asm{jmp mProcs[61 * 4]}
}
extern "C" __declspec(naked) void __stdcall midiInGetID_wrapper(){
#ifdef _DEBUG
  log_info("calling midiInGetID");
#endif
  __asm{jmp mProcs[62 * 4]}
}
extern "C" __declspec(naked) void __stdcall midiInGetNumDevs_wrapper(){
#ifdef _DEBUG
  log_info("calling midiInGetNumDevs");
#endif
  __asm{jmp mProcs[63 * 4]}
}
extern "C" __declspec(naked) void __stdcall midiInMessage_wrapper(){
#ifdef _DEBUG
  log_info("calling midiInMessage");
#endif
  __asm{jmp mProcs[64 * 4]}
}
extern "C" __declspec(naked) void __stdcall midiInOpen_wrapper(){
#ifdef _DEBUG
  log_info("calling midiInOpen");
#endif
  __asm{jmp mProcs[65 * 4]}
}
extern "C" __declspec(naked) void __stdcall midiInPrepareHeader_wrapper(){
#ifdef _DEBUG
  log_info("calling midiInPrepareHeader");
#endif
  __asm{jmp mProcs[66 * 4]}
}
extern "C" __declspec(naked) void __stdcall midiInReset_wrapper(){
#ifdef _DEBUG
  log_info("calling midiInReset");
#endif
  __asm{jmp mProcs[67 * 4]}
}
extern "C" __declspec(naked) void __stdcall midiInStart_wrapper(){
#ifdef _DEBUG
  log_info("calling midiInStart");
#endif
  __asm{jmp mProcs[68 * 4]}
}
extern "C" __declspec(naked) void __stdcall midiInStop_wrapper(){
#ifdef _DEBUG
  log_info("calling midiInStop");
#endif
  __asm{jmp mProcs[69 * 4]}
}
extern "C" __declspec(naked) void __stdcall midiInUnprepareHeader_wrapper(){
#ifdef _DEBUG
  log_info("calling midiInUnprepareHeader");
#endif
  __asm{jmp mProcs[70 * 4]}
}
extern "C" __declspec(naked) void __stdcall midiOutCacheDrumPatches_wrapper(){
#ifdef _DEBUG
  log_info("calling midiOutCacheDrumPatches");
#endif
  __asm{jmp mProcs[71 * 4]}
}
extern "C" __declspec(naked) void __stdcall midiOutCachePatches_wrapper(){
#ifdef _DEBUG
  log_info("calling midiOutCachePatches");
#endif
  __asm{jmp mProcs[72 * 4]}
}
extern "C" __declspec(naked) void __stdcall midiOutClose_wrapper(){
#ifdef _DEBUG
  log_info("calling midiOutClose");
#endif
  __asm{jmp mProcs[73 * 4]}
}
extern "C" __declspec(naked) void __stdcall midiOutGetDevCapsA_wrapper(){
#ifdef _DEBUG
  log_info("calling midiOutGetDevCapsA");
#endif
  __asm{jmp mProcs[74 * 4]}
}
extern "C" __declspec(naked) void __stdcall midiOutGetDevCapsW_wrapper(){
#ifdef _DEBUG
  log_info("calling midiOutGetDevCapsW");
#endif
  __asm{jmp mProcs[75 * 4]}
}
extern "C" __declspec(naked) void __stdcall midiOutGetErrorTextA_wrapper(){
#ifdef _DEBUG
  log_info("calling midiOutGetErrorTextA");
#endif
  __asm{jmp mProcs[76 * 4]}
}
extern "C" __declspec(naked) void __stdcall midiOutGetErrorTextW_wrapper(){
#ifdef _DEBUG
  log_info("calling midiOutGetErrorTextW");
#endif
  __asm{jmp mProcs[77 * 4]}
}
extern "C" __declspec(naked) void __stdcall midiOutGetID_wrapper(){
#ifdef _DEBUG
  log_info("calling midiOutGetID");
#endif
  __asm{jmp mProcs[78 * 4]}
}
extern "C" __declspec(naked) void __stdcall midiOutGetNumDevs_wrapper(){
#ifdef _DEBUG
  log_info("calling midiOutGetNumDevs");
#endif
  __asm{jmp mProcs[79 * 4]}
}
extern "C" __declspec(naked) void __stdcall midiOutGetVolume_wrapper(){
#ifdef _DEBUG
  log_info("calling midiOutGetVolume");
#endif
  __asm{jmp mProcs[80 * 4]}
}
extern "C" __declspec(naked) void __stdcall midiOutLongMsg_wrapper(){
#ifdef _DEBUG
  log_info("calling midiOutLongMsg");
#endif
  __asm{jmp mProcs[81 * 4]}
}
extern "C" __declspec(naked) void __stdcall midiOutMessage_wrapper(){
#ifdef _DEBUG
  log_info("calling midiOutMessage");
#endif
  __asm{jmp mProcs[82 * 4]}
}
extern "C" __declspec(naked) void __stdcall midiOutOpen_wrapper(){
#ifdef _DEBUG
  log_info("calling midiOutOpen");
#endif
  __asm{jmp mProcs[83 * 4]}
}
extern "C" __declspec(naked) void __stdcall midiOutPrepareHeader_wrapper(){
#ifdef _DEBUG
  log_info("calling midiOutPrepareHeader");
#endif
  __asm{jmp mProcs[84 * 4]}
}
extern "C" __declspec(naked) void __stdcall midiOutReset_wrapper(){
#ifdef _DEBUG
  log_info("calling midiOutReset");
#endif
  __asm{jmp mProcs[85 * 4]}
}
extern "C" __declspec(naked) void __stdcall midiOutSetVolume_wrapper(){
#ifdef _DEBUG
  log_info("calling midiOutSetVolume");
#endif
  __asm{jmp mProcs[86 * 4]}
}
extern "C" __declspec(naked) void __stdcall midiOutShortMsg_wrapper(){
#ifdef _DEBUG
  log_info("calling midiOutShortMsg");
#endif
  __asm{jmp mProcs[87 * 4]}
}
extern "C" __declspec(naked) void __stdcall midiOutUnprepareHeader_wrapper(){
#ifdef _DEBUG
  log_info("calling midiOutUnprepareHeader");
#endif
  __asm{jmp mProcs[88 * 4]}
}
extern "C" __declspec(naked) void __stdcall midiStreamClose_wrapper(){
#ifdef _DEBUG
  log_info("calling midiStreamClose");
#endif
  __asm{jmp mProcs[89 * 4]}
}
extern "C" __declspec(naked) void __stdcall midiStreamOpen_wrapper(){
#ifdef _DEBUG
  log_info("calling midiStreamOpen");
#endif
  __asm{jmp mProcs[90 * 4]}
}
extern "C" __declspec(naked) void __stdcall midiStreamOut_wrapper(){
#ifdef _DEBUG
  log_info("calling midiStreamOut");
#endif
  __asm{jmp mProcs[91 * 4]}
}
extern "C" __declspec(naked) void __stdcall midiStreamPause_wrapper(){
#ifdef _DEBUG
  log_info("calling midiStreamPause");
#endif
  __asm{jmp mProcs[92 * 4]}
}
extern "C" __declspec(naked) void __stdcall midiStreamPosition_wrapper(){
#ifdef _DEBUG
  log_info("calling midiStreamPosition");
#endif
  __asm{jmp mProcs[93 * 4]}
}
extern "C" __declspec(naked) void __stdcall midiStreamProperty_wrapper(){
#ifdef _DEBUG
  log_info("calling midiStreamProperty");
#endif
  __asm{jmp mProcs[94 * 4]}
}
extern "C" __declspec(naked) void __stdcall midiStreamRestart_wrapper(){
#ifdef _DEBUG
  log_info("calling midiStreamRestart");
#endif
  __asm{jmp mProcs[95 * 4]}
}
extern "C" __declspec(naked) void __stdcall midiStreamStop_wrapper(){
#ifdef _DEBUG
  log_info("calling midiStreamStop");
#endif
  __asm{jmp mProcs[96 * 4]}
}
extern "C" __declspec(naked) void __stdcall mixerClose_wrapper(){
#ifdef _DEBUG
  log_info("calling mixerClose");
#endif
  __asm{jmp mProcs[97 * 4]}
}
extern "C" __declspec(naked) void __stdcall mixerGetControlDetailsA_wrapper(){
#ifdef _DEBUG
  log_info("calling mixerGetControlDetailsA");
#endif
  __asm{jmp mProcs[98 * 4]}
}
extern "C" __declspec(naked) void __stdcall mixerGetControlDetailsW_wrapper(){
#ifdef _DEBUG
  log_info("calling mixerGetControlDetailsW");
#endif
  __asm{jmp mProcs[99 * 4]}
}
extern "C" __declspec(naked) void __stdcall mixerGetDevCapsA_wrapper(){
#ifdef _DEBUG
  log_info("calling mixerGetDevCapsA");
#endif
  __asm{jmp mProcs[100 * 4]}
}
extern "C" __declspec(naked) void __stdcall mixerGetDevCapsW_wrapper(){
#ifdef _DEBUG
  log_info("calling mixerGetDevCapsW");
#endif
  __asm{jmp mProcs[101 * 4]}
}
extern "C" __declspec(naked) void __stdcall mixerGetID_wrapper(){
#ifdef _DEBUG
  log_info("calling mixerGetID");
#endif
  __asm{jmp mProcs[102 * 4]}
}
extern "C" __declspec(naked) void __stdcall mixerGetLineControlsA_wrapper(){
#ifdef _DEBUG
  log_info("calling mixerGetLineControlsA");
#endif
  __asm{jmp mProcs[103 * 4]}
}
extern "C" __declspec(naked) void __stdcall mixerGetLineControlsW_wrapper(){
#ifdef _DEBUG
  log_info("calling mixerGetLineControlsW");
#endif
  __asm{jmp mProcs[104 * 4]}
}
extern "C" __declspec(naked) void __stdcall mixerGetLineInfoA_wrapper(){
#ifdef _DEBUG
  log_info("calling mixerGetLineInfoA");
#endif
  __asm{jmp mProcs[105 * 4]}
}
extern "C" __declspec(naked) void __stdcall mixerGetLineInfoW_wrapper(){
#ifdef _DEBUG
  log_info("calling mixerGetLineInfoW");
#endif
  __asm{jmp mProcs[106 * 4]}
}
extern "C" __declspec(naked) void __stdcall mixerGetNumDevs_wrapper(){
#ifdef _DEBUG
  log_info("calling mixerGetNumDevs");
#endif
  __asm{jmp mProcs[107 * 4]}
}
extern "C" __declspec(naked) void __stdcall mixerMessage_wrapper(){
#ifdef _DEBUG
  log_info("calling mixerMessage");
#endif
  __asm{jmp mProcs[108 * 4]}
}
extern "C" __declspec(naked) void __stdcall mixerOpen_wrapper(){
#ifdef _DEBUG
  log_info("calling mixerOpen");
#endif
  __asm{jmp mProcs[109 * 4]}
}
extern "C" __declspec(naked) void __stdcall mixerSetControlDetails_wrapper(){
#ifdef _DEBUG
  log_info("calling mixerSetControlDetails");
#endif
  __asm{jmp mProcs[110 * 4]}
}
extern "C" __declspec(naked) void __stdcall mmDrvInstall_wrapper(){
#ifdef _DEBUG
  log_info("calling mmDrvInstall");
#endif
  __asm{jmp mProcs[111 * 4]}
}
extern "C" __declspec(naked) void __stdcall mmGetCurrentTask_wrapper(){
#ifdef _DEBUG
  log_info("calling mmGetCurrentTask");
#endif
  __asm{jmp mProcs[112 * 4]}
}
extern "C" __declspec(naked) void __stdcall mmTaskBlock_wrapper(){
#ifdef _DEBUG
  log_info("calling mmTaskBlock");
#endif
  __asm{jmp mProcs[113 * 4]}
}
extern "C" __declspec(naked) void __stdcall mmTaskCreate_wrapper(){
#ifdef _DEBUG
  log_info("calling mmTaskCreate");
#endif
  __asm{jmp mProcs[114 * 4]}
}
extern "C" __declspec(naked) void __stdcall mmTaskSignal_wrapper(){
#ifdef _DEBUG
  log_info("calling mmTaskSignal");
#endif
  __asm{jmp mProcs[115 * 4]}
}
extern "C" __declspec(naked) void __stdcall mmTaskYield_wrapper(){
#ifdef _DEBUG
  log_info("calling mmTaskYield");
#endif
  __asm{jmp mProcs[116 * 4]}
}
extern "C" __declspec(naked) void __stdcall mmioAdvance_wrapper(){
#ifdef _DEBUG
  log_info("calling mmioAdvance");
#endif
  __asm{jmp mProcs[117 * 4]}
}
extern "C" __declspec(naked) void __stdcall mmioAscend_wrapper(){
#ifdef _DEBUG
  log_info("calling mmioAscend");
#endif
  __asm{jmp mProcs[118 * 4]}
}
extern "C" __declspec(naked) void __stdcall mmioClose_wrapper(){
#ifdef _DEBUG
  log_info("calling mmioClose");
#endif
  __asm{jmp mProcs[119 * 4]}
}
extern "C" __declspec(naked) void __stdcall mmioCreateChunk_wrapper(){
#ifdef _DEBUG
  log_info("calling mmioCreateChunk");
#endif
  __asm{jmp mProcs[120 * 4]}
}
extern "C" __declspec(naked) void __stdcall mmioDescend_wrapper(){
#ifdef _DEBUG
  log_info("calling mmioDescend");
#endif
  __asm{jmp mProcs[121 * 4]}
}
extern "C" __declspec(naked) void __stdcall mmioFlush_wrapper(){
#ifdef _DEBUG
  log_info("calling mmioFlush");
#endif
  __asm{jmp mProcs[122 * 4]}
}
extern "C" __declspec(naked) void __stdcall mmioGetInfo_wrapper(){
#ifdef _DEBUG
  log_info("calling mmioGetInfo");
#endif
  __asm{jmp mProcs[123 * 4]}
}
extern "C" __declspec(naked) void __stdcall mmioInstallIOProcA_wrapper(){
#ifdef _DEBUG
  log_info("calling mmioInstallIOProcA");
#endif
  __asm{jmp mProcs[124 * 4]}
}
extern "C" __declspec(naked) void __stdcall mmioInstallIOProcW_wrapper(){
#ifdef _DEBUG
  log_info("calling mmioInstallIOProcW");
#endif
  __asm{jmp mProcs[125 * 4]}
}
extern "C" __declspec(naked) void __stdcall mmioOpenA_wrapper(){
#ifdef _DEBUG
  log_info("calling mmioOpenA");
#endif
  __asm{jmp mProcs[126 * 4]}
}
extern "C" __declspec(naked) void __stdcall mmioOpenW_wrapper(){
#ifdef _DEBUG
  log_info("calling mmioOpenW");
#endif
  __asm{jmp mProcs[127 * 4]}
}
extern "C" __declspec(naked) void __stdcall mmioRead_wrapper(){
#ifdef _DEBUG
  log_info("calling mmioRead");
#endif
  __asm{jmp mProcs[128 * 4]}
}
extern "C" __declspec(naked) void __stdcall mmioRenameA_wrapper(){
#ifdef _DEBUG
  log_info("calling mmioRenameA");
#endif
  __asm{jmp mProcs[129 * 4]}
}
extern "C" __declspec(naked) void __stdcall mmioRenameW_wrapper(){
#ifdef _DEBUG
  log_info("calling mmioRenameW");
#endif
  __asm{jmp mProcs[130 * 4]}
}
extern "C" __declspec(naked) void __stdcall mmioSeek_wrapper(){
#ifdef _DEBUG
  log_info("calling mmioSeek");
#endif
  __asm{jmp mProcs[131 * 4]}
}
extern "C" __declspec(naked) void __stdcall mmioSendMessage_wrapper(){
#ifdef _DEBUG
  log_info("calling mmioSendMessage");
#endif
  __asm{jmp mProcs[132 * 4]}
}
extern "C" __declspec(naked) void __stdcall mmioSetBuffer_wrapper(){
#ifdef _DEBUG
  log_info("calling mmioSetBuffer");
#endif
  __asm{jmp mProcs[133 * 4]}
}
extern "C" __declspec(naked) void __stdcall mmioSetInfo_wrapper(){
#ifdef _DEBUG
  log_info("calling mmioSetInfo");
#endif
  __asm{jmp mProcs[134 * 4]}
}
extern "C" __declspec(naked) void __stdcall mmioStringToFOURCCA_wrapper(){
#ifdef _DEBUG
  log_info("calling mmioStringToFOURCCA");
#endif
  __asm{jmp mProcs[135 * 4]}
}
extern "C" __declspec(naked) void __stdcall mmioStringToFOURCCW_wrapper(){
#ifdef _DEBUG
  log_info("calling mmioStringToFOURCCW");
#endif
  __asm{jmp mProcs[136 * 4]}
}
extern "C" __declspec(naked) void __stdcall mmioWrite_wrapper(){
#ifdef _DEBUG
  log_info("calling mmioWrite");
#endif
  __asm{jmp mProcs[137 * 4]}
}
extern "C" __declspec(naked) void __stdcall mmsystemGetVersion_wrapper(){
#ifdef _DEBUG
  log_info("calling mmsystemGetVersion");
#endif
  __asm{jmp mProcs[138 * 4]}
}
extern "C" __declspec(naked) void __stdcall mod32Message_wrapper(){
#ifdef _DEBUG
  log_info("calling mod32Message");
#endif
  __asm{jmp mProcs[139 * 4]}
}
extern "C" __declspec(naked) void __stdcall mxd32Message_wrapper(){
#ifdef _DEBUG
  log_info("calling mxd32Message");
#endif
  __asm{jmp mProcs[140 * 4]}
}
extern "C" __declspec(naked) void __stdcall sndPlaySoundA_wrapper(){
#ifdef _DEBUG
  log_info("calling sndPlaySoundA");
#endif
  __asm{jmp mProcs[141 * 4]}
}
extern "C" __declspec(naked) void __stdcall sndPlaySoundW_wrapper(){
#ifdef _DEBUG
  log_info("calling sndPlaySoundW");
#endif
  __asm{jmp mProcs[142 * 4]}
}
extern "C" __declspec(naked) void __stdcall tid32Message_wrapper(){
#ifdef _DEBUG
  log_info("calling tid32Message");
#endif
  __asm{jmp mProcs[143 * 4]}
}
extern "C" __declspec(naked) void __stdcall timeBeginPeriod_wrapper(){
#ifdef _DEBUG
  log_info("calling timeBeginPeriod");
#endif
  __asm{jmp mProcs[144 * 4]}
}
extern "C" __declspec(naked) void __stdcall timeEndPeriod_wrapper(){
#ifdef _DEBUG
  log_info("calling timeEndPeriod");
#endif
  __asm{jmp mProcs[145 * 4]}
}
extern "C" __declspec(naked) void __stdcall timeGetDevCaps_wrapper(){
#ifdef _DEBUG
  log_info("calling timeGetDevCaps");
#endif
  __asm{jmp mProcs[146 * 4]}
}
extern "C" __declspec(naked) void __stdcall timeGetSystemTime_wrapper(){
#ifdef _DEBUG
  log_info("calling timeGetSystemTime");
#endif
  __asm{jmp mProcs[147 * 4]}
}
extern "C" __declspec(naked) void __stdcall timeGetTime_wrapper(){
#ifdef _DEBUG
  log_info("calling timeGetTime");
#endif
  __asm{jmp mProcs[148 * 4]}
}
extern "C" __declspec(naked) void __stdcall timeKillEvent_wrapper(){
#ifdef _DEBUG
  log_info("calling timeKillEvent");
#endif
  __asm{jmp mProcs[149 * 4]}
}
extern "C" __declspec(naked) void __stdcall timeSetEvent_wrapper(){
#ifdef _DEBUG
  log_info("calling timeSetEvent");
#endif
  __asm{jmp mProcs[150 * 4]}
}
extern "C" __declspec(naked) void __stdcall waveInAddBuffer_wrapper(){
#ifdef _DEBUG
  log_info("calling waveInAddBuffer");
#endif
  __asm{jmp mProcs[151 * 4]}
}
extern "C" __declspec(naked) void __stdcall waveInClose_wrapper(){
#ifdef _DEBUG
  log_info("calling waveInClose");
#endif
  __asm{jmp mProcs[152 * 4]}
}
extern "C" __declspec(naked) void __stdcall waveInGetDevCapsA_wrapper(){
#ifdef _DEBUG
  log_info("calling waveInGetDevCapsA");
#endif
  __asm{jmp mProcs[153 * 4]}
}
extern "C" __declspec(naked) void __stdcall waveInGetDevCapsW_wrapper(){
#ifdef _DEBUG
  log_info("calling waveInGetDevCapsW");
#endif
  __asm{jmp mProcs[154 * 4]}
}
extern "C" __declspec(naked) void __stdcall waveInGetErrorTextA_wrapper(){
#ifdef _DEBUG
  log_info("calling waveInGetErrorTextA");
#endif
  __asm{jmp mProcs[155 * 4]}
}
extern "C" __declspec(naked) void __stdcall waveInGetErrorTextW_wrapper(){
#ifdef _DEBUG
  log_info("calling waveInGetErrorTextW");
#endif
  __asm{jmp mProcs[156 * 4]}
}
extern "C" __declspec(naked) void __stdcall waveInGetID_wrapper(){
#ifdef _DEBUG
  log_info("calling waveInGetID");
#endif
  __asm{jmp mProcs[157 * 4]}
}
extern "C" __declspec(naked) void __stdcall waveInGetNumDevs_wrapper(){
#ifdef _DEBUG
  log_info("calling waveInGetNumDevs");
#endif
  __asm{jmp mProcs[158 * 4]}
}
extern "C" __declspec(naked) void __stdcall waveInGetPosition_wrapper(){
#ifdef _DEBUG
  log_info("calling waveInGetPosition");
#endif
  __asm{jmp mProcs[159 * 4]}
}
extern "C" __declspec(naked) void __stdcall waveInMessage_wrapper(){
#ifdef _DEBUG
  log_info("calling waveInMessage");
#endif
  __asm{jmp mProcs[160 * 4]}
}
extern "C" __declspec(naked) void __stdcall waveInOpen_wrapper(){
#ifdef _DEBUG
  log_info("calling waveInOpen");
#endif
  __asm{jmp mProcs[161 * 4]}
}
extern "C" __declspec(naked) void __stdcall waveInPrepareHeader_wrapper(){
#ifdef _DEBUG
  log_info("calling waveInPrepareHeader");
#endif
  __asm{jmp mProcs[162 * 4]}
}
extern "C" __declspec(naked) void __stdcall waveInReset_wrapper(){
#ifdef _DEBUG
  log_info("calling waveInReset");
#endif
  __asm{jmp mProcs[163 * 4]}
}
extern "C" __declspec(naked) void __stdcall waveInStart_wrapper(){
#ifdef _DEBUG
  log_info("calling waveInStart");
#endif
  __asm{jmp mProcs[164 * 4]}
}
extern "C" __declspec(naked) void __stdcall waveInStop_wrapper(){
#ifdef _DEBUG
  log_info("calling waveInStop");
#endif
  __asm{jmp mProcs[165 * 4]}
}
extern "C" __declspec(naked) void __stdcall waveInUnprepareHeader_wrapper(){
#ifdef _DEBUG
  log_info("calling waveInUnprepareHeader");
#endif
  __asm{jmp mProcs[166 * 4]}
}
extern "C" __declspec(naked) void __stdcall waveOutBreakLoop_wrapper(){
#ifdef _DEBUG
  log_info("calling waveOutBreakLoop");
#endif
  __asm{jmp mProcs[167 * 4]}
}
extern "C" __declspec(naked) void __stdcall waveOutClose_wrapper(){
#ifdef _DEBUG
  log_info("calling waveOutClose");
#endif
  __asm{jmp mProcs[168 * 4]}
}
extern "C" __declspec(naked) void __stdcall waveOutGetDevCapsA_wrapper(){
#ifdef _DEBUG
  log_info("calling waveOutGetDevCapsA");
#endif
  __asm{jmp mProcs[169 * 4]}
}
extern "C" __declspec(naked) void __stdcall waveOutGetDevCapsW_wrapper(){
#ifdef _DEBUG
  log_info("calling waveOutGetDevCapsW");
#endif
  __asm{jmp mProcs[170 * 4]}
}
extern "C" __declspec(naked) void __stdcall waveOutGetErrorTextA_wrapper(){
#ifdef _DEBUG
  log_info("calling waveOutGetErrorTextA");
#endif
  __asm{jmp mProcs[171 * 4]}
}
extern "C" __declspec(naked) void __stdcall waveOutGetErrorTextW_wrapper(){
#ifdef _DEBUG
  log_info("calling waveOutGetErrorTextW");
#endif
  __asm{jmp mProcs[172 * 4]}
}
extern "C" __declspec(naked) void __stdcall waveOutGetID_wrapper(){
#ifdef _DEBUG
  log_info("calling waveOutGetID");
#endif
  __asm{jmp mProcs[173 * 4]}
}
extern "C" __declspec(naked) void __stdcall waveOutGetNumDevs_wrapper(){
#ifdef _DEBUG
  log_info("calling waveOutGetNumDevs");
#endif
  __asm{jmp mProcs[174 * 4]}
}
extern "C" __declspec(naked) void __stdcall waveOutGetPitch_wrapper(){
#ifdef _DEBUG
  log_info("calling waveOutGetPitch");
#endif
  __asm{jmp mProcs[175 * 4]}
}
extern "C" __declspec(naked) void __stdcall waveOutGetPlaybackRate_wrapper(){
#ifdef _DEBUG
  log_info("calling waveOutGetPlaybackRate");
#endif
  __asm{jmp mProcs[176 * 4]}
}
extern "C" __declspec(naked) void __stdcall waveOutGetPosition_wrapper(){
#ifdef _DEBUG
  log_info("calling waveOutGetPosition");
#endif
  __asm{jmp mProcs[177 * 4]}
}
extern "C" __declspec(naked) void __stdcall waveOutGetVolume_wrapper(){
#ifdef _DEBUG
  log_info("calling waveOutGetVolume");
#endif
  __asm{jmp mProcs[178 * 4]}
}
extern "C" __declspec(naked) void __stdcall waveOutMessage_wrapper(){
#ifdef _DEBUG
  log_info("calling waveOutMessage");
#endif
  __asm{jmp mProcs[179 * 4]}
}
extern "C" __declspec(naked) void __stdcall waveOutOpen_wrapper(){
#ifdef _DEBUG
  log_info("calling waveOutOpen");
#endif
  __asm{jmp mProcs[180 * 4]}
}
extern "C" __declspec(naked) void __stdcall waveOutPause_wrapper(){
#ifdef _DEBUG
  log_info("calling waveOutPause");
#endif
  __asm{jmp mProcs[181 * 4]}
}
extern "C" __declspec(naked) void __stdcall waveOutPrepareHeader_wrapper(){
#ifdef _DEBUG
  log_info("calling waveOutPrepareHeader");
#endif
  __asm{jmp mProcs[182 * 4]}
}
extern "C" __declspec(naked) void __stdcall waveOutReset_wrapper(){
#ifdef _DEBUG
  log_info("calling waveOutReset");
#endif
  __asm{jmp mProcs[183 * 4]}
}
extern "C" __declspec(naked) void __stdcall waveOutRestart_wrapper(){
#ifdef _DEBUG
  log_info("calling waveOutRestart");
#endif
  __asm{jmp mProcs[184 * 4]}
}
extern "C" __declspec(naked) void __stdcall waveOutSetPitch_wrapper(){
#ifdef _DEBUG
  log_info("calling waveOutSetPitch");
#endif
  __asm{jmp mProcs[185 * 4]}
}
extern "C" __declspec(naked) void __stdcall waveOutSetPlaybackRate_wrapper(){
#ifdef _DEBUG
  log_info("calling waveOutSetPlaybackRate");
#endif
  __asm{jmp mProcs[186 * 4]}
}
extern "C" __declspec(naked) void __stdcall waveOutSetVolume_wrapper(){
#ifdef _DEBUG
  log_info("calling waveOutSetVolume");
#endif
  __asm{jmp mProcs[187 * 4]}
}
extern "C" __declspec(naked) void __stdcall waveOutUnprepareHeader_wrapper(){
#ifdef _DEBUG
  log_info("calling waveOutUnprepareHeader");
#endif
  __asm{jmp mProcs[188 * 4]}
}
extern "C" __declspec(naked) void __stdcall waveOutWrite_wrapper(){
#ifdef _DEBUG
  log_info("calling waveOutWrite");
#endif
  __asm{jmp mProcs[189 * 4]}
}
extern "C" __declspec(naked) void __stdcall wid32Message_wrapper(){
#ifdef _DEBUG
  log_info("calling wid32Message");
#endif
  __asm{jmp mProcs[190 * 4]}
}
extern "C" __declspec(naked) void __stdcall wod32Message_wrapper(){
#ifdef _DEBUG
  log_info("calling wod32Message");
#endif
  __asm{jmp mProcs[191 * 4]}
}
extern "C" __declspec(naked) void __stdcall ExportByOrdinal2(){
#ifdef _DEBUG
  log_info("calling _NONAME_");
#endif
  __asm{jmp mProcs[192 * 4]}
}
