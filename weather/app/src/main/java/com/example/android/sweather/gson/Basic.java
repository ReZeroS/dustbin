package com.example.android.sweather.gson;

import com.google.gson.annotations.SerializedName;

/**
 * Created by ReZero on 2017/2/24.
 */

public class Basic {
    @SerializedName("city")
    public String cityName;

    @SerializedName("id")
    public String weatherId;

    public Update update;

    public class Update{
        @SerializedName("loc")
        public String updateTime;
    }
}
