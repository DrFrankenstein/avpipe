#ifndef AVINFODIALOG_HPP
#define AVINFODIALOG_HPP

#include <QDialog>

namespace Ui {
class AvInfoDialog;
}

class AvInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AvInfoDialog(QWidget *parent = nullptr);
    ~AvInfoDialog();

private:
    Ui::AvInfoDialog *ui;
};

#endif // AVINFODIALOG_HPP
