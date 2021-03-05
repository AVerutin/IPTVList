#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "playlist.h"
#include "channel.h"
#include "parser.h"
#include "database.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    // Элементы главного окна приложения
    QWidget *mainWindget;
    QVBoxLayout *mainLayout;
    QMenuBar *mainMenu;
    QStatusBar *statBar;
    QTableView *tvChannels;
    QStandardItemModel *model;
    Database *sdb;
    Parser *parser;

    // Элементы главного меню
    QMenu *mFile;
    QMenu *mChannel;
    QAction *aImportChannels;
    QAction *aExportChannels;
    QAction *aAddChannel;
    QAction *aEditChannel;
    QAction *aRemoveChannel;
    QAction *aCloseApplication;

    // Методы класса
    void createMenu();      // Создать главное меню приложения
    void createWidget();    // Создать главную форму приложения
    void showChannels();    // Вывести список каналов из базы данных

private slots:
    void slotImportChannels();  // Импорт каналов из списка
    void slotExportChannels();  // Экспорт каналов в список
    void slotAddChannel();      // Добавить новый канал
    void slotEditChannel();     // Правка выделенного канала
    void slotRemoveChannel();   // Удалить выделенный канал
    void slotAppClose();
};

#endif // MAINWINDOW_H
