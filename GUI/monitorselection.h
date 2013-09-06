/**
 * @file    monitorselection.h
 * @author  Alessio Balsini <alessio.balsini@gmail.com>
 * @version 1.0
 *
 * @section DESCRIPTION
 *
 * The window that allows the user to select which gauge
 * monitors will be shown on the window.
 */

#ifndef MONITORSELECTION_H
#define MONITORSELECTION_H

#include <QWidget>
#include <QApplication>
#include <QDesktopWidget>
#include <QCheckBox>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDialogButtonBox>

#include "vehicle.h"

/**
 * The MonitorSelection class, that allows the user to
 * select which gauge monitors will be shown on the window.
 */

class MonitorSelection : public QWidget
{
    Q_OBJECT

    QHBoxLayout hLayout;
    QVBoxLayout vLayout;
    QButtonGroup buttonGroup;

    QDialogButtonBox buttons;

    Vehicle * vehicle;

private slots:

    /**
     * The user pushed OK, so the monitors will be shown.
     */

    void okSlot();

    /**
     * The user pushed CANCEL, so nothing changes.
     */

    void cancelSlot();

public:

    /**
     * Class constructor.
     * @param vehicle The vehicle to be associated with the monitor.
     * @param parent The parent widget.
     * @param f The window flags.
     */

    MonitorSelection(Vehicle * vehicle, QWidget *parent = 0, Qt::WindowFlags f = 0);
};

#endif // MONITORSELECTION_H
