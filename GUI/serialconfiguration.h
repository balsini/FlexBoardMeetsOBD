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

    void initVariables();
    void createWidget();

private slots:
    void refreshDevicesSlot();
    void okSlot();
    void cancelSlot();

public:
    SerialConfiguration(Serial * serial, QWidget *parent = 0, Qt::WindowFlags f = 0);
};

#endif // SERIALCONFIGURATION_H
