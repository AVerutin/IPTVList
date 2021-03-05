#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createMenu();
    createWidget();
}

MainWindow::~MainWindow()
{
}


/// Создание главной формы приложения
void MainWindow::createWidget()
{
    tvChannels = new QTableView(this);

    statBar = statusBar();
    statBar->setSizeGripEnabled(false);
    statBar->showMessage("Готово");

    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(tvChannels);
    mainLayout->setContentsMargins(0,0,0,0);

    mainWindget = new QWidget(this);
    mainWindget->setLayout(mainLayout);

    setCentralWidget(mainWindget);
    setFixedSize(750, 550);
    setWindowTitle("База каналов IPTV");
    setWindowIcon(QIcon(":/icons/icon.ico"));
}


/// Создание главного меню приложения
void MainWindow::createMenu()
{
    // Пункт меню Импорт
    aImportChannels = new QAction(this);
    aImportChannels->setText("Импорт каналов");
    aImportChannels->setToolTip("Импортировать список каналов из файла");
    aImportChannels->setStatusTip("Импортировать список каналов из файла");
    aImportChannels->setShortcut(QKeySequence("CTRL+I"));
    connect(aImportChannels, &QAction::triggered, this, &MainWindow::slotImportChannels);

    // Пункт меню Экспорт
    aExportChannels = new QAction(this);
    aExportChannels->setText("Экспорт каналов");
    aExportChannels->setToolTip("Экспортировать каналы в список воспроизведеня");
    aExportChannels->setStatusTip("Экспортировать каналы в список воспроизведеня");
    aExportChannels->setShortcut(QKeySequence("CTRL+E"));
    connect(aExportChannels, &QAction::triggered, this, &MainWindow::slotExportChannels);

    // Пункт меню Выход
    aCloseApplication = new QAction(this);
    aCloseApplication->setText("Закрыть");
    aCloseApplication->setToolTip("Закрыть приложение");
    aCloseApplication->setStatusTip("Закрыть приложение");
    aCloseApplication->setShortcut(QKeySequence("CTRL+Q"));
    connect(aCloseApplication, &QAction::triggered, this, &MainWindow::slotAppClose);

    // Меню Файл
    mFile = new QMenu(this);
    mFile->setTitle("Файл");
    mFile->setStatusTip("Управление списком каналов");
    mFile->setToolTip("Управление списком каналов");
    mFile->addAction(aImportChannels);
    mFile->addAction(aExportChannels);
    mFile->addSeparator();
    mFile->addAction(aCloseApplication);

    // Меню Добавить канал
    aAddChannel = new QAction(this);
    aAddChannel->setText("Добавить");
    aAddChannel->setToolTip("Добавить новый канал");
    aAddChannel->setStatusTip("Добавить новый канал");
    aAddChannel->setShortcut(QKeySequence("CTRL+A"));
    connect(aAddChannel, &QAction::triggered, this, &MainWindow::slotAddChannel);

    // Меню Правка канала
    aEditChannel = new QAction(this);
    aEditChannel->setText("Редактировать");
    aEditChannel->setToolTip("Изменить параметры выделенного канала");
    aEditChannel->setStatusTip("Изменить параметры выделенного канала");
    aEditChannel->setShortcut(QKeySequence("CTRL+D"));
    connect(aEditChannel, &QAction::triggered, this, &MainWindow::slotEditChannel);

    // Меню Удалить канал
    aRemoveChannel = new QAction(this);
    aRemoveChannel->setText("Удалить");
    aRemoveChannel->setToolTip("Удалить выделенный канал");
    aRemoveChannel->setStatusTip("Удалить выделенный канал");
    aRemoveChannel->setShortcut(QKeySequence("CTRL+R"));
    connect(aRemoveChannel, &QAction::triggered, this, &MainWindow::slotRemoveChannel);

    // Меню Канал
    mChannel = new QMenu(this);
    mChannel->setTitle("Канал");
    mChannel->setStatusTip("Управление выделенным каналом");
    mChannel->setToolTip("Управление выделенным каналом");
    mChannel->addAction(aAddChannel);
    mChannel->addAction(aEditChannel);
    mChannel->addAction(aRemoveChannel);

    mainMenu = menuBar();
    mainMenu->addMenu(mFile);
    mainMenu->addMenu(mChannel);
}


/// Реализация слотов
///
/// Импорт каналов из файла
void MainWindow::slotImportChannels()
{
    QMessageBox::information(this, QString(tr("Внимание")),
                                QString(tr("Импорт каналов из списка")),
                                QMessageBox::Ok);
}


/// Экспорт каналов в список
void MainWindow::slotExportChannels()
{
    QMessageBox::information(this, QString(tr("Внимание")),
                                QString(tr("Экспорт каналов в список")),
                                QMessageBox::Ok);
}


/// Добавить новый канал
void MainWindow::slotAddChannel()
{
    QMessageBox::information(this, QString(tr("Внимание")),
                                QString(tr("Добавить канал")),
                                QMessageBox::Ok);
}


/// Редактировать выделенный канал
void MainWindow::slotEditChannel()
{
    QMessageBox::information(this, QString(tr("Внимание")),
                                QString(tr("Править канал")),
                                QMessageBox::Ok);
}


/// Удалить выделенный канал
void MainWindow::slotRemoveChannel()
{
    QMessageBox::information(this, QString(tr("Внимание")),
                                QString(tr("Удалить выбранный канал")),
                                QMessageBox::Ok);
}


/// Завершить работу приложения
void MainWindow::slotAppClose()
{
    close();
}
