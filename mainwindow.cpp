#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    sdb = new Database();

    createMenu();
    createWidget();
    showChannels();
}

MainWindow::~MainWindow()
{
    sdb->dbClose();
}


/// Создание главной формы приложения
void MainWindow::createWidget()
{
    tvChannels = new QTableView(this);
    model = new QStandardItemModel(this);
    tvChannels->setModel(model);

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


/// Вывести список каналов из базы данных
void MainWindow::showChannels()
{
    QList<ChannelInfo> channels = sdb->getChannelsList();
    model->clear();

    for(int i=0; i<channels.count(); i++)
    {
        QList<QStandardItem *> items;
        items.append(new QStandardItem(QString::number(channels[i].id)));
        items.append(new QStandardItem(channels[i].name));
        items.append(new QStandardItem(channels[i].groupName));
        items.append(new QStandardItem(channels[i].url));

        model->appendRow(items);
    }

    model->setHorizontalHeaderLabels(QStringList() <<"№" << "Имя" << "Группа" << "Источник");
    // tvChannels->resizeColumnToContents(0);
    // tvChannels->resizeColumnToContents(1);
    // tvChannels->resizeColumnToContents(2);
    tvChannels->setColumnWidth(0, 25);
    tvChannels->setColumnWidth(1, 100);
    tvChannels->setColumnWidth(2, 120);
    tvChannels->setColumnWidth(3, 245);
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
/// Импорт каналов из файла
void MainWindow::slotImportChannels()
{
    QString listFileName = QFileDialog::getOpenFileName(this,
                                QString(tr("Открыть список воспроизведения")),
                                QDir::currentPath(),
                                tr("Списки воспроизведения (*.m3u *.m3u8);;Все файла (*.*)"));

    // Пользователь отменил открытие файла
    if(listFileName.isEmpty())
      return;

    QString msg = tr("Читаем файл [%1]...");
    msg = msg.arg(listFileName);
    statBar->showMessage(msg);

    // Получаем список каналов из списка
    parser = new Parser(listFileName);
    Playlist playlist = parser->parse();
    QList<Channel> channels = playlist.getChannelsList();
    msg = "Получено каналов: %1. Сохраняем в БД...";
    msg = msg.arg(channels.count());
    statBar->showMessage(msg);

    // Получаем список групп из базы данных
    QList<Group> groups = sdb->getGroups();

    // Получаем список звуковых дорожек из базы данных
    QList<Soundtrack> tracks = sdb->getTracks();

    // Сохранить полученный список каналов в базу данных
    QList<Channel> saved = sdb->addChannels(channels);

    msg = "Сохранено каналов: %1";
    statBar->showMessage(msg);
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
