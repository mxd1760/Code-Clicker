#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include <QMainWindow>


#define START_LINE_PRICE 10
#define START_FUNC_PRICE 400
#define START_CLASS_PRICE 2500
#define START_PACK_PRICE 10000
#define START_API_PRICE 100000
#define PRICE_MUL 1.1

#define LINE_TICKS 1
#define FUNC_TICKS 5
#define CLASS_TICKS 25
#define PACK_TICKS 100
#define API_TICKS 500

// payout ~= ticks*ticks*ticks/2
#define LINE_PAYOUT            1
#define FUNC_PAYOUT           50
#define CLASS_PAYOUT       10000
#define PACK_PAYOUT       500000
#define API_PAYOUT      75000000

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
    void on_LineBuyButton_pressed();

    void on_WorkTickButton_pressed();

    void on_FnBuyButton_pressed();

    void on_ClassBuyButton_pressed();

    void on_PackageBuyButton_pressed();

    void on_ApiBuyButton_pressed();

private:
    Ui::MainWindow *ui;
    double cash;
    int line_cnt;
    int func_cnt;
    int class_cnt;
    int pack_cnt;
    int api_cnt;
    int line_rem;
    int func_rem;
    int class_rem;
    int pack_rem;
    int api_rem;

    void validation();
    void calc_next_tick_cash();

    void update_ticks(){
        ui->LineTicksRemaining->setText(QString::number(line_rem));
        ui->line_PB->setValue(100*line_rem/LINE_TICKS);
        ui->FnTicksRemaining->setText(QString::number(func_rem));
        ui->func_PB->setValue(100*func_rem/FUNC_TICKS);
        ui->ClassTicksRemaining->setText(QString::number(class_rem));
        ui->class_PB->setValue(100*class_rem/CLASS_TICKS);
        ui->PackageTicksRemaining->setText(QString::number(pack_rem));
        ui->pack_PB->setValue(100*pack_rem/PACK_TICKS);
        ui->ApiTicksRemaining->setText(QString::number(api_rem));
        ui->api_PB->setValue(100*api_rem/API_TICKS);
    }
    void update_line_cnt(){
        ui->LineCount->setText(QString::number(line_cnt));
        ui->LineBuyButton->setText(QString::number(line_price));
    }
    void update_func_cnt(){
        ui->FnCount->setText(QString::number(func_cnt));
        ui->FnBuyButton->setText(QString::number(func_price));
    }
    void update_class_cnt(){
        ui->ClassCount->setText(QString::number(class_cnt));
        ui->ClassBuyButton->setText(QString::number(class_price));
    }
    void update_pack_cnt(){
        ui->PackageCount->setText(QString::number(pack_cnt));
        ui->PackageBuyButton->setText(QString::number(pack_price));
    }
    void update_api_cnt(){
        ui->ApiCount->setText(QString::number(api_cnt));
        ui->ApiBuyButton->setText(QString::number(api_price));
    }
    void update_cash(){
        ui->CashCount->setText("Cash: "+QString::number(cash));
    }
public:
    static int line_price;
    static int func_price;
    static int class_price;
    static int pack_price;
    static int api_price;
};
#endif // MAINWINDOW_H
