#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QIcon>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

class MainWidget : public QWidget
{
    Q_OBJECT
private:
    // 单例模式
    static MainWidget* instance;
    MainWidget(QWidget *parent = nullptr);
public:
    static MainWidget* getInstance();
    ~MainWidget();
private:
    QWidget* windowLeft;
    QWidget* windowMid;
    QWidget* windowRight;

    QPushButton* userAvatar;        // 用户头像
    QPushButton* sessionTabBtn;     // 会话标签页按钮
    QPushButton* friendTabBtn;      // 好友标签页按钮
    QPushButton* applyTabBtn;       // 好友申请标签页按钮

    enum ActiveTab {
        SESSION_LIST,
        FRIEND_LIST,
        APPLY_LIST
    };

    ActiveTab activeTab = SESSION_LIST;

    /*
     * 初始化操作
     */
    void initMainWindow();
    void initLeftWindow();
    void initMidWindow();
    void initRightWindow();
    void initSignalSlot();

    void switchTabToSession();
    void switchTabToFriend();
    void switchTabToApply();

    void loadSessionList();
    void loadFriendList();
    void loadApplyList();

};
#endif // MAINWIDGET_H
