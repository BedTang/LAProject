/********************************************************************************
** Form generated from reading UI file 'mqtt_form.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MQTT_FORM_H
#define UI_MQTT_FORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MqttForm
{
public:
    QFormLayout *formLayout;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_7;
    QTextBrowser *log_browser_;
    QListWidget *mqtt_clinet_list_;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *server_host_label_;
    QLineEdit *server_host_line_;
    QLineEdit *server_port_line_;
    QHBoxLayout *horizontalLayout_2;
    QLabel *client_id_label_;
    QLineEdit *client_id_line_;
    QHBoxLayout *horizontalLayout_3;
    QLabel *client_user_label_;
    QLineEdit *client_user_line_;
    QHBoxLayout *horizontalLayout_4;
    QLabel *client_password_label_;
    QLineEdit *client_password_line_;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *connect_button_;
    QPushButton *pushButton;
    QPushButton *ping_button_;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout_2;
    QSpinBox *qos_box_;
    QPushButton *publish_button_;
    QLabel *subscribe_topic_label_;
    QLineEdit *subscribe_topic_line_;
    QLabel *publish_topic_label_;
    QLineEdit *publish_topic_line_;
    QPushButton *unsubscribe_topic_button_;
    QPushButton *subscribe_topic_button_;
    QTextEdit *message_text_;

    void setupUi(QWidget *MqttForm)
    {
        if (MqttForm->objectName().isEmpty())
            MqttForm->setObjectName(QString::fromUtf8("MqttForm"));
        MqttForm->resize(884, 583);
        formLayout = new QFormLayout(MqttForm);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        log_browser_ = new QTextBrowser(MqttForm);
        log_browser_->setObjectName(QString::fromUtf8("log_browser_"));

        horizontalLayout_7->addWidget(log_browser_);

        mqtt_clinet_list_ = new QListWidget(MqttForm);
        mqtt_clinet_list_->setObjectName(QString::fromUtf8("mqtt_clinet_list_"));

        horizontalLayout_7->addWidget(mqtt_clinet_list_);

        horizontalLayout_7->setStretch(0, 4);

        verticalLayout_5->addLayout(horizontalLayout_7);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        server_host_label_ = new QLabel(MqttForm);
        server_host_label_->setObjectName(QString::fromUtf8("server_host_label_"));
        server_host_label_->setMinimumSize(QSize(0, 0));

        horizontalLayout->addWidget(server_host_label_);

        server_host_line_ = new QLineEdit(MqttForm);
        server_host_line_->setObjectName(QString::fromUtf8("server_host_line_"));

        horizontalLayout->addWidget(server_host_line_);

        server_port_line_ = new QLineEdit(MqttForm);
        server_port_line_->setObjectName(QString::fromUtf8("server_port_line_"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(server_port_line_->sizePolicy().hasHeightForWidth());
        server_port_line_->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(server_port_line_);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        client_id_label_ = new QLabel(MqttForm);
        client_id_label_->setObjectName(QString::fromUtf8("client_id_label_"));
        client_id_label_->setMinimumSize(QSize(0, 0));

        horizontalLayout_2->addWidget(client_id_label_);

        client_id_line_ = new QLineEdit(MqttForm);
        client_id_line_->setObjectName(QString::fromUtf8("client_id_line_"));

        horizontalLayout_2->addWidget(client_id_line_);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        client_user_label_ = new QLabel(MqttForm);
        client_user_label_->setObjectName(QString::fromUtf8("client_user_label_"));
        client_user_label_->setMinimumSize(QSize(0, 0));

        horizontalLayout_3->addWidget(client_user_label_);

        client_user_line_ = new QLineEdit(MqttForm);
        client_user_line_->setObjectName(QString::fromUtf8("client_user_line_"));

        horizontalLayout_3->addWidget(client_user_line_);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        client_password_label_ = new QLabel(MqttForm);
        client_password_label_->setObjectName(QString::fromUtf8("client_password_label_"));
        client_password_label_->setMinimumSize(QSize(0, 0));

        horizontalLayout_4->addWidget(client_password_label_);

        client_password_line_ = new QLineEdit(MqttForm);
        client_password_line_->setObjectName(QString::fromUtf8("client_password_line_"));

        horizontalLayout_4->addWidget(client_password_line_);


        verticalLayout->addLayout(horizontalLayout_4);


        verticalLayout_3->addLayout(verticalLayout);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        connect_button_ = new QPushButton(MqttForm);
        connect_button_->setObjectName(QString::fromUtf8("connect_button_"));

        horizontalLayout_5->addWidget(connect_button_);

        pushButton = new QPushButton(MqttForm);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_5->addWidget(pushButton);

        ping_button_ = new QPushButton(MqttForm);
        ping_button_->setObjectName(QString::fromUtf8("ping_button_"));

        horizontalLayout_5->addWidget(ping_button_);


        verticalLayout_3->addLayout(horizontalLayout_5);


        horizontalLayout_6->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        qos_box_ = new QSpinBox(MqttForm);
        qos_box_->setObjectName(QString::fromUtf8("qos_box_"));

        gridLayout_2->addWidget(qos_box_, 1, 3, 1, 1);

        publish_button_ = new QPushButton(MqttForm);
        publish_button_->setObjectName(QString::fromUtf8("publish_button_"));

        gridLayout_2->addWidget(publish_button_, 1, 4, 1, 1);

        subscribe_topic_label_ = new QLabel(MqttForm);
        subscribe_topic_label_->setObjectName(QString::fromUtf8("subscribe_topic_label_"));
        subscribe_topic_label_->setMinimumSize(QSize(45, 0));

        gridLayout_2->addWidget(subscribe_topic_label_, 0, 0, 1, 1);

        subscribe_topic_line_ = new QLineEdit(MqttForm);
        subscribe_topic_line_->setObjectName(QString::fromUtf8("subscribe_topic_line_"));

        gridLayout_2->addWidget(subscribe_topic_line_, 0, 1, 1, 1);

        publish_topic_label_ = new QLabel(MqttForm);
        publish_topic_label_->setObjectName(QString::fromUtf8("publish_topic_label_"));
        publish_topic_label_->setMinimumSize(QSize(45, 0));

        gridLayout_2->addWidget(publish_topic_label_, 1, 0, 1, 1);

        publish_topic_line_ = new QLineEdit(MqttForm);
        publish_topic_line_->setObjectName(QString::fromUtf8("publish_topic_line_"));

        gridLayout_2->addWidget(publish_topic_line_, 1, 1, 1, 1);

        unsubscribe_topic_button_ = new QPushButton(MqttForm);
        unsubscribe_topic_button_->setObjectName(QString::fromUtf8("unsubscribe_topic_button_"));

        gridLayout_2->addWidget(unsubscribe_topic_button_, 0, 4, 1, 1);

        subscribe_topic_button_ = new QPushButton(MqttForm);
        subscribe_topic_button_->setObjectName(QString::fromUtf8("subscribe_topic_button_"));

        gridLayout_2->addWidget(subscribe_topic_button_, 0, 3, 1, 1);


        verticalLayout_2->addLayout(gridLayout_2);


        verticalLayout_4->addLayout(verticalLayout_2);

        message_text_ = new QTextEdit(MqttForm);
        message_text_->setObjectName(QString::fromUtf8("message_text_"));

        verticalLayout_4->addWidget(message_text_);


        horizontalLayout_6->addLayout(verticalLayout_4);

        horizontalLayout_6->setStretch(0, 4);
        horizontalLayout_6->setStretch(1, 3);

        verticalLayout_5->addLayout(horizontalLayout_6);

        verticalLayout_5->setStretch(0, 2);

        formLayout->setLayout(0, QFormLayout::SpanningRole, verticalLayout_5);


        retranslateUi(MqttForm);

        QMetaObject::connectSlotsByName(MqttForm);
    } // setupUi

    void retranslateUi(QWidget *MqttForm)
    {
        MqttForm->setWindowTitle(QCoreApplication::translate("MqttForm", "Form", nullptr));
        server_host_label_->setText(QCoreApplication::translate("MqttForm", "\346\234\215\345\212\241\345\231\250\345\234\260\345\235\200\357\274\232", nullptr));
        server_host_line_->setText(QCoreApplication::translate("MqttForm", "mqtts.heclouds.com", nullptr));
        server_port_line_->setText(QCoreApplication::translate("MqttForm", "1883", nullptr));
        client_id_label_->setText(QCoreApplication::translate("MqttForm", "\345\256\242\346\210\267\347\253\257ID\357\274\232", nullptr));
        client_id_line_->setText(QCoreApplication::translate("MqttForm", "Node1", nullptr));
        client_user_label_->setText(QCoreApplication::translate("MqttForm", "\347\224\250\346\210\267\345\220\215:", nullptr));
        client_user_line_->setText(QCoreApplication::translate("MqttForm", "zdgol22rNA", nullptr));
        client_password_label_->setText(QCoreApplication::translate("MqttForm", "\345\257\206\347\240\201\357\274\232", nullptr));
        client_password_line_->setText(QCoreApplication::translate("MqttForm", "version=2018-10-31&res=products%2Fzdgol22rNA%2Fdevices%2FNode1&et=1748431311&method=md5&sign=VhXJ4v9mlpTdyd29xppI8Q%3D%3D", nullptr));
        connect_button_->setText(QCoreApplication::translate("MqttForm", "\350\277\236\346\216\245", nullptr));
        pushButton->setText(QCoreApplication::translate("MqttForm", "\346\265\213\350\257\225", nullptr));
        ping_button_->setText(QCoreApplication::translate("MqttForm", "Ping", nullptr));
        publish_button_->setText(QCoreApplication::translate("MqttForm", "\345\217\221\345\270\203", nullptr));
        subscribe_topic_label_->setText(QCoreApplication::translate("MqttForm", "\350\256\242\351\230\205\344\270\273\351\242\230\357\274\232", nullptr));
        publish_topic_label_->setText(QCoreApplication::translate("MqttForm", "\345\217\221\345\270\203\344\270\273\351\242\230\357\274\232", nullptr));
        publish_topic_line_->setText(QCoreApplication::translate("MqttForm", "$sys/zdgol22rNA/Node1/thing/property/post", nullptr));
        unsubscribe_topic_button_->setText(QCoreApplication::translate("MqttForm", "\345\217\226\346\266\210\350\256\242\351\230\205", nullptr));
        subscribe_topic_button_->setText(QCoreApplication::translate("MqttForm", "\350\256\242\351\230\205", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MqttForm: public Ui_MqttForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MQTT_FORM_H
