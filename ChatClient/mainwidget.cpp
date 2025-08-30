#include "mainwidget.h"


MainWidget *MainWidget::instance = nullptr;

MainWidget *MainWidget::getInstance()
{
    if(instance == nullptr) {
        // 以桌面为父窗口
        instance = new MainWidget();
    }
    return instance;
}

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    this->setWindowTitle("我的聊天室");
    this->setWindowIcon(QIcon(":/resource/image/logo.png"));

    // 初始化操作
    initMainWindow();
    initLeftWindow();
    initMidWindow();
    initRightWindow();

    // 初始化信号槽
    initSignalSlot();
}

MainWidget::~MainWidget() {}

void MainWidget::initMainWindow()
{
    // setWindowFlags(Qt::FramelessWindowHint);
    QHBoxLayout *layout = new QHBoxLayout();
    layout->setSpacing(0);                  // Spacing 就是 layout 内部元素之间的间隔距离
    layout->setContentsMargins(0, 0, 0, 0); // 里面元素四个边界的距离
    this->setLayout(layout);
    resize(800, 600);

    windowLeft = new QWidget();
    windowMid = new QWidget();
    windowRight = new QWidget();

    windowLeft->setFixedWidth(70);
    windowMid->setFixedWidth(310);
    windowRight->setMinimumWidth(800);

    windowLeft->setStyleSheet("QWidget { background-color: rgb(46,46,46); } ");
    windowMid->setStyleSheet("QWidget { background-color: rgb(247,247,247); } ");
    windowRight->setStyleSheet("QWidget { background-color: rgb(237,237,237); } ");

    layout->addWidget(windowLeft);
    layout->addWidget(windowMid);
    layout->addWidget(windowRight);
}

void MainWidget::initLeftWindow()
{
    QVBoxLayout *layout = new QVBoxLayout();
    layout->setSpacing(00);
    layout->setContentsMargins(0, 20, 0, 0);
    windowLeft->setLayout(layout);

    // 用户头像
    userAvatar = new QPushButton();
    userAvatar->setFixedSize(45, 45);
    userAvatar->setIconSize(QSize(45, 45));
    userAvatar->setIcon(QIcon(":/resource/image/defaultAvatar.png"));
    userAvatar->setStyleSheet("QPushButton { background-color: transparent; }");
    layout->addWidget(userAvatar, 1, Qt::AlignTop | Qt::AlignCenter);

    // 会话标签页按钮
    sessionTabBtn = new QPushButton();
    sessionTabBtn->setFixedSize(45, 45);
    sessionTabBtn->setIconSize(QSize(30, 30));
    sessionTabBtn->setIcon(QIcon(":/resource/image/session_active.png"));
    sessionTabBtn->setStyleSheet("QPushButton { background-color: transparent; }");
    layout->addWidget(sessionTabBtn, 1, Qt::AlignTop | Qt::AlignCenter);

    // 好友标签页按钮
    friendTabBtn = new QPushButton();
    friendTabBtn->setFixedSize(45, 45);
    friendTabBtn->setIconSize(QSize(30, 30));
    friendTabBtn->setIcon(QIcon(":/resource/image/friend_inactive.png"));
    friendTabBtn->setStyleSheet("QPushButton { background-color: transparent; }");
    layout->addWidget(friendTabBtn, 1, Qt::AlignTop | Qt::AlignCenter);

    // 好友申请标签页按钮
    applyTabBtn = new QPushButton();
    applyTabBtn->setFixedSize(45, 45);
    applyTabBtn->setIconSize(QSize(30, 30));
    applyTabBtn->setIcon(QIcon(":/resource/image/apply_inactive.png"));
    applyTabBtn->setStyleSheet("QPushButton { background-color: transparent; }");
    layout->addWidget(applyTabBtn, 1, Qt::AlignTop | Qt::AlignCenter);

    layout->addStretch(20);
}

void MainWidget::initMidWindow()
{

}

void MainWidget::initRightWindow()
{

}

void MainWidget::initSignalSlot()
{
    //////////////////////////////////////////
    /// 处理标签页按钮切换的问题
    /////////////////////////////////////////
    connect(sessionTabBtn, &QPushButton::clicked, this, &MainWidget::switchTabToSession);
    connect(friendTabBtn, &QPushButton::clicked, this, &MainWidget::switchTabToFriend);
    connect(applyTabBtn, &QPushButton::clicked, this, &MainWidget::switchTabToApply);
}

void MainWidget::switchTabToSession()
{
    // 记录切换的标签页
    activeTab = SESSION_LIST;
    // 调整其他图标
    sessionTabBtn->setIcon(QIcon(":/resource/image/session_active.png"));
    friendTabBtn->setIcon(QIcon(":/resource/image/friend_inactive.png"));
    applyTabBtn->setIcon(QIcon(":/resource/image/apply_inactive.png"));

    // 加载会话列表数据
    loadSessionList();
}

void MainWidget::switchTabToFriend()
{
    // 记录切换的标签页
    activeTab = FRIEND_LIST;
    // 调整其他图标
    friendTabBtn->setIcon(QIcon(":/resource/image/friend_active.png"));
    sessionTabBtn->setIcon(QIcon(":/resource/image/session_inactive.png"));
    applyTabBtn->setIcon(QIcon(":/resource/image/apply_inactive.png"));

    // 加载会话列表数据
    loadFriendList();
}

void MainWidget::switchTabToApply()
{
    // 记录切换的标签页
    activeTab = APPLY_LIST;
    // 调整其他图标
    applyTabBtn->setIcon(QIcon(":/resource/image/apply_active.png"));
    sessionTabBtn->setIcon(QIcon(":/resource/image/session_inactive.png"));
    friendTabBtn->setIcon(QIcon(":/resource/image/friend_inactive.png"));

    // 加载会话列表数据
    loadApplyList();
}

void MainWidget::loadSessionList()
{
    // TODO
}

void MainWidget::loadFriendList()
{
    // TODO
}

void MainWidget::loadApplyList()
{
    // TODO
}
