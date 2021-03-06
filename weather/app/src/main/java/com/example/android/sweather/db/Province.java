package com.example.android.sweather.db;

import org.litepal.crud.DataSupport;

/**
 * Created by ReZero on 2017/2/12.
 */

public class Province extends DataSupport {
    private int id;
    private String provinceName;
    //the symbol of province:
    private int provinceCode;

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getProvinceName() {
        return provinceName;
    }

    public void setProvinceName(String provinceName) {
        this.provinceName = provinceName;
    }

    public int getProvinceCode() {
        return provinceCode;
    }

    public void setProvinceCode(int provinceCode) {
        this.provinceCode = provinceCode;
    }
}
