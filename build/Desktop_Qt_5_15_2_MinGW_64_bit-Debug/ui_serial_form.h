/********************************************************************************
** Form generated from reading UI file 'serial_form.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERIAL_FORM_H
#define UI_SERIAL_FORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SerialForm
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_11;
    QHBoxLayout *horizontalLayout_9;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_6;
    QLabel *label_8;
    QTextEdit *receiveEdit;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_10;
    QVBoxLayout *verticalLayout;
    QPushButton *scanSerialBtn;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *serialPortList;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QComboBox *baudRateList;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QComboBox *dataBitsList;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QComboBox *parityList;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QComboBox *stopBitsList;
    QPushButton *serialSwitchBtn;
    QHBoxLayout *horizontalLayout_8;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_7;
    QLabel *label_9;
    QTextEdit *sendEdit;
    QVBoxLayout *verticalLayout_8;
    QVBoxLayout *verticalLayout_10;
    QPushButton *pushButton;
    QVBoxLayout *verticalLayout_4;
    QRadioButton *textReceiveRadioBtn;
    QRadioButton *hexReceiveRadioBtn;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_3;
    QRadioButton *textSendRadioBtn;
    QRadioButton *hexSendRadioBtn;
    QCheckBox *checkBox;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *checkBox_2;
    QSpinBox *spinBox;
    QPushButton *pushButton_2;
    QPushButton *dataSendBtn;

    void setupUi(QWidget *SerialForm)
    {
        if (SerialForm->objectName().isEmpty())
            SerialForm->setObjectName(QString::fromUtf8("SerialForm"));
        SerialForm->resize(785, 548);
        gridLayout = new QGridLayout(SerialForm);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_6 = new QLabel(SerialForm);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_7->addWidget(label_6);

        label_8 = new QLabel(SerialForm);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_7->addWidget(label_8);


        verticalLayout_7->addLayout(horizontalLayout_7);

        receiveEdit = new QTextEdit(SerialForm);
        receiveEdit->setObjectName(QString::fromUtf8("receiveEdit"));

        verticalLayout_7->addWidget(receiveEdit);


        horizontalLayout_9->addLayout(verticalLayout_7);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));

        horizontalLayout_9->addLayout(verticalLayout_5);


        verticalLayout_11->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        scanSerialBtn = new QPushButton(SerialForm);
        scanSerialBtn->setObjectName(QString::fromUtf8("scanSerialBtn"));

        verticalLayout->addWidget(scanSerialBtn);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(SerialForm);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        serialPortList = new QComboBox(SerialForm);
        serialPortList->setObjectName(QString::fromUtf8("serialPortList"));

        horizontalLayout->addWidget(serialPortList);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(SerialForm);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        baudRateList = new QComboBox(SerialForm);
        baudRateList->addItem(QString());
        baudRateList->addItem(QString());
        baudRateList->addItem(QString());
        baudRateList->addItem(QString());
        baudRateList->addItem(QString());
        baudRateList->addItem(QString());
        baudRateList->addItem(QString());
        baudRateList->addItem(QString());
        baudRateList->setObjectName(QString::fromUtf8("baudRateList"));

        horizontalLayout_2->addWidget(baudRateList);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(SerialForm);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        dataBitsList = new QComboBox(SerialForm);
        dataBitsList->addItem(QString());
        dataBitsList->addItem(QString());
        dataBitsList->addItem(QString());
        dataBitsList->addItem(QString());
        dataBitsList->setObjectName(QString::fromUtf8("dataBitsList"));

        horizontalLayout_3->addWidget(dataBitsList);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_4 = new QLabel(SerialForm);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_4->addWidget(label_4);

        parityList = new QComboBox(SerialForm);
        parityList->addItem(QString());
        parityList->addItem(QString());
        parityList->addItem(QString());
        parityList->addItem(QString());
        parityList->addItem(QString());
        parityList->setObjectName(QString::fromUtf8("parityList"));

        horizontalLayout_4->addWidget(parityList);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_5 = new QLabel(SerialForm);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_5->addWidget(label_5);

        stopBitsList = new QComboBox(SerialForm);
        stopBitsList->addItem(QString());
        stopBitsList->addItem(QString());
        stopBitsList->addItem(QString());
        stopBitsList->setObjectName(QString::fromUtf8("stopBitsList"));

        horizontalLayout_5->addWidget(stopBitsList);


        verticalLayout->addLayout(horizontalLayout_5);

        serialSwitchBtn = new QPushButton(SerialForm);
        serialSwitchBtn->setObjectName(QString::fromUtf8("serialSwitchBtn"));

        verticalLayout->addWidget(serialSwitchBtn);


        horizontalLayout_10->addLayout(verticalLayout);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_7 = new QLabel(SerialForm);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_6->addWidget(label_7);

        label_9 = new QLabel(SerialForm);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_6->addWidget(label_9);


        verticalLayout_9->addLayout(horizontalLayout_6);

        sendEdit = new QTextEdit(SerialForm);
        sendEdit->setObjectName(QString::fromUtf8("sendEdit"));

        verticalLayout_9->addWidget(sendEdit);


        horizontalLayout_8->addLayout(verticalLayout_9);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        pushButton = new QPushButton(SerialForm);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout_10->addWidget(pushButton);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        textReceiveRadioBtn = new QRadioButton(SerialForm);
        textReceiveRadioBtn->setObjectName(QString::fromUtf8("textReceiveRadioBtn"));
        textReceiveRadioBtn->setAutoExclusive(true);

        verticalLayout_4->addWidget(textReceiveRadioBtn);

        hexReceiveRadioBtn = new QRadioButton(SerialForm);
        hexReceiveRadioBtn->setObjectName(QString::fromUtf8("hexReceiveRadioBtn"));
        hexReceiveRadioBtn->setAutoExclusive(true);

        verticalLayout_4->addWidget(hexReceiveRadioBtn);


        verticalLayout_10->addLayout(verticalLayout_4);


        verticalLayout_8->addLayout(verticalLayout_10);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        textSendRadioBtn = new QRadioButton(SerialForm);
        textSendRadioBtn->setObjectName(QString::fromUtf8("textSendRadioBtn"));
        textSendRadioBtn->setChecked(true);
        textSendRadioBtn->setAutoRepeat(false);
        textSendRadioBtn->setAutoExclusive(true);

        verticalLayout_3->addWidget(textSendRadioBtn);

        hexSendRadioBtn = new QRadioButton(SerialForm);
        hexSendRadioBtn->setObjectName(QString::fromUtf8("hexSendRadioBtn"));
        hexSendRadioBtn->setAutoRepeat(false);
        hexSendRadioBtn->setAutoExclusive(true);

        verticalLayout_3->addWidget(hexSendRadioBtn);

        checkBox = new QCheckBox(SerialForm);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        verticalLayout_3->addWidget(checkBox);


        verticalLayout_6->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        checkBox_2 = new QCheckBox(SerialForm);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));

        verticalLayout_2->addWidget(checkBox_2);

        spinBox = new QSpinBox(SerialForm);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setMaximum(99999);
        spinBox->setValue(1000);

        verticalLayout_2->addWidget(spinBox);


        verticalLayout_6->addLayout(verticalLayout_2);

        pushButton_2 = new QPushButton(SerialForm);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        verticalLayout_6->addWidget(pushButton_2);

        dataSendBtn = new QPushButton(SerialForm);
        dataSendBtn->setObjectName(QString::fromUtf8("dataSendBtn"));

        verticalLayout_6->addWidget(dataSendBtn);


        verticalLayout_8->addLayout(verticalLayout_6);


        horizontalLayout_8->addLayout(verticalLayout_8);


        horizontalLayout_10->addLayout(horizontalLayout_8);


        verticalLayout_11->addLayout(horizontalLayout_10);


        gridLayout->addLayout(verticalLayout_11, 0, 0, 1, 1);


        retranslateUi(SerialForm);

        baudRateList->setCurrentIndex(3);
        dataBitsList->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(SerialForm);
    } // setupUi

    void retranslateUi(QWidget *SerialForm)
    {
        SerialForm->setWindowTitle(QCoreApplication::translate("SerialForm", "Form", nullptr));
        label_6->setText(QCoreApplication::translate("SerialForm", "\346\216\245\346\224\266\345\214\272", nullptr));
        label_8->setText(QCoreApplication::translate("SerialForm", "\346\216\245\346\224\266\350\256\241\346\225\260\357\274\2320", nullptr));
        scanSerialBtn->setText(QCoreApplication::translate("SerialForm", "\346\211\253\346\217\217\344\270\262\345\217\243", nullptr));
        label->setText(QCoreApplication::translate("SerialForm", "\344\270\262\345\217\243\345\217\267\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("SerialForm", "\346\263\242\347\211\271\347\216\207\357\274\232", nullptr));
        baudRateList->setItemText(0, QCoreApplication::translate("SerialForm", "1200", nullptr));
        baudRateList->setItemText(1, QCoreApplication::translate("SerialForm", "2400", nullptr));
        baudRateList->setItemText(2, QCoreApplication::translate("SerialForm", "4800", nullptr));
        baudRateList->setItemText(3, QCoreApplication::translate("SerialForm", "9600", nullptr));
        baudRateList->setItemText(4, QCoreApplication::translate("SerialForm", "19200", nullptr));
        baudRateList->setItemText(5, QCoreApplication::translate("SerialForm", "38400", nullptr));
        baudRateList->setItemText(6, QCoreApplication::translate("SerialForm", "57600", nullptr));
        baudRateList->setItemText(7, QCoreApplication::translate("SerialForm", "115200", nullptr));

        label_3->setText(QCoreApplication::translate("SerialForm", "\346\225\260\346\215\256\344\270\272\357\274\232", nullptr));
        dataBitsList->setItemText(0, QCoreApplication::translate("SerialForm", "5", nullptr));
        dataBitsList->setItemText(1, QCoreApplication::translate("SerialForm", "6", nullptr));
        dataBitsList->setItemText(2, QCoreApplication::translate("SerialForm", "7", nullptr));
        dataBitsList->setItemText(3, QCoreApplication::translate("SerialForm", "8", nullptr));

        label_4->setText(QCoreApplication::translate("SerialForm", "\346\240\241\351\252\214\344\275\215\357\274\232", nullptr));
        parityList->setItemText(0, QCoreApplication::translate("SerialForm", "None", nullptr));
        parityList->setItemText(1, QCoreApplication::translate("SerialForm", "\345\245\207\346\240\241\351\252\214", nullptr));
        parityList->setItemText(2, QCoreApplication::translate("SerialForm", "\345\201\266\346\240\241\351\252\214", nullptr));
        parityList->setItemText(3, QCoreApplication::translate("SerialForm", "\346\240\241\351\252\214\344\275\215\345\247\213\347\273\210\344\270\2721", nullptr));
        parityList->setItemText(4, QCoreApplication::translate("SerialForm", "\346\240\241\351\252\214\344\275\215\345\247\213\347\273\210\344\270\2720", nullptr));

        label_5->setText(QCoreApplication::translate("SerialForm", "\345\201\234\346\255\242\344\275\215\357\274\232", nullptr));
        stopBitsList->setItemText(0, QCoreApplication::translate("SerialForm", "1", nullptr));
        stopBitsList->setItemText(1, QCoreApplication::translate("SerialForm", "1.5", nullptr));
        stopBitsList->setItemText(2, QCoreApplication::translate("SerialForm", "2", nullptr));

        serialSwitchBtn->setText(QCoreApplication::translate("SerialForm", "\346\211\223\345\274\200\344\270\262\345\217\243", nullptr));
        label_7->setText(QCoreApplication::translate("SerialForm", "\345\217\221\351\200\201\345\214\272", nullptr));
        label_9->setText(QCoreApplication::translate("SerialForm", "\346\216\245\346\224\266\350\256\241\346\225\260\357\274\2320", nullptr));
        pushButton->setText(QCoreApplication::translate("SerialForm", "\346\270\205\347\251\272", nullptr));
        textReceiveRadioBtn->setText(QCoreApplication::translate("SerialForm", "\346\226\207\346\234\254", nullptr));
        hexReceiveRadioBtn->setText(QCoreApplication::translate("SerialForm", "\345\215\201\345\205\255\350\277\233\345\210\266", nullptr));
        textSendRadioBtn->setText(QCoreApplication::translate("SerialForm", "\346\226\207\346\234\254", nullptr));
        hexSendRadioBtn->setText(QCoreApplication::translate("SerialForm", "\345\215\201\345\205\255\350\277\233\345\210\266", nullptr));
        checkBox->setText(QCoreApplication::translate("SerialForm", "\345\212\240\345\233\236\350\275\246\346\215\242\350\241\214", nullptr));
        checkBox_2->setText(QCoreApplication::translate("SerialForm", "\345\256\232\346\227\266\345\217\221\351\200\201\357\274\232", nullptr));
        pushButton_2->setText(QCoreApplication::translate("SerialForm", "\346\270\205\347\251\272", nullptr));
        dataSendBtn->setText(QCoreApplication::translate("SerialForm", "\345\217\221\351\200\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SerialForm: public Ui_SerialForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERIAL_FORM_H
