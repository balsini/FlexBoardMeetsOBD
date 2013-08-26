#include "bluetoothdevices.h"
#include "mainwindow.h"

BluetoothDevices::BluetoothDevices(QWidget * parent, Qt::WindowFlags f)
    : QWidget(parent, f)
{
    this->setWindowTitle("Bluetooth Scan Results");

    this->setLayout(&hLayout);

    buttonGroup.setExclusive(true);

    hLayout.addLayout(&vLayout);

    buttons.setOrientation(Qt::Vertical);
    buttons.setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(&buttons, SIGNAL(accepted()), this, SLOT(okSlot()));
    connect(&buttons, SIGNAL(rejected()), this, SLOT(cancelSlot()));

    hLayout.addWidget(&buttons);

    this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center());
}

void BluetoothDevices::okSlot()
{
    QList<QAbstractButton *> buttonList = buttonGroup.buttons();
    bool checked = false;

    for (unsigned int i=0; !buttonList.isEmpty(); i++) {
        if (buttonList.takeFirst()->isChecked()) {
            ((MainWindow *)this->parent())->bluetoothDeviceChosen(i);
            checked = true;
            break;
        }
    }
    if (!checked)
        ((MainWindow *)this->parent())->bluetoothDeviceChosen(-1);

    this->hide();
}

void BluetoothDevices::cancelSlot()
{
    this->hide();
}


void BluetoothDevices::showBluetoothInquirySlot(inquiry_result_t * devices, unsigned int num)
{
    QCheckBox * checkBox;
    QString name;
    buttonGroup.buttons().clear();
    for (unsigned int i=0; i<num; i++) {
        name.clear();
        name.append(devices[i].name);
        name.append(" | ");
        name.append(devices[i].addr);
        name.append(" | ");
        name.append(devices[i].cod);
        checkBox = new QCheckBox(name, this);
        buttonGroup.addButton(checkBox);
        vLayout.addWidget(checkBox);
    }
    this->show();
}
