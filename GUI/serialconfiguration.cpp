#include "serialconfiguration.h"

SerialConfiguration::SerialConfiguration(Serial * serial, QWidget *parent, Qt::WindowFlags f)
    : QWidget(parent, f)
{
    this->serial = serial;

    initVariables();
    createWidget();

    mainLayout->addLayout(selectionLayout);
    mainLayout->addLayout(buttonsLayout);
    setLayout(mainLayout);

    this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center());
}

void SerialConfiguration::createWidget()
{
    setWindowTitle(tr("Serial port configuration"));

    serialDeviceLabel->setText(tr("Serial Device"));

    // Generating list of serial communication devices

    refreshDevicesSlot();

    serialDeviceRefreshButton->setText(tr("&Refresh"));

    connect(serialDeviceRefreshButton,
            SIGNAL(released()),
            this,
            SLOT(refreshDevicesSlot()));

    serialDeviceLayout->addWidget(serialDeviceLabel);
    serialDeviceLayout->addWidget(serialDevice);
    serialDeviceLayout->addWidget(serialDeviceRefreshButton);
    serialDeviceLayout->addSpacerItem(serialSpacer);

    baudRateLabel->setText(tr("Baud Rate"));
    baudRate->addItem(tr("300"));
    baudRate->addItem(tr("600"));
    baudRate->addItem(tr("1200"));
    baudRate->addItem(tr("2400"));
    baudRate->addItem(tr("4800"));
    baudRate->addItem(tr("9600"));
    baudRate->addItem(tr("19200"));
    baudRate->addItem(tr("38400"));
    baudRate->addItem(tr("57600"));
    baudRate->addItem(tr("115200"));
    baudRate->setCurrentIndex(5);

    baudRateLayout->addWidget(baudRateLabel);
    baudRateLayout->addWidget(baudRate);
    baudRateLayout->addSpacerItem(baudRateSpacer);

    parityLabel->setText(tr("Parity"));
    parity->addItem(tr("none"));
    parity->addItem(tr("odd"));
    parity->addItem(tr("even"));

    parityLayout->addWidget(parityLabel);
    parityLayout->addWidget(parity);
    parityLayout->addSpacerItem(paritySpacer);

    bitsLabel->setText(tr("Bits"));
    bits->addItem(tr("8"));
    bits->addItem(tr("7"));
    bits->addItem(tr("6"));
    bits->addItem(tr("5"));

    bitsLayout->addWidget(bitsLabel);
    bitsLayout->addWidget(bits);
    bitsLayout->addSpacerItem(bitsSpacer);

    stopBitsLabel->setText(tr("Stopbits"));
    stopBits->addItem(tr("1"));
    stopBits->addItem(tr("2"));

    stopBitsLayout->addWidget(stopBitsLabel);
    stopBitsLayout->addWidget(stopBits);
    stopBitsLayout->addSpacerItem(stopBitsSpacer);

    buttons->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttons, SIGNAL(accepted()), this, SLOT(okSlot()));
    connect(buttons, SIGNAL(rejected()), this, SLOT(cancelSlot()));


    selectionLayout->addLayout(serialDeviceLayout);
    selectionLayout->addLayout(baudRateLayout);
    selectionLayout->addLayout(parityLayout);
    selectionLayout->addLayout(bitsLayout);
    selectionLayout->addLayout(stopBitsLayout);

    buttonsLayout->addWidget(buttons);
}

void SerialConfiguration::initVariables()
{
    serialSpacer = new QSpacerItem(0,0,QSizePolicy::Minimum,QSizePolicy::MinimumExpanding);
    serialDeviceLayout = new QVBoxLayout();
    serialDeviceLabel = new QLabel(this);
    serialDevice = new QComboBox(this);

    baudRateSpacer = new QSpacerItem(0,0,QSizePolicy::Minimum,QSizePolicy::MinimumExpanding);
    baudRateLayout = new QVBoxLayout();
    baudRateLabel = new QLabel(this);
    baudRate = new QComboBox(this);

    paritySpacer = new QSpacerItem(0,0,QSizePolicy::Minimum,QSizePolicy::MinimumExpanding);
    parityLayout = new QVBoxLayout();
    parityLabel = new QLabel(this);
    parity = new QComboBox(this);

    bitsSpacer = new QSpacerItem(0,0,QSizePolicy::Minimum,QSizePolicy::MinimumExpanding);
    bitsLayout = new QVBoxLayout();
    bitsLabel = new QLabel(this);
    bits = new QComboBox(this);

    stopBitsSpacer = new QSpacerItem(0,0,QSizePolicy::Minimum,QSizePolicy::MinimumExpanding);
    stopBitsLayout = new QVBoxLayout();
    stopBitsLabel = new QLabel(this);
    stopBits = new QComboBox(this);

    selectionLayout = new QHBoxLayout();
    buttonsLayout = new QHBoxLayout();
    mainLayout = new QVBoxLayout();
    buttons = new QDialogButtonBox(this);
    serialDeviceRefreshButton = new QPushButton(this);
}

void SerialConfiguration::refreshDevicesSlot()
{
    serialDevice->clear();
    ttyFilesList = serial->getDevices();
    while (!ttyFilesList.isEmpty())
        serialDevice->addItem(ttyFilesList.takeFirst());
}

void SerialConfiguration::okSlot()
{
    Serial_t config;

    config.baud_rate = baudRate->currentText().toUInt();
    config.bits = bits->currentText().toUInt();
    config.device = serialDevice->currentText().toStdString();
    config.parity = parity->currentText().toUInt();
    config.stop_bits = stopBits->currentText().toUInt();

    serial->setConfig(config);

    this->hide();
}

void SerialConfiguration::cancelSlot()
{
    this->hide();
}

