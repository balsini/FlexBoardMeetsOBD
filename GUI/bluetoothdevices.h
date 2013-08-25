#ifndef BLUETOOTHDEVICES_H
#define BLUETOOTHDEVICES_H

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QButtonGroup>
#include <QDialogButtonBox>
#include <QApplication>
#include <QDesktopWidget>

typedef struct inquiry_result_t_ {
    char addr[13];
    char name[17];
    char cod[7];
} inquiry_result_t;

class BluetoothDevices : public QWidget
{
    Q_OBJECT

    QHBoxLayout hLayout;
    QVBoxLayout vLayout;
    QButtonGroup buttonGroup;

    QDialogButtonBox buttons;

private slots:
    void okSlot();
    void cancelSlot();

public slots:
    void showBluetoothInquirySlot(inquiry_result_t * devices, unsigned int num);

public:
    BluetoothDevices(QWidget *parent = 0, Qt::WindowFlags f = 0);
};

#endif // BLUETOOTHDEVICES_H
