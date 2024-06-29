/********************************************************************************
** Form generated from reading UI file 'main_form.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_FORM_H
#define UI_MAIN_FORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainForm
{
public:
    QGridLayout *gridLayout_3;
    QStatusBar *statusBar;
    QSplitter *splitter_;
    QWidget *layoutWidget;
    QVBoxLayout *leftVerticalLayout_2;
    QGroupBox *devicesGroupBox;
    QGridLayout *gridLayout_2;
    QTableView *devices_table_view_;
    QGroupBox *logGroupBox;
    QGridLayout *logGridLayout;
    QTextBrowser *logBrowser;
    QTabWidget *devices_tab;
    QWidget *tab;
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer_4;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_3;
    QLabel *label;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *start_server;
    QPushButton *save_button;
    QPushButton *test_button;
    QPushButton *setting_button;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *MainForm)
    {
        if (MainForm->objectName().isEmpty())
            MainForm->setObjectName(QString::fromUtf8("MainForm"));
        MainForm->resize(833, 498);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainForm->sizePolicy().hasHeightForWidth());
        MainForm->setSizePolicy(sizePolicy);
        MainForm->setMinimumSize(QSize(0, 0));
        MainForm->setStyleSheet(QString::fromUtf8(""));
        gridLayout_3 = new QGridLayout(MainForm);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(2, 2, 2, 2);
        statusBar = new QStatusBar(MainForm);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(statusBar->sizePolicy().hasHeightForWidth());
        statusBar->setSizePolicy(sizePolicy1);
        statusBar->setMaximumSize(QSize(16777215, 15));

        gridLayout_3->addWidget(statusBar, 3, 1, 1, 1);

        splitter_ = new QSplitter(MainForm);
        splitter_->setObjectName(QString::fromUtf8("splitter_"));
        splitter_->setOrientation(Qt::Horizontal);
        layoutWidget = new QWidget(splitter_);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(layoutWidget->sizePolicy().hasHeightForWidth());
        layoutWidget->setSizePolicy(sizePolicy2);
        leftVerticalLayout_2 = new QVBoxLayout(layoutWidget);
        leftVerticalLayout_2->setObjectName(QString::fromUtf8("leftVerticalLayout_2"));
        leftVerticalLayout_2->setContentsMargins(0, 0, 0, 0);
        devicesGroupBox = new QGroupBox(layoutWidget);
        devicesGroupBox->setObjectName(QString::fromUtf8("devicesGroupBox"));
        sizePolicy2.setHeightForWidth(devicesGroupBox->sizePolicy().hasHeightForWidth());
        devicesGroupBox->setSizePolicy(sizePolicy2);
        devicesGroupBox->setAlignment(Qt::AlignCenter);
        gridLayout_2 = new QGridLayout(devicesGroupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        devices_table_view_ = new QTableView(devicesGroupBox);
        devices_table_view_->setObjectName(QString::fromUtf8("devices_table_view_"));
        sizePolicy2.setHeightForWidth(devices_table_view_->sizePolicy().hasHeightForWidth());
        devices_table_view_->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(devices_table_view_, 0, 0, 1, 1);


        leftVerticalLayout_2->addWidget(devicesGroupBox);

        logGroupBox = new QGroupBox(layoutWidget);
        logGroupBox->setObjectName(QString::fromUtf8("logGroupBox"));
        sizePolicy2.setHeightForWidth(logGroupBox->sizePolicy().hasHeightForWidth());
        logGroupBox->setSizePolicy(sizePolicy2);
        logGroupBox->setAlignment(Qt::AlignCenter);
        logGridLayout = new QGridLayout(logGroupBox);
        logGridLayout->setObjectName(QString::fromUtf8("logGridLayout"));
        logGridLayout->setContentsMargins(0, 0, 0, 0);
        logBrowser = new QTextBrowser(logGroupBox);
        logBrowser->setObjectName(QString::fromUtf8("logBrowser"));
        sizePolicy2.setHeightForWidth(logBrowser->sizePolicy().hasHeightForWidth());
        logBrowser->setSizePolicy(sizePolicy2);

        logGridLayout->addWidget(logBrowser, 0, 0, 1, 1);


        leftVerticalLayout_2->addWidget(logGroupBox);

        leftVerticalLayout_2->setStretch(0, 3);
        leftVerticalLayout_2->setStretch(1, 2);
        splitter_->addWidget(layoutWidget);
        devices_tab = new QTabWidget(splitter_);
        devices_tab->setObjectName(QString::fromUtf8("devices_tab"));
        QSizePolicy sizePolicy3(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(devices_tab->sizePolicy().hasHeightForWidth());
        devices_tab->setSizePolicy(sizePolicy3);
        devices_tab->setTabsClosable(true);
        devices_tab->setMovable(true);
        devices_tab->setTabBarAutoHide(false);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        sizePolicy2.setHeightForWidth(tab->sizePolicy().hasHeightForWidth());
        tab->setSizePolicy(sizePolicy2);
        gridLayout = new QGridLayout(tab);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_4, 1, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_3);

        label = new QLabel(tab);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_2->addWidget(label);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        start_server = new QPushButton(tab);
        start_server->setObjectName(QString::fromUtf8("start_server"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(start_server->sizePolicy().hasHeightForWidth());
        start_server->setSizePolicy(sizePolicy4);
        QFont font;
        font.setPointSize(12);
        start_server->setFont(font);
        start_server->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(start_server);

        save_button = new QPushButton(tab);
        save_button->setObjectName(QString::fromUtf8("save_button"));
        sizePolicy4.setHeightForWidth(save_button->sizePolicy().hasHeightForWidth());
        save_button->setSizePolicy(sizePolicy4);
        save_button->setFont(font);
        save_button->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(save_button);

        test_button = new QPushButton(tab);
        test_button->setObjectName(QString::fromUtf8("test_button"));
        sizePolicy4.setHeightForWidth(test_button->sizePolicy().hasHeightForWidth());
        test_button->setSizePolicy(sizePolicy4);
        test_button->setFont(font);
        test_button->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(test_button);

        setting_button = new QPushButton(tab);
        setting_button->setObjectName(QString::fromUtf8("setting_button"));
        sizePolicy4.setHeightForWidth(setting_button->sizePolicy().hasHeightForWidth());
        setting_button->setSizePolicy(sizePolicy4);
        setting_button->setFont(font);
        setting_button->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(setting_button);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);


        gridLayout->addLayout(verticalLayout_2, 0, 0, 1, 1);

        devices_tab->addTab(tab, QString());
        splitter_->addWidget(devices_tab);

        gridLayout_3->addWidget(splitter_, 2, 1, 1, 1);


        retranslateUi(MainForm);

        devices_tab->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainForm);
    } // setupUi

    void retranslateUi(QWidget *MainForm)
    {
        MainForm->setWindowTitle(QCoreApplication::translate("MainForm", "Widget", nullptr));
        devicesGroupBox->setTitle(QCoreApplication::translate("MainForm", "\350\256\276\345\244\207\345\210\227\350\241\250", nullptr));
        logGroupBox->setTitle(QCoreApplication::translate("MainForm", "\346\227\245\345\277\227", nullptr));
        label->setText(QCoreApplication::translate("MainForm", "<html><head/><body><p align=\"center\"><span style=\" font-size:10pt;\">\345\210\206\345\270\203\345\274\217\345\267\245\344\270\232\350\212\202\347\202\271\344\270\216\347\224\265\346\234\272\346\231\272\350\203\275\347\233\221\346\265\213\347\263\273\347\273\237</span></p><p align=\"center\">XXX</p><p align=\"center\">XXX</p><p align=\"center\">XXX</p><p align=\"center\">XXX</p><p align=\"center\">XXX<br/></p></body></html>", nullptr));
        start_server->setText(QCoreApplication::translate("MainForm", "\345\220\257\345\212\250\346\234\215\345\212\241\345\231\250", nullptr));
        save_button->setText(QCoreApplication::translate("MainForm", "\344\277\235\345\255\230", nullptr));
        test_button->setText(QCoreApplication::translate("MainForm", "\346\270\205\347\251\272\346\225\260\346\215\256\357\274\210\346\265\213\350\257\225\346\214\211\351\222\256\357\274\211", nullptr));
        setting_button->setText(QCoreApplication::translate("MainForm", "\350\256\276\347\275\256", nullptr));
        devices_tab->setTabText(devices_tab->indexOf(tab), QCoreApplication::translate("MainForm", "\344\270\273\351\241\265", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainForm: public Ui_MainForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_FORM_H
