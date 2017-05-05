#include <jni.h>

#include <iostream>
#include <fmod.hpp>
#include <unistd.h>
//变音
extern  "C"
JNIEXPORT void JNICALL
Java_com_example_fmy_selfplaymusic_MainActivity_effects(JNIEnv *env, jobject instance, jint flag) {

    //音频地址
  char * rawPath = "file:///android_asset/te.mp3";

    //FMOD系统对象
    FMOD::System       *system         = 0;
    //音效
    FMOD::Sound        *sound          = 0;
    //声轨
    FMOD::Channel       *channel       = 0;
    //声轨集合
    FMOD::ChannelGroup  * mastergroup  = 0;
    //一个数字信号处理单元
    FMOD::DSP            *dsp        = 0;

    //创建对象
    FMOD::System_Create(&system);

    //初始化 系统对象最大声轨为32
    system->init(32,FMOD_INIT_NORMAL,0);

    //加载声音 如果过大建议你用FMOD_CREATESTREAM 标志
    system->createSound(rawPath,FMOD_DEFAULT,0,&sound);

    //得到声音轨道集合
    system->getMasterChannelGroup(&mastergroup);

    //播放音乐
    system->playSound(sound,0,false,&channel);

    switch (flag){
        //萝莉
        case 1:
            //创建音频处理DSP 类型 为音频提高
            system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT,&dsp);
           //设置dsp大小
            dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH,2.0);

            //添加一个处理单元到通道
            channel->addDSP(0,dsp);

            break;
        //惊悚
        case 2:
            //创建音频处理DSP 类型 为颤抖
            system->createDSPByType(FMOD_DSP_TYPE_TREMOLO,&dsp);
            //设置低频震旦器频率
            dsp->setParameterFloat(FMOD_DSP_TREMOLO_FREQUENCY,20);
            //设置声音歪斜
            dsp->setParameterFloat(FMOD_DSP_TREMOLO_SKEW,0.5);

            //添加一个处理单元到通道
            channel->addDSP(0,dsp);
            break;
            //大叔
        case 3:

            //创建音频处理DSP 类型 为音频提高
            system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT,&dsp);
            //设置dsp大小
            dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH,0.5);

            //添加一个处理单元到通道
            channel->addDSP(0,dsp);
            break;
            //搞怪
        case 4:
        {

            float mfrequency = 0;
            //得到频率
            channel->getFrequency(&mfrequency);
            channel->setFrequency(mfrequency*2);
            break;
        }

            //空灵
        case 5 :{
            //创建音频处理DSP 类型 为音频提高
            system->createDSPByType(FMOD_DSP_TYPE_ECHO,&dsp);
            //设置dsp大小  延迟声
            dsp->setParameterFloat(FMOD_DSP_ECHO_DELAY,300);
            //回音音量
            dsp->setParameterFloat(FMOD_DSP_ECHO_FEEDBACK,20);

            //添加一个处理单元到通道
            channel->addDSP(0,dsp);
            break;
        }



    }

}

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

