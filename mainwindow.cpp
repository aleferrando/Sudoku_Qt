#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    row = 0;
    col = 0;
    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            /* Nella documentazione Qt viene scritto che "The table takes ownership of the item".
            Ciò mi fa presupporre che questa operazione non generi Memory Leaks */
            ui->grid->setItem(i,j, new QTableWidgetItem);

            QString str = "";
            const QString cstr = str;

            ui->grid->item(i, j)->setText(cstr);
            ui->label->setText("SUDOKU");

            if(i < 3 && j < 3)                              // primo quadrante
                ui->grid->item(i,j)->setBackground(Qt::lightGray);
            if(i < 3 && j > 5)                              // secondo quadrante
                ui->grid->item(i,j)->setBackground(Qt::lightGray);
            if(i > 5 && j < 3)                              // terzo quadrante
                ui->grid->item(i,j)->setBackground(Qt::lightGray);
            if(i > 5 && j > 5)                              // Ultimo quadrante
                ui->grid->item(i,j)->setBackground(Qt::lightGray);
            if(i > 2 && i < 6 && j > 2 && j < 6)            // quadrante centrale
                ui->grid->item(i,j)->setBackground(Qt::lightGray);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;

}

// Struttura dati di appoggio.
QVector<QVector<int>> sudoku(9, QVector<int>(9, 0));

// Metodo che cerca se nella colonna data c'è il numero dato. ( T se c'è, F altrimenti )
bool MainWindow::checkCol(int col1, int num){
   for (int r = 0; r < 9; r++){
       if(sudoku[r][col1] == num)
         return true;
   }
  return false;
}

// Metodo che cerca se nella riga data c'è il numero dato. ( T se c'è, F altrimenti )
bool MainWindow::checkRow(int row1, int num){
   for (int c = 0; c < 9; c++){
      if(sudoku[row1][c] == num)
         return true;
   }
  return false;
}

// Metodo che cerca se nel quadrante (box) c'è il numero dato. ( T se c'è, F altrimenti )
bool MainWindow::checkBox(int boxStartRow, int boxStartCol, int num){
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            if(sudoku[r + boxStartRow][c + boxStartCol] == num){
                return true;
            }
        }
    }
    return false;
}


// Metodo che valuta se la cella è valida per il numero dato. ( T se valida, F altrimenti )
bool MainWindow::isValidCell(int row1, int col1, int num1){
    if(checkCol(col1,num1) == false && checkRow(row1,num1) == false && checkBox(row1 - row1%3 ,col1 - col1%3, num1) == false){
        return true;
    }
   return false;
}

// Metodo di supporto per riempire la struttura dati di appoggio con i valori inseriti dall'utente nella grid.
void MainWindow::fillVector(){
    for(int i = 0; i < 9; i++){
            for(int j = 0; j < 9; j++){
                QTableWidgetItem *cell = ui->grid->item(i,j);
                if(cell->text() == ""){
                    sudoku[i][j] = 0;
                }
                else sudoku[i][j] = cell->text().toInt();
             }
         }
}
/*
bool MainWindow::improveSolve(){

        for (int i = 0; i < 9; i++) {
           for (int j = 0; j < 9; j++) {
              if(sudoku[i][j] != 0){
                   if(isValidCell(i,j,sudoku[i][j]) == false){
                         return false;
                  }
           }
        }
     }
    return true;
}*/

// Metodo con l'algoritmo di Backtracking ricorsivo per la risoluzione del Sudoku.
bool MainWindow::solveSudoku(int row1, int col1){

    // Se sei arrivato all'ultima cella, hai finito e ritona true.
    if(row1 == 8 && col1 == 9) {
        return true;
    }

    // Se sei arrivato all'ultima colonna ma non all'ultima riga, vai alla riga successiva.
    if (col1 == 9) {
        row1++;
        col1 = 0;
    }

    // Se la cella è occupata, cerca ricorsivamente la prossima cella libera.
    if(sudoku[row1][col1] != 0) {
        return solveSudoku(row1,col1 + 1);
      }

    // Se la cella è occupata, cerca ricorsivamente la prossima cella libera.
    if(sudoku[row1][col1] != 0) {
        return solveSudoku(row1,col1 + 1);
      }

    // Prova tutti i numeri possibili ( 1 - 9 )
    for(int num = 1; num <= 9; num++){
            if(isValidCell(row1, col1, num)) { // Se il numero è valido inseriscilo nella cella.
                 sudoku[row1][col1] = num;
            if(solveSudoku(row1,col1 + 1)) // Ricorsivamente prova la cella successiva.
                return true;
            }
            sudoku[row1][col1] = 0; // Se sei arrivato qui, il numero non andava bene, risettalo a 0.
        }
    return false; // Se arrivi in fondo, nessuna scelta precedente andava bene per risolvere il Sudoku, quindi ritorna che è impossibile risolverlo.
}

