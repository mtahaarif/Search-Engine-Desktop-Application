#include "gui2.h"
#include "ui_gui2.h"

gui2::gui2(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::gui2)
{
    ui->setupUi(this);
}

gui2::~gui2()
{
    delete ui;
}
