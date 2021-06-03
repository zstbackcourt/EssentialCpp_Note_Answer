//
// Created by swj93 on 2021-05-01.
//

#include "UserProfile.h"


set<long> UserProfile::_login_session_set = {};

inline UserProfile::UserProfile():_user_name("guest"),_times_logged(0),_guesses(0),_correct_guesses(0),_uLevel("Junior"){
    long tmp_session = rand();
    while (_login_session_set.find(tmp_session)!=_login_session_set.end()){
        tmp_session = rand();
    }
    _login_session_set.insert(tmp_session);
    _login_session = tmp_session;
}

inline UserProfile::UserProfile(const string& user_name, const string& level):
_user_name(user_name),_times_logged(0),_guesses(0),_correct_guesses(0),_uLevel(level){
    long tmp_session = rand();
    while (_login_session_set.find(tmp_session)!=_login_session_set.end()){
        tmp_session = rand();
    }
    _login_session_set.insert(tmp_session);
    _login_session = tmp_session;
}

inline double UserProfile::average() const {
    return _guesses ? double(_correct_guesses)/double(_guesses) *100 : 0.0;
}

inline bool UserProfile::operator==(const UserProfile &ref) {
    if(_login_session == ref._login_session && _user_name == ref._user_name){
        return true;
    }
    return false;
}

inline bool UserProfile::operator!=(const UserProfile &ref) {
    if(_login_session == ref._login_session && _user_name == ref._user_name){
        return false;
    }
    return true;
}

ostream& operator<<(ostream& os, const UserProfile &user){
    cout << " User_name: " << user.user_name()
         << " login_session: " << user.login_session()
         << " times_logged: " << user.times_logged()
         << " guesses: " << user.guesses()
         << " correct_guesses: " << user.correct_guesses()
         << " uLevel: " << user.uLevel() << endl;
    return os;
}

void UserProfile::print_session_set(){
    cout << "Exist session: " << endl;
    for(long sess:_login_session_set){
        cout << sess << " ";
    }
    cout << endl;
}

