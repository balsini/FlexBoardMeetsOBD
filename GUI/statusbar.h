/**
 * @file    statusbar.h
 * @author  Alessio Balsini <alessio.balsini@gmail.com>
 * @version 1.0
 *
 * @section DESCRIPTION
 *
 * Main window status bar.
 */

#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QStatusBar>
#include <QLabel>

/**
 * @brief The StatusBar class redefines
 * the main window status bar.
 */

class StatusBar : public QStatusBar
{
    Q_OBJECT

    QLabel serialStatusText;
    QLabel serialStatusImg;
    QLabel flexStatusText;
    QLabel flexStatusImg;
    QLabel vehicleStatusText;
    QLabel vehicleStatusImg;

public slots:

    /**
     * It is notified that the serial connection
     * has been established.
     */

    void serialConnectionEstabilished();

    /**
     * It is notified that the serial connection
     * has been lost.
     */

    void serialConnectionLost();

    /**
     * It is notified that the connection to the Flex
     * has been established.
     */

    void flexConnectionEstabilished();

    /**
     * It is notified that the connection to the Flex
     * has been lost.
     */

    void flexConnectionLost();

    /**
     * It is notified that the connection to the vehicle
     * has been established.
     */

    void vehicleConnectionEstabilished();

    /**
     * It is notified that the connection to the vehicle
     * has been lost.
     */

    void vehicleConnectionLost();

public:

    /**
     * StatusBar constructor.
     * @param parent The parent widget.
     */
    StatusBar(QWidget * parent = 0);
};

#endif // STATUSBAR_H
