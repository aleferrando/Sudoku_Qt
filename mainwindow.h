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
    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_grid_cellClicked(int row, int column);

    void on_reset_clicked();

    void on_resolve_clicked();

    void on_stepByStep_clicked();

private:
    Ui::MainWindow *ui;
    void manageDigitClicked(int num);
    bool checkCol(int col, int num);
    bool checkRow(int col1, int num);
    bool checkBox(int boxStartRow, int boxStartCol, int num);
    bool isValidCell(int row1, int col1, int num);
    void fillVector();
    //bool improveSolve();
    bool solveSudoku(int row1, int col1);
    int row;
    int col;
};
#endif // MAINWINDOW_H
