#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QTextBrowser;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event);

private:
    void createActions();
    void createMenus();
    void createCentralWidget();

    void loadFile(const QString& fileName);

private slots:
    //
    // File nemu
    //
    void open();

    void writeSettings();
    void readSettings();

private:
    //
    // File menu
    //
    QAction* openAction_;
    QMenu* fileMenu_;

    //
    // Central widget
    //
    QTextBrowser* contentBoard_;

private:
    QString packFileName_;
    
};

#endif // MAINWINDOW_H
