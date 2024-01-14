#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

#include "poker.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnPlay_clicked();

    void on_compare_clicked();

private:
    Ui::MainWindow *ui;

    QLabel* label[9];
    QList<Card> curCards;
};
#endif // MAINWINDOW_H
