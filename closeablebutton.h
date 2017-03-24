#ifndef CLOSEABLEBUTTON_H
#define CLOSEABLEBUTTON_H

#include <QPushButton>

class CloseableButton : public QPushButton
{
    Q_OBJECT

public:
    explicit CloseableButton(const QString &text, QWidget *parent = Q_NULLPTR);

signals:
    void closeButtonClicked(CloseableButton *closeableButton);

protected:
    void paintEvent(QPaintEvent *e) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;

private:
    QRect getCloseButtonRect();
    QPoint getCursorPos();
    void resetPressState();

private:
    bool m_pressedOnCloseButton = false;
    bool m_pressedOnButton = false;
};

#endif // CLOSEABLEBUTTON_H
