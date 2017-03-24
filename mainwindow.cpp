#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "closeablebutton.h"
#include <QSpacerItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_tabButtonGroup = new QButtonGroup();
    m_tabButtonGroup->setExclusive(true);
    connect(m_tabButtonGroup, SIGNAL(buttonClicked(int)), this, SLOT(onTabButtonClicked(int)));

    m_tabButtonLayout = new QHBoxLayout(ui->centralWidget);
    m_tabButtonLayout->setContentsMargins(0, 0, 1, 0);
    m_tabButtonLayout->setSpacing(0);
    ui->centralWidget->setLayout(m_tabButtonLayout);

    QList<QString> bookNames = { QStringLiteral("《飞狐外传》"),
                                 QStringLiteral("《雪山飞狐》"),
                                 QStringLiteral("《连城诀》"),
                                 QStringLiteral("《天龙八部》"),
                                 QStringLiteral("《射雕英雄传》")};
    for (decltype(bookNames.size()) i = 0; i < bookNames.size(); ++i)
    {
        auto tabButton = new CloseableButton(bookNames.at(i), this);
        tabButton->setFixedSize(150, 30);
        m_tabButtonLayout->addWidget(tabButton);
        m_tabButtonGroup->addButton(tabButton);
        auto separatorLabel = new QLabel(this);
        separatorLabel->setPixmap(QPixmap(":/skin/separator.png"));
        m_tabButtonLayout->addWidget(separatorLabel);
        m_btn2Label[tabButton] = separatorLabel;
        connect(tabButton, &CloseableButton::closeButtonClicked, [this](CloseableButton *button) {
            m_tabButtonLayout->removeWidget(m_btn2Label[button]);
            m_tabButtonLayout->removeWidget(button);
            m_tabButtonGroup->removeButton(button);
            delete m_btn2Label[button];
            delete button;
        });
    }
    m_tabButtonLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
    m_tabButtonGroup->buttons().at(0)->setChecked(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}
