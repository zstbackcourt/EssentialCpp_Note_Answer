//
// Created by swj93 on 2021-05-01.
//

#ifndef ESSENTIALCPP_GLOBALWRAPPER_H
#define ESSENTIALCPP_GLOBALWRAPPER_H

#include <string>
class globalWrapper{
public:
    static int tests_passed() { return _tests_passed;}
    static int tests_run() { return  _tests_run;}
    static int version_number() { return _version_number;}
    static string version_stamp() { return _version_stamp;}
    static string program_name() { return _program_name;}

    static void tests_passed(int val) { _tests_passed = val;}
    static void tests_run(int val) { _tests_run = val;}
    static void version_number(int val) { _version_number = val;}
    static void version_stamp(string str) { _version_stamp = str;}
    static void program_name(string str) { _program_name = str;}
private:
    static string _program_name;
    static string _version_stamp;
    static int _version_number;
    static int _tests_run;
    static int _tests_passed;
};

#endif //ESSENTIALCPP_GLOBALWRAPPER_H
