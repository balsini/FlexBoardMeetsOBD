#include "monitorselection.h"

MonitorSelection::MonitorSelection(QWidget * parent, Qt::WindowFlags f)
    : QWidget(parent, f)
{
    QCheckBox * checkBox;
    this->setWindowTitle("Monitor Selection");

    this->setLayout(&hLayout);

    buttonGroup.setExclusive(false);

    checkBox = new QCheckBox("&RPM",this);
    buttonGroup.addButton(checkBox);
    vLayout.addWidget(checkBox);

    checkBox = new QCheckBox("&Speed",this);
    buttonGroup.addButton(checkBox);
    vLayout.addWidget(checkBox);

    checkBox = new QCheckBox("&Fuel",this);
    buttonGroup.addButton(checkBox);
    vLayout.addWidget(checkBox);

    hLayout.addLayout(&vLayout);

    buttons.setOrientation(Qt::Vertical);
    buttons.setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(&buttons, SIGNAL(accepted()), this, SLOT(okSlot()));
    connect(&buttons, SIGNAL(rejected()), this, SLOT(cancelSlot()));

    hLayout.addWidget(&buttons);

    this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center());
}

void MonitorSelection::okSlot()
{

}

void MonitorSelection::cancelSlot()
{
    this->hide();
}
