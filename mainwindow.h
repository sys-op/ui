#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
    Ui::MainWindow *ui;

    bool writeSettings();
    bool readSettings();

    bool writeQSettings();
    bool readQSettings();

    bool writeJSONSettings();
    bool readJSONSettings();
};
#endif // MAINWINDOW_H
