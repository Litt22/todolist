#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


#include <QListView>
#include <QStringListModel>

class CToDoList : public QMainWindow
{
    Q_OBJECT
public:
    CToDoList();



protected slots:
    void onAdd();
    void onRemove();
    void SaveToFile();
    void addTaskToModel(const QString &task);
    void addTaskToModel2(const QString &task2);
    void loadFromFile();
    void loadFromFile2();

private:
    QListView* m_pwPending = nullptr;
    QListView* m_pwCompleted = nullptr;

    QAction* m_pActAdd = nullptr;
    QAction* m_pActRemove = nullptr;
    QAction* m_pSave = nullptr;
    QAction* m_pLoad = nullptr;

};


#endif // MAINWINDOW_H
