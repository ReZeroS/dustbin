package com.example.android.sweather.gson;

/**
 * Created by ReZero on 2017/2/25.
 */

public class AQI {
    public AQICity city;

    public class AQICity {
        public String aqi;
        public String pm25;
    }
}
