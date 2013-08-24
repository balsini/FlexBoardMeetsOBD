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

class MonitorSelection : public QWidget
{
    Q_OBJECT

    QHBoxLayout hLayout;
    QVBoxLayout vLayout;
    QButtonGroup buttonGroup;

    QDialogButtonBox buttons;

private slots:
    void okSlot();
    void cancelSlot();

public:
    MonitorSelection(QWidget *parent = 0, Qt::WindowFlags f = 0);
};

#endif // MONITORSELECTION_H
