#pragma once

#include "../System/DirectXIncLib.h"
#include <XAudio2.h>
#include <memory>
#include <string>

struct SoundInfo {
    IXAudio2SourceVoice* mSourceVoice;
    BYTE* mWavBuffer; //波形データ(フォーマット等を含まない、純粋に波形データのみ)
    DWORD mWavSize; //波形データのサイズ

    SoundInfo() :
        mSourceVoice(nullptr),
        mWavBuffer(nullptr),
        mWavSize(0) {
    }
    ~SoundInfo() {
        //mSourceVoice->DestroyVoice();
        //SAFE_DELETE(mWavBuffer);
    }
    void play(bool isLoop = false);
    void stop();
};

class Sound {
public:
    Sound();
    ~Sound();
    static HRESULT init();
    static void end();
    static void load(const std::string& fileName, std::shared_ptr<SoundInfo> soundInfo);
    static void play(const std::string& fileName, bool isLoop = false);

private:
    static IXAudio2* mXAudio2;
    static IXAudio2MasteringVoice* mMasteringVoice;
};
