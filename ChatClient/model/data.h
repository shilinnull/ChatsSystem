#pragma once

#include <Qstring>
#include <QIcon>

namespace model {

/*
 * 用户信息
 */
class UserInfo {
    QString UserId;     // 用户id
    QString nickname;   // 用户名字
    QString description;// 个性签名
    QString phone;      // 用户电话
    QIcon avatar;       // 用户头像
};


} // end model
