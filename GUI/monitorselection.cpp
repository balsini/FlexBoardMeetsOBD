#include "monitorselection.h"
#include "mainwindow.h"

MonitorSelection::MonitorSelection(Vehicle * vehicle, QWidget * parent, Qt::WindowFlags f)
    : QWidget(parent, f)
{
    QCheckBox * checkBox;

    this->vehicle = vehicle;

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

    checkBox = new QCheckBox("&Water Temperature",this);
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
    QList<QAbstractButton *> buttonList = buttonGroup.buttons();

    vehicle->clearBitmask();
    for (unsigned int i=0; !buttonList.isEmpty(); i++) {
        if (buttonList.takeFirst()->isChecked())
            vehicle->setBitmaskBit(i);
    }

    this->hide();
    ((MainWindow *)this->parent())->updateMonitorsSlot();
}

void MonitorSelection::cancelSlot()
{
    this->hide();
}
