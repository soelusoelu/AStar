#include "Sound.h"
#include "Renderer.h"
#include "../System/Game.h"

Sound::Sound() = default;

Sound::~Sound() = default;

HRESULT Sound::init() {
//    if (FAILED(CoInitializeEx(NULL, COINIT_MULTITHREADED))) {
//        return E_FAIL;
//    }
//#ifdef _DEBUG
//    if (FAILED(XAudio2Create(&mXAudio2, XAUDIO2_DEBUG_ENGINE))) {
//        CoUninitialize();
//        return E_FAIL;
//    }
//#else
//    if (FAILED(XAudio2Create(&mXAudio2, 0))) {
//        CoUninitialize();
//        return E_FAIL;
//    }
//#endif // DEBUG
//
//    if (FAILED(mXAudio2->CreateMasteringVoice(&mMasteringVoice))) {
//        CoUninitialize();
//        return E_FAIL;
//    }
    return S_OK;
}

void Sound::end() {
    //SAFE_RELEASE(mXAudio2);
    //CoUninitialize();
}

void Sound::load(const std::string& fileName, std::shared_ptr<SoundInfo> soundInfo) {
    //HMMIO hMmio = NULL; //WindowsマルチメディアAPIのハンドル(WindowsマルチメディアAPIはWAVファイル関係の操作用のAPI)
    //DWORD wavSize = 0; //WAVファイル内 WAVデータのサイズ(WAVファイルはWAVデータで占められているので、ほぼファイルサイズと同一)
    //WAVEFORMATEX* pwfex; //WAVのフォーマット 例)16ビット、44100Hz、ステレオなど
    //MMCKINFO ckInfo; //チャンク情報
    //MMCKINFO riffckInfo; // 最上部チャンク(RIFFチャンク)保存用
    //PCMWAVEFORMAT pcmWaveForm;
    ////WAVファイル内のヘッダー情報(音データ以外)の確認と読み込み
    //setSoundDirectory();
    //char* fn = const_cast<char*>(fileName.c_str()); //他にやり方思い浮かばない
    //hMmio = mmioOpenA(fn, NULL, MMIO_ALLOCBUF | MMIO_READ);
    ////ファイルポインタをRIFFチャンクの先頭にセットする
    //mmioDescend(hMmio, &riffckInfo, NULL, 0);
    ////ファイルポインタを'f' 'm' 't' ' ' チャンクにセットする
    //ckInfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
    //mmioDescend(hMmio, &ckInfo, &riffckInfo, MMIO_FINDCHUNK);
    ////フォーマットを読み込む
    //mmioRead(hMmio, reinterpret_cast<HPSTR>(&pcmWaveForm), sizeof(pcmWaveForm));
    //pwfex = reinterpret_cast<WAVEFORMATEX*>(new CHAR[sizeof(WAVEFORMATEX)]);
    //memcpy(pwfex, &pcmWaveForm, sizeof(pcmWaveForm));
    //pwfex->cbSize = 0;
    //mmioAscend(hMmio, &ckInfo, 0);
    ////WAVファイル内の音データの読み込み
    //ckInfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
    //mmioDescend(hMmio, &ckInfo, &riffckInfo, MMIO_FINDCHUNK); //データチャンクにセット
    //wavSize = ckInfo.cksize;
    //soundInfo->mWavBuffer = new BYTE[wavSize];
    //DWORD offset = ckInfo.dwDataOffset;
    //mmioRead(hMmio, reinterpret_cast<HPSTR>(soundInfo->mWavBuffer), wavSize);
    ////ソースボイスにデータを詰め込む
    //if (FAILED(mXAudio2->CreateSourceVoice(&soundInfo->mSourceVoice, pwfex))) {
    //    MessageBox(0, L"ソースボイス作成失敗", 0, MB_OK);
    //}
    //soundInfo->mWavSize = wavSize;
}

void SoundInfo::play(bool isLoop) {
    //XAUDIO2_BUFFER buffer = { 0 };
    //buffer.pAudioData = mWavBuffer;
    //buffer.Flags = XAUDIO2_END_OF_STREAM;
    //buffer.AudioBytes = mWavSize;
    //if (isLoop) {
    //    buffer.LoopCount = XAUDIO2_LOOP_INFINITE;
    //}
    //if (FAILED(mSourceVoice->SubmitSourceBuffer(&buffer))) {
    //    MessageBox(0, L"ソースボイスにサブミット失敗", 0, MB_OK);
    //    return;
    //}
    //mSourceVoice->Start(0, XAUDIO2_COMMIT_NOW);
}

void Sound::play(const std::string& fileName, bool isLoop) {
    //auto soundInfo = Renderer::getSound(fileName);
    //XAUDIO2_BUFFER buffer = { 0 };
    //buffer.pAudioData = soundInfo->mWavBuffer;
    //buffer.Flags = XAUDIO2_END_OF_STREAM;
    //buffer.AudioBytes = soundInfo->mWavSize;
    //if (isLoop) {
    //    buffer.LoopCount = XAUDIO2_LOOP_INFINITE;
    //}
    //if (FAILED(soundInfo->mSourceVoice->SubmitSourceBuffer(&buffer))) {
    //    MessageBox(0, L"ソースボイスにサブミット失敗", 0, MB_OK);
    //    return;
    //}
    //soundInfo->mSourceVoice->Start(0, XAUDIO2_COMMIT_NOW);
}

void SoundInfo::stop() {
    //mSourceVoice->Stop(0, XAUDIO2_COMMIT_NOW);
}

IXAudio2* Sound::mXAudio2 = nullptr;
IXAudio2MasteringVoice* Sound::mMasteringVoice = nullptr;
