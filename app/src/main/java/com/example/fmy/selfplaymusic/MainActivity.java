package com.example.fmy.selfplaymusic;

import android.content.Context;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;

public class MainActivity extends AppCompatActivity {


    static {
        System.loadLibrary("native-lib");
    }

    //当前对象
    Context mContext;

    //要播放的音乐文件地址
    public static final String  music_path = "file:///android_asset/jaguar.wav";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.activity_main);

        //当前对象
        this.mContext = this;
        //初始化FMOD
        org.fmod.FMOD.init(this);


    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        //同步FMOD的生命周期
        org.fmod.FMOD.close();
    }



    //调用fmod去播放音乐
    public native void playsMusic(String music_path);

    //点击按钮触发jni方法播放音乐
    public void onClick(View view) {


        //播放音乐
        playsMusic(music_path);

    }
}
