#pragma once

#include <QString>
#include <QIcon>
#include <QUuid>
#include <QDateTime>
#include <QFile>
#include <QFileInfo>
#include <QDebug>

namespace model {

/*
 * 工具函数
 */
static inline QString getFileName(const QString& path) {
    QFileInfo fileInfo(path);
    return fileInfo.fileName();
}

// 宏日志
#define TAG QString("[%1:%2]").arg(model::getFileName(__FILE__), QString::number(__LINE__))
#define LOG() qDebug().noquote() << TAG

// 要求函数的定义如果写在 .h 中, 必须加 static 或者 inline 避免链接阶段出现 "函数重定义" 的问题.
static inline QString formatTime(int64_t timestamp) {
    // 先把时间戳, 转换成 QDateTime 对象
    QDateTime dateTime = QDateTime::fromSecsSinceEpoch(timestamp);
    return dateTime.toString("MM-dd HH:mm:ss");
}

// 通过这个函数得到 秒级 的时间
static inline int64_t getTime() {
    return QDateTime::currentSecsSinceEpoch();
}

// 根据 QByteArray, 转成 QIcon
static inline QIcon makeIcon(const QByteArray& byteArray) {
    // 首先通过QPixmap进行构造
    QPixmap pixmap;
    pixmap.loadFromData(byteArray);
    // 再通过QIcon构造
    QIcon icon(pixmap);
    return icon;
}

// 从指定文件中, 读取所有的二进制内容. 得到一个 QByteArray
static inline QByteArray loadFileToByteArray(const QString& path) {
    QFile file(path);
    bool ok = file.open(QFile::ReadOnly);
    if(!ok) {
        LOG() << "文件打开失败";
        return QByteArray();
    }
    QByteArray content = file.readAll();
    file.close();
    return content;
}

// 把 QByteArray 中的内容, 写入到某个指定文件里
static inline void writeByteArrayToFile(const QString& path, const QByteArray& content) {
    QFile file(path);
    bool ok = file.open(QFile::WriteOnly);
    if(!ok) {
        LOG() << "文件打开失败";
        return ;
    }
    file.write(content);
    file.flush(); // 刷新缓冲区
    file.close();
    return ;
}

/*
 * 用户信息
 */
class UserInfo {
    QString UserId = "";        // 用户编号
    QString nickname = "";      // 用户昵称
    QString description = "";   // 用户签名
    QString phone = "";         // 用户电话
    QIcon avatar;               // 用户头像
};

/*
 * 消息信息
 */
enum MessageType {
    TEXT_TYPE,          // 文本类型
    IMAGE_TYPE,         // 图片信息
    FILE_TYPE,          // 文件消息
    SPEECH_TYPE         // 语音消息
};

class Message {
public:
    QString messageId = "";                         // 消息的编号
    QString chatSessionId = "";                     // 消息所属会话编号
    QString time = "";                              // 消息时间
    MessageType messageType = TEXT_TYPE;            // 消息类型
    UserInfo sender;                                // 发送者的消息
    QByteArray content;                             // 消息的正文内容
    QString fileId = "";                            // 文件的身份标识
    QString fileName = "";                          // 文件名称

    // 此处 extraInfo 目前只是在消息类型为文件消息时, 作为 "文件名" 补充.
    static Message makeMessage(MessageType messageType, const QString& chatSessionId, const UserInfo& sender,
                               const QByteArray& content, const QString& extraInfo) {
        if(messageType == TEXT_TYPE) {
            return makeTextMessage(chatSessionId, sender, content);
        } else if(messageType == IMAGE_TYPE) {
            return makeImageMessage(chatSessionId, sender, content);
        } else if(messageType == FILE_TYPE) {
            return makeFileMessage(chatSessionId, sender, content, extraInfo);
        } else if(messageType == SPEECH_TYPE) {
            return makeSpeechMessage(chatSessionId, sender, content);
        } else {
            // 未知类型
            return Message();
        }
    }

    static QString makeId() {
        return "M" + QUuid::createUuid().toString().sliced(25, 12); // 发返回的是 类型 + uuid最后一段字符串
    }

private:
    static Message makeTextMessage(const QString &chatSessionId, const UserInfo &sender, const QByteArray &content) {
        Message message;
        message.messageId = makeId();
        message.chatSessionId = chatSessionId;
        message.sender = sender;
        message.time = formatTime(getTime());
        message.content = content;
        message.messageType = TEXT_TYPE;
        // 对于文本来说，文件的属性不使用
        message.fileId = "";
        message.fileName = "";
        return message;
    }
    static Message makeImageMessage(const QString &chatSessionId, const UserInfo &sender, const QByteArray &content) {
        Message message;
        message.messageId = makeId();
        message.chatSessionId = chatSessionId;
        message.sender = sender;
        message.time = formatTime(getTime());
        message.content = content;
        message.messageType = IMAGE_TYPE;
        message.fileId = "";
        message.fileName = "";
        return message;
    }
    static Message makeFileMessage(const QString &chatSessionId, const UserInfo &sender, const QByteArray &content, const QString &filename) {
        Message message;
        message.messageId = makeId();
        message.chatSessionId = chatSessionId;
        message.sender = sender;
        message.time = formatTime(getTime());
        message.content = content;
        message.messageType = FILE_TYPE;
        message.fileId = "";
        message.fileName = filename;
        return message;
    }
    static Message makeSpeechMessage(const QString &chatSessionId, const UserInfo &sender, const QByteArray &content) {
        Message message;
        message.messageId = makeId();
        message.chatSessionId = chatSessionId;
        message.sender = sender;
        message.time = formatTime(getTime());
        message.content = content;
        message.messageType = SPEECH_TYPE;
        message.fileId = "";
        message.fileName = "";
        return message;
    }
};

/*
 * 会话信息
*/
class ChatSessionInfo {
    QString chatSessionId = "";      // 会话编号
    QString chatSessionName = "";    // 会话名字
    Message lastMessage;        // 最新的消息
    QIcon avatar;               // 会话头像
    QString userId = "";             // 对方用户的id，群聊表示""
};

} // end model
