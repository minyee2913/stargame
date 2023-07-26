#include "sound.h"
#define NUM_SOUNDS 2

struct sample {
    Uint8* data;
    Uint32 dpos;
    Uint32 dlen;
} sounds[NUM_SOUNDS];

void mixaudio(void* unused, Uint8* stream, unsigned int len)
{
    int i;
    Uint32 amount;

    for (i = 0; i < NUM_SOUNDS; ++i) {
        amount = (sounds[i].dlen - sounds[i].dpos);
        if (amount > len) {
            amount = len;
        }
        SDL_MixAudio(stream, &sounds[i].data[sounds[i].dpos], amount, SDL_MIX_MAXVOLUME);
        sounds[i].dpos += amount;
    }
}

void PlaySound(char* file)
{
    int index;
    SDL_AudioSpec wave;
    Uint8* data;
    Uint32 dlen;
    SDL_AudioCVT cvt;

    /* ����ִ�(�Ǵ� ����) ���� ������ ã�´�. */
    for (index = 0; index < NUM_SOUNDS; ++index) {
        if (sounds[index].dpos == sounds[index].dlen) {
            break;
        }
    }
    if (index == NUM_SOUNDS)
        return;

    /* ���� ������ �ε��Ͽ� 22kHz�� 16-bit ���׷����� ��ȯ�Ѵ�. */
    if (SDL_LoadWAV(file, &wave, &data, &dlen) == NULL) {
        fprintf(stderr, "Couldn't load %s: %s\n", file, SDL_GetError());
        return;
    }
    SDL_BuildAudioCVT(&cvt, wave.format, wave.channels, wave.freq,
        AUDIO_S16, 2, 22050);
    cvt.buf = malloc(dlen * cvt.len_mult);
    memcpy(cvt.buf, data, dlen);
    cvt.len = dlen;
    SDL_ConvertAudio(&cvt);
    SDL_FreeWAV(data);

    /* ���� ����Ÿ�� ���Կ� �ִ´�(��ٷ� ����ȴ�). */
    if (sounds[index].data) {
        free(sounds[index].data);
    }
    SDL_LockAudio();
    sounds[index].data = cvt.buf;
    sounds[index].dlen = cvt.len_cvt;
    sounds[index].dpos = 0;
    SDL_UnlockAudio();
}