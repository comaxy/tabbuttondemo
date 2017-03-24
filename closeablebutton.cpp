#include "closeablebutton.h"
#include <QPainter>

CloseableButton::CloseableButton(const QString &text, QWidget *parent)
    : QPushButton{text, parent}
{
    // 页签有两种状态，普通状态和按下状态，因此设置checkable为true
    setCheckable(true);

    // 为了在没有鼠标按下的时候响应MouseMove事件，设置MouseTracking为true
    setMouseTracking(true);
}

void CloseableButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);  // 创建Painter

    QPoint curPos = getCursorPos();  // 当前鼠标位置

    // 背景
    if (isChecked())  // 选中状态
    {
        painter.fillRect(rect(), QColor(244,248,255));
    }
    else  // 非选中状态
    {
        if (rect().contains(curPos))  // 鼠标在按钮区域
        {
            painter.fillRect(rect(), QColor(222,231,245));
        }
        else  // 鼠标不在按钮区域
        {
            painter.fillRect(rect(), QColor(213,225,242));
        }
    }

    // 关闭按钮
    QRect closeButtonRect = getCloseButtonRect();  // 获取关闭按钮坐标
    if (closeButtonRect.contains(curPos))  // 鼠标在关闭按钮区域
    {
        if (m_pressedOnCloseButton)  // 鼠标在关闭按钮区域按下
        {
            painter.drawImage(closeButtonRect.topLeft(), QImage(":/skin/closeTabPressed.png"));
        }
        else  // 鼠标悬停在关闭按钮区域
        {
            painter.drawImage(closeButtonRect.topLeft(), QImage(":/skin/closeTabHot.png"));
        }
    }
    else  // 鼠标不在按钮区域
    {
        painter.drawImage(closeButtonRect.topLeft(), QImage(":/skin/closeTabNormal.png"));
    }

    // 文本
    QRect textRect;
    textRect.setTop(9);
    textRect.setLeft(8);
    textRect.setBottom(25);
    if (isChecked())  // 选中状态
    {
        textRect.setRight(rect().right() - 23);
        painter.setFont(QFont(painter.font().family(), -1, QFont::Bold));  // 选中状态文字设置为粗体
    }
    else  // 非选中状态
    {
        textRect.setRight(rect().right() - 28);
    }
    QFontMetrics fontMetrics(painter.font());
    QString textDraw = fontMetrics.elidedText(text(), Qt::ElideRight, textRect.width());  // 如果文字超出显示区域，则末尾截断，加省略号
    painter.drawText(textRect, Qt::TextSingleLine, textDraw);
}

void CloseableButton::mouseMoveEvent(QMouseEvent *e)
{
    QPushButton::mouseMoveEvent(e);
    update();
}

void CloseableButton::mousePressEvent(QMouseEvent *e)
{
    // 记录按下位置
    auto curPos = getCursorPos();
    if (getCloseButtonRect().contains(curPos))
    {
        m_pressedOnCloseButton = true;
    }
    else
    {
        m_pressedOnCloseButton = false;
        if (rect().contains(curPos))
        {
            m_pressedOnButton = true;
            QPushButton::mousePressEvent(e);
        }
        else
        {
            m_pressedOnButton = false;
        }
    }
    update();
}

void CloseableButton::mouseReleaseEvent(QMouseEvent *e)
{
    // 根据不同的鼠标按下状态发射不同的信号
    auto curPos = getCursorPos();
    if (m_pressedOnCloseButton && getCloseButtonRect().contains(curPos))  // 在关闭按钮区域按下并释放鼠标左键
    {
        resetPressState();
        update();
        emit closeButtonClicked(this);  // 发射自定义信号
    }
    else
    {
        if (m_pressedOnButton && rect().contains(curPos))  // 在页签区域按下并释放鼠标左键
        {
            resetPressState();
            update();
            QPushButton::mouseReleaseEvent(e);  // 调用父类方法发射clicked信号
        }
        else
        {
            resetPressState();
            update();
        }
    }
}

QRect CloseableButton::getCloseButtonRect()
{
    QRect closeButtonRect;
    closeButtonRect.setLeft(rect().width() - 23);
    closeButtonRect.setTop(rect().top() + 6);
    closeButtonRect.setRight(rect().width() - 5);
    closeButtonRect.setBottom(rect().top() + 24);
    return closeButtonRect;
}

QPoint CloseableButton::getCursorPos()
{
    QCursor cur = cursor();
    return mapFromGlobal(cur.pos());
}

void CloseableButton::resetPressState()
{
    m_pressedOnCloseButton = false;
    m_pressedOnButton = false;
}
