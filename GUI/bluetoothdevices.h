/**
 * @file    bluetoothdevices.h
 * @author  Alessio Balsini <alessio.balsini@gmail.com>
 * @version 1.0
 *
 * @section DESCRIPTION
 *
 * The window that shows the inquiry resulst and
 * allows the user to choose the one to which
 * the connection will be estabilished.
 */

#ifndef BLUETOOTHDEVICES_H
#define BLUETOOTHDEVICES_H

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QButtonGroup>
#include <QDialogButtonBox>
#include <QApplication>
#include <QDesktopWidget>

/**
 * Inquiry results contain
 *
 * [Bluetooth Address], [Device name], [Device class code]
 *
 * so this data is stored using this structure.
 */

typedef struct inquiry_result_t_ {
    char addr[13];
    char name[17];
    char cod[7];
} inquiry_result_t;

/**
 * The BluetoothDevices class, which creates the
 * window that shows the inquiry resulst and
 * allows the user to choose the one to which
 * the connection will be estabilished.
 */

class BluetoothDevices : public QWidget
{
    Q_OBJECT

    QHBoxLayout hLayout;
    QVBoxLayout vLayout;
    QButtonGroup buttonGroup;

    QDialogButtonBox buttons;

private slots:

    /**
     * User pushed OK button, so the connection
     * will be established.
     */

    void okSlot();

    /**
     * User pushed CANCEL button, so the inquiry
     * results are rejected.
     */

    void cancelSlot();

public slots:

    /**
     * Inquiry results are shown to the user.
     * @param devices the list of devices to be shown.
     * @param num the number of devices contained in the list.
     */

    void showBluetoothInquirySlot(inquiry_result_t * devices, unsigned int num);

public:

    /**
     * Class constructor, which generates the window.
     * @param parent The class's parent widget.
     * @param f Window flags.
     */

    BluetoothDevices(QWidget *parent = 0, Qt::WindowFlags f = 0);
};

#endif // BLUETOOTHDEVICES_H
