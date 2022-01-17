#include "avinfodialog.hpp"
#include "ui_avinfodialog.h"

AvInfoDialog::AvInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AvInfoDialog)
{
    ui->setupUi(this);
}

AvInfoDialog::~AvInfoDialog()
{
    delete ui;
}
