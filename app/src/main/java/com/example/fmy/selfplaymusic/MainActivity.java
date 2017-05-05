package com.example.fmy.selfplaymusic;

import android.content.Context;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {


    static {
        System.loadLibrary("native-lib");
    }

    //当前对象
    Context mContext;

    //要播放的音乐文件地址
    public static final String  music_path = "file:///android_asset/te.mp3";

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

    public native  void  effects(int flag);

    public void onClick2(View view) {

        TextView t = (TextView) view;

        String flag =t.getText().toString();

        //变音
        switch (flag) {
            case "萝莉":
                effects(1);
                break;
            case "惊悚":
                effects(2);
            case "大叔":
                effects(3);
                break;
            case "搞怪":
                effects(4);
            case "空灵":
                effects(5);
                break;
        }

    }
}