// Metodo per gestire l'inserimento di un numero nella cella selezionata.
void MainWindow::manageDigitClicked(int num)
{
    QTableWidgetItem* Cell = ui->grid->item(row, col);
    const QString cstr = QString::number(num);
    Cell->setText(cstr);
    }

// Metodi per quandi selezioni un numero da inserire.
void MainWindow::on_pushButton_1_clicked()
{
manageDigitClicked(1);
}

void MainWindow::on_pushButton_2_clicked()
{
manageDigitClicked(2);
}

void MainWindow::on_pushButton_3_clicked()
{
manageDigitClicked(3);
}

void MainWindow::on_pushButton_4_clicked()
{
manageDigitClicked(4);
}

void MainWindow::on_pushButton_5_clicked()
{
manageDigitClicked(5);
}

void MainWindow::on_pushButton_6_clicked()
{
manageDigitClicked(6);
}

void MainWindow::on_pushButton_7_clicked()
{
manageDigitClicked(7);
}

void MainWindow::on_pushButton_8_clicked()
{
manageDigitClicked(8);
}

void MainWindow::on_pushButton_9_clicked()
{
manageDigitClicked(9);
}

// Metodo per indicare quale cella è stata selezionata per inserirci un valore.
void MainWindow::on_grid_cellClicked(int row1, int column)
{
    row = row1;
    col = column;
}

// Metodo che gestisce la chiamata al reset del gioco. Tutto viene ristabilito alle condizioni di partenza, compresa la struttura dati di appoggio.
void MainWindow::on_reset_clicked()
{

    ui->label->setText("SUDOKU!");
    ui->grid->setEnabled(true);
    for(int i = 0; i < 9; i++){
            for(int j = 0; j < 9; j++){
                ui->grid->setItem(i,j, new QTableWidgetItem);
                sudoku[i][j] = 0;
                if(i < 3 && j < 3)                              // primo quadrante
                    ui->grid->item(i,j)->setBackground(Qt::lightGray);
                if(i < 3 && j > 5)                              // secondo quadrante
                    ui->grid->item(i,j)->setBackground(Qt::lightGray);
                if(i > 5 && j < 3)                              // terzo quadrante
                    ui->grid->item(i,j)->setBackground(Qt::lightGray);
                if(i > 5 && j > 5)                              // Ultimo quadrante
                    ui->grid->item(i,j)->setBackground(Qt::lightGray);
                if(i > 2 && i < 6 && j > 2 && j < 6)            // quadrante centrale
                    ui->grid->item(i,j)->setBackground(Qt::lightGray);
            }
        }
}

// Metodo che gestisce la scelta dell'utente di risolvere il sudoku. Usa la funzione creata prima partendo dall'origine riga = 0, colonna = 0.
void MainWindow::on_resolve_clicked()
{
    fillVector();

    if(solveSudoku(0,0) == false) {
        ui->label->setText("Sudoku Impossibile");
        ui->grid->setEnabled(false);
    }
    else {
        for (int r = 0; r < 9; r++) {
            for (int c = 0; c < 9; c++) {
                QString str = QString::number(sudoku[r][c]);  // Riempe la grid coi valori della struttura dati di appoggio.
                ui->grid->item(r,c)->setText(str);
            }
        }
        ui->label->setText("HAI VINTO !");
    }
}

// Metodo per gestire la scelta dell'utente di vedere la soluzione Step-By-Step. Utilizza i valori nella struttura dati di appoggio.
void MainWindow::on_stepByStep_clicked()
{
    QVector<QVector<bool>> inserted(9, QVector<bool>(9, 0)); // Struttura dati di appoggio secondaria per ricordarsi quali valori sono già stati inseriti.
    fillVector();
    for (int i = 0; i< 9; i++) {
        for (int j = 0; j < 9; j++) {
            if(sudoku[i][j] != 0)
                inserted[i][j] = true;
            else inserted[i][j] = false;
        }
    }
    if(solveSudoku(0,0) == false){
        ui->grid->setEnabled(false);
        ui->label->setText("Sudoku Impossibile");
    }
    else {
        for (int r = 0; r < 9; r++) {
            for (int c = 0; c < 9; c++) {
                if(inserted[r][c] == false){
                     QString str = QString::number(sudoku[r][c]);
                     ui->grid->item(r,c)->setText(str);
                     return;
                }
            }
        }
    }
}
