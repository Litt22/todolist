#include "/mainwindow.h"
//#include "ui_mainwindow.h"



#include <QLabel>
#include <QToolBar>
#include <QBoxLayout>
#include <QtGui>
#include <QMessageBox>
#include <QList>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QPixmap>

CToDoList::CToDoList()
{

    QWidget* pWidget = new QWidget(this);
    pWidget->setStyleSheet("background-color: #ECF0F1");
    setCentralWidget(pWidget);

    QVBoxLayout* pMainLayout = new QVBoxLayout();
    pWidget->setLayout(pMainLayout);

    QLabel* pwTitle = new QLabel("To Do List", this);
    pMainLayout->addWidget(pwTitle);
    pwTitle->setAlignment(Qt::AlignCenter);
    pwTitle->setStyleSheet("font-size: 30pt; margin: 10%;");

    QHBoxLayout* pHLayoutLabels = new QHBoxLayout();
    pMainLayout->addLayout(pHLayoutLabels);

    QLabel* plblPending = new QLabel("В процессе:", this);
    plblPending->setStyleSheet("font-size: 15pt;");
    pHLayoutLabels->addWidget(plblPending);

    QLabel* plblCompleted = new QLabel("Готово:", this);
    plblCompleted->setStyleSheet("font-size: 15pt;");
    pHLayoutLabels->addWidget(plblCompleted);

    QHBoxLayout* pHLayout = new QHBoxLayout();
    pMainLayout->addLayout(pHLayout);

    m_pwPending = new QListView(this);
    m_pwPending->setDragEnabled(true);
    m_pwPending->setAcceptDrops(true);
    m_pwPending->setDropIndicatorShown(true);
    m_pwPending->setDefaultDropAction(Qt::MoveAction);
    pHLayout->addWidget(m_pwPending);

    m_pwCompleted = new QListView(this);
    m_pwCompleted->setDragEnabled(true);
    m_pwCompleted->setAcceptDrops(true);
    m_pwCompleted->setDropIndicatorShown(true);
    m_pwCompleted->setDefaultDropAction(Qt::MoveAction);
    pHLayout->addWidget(m_pwCompleted);

    m_pwPending->setModel(new QStringListModel());
    m_pwCompleted->setModel(new QStringListModel());

    m_pwPending->setStyleSheet
        ("QListView { font-size: 20pt; font-weight: bold; }"
         "QListView::item { background-color: #E74C3C; padding: 10%;"
         "border: 2px solid #C0392B; }"
         "QListView::item::hover { background-color: #C0392B }");

    m_pwCompleted->setStyleSheet
        ("QListView { font-size: 20pt; font-weight: bold; }"
         "QListView::item { background-color: #2ECC71; padding: 10%;"
         "border: 2px solid #27AE60; }"
         "QListView::item::hover { background-color: #27AE60 }");


    QToolBar* pToolBar = new QToolBar(this);
    addToolBar(pToolBar);

    m_pActAdd = new QAction(this);
    m_pActAdd->setIcon(QIcon(":/plus.png"));
    connect(m_pActAdd, &QAction::triggered, this, &CToDoList::onAdd);

    m_pActRemove = new QAction(this);
    m_pActRemove->setIcon(QIcon(":/remove.png"));
    connect(m_pActRemove, &QAction::triggered, this, &CToDoList::onRemove);


    m_pSave = new QAction(this);
    m_pSave->setIcon(QIcon(":/diskette.png"));
    connect(m_pSave, &QAction::triggered, this, &CToDoList::SaveToFile);

    m_pLoad = new QAction(this);
    m_pLoad->setIcon(QIcon(":/inbox.png"));



    connect(m_pLoad, &QAction::triggered, this, &CToDoList::loadFromFile);
    connect(m_pLoad, &QAction::triggered, this, &CToDoList::loadFromFile2);


    pToolBar->addAction(m_pActAdd);
    pToolBar->addAction(m_pActRemove);
    pToolBar->addAction(m_pSave);
    pToolBar->addAction(m_pLoad);

}





 void CToDoList::loadFromFile() {

     // Открываем файл для чтения

     const QString &filePath = "C:/todolist/release/notes.txt";
     QFile file(filePath);

     if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
         QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл для чтения.");
         return;
     }

     QTextStream in(&file);
     QString line;

     // Очищаем текущую модель перед загрузкой
     m_pwPending->model()->removeRows(0, m_pwPending->model()->rowCount());

     // Читаем файл построчно и добавляем каждую строку в модель
     while (!in.atEnd()) {
         line = in.readLine().trimmed(); // Читаем строку и удаляем лишние пробелы
         if (!line.isEmpty()) { // Пропускаем пустые строки
             // Код для добавления строки в модель
              // Вызов метода для добавления задачи
             addTaskToModel(line);
         }
     }
     file.close();

 }
 void CToDoList::addTaskToModel(const QString &task) {



     // Здесь вы добавляете строку в вашу модель
     QAbstractItemModel *model = m_pwPending->model();
     int rowCount = model->rowCount();
     model->insertRow(rowCount); // Добавляем новую строку в конец
     QModelIndex index = model->index(rowCount, 0); // Получаем индекс новой строки
     model->setData(index, task); // Устанавливаем текст задачи

 }












