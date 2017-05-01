/********************************************************************************
** Form generated from reading UI file 'LoggingForm.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGGINGFORM_H
#define UI_LOGGINGFORM_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoggingForm
{
public:
    QPushButton *connectButton;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *loginLabel;
    QLineEdit *loginLineEdit;
    QLabel *passwordLabel;
    QLineEdit *passwordLineEdit;
    QLabel *addressLabel;
    QLineEdit *addressLineEdit;

    void setupUi(QDialog *LoggingForm)
    {
        if (LoggingForm->objectName().isEmpty())
            LoggingForm->setObjectName(QStringLiteral("LoggingForm"));
        LoggingForm->setWindowModality(Qt::WindowModal);
        LoggingForm->resize(400, 200);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(LoggingForm->sizePolicy().hasHeightForWidth());
        LoggingForm->setSizePolicy(sizePolicy);
        LoggingForm->setMinimumSize(QSize(400, 200));
        LoggingForm->setMaximumSize(QSize(400, 200));
        LoggingForm->setStyleSheet(QLatin1String("QWidget\n"
"{\n"
"    color: #e1e1e1;\n"
"    background-color: #323232;\n"
"}\n"
"\n"
"QWidget:item:hover\n"
"{\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #ca0619);\n"
"    color: #000;\n"
"}\n"
"\n"
"QWidget:item:selected\n"
"{\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #d7801a);\n"
"}\n"
"\n"
"QWidget:disabled\n"
"{\n"
"    color: #404040;\n"
"    background-color: #323232;\n"
"}\n"
"\n"
"QPushButton\n"
"{\n"
"    color: #b1b1b1;\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #565656, stop: 0.1 #525252, stop: 0.5 #4e4e4e, stop: 0.9 #4a4a4a, stop: 1 #464646);\n"
"    border-width: 1px;\n"
"    border-color: #1e1e1e;\n"
"    border-style: solid;\n"
"    border-radius: 6;\n"
"    padding: 3px;\n"
"    font-size: 12px;\n"
"    padding-left: 5px;\n"
"    padding-right: 5px;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0,"
                        " y2: 1, stop: 0 #2d2d2d, stop: 0.1 #2b2b2b, stop: 0.5 #292929, stop: 0.9 #282828, stop: 1 #252525);\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"    border: 2px solid QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #d7801a);\n"
"}\n"
"\n"
"QLineEdit\n"
"{\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #4d4d4d, stop: 0 #646464, stop: 1 #5d5d5d);\n"
"    padding: 1px;\n"
"    border-style: solid;\n"
"    border: 1px solid #1e1e1e;\n"
"}\n"
"\n"
"QLabel\n"
"{\n"
"	Font-size: 14px;\n"
"}\n"
""));
        LoggingForm->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        LoggingForm->setModal(true);
        connectButton = new QPushButton(LoggingForm);
        connectButton->setObjectName(QStringLiteral("connectButton"));
        connectButton->setEnabled(false);
        connectButton->setGeometry(QRect(160, 160, 75, 23));
        widget = new QWidget(LoggingForm);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 10, 381, 151));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        loginLabel = new QLabel(widget);
        loginLabel->setObjectName(QStringLiteral("loginLabel"));

        gridLayout->addWidget(loginLabel, 0, 0, 1, 1);

        loginLineEdit = new QLineEdit(widget);
        loginLineEdit->setObjectName(QStringLiteral("loginLineEdit"));

        gridLayout->addWidget(loginLineEdit, 0, 1, 1, 1);

        passwordLabel = new QLabel(widget);
        passwordLabel->setObjectName(QStringLiteral("passwordLabel"));

        gridLayout->addWidget(passwordLabel, 1, 0, 1, 1);

        passwordLineEdit = new QLineEdit(widget);
        passwordLineEdit->setObjectName(QStringLiteral("passwordLineEdit"));

        gridLayout->addWidget(passwordLineEdit, 1, 1, 1, 1);

        addressLabel = new QLabel(widget);
        addressLabel->setObjectName(QStringLiteral("addressLabel"));

        gridLayout->addWidget(addressLabel, 2, 0, 1, 1);

        addressLineEdit = new QLineEdit(widget);
        addressLineEdit->setObjectName(QStringLiteral("addressLineEdit"));

        gridLayout->addWidget(addressLineEdit, 2, 1, 1, 1);


        retranslateUi(LoggingForm);

        QMetaObject::connectSlotsByName(LoggingForm);
    } // setupUi

    void retranslateUi(QDialog *LoggingForm)
    {
        LoggingForm->setWindowTitle(QApplication::translate("LoggingForm", "Logging Window", Q_NULLPTR));
        connectButton->setText(QApplication::translate("LoggingForm", "&Connect", Q_NULLPTR));
        loginLabel->setText(QApplication::translate("LoggingForm", "Login", Q_NULLPTR));
        passwordLabel->setText(QApplication::translate("LoggingForm", "Password", Q_NULLPTR));
        addressLabel->setText(QApplication::translate("LoggingForm", "Address", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LoggingForm: public Ui_LoggingForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGGINGFORM_H
