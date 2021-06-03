//
// Created by swj93 on 2021-05-01.
//

#ifndef ESSENTIALCPP_USERPROFILE_H
#define ESSENTIALCPP_USERPROFILE_H

#include <string>
#include <map>
#include <set>
#include <iostream>
using namespace std;

class UserProfile{
public:

    UserProfile();
    UserProfile(const string& user_name, const string& level);
    // 用于写入数据
    void reset_login_session(const long &id) {_login_session = id;}
    void reset_user_name(const string &name) {_user_name = name;}
    void reset_times_logged(int val) {_times_logged = val;}
    void reset_guesses(int val) {_guesses = val;}
    void reset_correct_guesses(int val) {_correct_guesses = val;}
    void reset_uLevel(const string &level) {_uLevel = level;}

    // 自动增加
    void add_times_logged() {_times_logged += 1;}
    void add_guesses() {_guesses += 1;}
    void add_correct_guesses() {_correct_guesses += 1;}

    // 用于直接访问成员对象
    long login_session()const { return _login_session;}
    string user_name()const { return _user_name;}
    int times_logged()const { return _times_logged;}
    int guesses()const { return _guesses;}
    int correct_guesses()const { return _correct_guesses;}
    string uLevel()const { return _uLevel;}

    static void print_session_set(); // 打印用户的会话id
    double average() const;

    bool operator==(const UserProfile &ref);
    bool operator!=(const UserProfile &ref);

private:
    long _login_session; // session id
    static set<long> _login_session_set; // 静态成员变量用于存放所有用户的session id保证session id是独一无二的
    string _user_name; // 用户名
    int _times_logged; // 用户登录次数
    int _guesses; // 用户猜测次数
    int _correct_guesses; // 用户猜对次数
    string _uLevel; // Junior Intermediate Senior Expert
};


#endif //ESSENTIALCPP_USERPROFILE_H