void CToDoList::loadFromFile2() {

    // Открываем файл для чтения

    const QString &filePath2 = "C:/todolist/release/notes2.txt";
    QFile file2(filePath2);

    if (!file2.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл для чтения.");
        return;
    }

    QTextStream in2(&file2);
    QString line2;

    // Очищаем текущую модель перед загрузкой
    m_pwCompleted->model()->removeRows(0, m_pwCompleted->model()->rowCount());

    // Читаем файл построчно и добавляем каждую строку в модель
    while (!in2.atEnd()) {
        line2 = in2.readLine().trimmed(); // Читаем строку и удаляем лишние пробелы
        if (!line2.isEmpty()) { // Пропускаем пустые строки
            // Код для добавления строки в модель
            // Вызов метода для добавления задачи
            addTaskToModel2(line2);
        }
    }
    file2.close();
    QMessageBox::information(this, "Загрузка", "Данные успешно загружены из файла.");
    //QMessageBox::information(this, "Загрузка", "Данные успешно загружены из файла.");
}

void CToDoList::addTaskToModel2(const QString &task2) {

    // Здесь вы добавляете строку в вашу модель
    QAbstractItemModel *model2 = m_pwCompleted->model();
    int rowCount2 = model2->rowCount();
    model2->insertRow(rowCount2); // Добавляем новую строку в конец
    QModelIndex index2 = model2->index(rowCount2, 0); // Получаем индекс новой строки
    model2->setData(index2, task2); // Устанавливаем текст задачи

}








void CToDoList::SaveToFile() {

    bool flag1 = false;
    bool flag2 = false;
    // Открываем файл для записи

    QListView* view = m_pwPending;
    const QString &filePath = "C:/todolist/release/notes.txt";
    QFile file(filePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл для записи.");
        return;
    }

    QTextStream out(&file);

    // Получаем модель и количество строк
    auto model = view->model();

    int rowCount = model->rowCount();

    // Проходим по всем строкам модели и записываем данные в файл
    for (int row = 0; row < rowCount; ++row) {
        QModelIndex index = model->index(row, 0); // Первый столбец
        QString task = model->data(index).toString();
        out << task << "\n";  // Записываем строку в файл
    }

    flag1=true;




    //-----------------------------------
    QListView* view2 = m_pwCompleted;
    const QString &filePath2 = "C:/todolist/release/notes2.txt";
    QFile file2(filePath2);

    if (!file2.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл для записи.");
        return;
    }

    QTextStream out2(&file2);

    // Получаем модель и количество строк
    auto model2 = view2->model();

    int rowCount2 = model2->rowCount();

    // Проходим по всем строкам модели и записываем данные в файл
    for (int row2 = 0; row2 < rowCount2; ++row2) {
        QModelIndex index2 = model2->index(row2, 0); // Первый столбец
        QString task2 = model2->data(index2).toString();
        out2 << task2 << "\n";  // Записываем строку в файл
    }

    flag2 = true;



    //------------------------------------

    if(flag1==true && flag2==true){

        file.close();
        file2.close(); // Закрываем файл
        QMessageBox::information(this, "Сохранение", "Данные успешно сохранены в файл.");
    }





}




void CToDoList::onAdd()
{
    m_pwPending->model()->insertRow(m_pwPending->model()->rowCount());
    QModelIndex oIndex = m_pwPending->model()->index(
        m_pwPending->model()->rowCount() - 1, 0);

    m_pwPending->edit(oIndex);



}

void CToDoList::onRemove()
{
    QModelIndex oIndex = m_pwPending->currentIndex();
    m_pwPending->model()->removeRow(oIndex.row());
}


