/**
 * @file    serialconfiguration.h
 * @author  Alessio Balsini <alessio.balsini@gmail.com>
 * @version 1.0
 *
 * @section DESCRIPTION
 *
 * Serial configuration parameters window.
 */

#ifndef SERIALCONFIGURATION_H
#define SERIALCONFIGURATION_H

#include <QDebug>

#include <QWidget>

#include <QAction>
#include <QLayout>
#include <QLabel>
#include <QPixmap>
#include <QApplication>
#include <QDesktopWidget>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QSpacerItem>
#include <QDir>

#include "serial.h"

/**
 * The SerialConfiguration class creates a window
 * for managing the serial port parameters.
 */

class SerialConfiguration : public QWidget
{
    Q_OBJECT

    QStringList ttyFilesList;
    QWidget * serialConfigWidget;

    QSpacerItem * serialSpacer;
    QVBoxLayout * serialDeviceLayout;
    QLabel * serialDeviceLabel;
    QComboBox * serialDevice;

    QSpacerItem * baudRateSpacer;
    QVBoxLayout * baudRateLayout;
    QLabel * baudRateLabel;
    QComboBox * baudRate;

    QSpacerItem * paritySpacer;
    QVBoxLayout * parityLayout;
    QLabel * parityLabel;
    QComboBox * parity;

    QSpacerItem * bitsSpacer;
    QVBoxLayout * bitsLayout;
    QLabel * bitsLabel;
    QComboBox * bits;

    QSpacerItem * stopBitsSpacer;
    QVBoxLayout * stopBitsLayout;
    QLabel * stopBitsLabel;
    QComboBox * stopBits;

    QHBoxLayout * selectionLayout;
    QHBoxLayout * buttonsLayout;
    QVBoxLayout * mainLayout;
    QDialogButtonBox * buttons;
    QPushButton * serialDeviceRefreshButton;

    Serial * serial;

    /**
     * Initializes window contents variables.
     */

    void initVariables();

    /**
     * Creates window contents.
     */

    void createWidget();

private slots:

    /**
     * User requested to refresh the devices list.
     */

    void refreshDevicesSlot();

    /**
     * User pushed OK button, so serial parameters
     * chosen are saved.
     */

    void okSlot();

    /**
     * User pushed CANCEL button, so any modification
     * is discarded.
     */

    void cancelSlot();

public:

    /**
     * SerialConfiguration constructor.
     * @param serial Serial device to which the configuration
     * will be sent.
     * @param parent The parent widget.
     * @param f The window flags.
     */

    SerialConfiguration(Serial * serial, QWidget *parent = 0, Qt::WindowFlags f = 0);
};

#endif // SERIALCONFIGURATION_H
