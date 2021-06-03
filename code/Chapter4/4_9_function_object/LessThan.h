//
// Created by swj93 on 2021-05-01.
//

#ifndef ESSENTIALCPP_LESSTHAN_H
#define ESSENTIALCPP_LESSTHAN_H

class LessThan{
public:
    LessThan(int val):_val(val){}
    int comp_val() const { return _val;} // 基值的读取
    void comp_val(int nval){_val = nval;} // 基值的写入

    bool operator()(int value) const ;
private:
    int _val;
};

#endif //ESSENTIALCPP_LESSTHAN_H
