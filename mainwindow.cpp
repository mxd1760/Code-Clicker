#include "mainwindow.h"
#include "./ui_mainwindow.h"




int MainWindow::line_price = START_LINE_PRICE;
int MainWindow::func_price = START_FUNC_PRICE;
int MainWindow::class_price = START_CLASS_PRICE;
int MainWindow::pack_price = START_PACK_PRICE;
int MainWindow::api_price = START_API_PRICE;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{ 
    ui->setupUi(this);

    line_rem=0;
    func_rem=0;
    class_rem=0;
    pack_rem=0;
    api_rem=0;
    line_cnt=0;
    func_cnt=0;
    class_cnt=0;
    pack_cnt=0;
    api_cnt=0;
    cash=0;

    update_ticks();
    update_line_cnt();
    update_func_cnt();
    update_class_cnt();
    update_pack_cnt();
    update_api_cnt();
    validation();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::validation(){
    bool line_buyable=true;
    bool func_buyable=true;
    bool class_buyable=true;
    bool pack_buyable=true;
    bool api_buyable=true;
    do{
        if(cash>=api_price) break;
        api_buyable=false;
        if(cash>=pack_price) break;
        pack_buyable=false;
        if(cash>=class_price) break;
        class_buyable=false;
        if(cash>=func_price) break;
        func_buyable=false;
        if(cash>=line_price) break;
        line_buyable=false;
    }while(false);
    ui->LineBuyButton->setDisabled(!line_buyable);
    ui->FnBuyButton->setDisabled(!func_buyable);
    ui->ClassBuyButton->setDisabled(!class_buyable);
    ui->PackageBuyButton->setDisabled(!pack_buyable);
    ui->ApiBuyButton->setDisabled(!api_buyable);
    update_cash();
    calc_next_tick_cash();
}

void MainWindow::calc_next_tick_cash(){
    double next_tick_cash = 1;
    if(line_rem==1) next_tick_cash+=LINE_PAYOUT*line_cnt;
    if(func_rem==1) next_tick_cash+=FUNC_PAYOUT*func_cnt;
    if(class_rem==1) next_tick_cash+=CLASS_PAYOUT*class_cnt;
    if(pack_rem==1) next_tick_cash+=PACK_PAYOUT*pack_cnt;
    if(api_rem==1) next_tick_cash+=API_PAYOUT*pack_cnt;

    ui->cashNextClick->setText(QString::number(next_tick_cash));
}

void MainWindow::on_WorkTickButton_pressed()
{
    cash+=1; // baseline pay
    if(line_cnt>=1){
        line_rem-=1;
        if(line_rem<=0){
            cash+=LINE_PAYOUT*line_cnt;
            line_rem=LINE_TICKS;
        }
    }
    if(func_cnt>=1){
        func_rem-=1;
        if(func_rem<=0){
            cash+=FUNC_PAYOUT*func_cnt;
            func_rem=FUNC_TICKS;
        }
    }
    if(class_cnt>=1){
        class_rem-=1;
        if(class_rem<=0){
            cash+=CLASS_PAYOUT*class_cnt;
            class_rem=CLASS_TICKS;
        }
    }
    if(pack_cnt>=1){
        pack_rem-=1;
        if(pack_rem<=0){
            cash+=PACK_PAYOUT*pack_cnt;
            pack_rem=PACK_TICKS;
        }
    }
    if(api_cnt>=1){
        api_rem-=1;
        if(api_rem<=0){
            cash+=API_PAYOUT*api_cnt;
            api_rem=API_TICKS;
        }
    }
    validation();
    update_ticks();
}


void MainWindow::on_LineBuyButton_pressed()
{
    cash-=line_price;
    line_price*=PRICE_MUL;
    line_cnt+=1;
    if(line_cnt==1){
        line_rem=LINE_TICKS;
        update_ticks();
    }
    update_line_cnt();
    validation();
}

void MainWindow::on_FnBuyButton_pressed()
{
    cash-=func_price;
    func_price*=PRICE_MUL;
    func_cnt+=1;
    if(func_cnt==1){
        func_rem=FUNC_TICKS;
        update_ticks();
    }
    update_func_cnt();
    validation();
}


void MainWindow::on_ClassBuyButton_pressed()
{
    cash-=class_price;
    class_price*=PRICE_MUL;
    class_cnt+=1;
    if(class_cnt==1){
        class_rem=CLASS_TICKS;
        update_ticks();
    }
    update_class_cnt();
    validation();
}


void MainWindow::on_PackageBuyButton_pressed()
{
    cash-=pack_price;
    pack_price*=PRICE_MUL;
    pack_cnt+=1;
    if(pack_cnt==1){
        pack_rem=PACK_TICKS;
        update_ticks();
    }
    update_pack_cnt();
    validation();
}


void MainWindow::on_ApiBuyButton_pressed()
{
    cash-=api_price;
    api_price*=PRICE_MUL;
    api_cnt+=1;
    if(api_cnt==1){
        api_rem=API_TICKS;
        update_ticks();
    }
    update_api_cnt();
    validation();
}

