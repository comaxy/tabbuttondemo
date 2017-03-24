#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QMap>
#include <QPushButton>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QButtonGroup *m_tabButtonGroup = nullptr;
    QHBoxLayout *m_tabButtonLayout = nullptr;
    QMap<QPushButton*, QLabel*> m_btn2Label;  // 记录按钮和分隔条的对应关系
};

#endif // MAINWINDOW_H
