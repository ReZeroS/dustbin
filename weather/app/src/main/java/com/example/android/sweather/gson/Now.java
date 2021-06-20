package com.example.android.sweather.gson;

import com.google.gson.annotations.SerializedName;

/**
 * Created by ReZero on 2017/2/25.
 */

public class Now {

    @SerializedName("tmp")
    public String temperature;

    @SerializedName("cond")
    public More more;

    public class More{
        @SerializedName("txt")
        public String info;
    }
}
