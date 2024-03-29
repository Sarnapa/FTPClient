#include "LoggingForm.h"
#include "ui_LoggingForm.h"

LoggingForm::LoggingForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoggingForm)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);

    ui->loginLineEdit->setMaxLength(32);
    ui->passwordLineEdit->setMaxLength(32);
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
    QString oIpRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
    QRegExp oIpRegex ("^" + oIpRange
                  + "\\." + oIpRange
                  + "\\." + oIpRange
                  + "\\." + oIpRange + "$");
    ui->addressLineEdit->setValidator(new QRegExpValidator(oIpRegex));

    connect(ui->loginLineEdit,SIGNAL(textChanged(const QString &)) ,this ,SLOT(activateConnectButton()));
    connect(ui->passwordLineEdit,SIGNAL(textChanged(const QString &)) ,this ,SLOT(activateConnectButton()));
    connect(ui->addressLineEdit,SIGNAL(textChanged(const QString &)) ,this ,SLOT(activateConnectButton()));
}

LoggingForm::~LoggingForm()
{
    delete ui;
}

void LoggingForm::on_connectButton_clicked()
{
    QString &login = ui->loginLineEdit->text();
    QString &password = ui->passwordLineEdit->text();
    QString &address = ui->addressLineEdit->text();
    setEnabled(false);
    emit connectSignal(login, password, address);
}

void LoggingForm::activateConnectButton()
{
    if(ui->loginLineEdit->text().isEmpty() || ui->passwordLineEdit->text().isEmpty() || !ui->addressLineEdit->hasAcceptableInput())
        ui->connectButton->setEnabled(false);
    else ui->connectButton->setEnabled(true);
}
