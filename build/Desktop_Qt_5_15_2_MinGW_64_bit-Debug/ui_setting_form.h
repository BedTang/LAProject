/********************************************************************************
** Form generated from reading UI file 'setting_form.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTING_FORM_H
#define UI_SETTING_FORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingForm
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QPushButton *SerialFormBtn;
    QPushButton *MQTTFormBtn;

    void setupUi(QWidget *SettingForm)
    {
        if (SettingForm->objectName().isEmpty())
            SettingForm->setObjectName(QString::fromUtf8("SettingForm"));
        SettingForm->resize(466, 363);
        layoutWidget = new QWidget(SettingForm);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 201, 24));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(layoutWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);

        SerialFormBtn = new QPushButton(SettingForm);
        SerialFormBtn->setObjectName(QString::fromUtf8("SerialFormBtn"));
        SerialFormBtn->setGeometry(QRect(360, 310, 80, 18));
        MQTTFormBtn = new QPushButton(SettingForm);
        MQTTFormBtn->setObjectName(QString::fromUtf8("MQTTFormBtn"));
        MQTTFormBtn->setGeometry(QRect(270, 310, 80, 18));

        retranslateUi(SettingForm);

        QMetaObject::connectSlotsByName(SettingForm);
    } // setupUi

    void retranslateUi(QWidget *SettingForm)
    {
        SettingForm->setWindowTitle(QCoreApplication::translate("SettingForm", "Form", nullptr));
        label->setText(QCoreApplication::translate("SettingForm", "\346\234\215\345\212\241\345\231\250\347\253\257\345\217\243\357\274\232", nullptr));
        lineEdit->setText(QCoreApplication::translate("SettingForm", "8080", nullptr));
        pushButton->setText(QCoreApplication::translate("SettingForm", "\347\241\256\345\256\232", nullptr));
        SerialFormBtn->setText(QCoreApplication::translate("SettingForm", " \344\270\262\345\217\243\345\267\245\345\205\267", nullptr));
        MQTTFormBtn->setText(QCoreApplication::translate("SettingForm", "MQTT\345\267\245\345\205\267", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingForm: public Ui_SettingForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTING_FORM_H
