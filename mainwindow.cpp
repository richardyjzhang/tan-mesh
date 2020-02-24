#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include "tanmeshtoolbasic.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString file = QFileDialog::getOpenFileName(this, "选择输入文件", "", "Inp File (*.inp)");
    if (!file.isNull())
        ui->tb_Input->setText(file);
}

void MainWindow::on_btn_Output_clicked()
{
    QString file = QFileDialog::getSaveFileName(this, "选择输出文件", "", "Inp File (*.inp)");
    if (!file.isNull())
        ui->tb_Output->setText(file);
}

void MainWindow::on_pushButton_2_clicked()
{
    if (ui->tb_Input->text().isNull() || ui->tb_Input->text().isEmpty())
    {
        QMessageBox::critical(this, "参数错误", "应指定输入文件");
        return;
    }
    if (ui->tb_Output->text().isNull() || ui->tb_Output->text().isEmpty())
    {
        QMessageBox::critical(this, "参数错误", "应指定输出文件");
        return;
    }
    bool valid = false;
    double tolerance = ui->tb_Tolerance->text().toDouble(&valid);
    if (!valid)
    {
        QMessageBox::critical(this, "参数错误", "应填入归并精度");
        return;
    }
    double maxLen = ui->tb_MaxLen->text().toDouble(&valid);
    if (!valid)
    {
        QMessageBox::critical(this, "参数错误", "应填入最大边长");
        return;
    }

    TanMeshTool * tool = new TanMeshToolBasic(ui->tb_Input->text(), ui->tb_Output->text(), tolerance, maxLen);
    bool success = tool->mesh();
    delete tool;
    if (success) QMessageBox::information(this, "完成", "网格细化完成");
    else QMessageBox::information(this, "失败", "网格细化失败");
}
