#include <jni.h>

#include <iostream>
#include <fmod.hpp>
#include <unistd.h>
using namespace std;
extern  "C"
////点击按钮播放音乐
JNIEXPORT void JNICALL
Java_com_example_fmy_selfplaymusic_MainActivity_playsMusic(JNIEnv *env, jobject instance,
                                                           jstring music_path_) {


    //得到音乐文件地址
    const char *music_path = env->GetStringUTFChars( music_path_, 0);

    //FMOD系统对象
    FMOD::System       *system         = 0;
    //音效
    FMOD::Sound        *sound          = 0;
    //声轨
    FMOD::Channel       *channel       = 0;
    //创建对象
    FMOD::System_Create(&system);

    //初始化 系统对象最大声轨为32
    system->init(32,FMOD_INIT_NORMAL,0);

    //加载声音 如果过大建议你用FMOD_CREATESTREAM 标志
    system->createSound(music_path,FMOD_DEFAULT,0,&sound);

    //播放音乐
    system->playSound(sound,0, false,&channel);

    //开启更新通道 官方demo写了 但是我我发现不写也没事
    system->update();

    //保存声音时间
    unsigned int duration  =  0;

    //得到声音
    sound->getLength(&duration,FMOD_TIMEUNIT_MS);

    //线程休眠 以微妙 所以要转
    usleep(duration*1000);
    //释放资源
    sound->release();
    system->close();
    system->release();

    env->ReleaseStringUTFChars(music_path_, music_path);

}

