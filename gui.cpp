#include "gui.h"
#include "./ui_gui.h"
#include "mainwindow.h"
#include <QMainWindow>
#include <QFile>
#include <QDir>
#include <QString>
#include <QDebug>
#include <QTextStream>
#include <iostream>
#include <QScrollArea>
#include "searchEngine.h"

using namespace std;

GUI::GUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GUI)
{

    home_page();

}



GUI::~GUI()
{
    delete ui;
}

void GUI::on_pushButton_clicked(){
    home=false;
    L1.clear();
    L2.clear();
    FileData.clear();
    body.clear();
    docsContainingSearchTerm.clear();

    SearchEngine ri;

    sizeChecker=0;
ui->label_6->setVisible(false);
    ri.buildIndexFromFiles(directoryPath);

    cout << "Reverse Index:" << endl;
    ri.printIndex();

    // Retrieve document IDs for a term or prefix
    string searchTerm = ui->textEdit_6->toPlainText().toStdString();
    ui->textEdit_6->setText("");
    cout << "\nDocuments containing '" << searchTerm << "', sorted by frequency count:" << endl;
     docsContainingSearchTerm = ri.getDocumentIDs(searchTerm);
    for (int docID : docsContainingSearchTerm) {


        L2.push_back(filePaths[docID-1]);
        L1.push_back(fileNames[docID-1]);
        cout <<docID-1<<endl;
        FileData.push_back("\n\n\n");
        body.push_back("");
    }
    cout << L2.size() <<endl;
    QString Title;

    for (int j=0;j<L2.size();j++){
        int i=0;
        QFile File(L2[j]);

        if (File.open(QIODevice::ReadOnly)){
            QTextStream stream(&File);

            while(stream.atEnd()==false){
                if (i==0){
                    Title =stream.readLine();
                    FileData[j] =Title;
                    i++;
                }
                else if (i<6){
                    FileData[j]+=stream.readLine();
                    body[j]=FileData[j];
                    i++;
                }

                else
                    FileData[j] += stream.readLine()+"\n";
            }
        }
    }


    switch(docsContainingSearchTerm.size()){
    case 0:
        ui->label_3->setVisible(true);
         ui->label_3->setText("                                                         No Result Found");
        break;

    case 1:
        ui->label->setVisible(true);
        ui->textEdit->setVisible(true);
        ui->label->setText("<a href=Title>"+L1[0]+"</a>");
        ui->textEdit->setFontPointSize(12);
        ui->textEdit->setText(body[0]);
        ui->pushButton_2->setVisible(true);
        break;
    case 2:
        ui->label->setVisible(true);
        ui->textEdit->setVisible(true);
        ui->label_2->setVisible(true);
        ui->textEdit_2->setVisible(true);
        ui->label->setText("<a href=Title>"+L1[0]+"</a>");
        ui->label_2->setText("<a href=Title>"+L1[1]+"</a>");
        ui->textEdit->setFontPointSize(12);
        ui->textEdit->setText(body[0]);
        ui->textEdit_2->setFontPointSize(12);
        ui->textEdit_2->setText(body[1]);
        ui->pushButton_2->setVisible(true);
        break;
    case 3:
        ui->label->setVisible(true);
        ui->textEdit->setVisible(true);
        ui->label_2->setVisible(true);
        ui->textEdit_2->setVisible(true);
        ui->label_3->setVisible(true);
        ui->textEdit_3->setVisible(true);
        ui->label->setText("<a href=Title>"+L1[0]+"</a>");
        ui->label_2->setText("<a href=Title>"+L1[1]+"</a>");
        ui->label_3->setText("<a href=Title>"+L1[2]+"</a>");
        ui->textEdit->setFontPointSize(12);
        ui->textEdit->setText(body[0]);
        ui->textEdit_2->setFontPointSize(12);
        ui->textEdit_2->setText(body[1]);
        ui->textEdit_3->setFontPointSize(12);
        ui->textEdit_3->setText(body[2]);
        ui->pushButton_2->setVisible(true);
        break;
    case 4:
        ui->label->setVisible(true);
        ui->textEdit->setVisible(true);
        ui->label_2->setVisible(true);
        ui->textEdit_2->setVisible(true);
        ui->label_3->setVisible(true);
        ui->textEdit_3->setVisible(true);
        ui->label_4->setVisible(true);
        ui->textEdit_4->setVisible(true);
        ui->label->setText("<a href=Title>"+L1[0]+"</a>");
        ui->label_2->setText("<a href=Title>"+L1[1]+"</a>");
        ui->label_3->setText("<a href=Title>"+L1[2]+"</a>");
        ui->label_4->setText("<a href=Title>"+L1[3]+"</a>");
        ui->textEdit->setFontPointSize(12);
        ui->textEdit->setText(body[0]);
        ui->textEdit_2->setFontPointSize(12);
        ui->textEdit_2->setText(body[1]);
        ui->textEdit_3->setFontPointSize(12);
        ui->textEdit_3->setText(body[2]);
        ui->textEdit_4->setFontPointSize(12);
        ui->textEdit_4->setText(body[3]);
        ui->pushButton_2->setVisible(true);
        break;
    case 5:
        ui->label->setVisible(true);
        ui->textEdit->setVisible(true);
        ui->label_2->setVisible(true);
        ui->textEdit_2->setVisible(true);
        ui->label_3->setVisible(true);
        ui->textEdit_3->setVisible(true);
        ui->label_4->setVisible(true);
        ui->textEdit_4->setVisible(true);
        ui->label_5->setVisible(true);
       // ui->textEdit_5->setVisible(true);
        ui->label->setText("<a href=Title>"+L1[0]+"</a>");
        ui->label_2->setText("<a href=Title>"+L1[1]+"</a>");
        ui->label_3->setText("<a href=Title>"+L1[2]+"</a>");
        ui->label_4->setText("<a href=Title>"+L1[3]+"</a>");
        ui->label_5->setText("<a href=Title>"+L1[4]+"</a>");
        ui->textEdit->setFontPointSize(12);
        ui->textEdit->setText(body[0]);
        ui->textEdit_2->setFontPointSize(12);
        ui->textEdit_2->setText(body[1]);
        ui->textEdit_3->setFontPointSize(12);
        ui->textEdit_3->setText(body[2]);
        ui->textEdit_4->setFontPointSize(12);
        ui->textEdit_4->setText(body[3]);
        ui->pushButton_2->setVisible(true);
        break;

    default:
        ui->label->setVisible(true);
        ui->textEdit->setVisible(true);
        ui->label_2->setVisible(true);
        ui->textEdit_2->setVisible(true);
        ui->label_3->setVisible(true);
        ui->textEdit_3->setVisible(true);
        ui->label_4->setVisible(true);
        ui->textEdit_4->setVisible(true);
        ui->label_5->setVisible(true);
       // ui->textEdit_5->setVisible(true);
        ui->label->setText("<a href=Title>"+L1[0]+"</a>");
        ui->label_2->setText("<a href=Title>"+L1[1]+"</a>");
        ui->label_3->setText("<a href=Title>"+L1[2]+"</a>");
        ui->label_4->setText("<a href=Title>"+L1[3]+"</a>");
        ui->label_5->setText("<a href=Title>"+L1[4]+"</a>");
        ui->textEdit->setFontPointSize(12);
        ui->textEdit->setText(body[0]);
        ui->textEdit_2->setFontPointSize(12);
        ui->textEdit_2->setText(body[1]);
        ui->textEdit_3->setFontPointSize(12);
        ui->textEdit_3->setText(body[2]);
        ui->textEdit_4->setFontPointSize(12);
        ui->textEdit_4->setText(body[3]);
        ui->pushButton_2->setVisible(true);
        ui->pushButton_3->setVisible(true);
        if(docsContainingSearchTerm.size()>10)
            ui->pushButton_4->setVisible(true);
         if(docsContainingSearchTerm.size()>15)
            ui->pushButton_5->setVisible(true);
         if(docsContainingSearchTerm.size()>20)
             ui->pushButton_7->setVisible(true);
         if(docsContainingSearchTerm.size()>25)
             ui->pushButton_8->setVisible(true);
         if(docsContainingSearchTerm.size()>30)
             ui->pushButton_9->setVisible(true);
         if(docsContainingSearchTerm.size()>35)
             ui->pushButton_10->setVisible(true);
         if(docsContainingSearchTerm.size()>40)
             ui->pushButton_11->setVisible(true);
         if(docsContainingSearchTerm.size()>45)
             ui->pushButton_12->setVisible(true);
        break;
    }
    //ri.displayDocumentContent(1, directoryPath);
    ui->pushButton->setVisible(false);
    ui->textEdit_6->setVisible(false);

    cout << endl;

    // Ask the user to select a document
    int selectedDocID{2};

   // cout << "Enter the document ID you want to view: ";


    //ri.displayDocumentContent(selectedDocID, directoryPath);
    if (selectedDocID == 3)
        ri.back();
    if (selectedDocID == 4)
        ri.forward();



}


void GUI::on_label_linkActivated(const QString &link)
{
    ui->label->setVisible(false);
    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    ui->label_5->setVisible(false);
    ui->textEdit->setVisible(false);
    ui->textEdit_2->setVisible(false);
    ui->textEdit_3->setVisible(false);
    ui->textEdit_4->setVisible(false);
    ui->textEdit_6->setVisible(false);
    ui->pushButton->setVisible(false);
    ui->textEdit_7->setVisible(true);
    cout << sizeChecker<<endl;
    if(sizeChecker==0)
        ui->textEdit_7->setText(FileData[0]);
    else if (sizeChecker==1)
        ui->textEdit_7->setText(FileData[5]);
    else if (sizeChecker==2)
        ui->textEdit_7->setText(FileData[10]);

}

void GUI::on_label_2_linkActivated(const QString &link)
{
    ui->label->setVisible(false);
    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    ui->label_5->setVisible(false);
    ui->textEdit->setVisible(false);
    ui->textEdit_2->setVisible(false);
    ui->textEdit_3->setVisible(false);
    ui->textEdit_4->setVisible(false);
    ui->textEdit_6->setVisible(false);
    ui->pushButton->setVisible(false);
    ui->textEdit_7->setVisible(true);
    cout << sizeChecker<<endl;
    if(sizeChecker==0)
        ui->textEdit_7->setText(FileData[1]);
    else if (sizeChecker==1)
        ui->textEdit_7->setText(FileData[6]);
    else if (sizeChecker==2)
        ui->textEdit_7->setText(FileData[11]);

}


void GUI::on_label_3_linkActivated(const QString &link)
{

    ui->label->setVisible(false);
    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    ui->label_5->setVisible(false);
    ui->textEdit->setVisible(false);
    ui->textEdit_2->setVisible(false);
    ui->textEdit_3->setVisible(false);
    ui->textEdit_4->setVisible(false);
    ui->textEdit_6->setVisible(false);
    ui->pushButton->setVisible(false);
    ui->textEdit_7->setVisible(true);
    cout << sizeChecker<<endl;
    if(sizeChecker==0)
        ui->textEdit_7->setText(FileData[2]);
    else if (sizeChecker==1)
        ui->textEdit_7->setText(FileData[7]);
    else if (sizeChecker==2)
        ui->textEdit_7->setText(FileData[12]);
}


void GUI::on_label_4_linkActivated(const QString &link)
{
    ui->label->setVisible(false);
    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    ui->label_5->setVisible(false);
    ui->textEdit->setVisible(false);
    ui->textEdit_2->setVisible(false);
    ui->textEdit_3->setVisible(false);
    ui->textEdit_4->setVisible(false);
    ui->textEdit_6->setVisible(false);
    ui->pushButton->setVisible(false);
    ui->textEdit_7->setVisible(true);
    cout << sizeChecker<<endl;
    if(sizeChecker==0)
        ui->textEdit_7->setText(FileData[3]);
    else if (sizeChecker==1)
        ui->textEdit_7->setText(FileData[8]);
    else if (sizeChecker==2)
        ui->textEdit_7->setText(FileData[13]);
}


void GUI::on_label_5_linkActivated(const QString &link)
{
    ui->label->setVisible(false);
    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    ui->label_5->setVisible(false);
    ui->textEdit->setVisible(false);
    ui->textEdit_2->setVisible(false);
    ui->textEdit_3->setVisible(false);
    ui->textEdit_4->setVisible(false);
    ui->textEdit_6->setVisible(false);
    ui->pushButton->setVisible(false);
    ui->textEdit_7->setVisible(true);
    cout << sizeChecker<<endl;
    if(sizeChecker==0)
        ui->textEdit_7->setText(FileData[4]);
    else if (sizeChecker==1)
        ui->textEdit_7->setText(FileData[9]);
    else if (sizeChecker==2)
        ui->textEdit_7->setText(FileData[14]);

}



void GUI::on_pushButton_3_clicked()
{
page_generator(1);


}

void GUI::on_pushButton_2_clicked()
{    page_generator(0);


}


void GUI::on_pushButton_4_clicked()
{
    page_generator(2);
}

void GUI::home_page(){
    QDir directory(dirPath);

    if (!directory.exists())
        qDebug() << "The specified directory does not exist.";

    QStringList filters;
    filters << "*.*"; // Example filter: all files

    QStringList fileList = directory.entryList(filters, QDir::Files);

    foreach (QString file, fileList) {
        QString fullPath = directory.absoluteFilePath(file);
        fileNames << file.remove(".txt");
        filePaths << fullPath;
        cout << fullPath.toStdString()<<endl;
    }

    ui->setupUi(this);
    QPixmap pix ("E:\\Documents\\4th semester\\DS\\Lab\\OIP.JPEG");
    ui->label_6->setPixmap(pix);
    ui->textEdit_6->setVisible(true);
    ui->pushButton->setVisible(true);
    ui->label_6->setVisible(true);
    ui->label->setVisible(false);
    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    ui->label_5->setVisible(false);
    ui->textEdit->setVisible(false);
    ui->textEdit_2->setVisible(false);
    ui->textEdit_3->setVisible(false);
    ui->textEdit_4->setVisible(false);
    ui->textEdit_7->setVisible(false);
    ui->pushButton_2->setVisible(false);
    ui->pushButton_3->setVisible(false);
    ui->pushButton_4->setVisible(false);
    ui->pushButton_5->setVisible(false);
    ui->pushButton_7->setVisible(false);
    ui->pushButton_8->setVisible(false);
    ui->pushButton_9->setVisible(false);
    ui->pushButton_10->setVisible(false);
    ui->pushButton_11->setVisible(false);
    ui->pushButton_12->setVisible(false);

}



void GUI::on_pushButton_6_clicked()
{
    if (home==false)
    {
        ui->label_6->setPixmap(QPixmap("E:\\Documents\\4th semester\\DS\\Lab\\OIP.JPEG"));
        ui->textEdit_6->setVisible(true);
        ui->pushButton->setVisible(true);
        ui->label_6->setVisible(true);
        ui->label->setVisible(false);
        ui->label_2->setVisible(false);
        ui->label_3->setVisible(false);
        ui->label_4->setVisible(false);
        ui->label_5->setVisible(false);
        ui->textEdit->setVisible(false);
        ui->textEdit_2->setVisible(false);
        ui->textEdit_3->setVisible(false);
        ui->textEdit_4->setVisible(false);
        ui->textEdit_7->setVisible(false);
        ui->pushButton_2->setVisible(false);
        ui->pushButton_3->setVisible(false);
        ui->pushButton_4->setVisible(false);
        ui->pushButton_5->setVisible(false);
        ui->pushButton_7->setVisible(false);
        ui->pushButton_8->setVisible(false);
        ui->pushButton_9->setVisible(false);
        ui->pushButton_10->setVisible(false);
        ui->pushButton_11->setVisible(false);
        ui->pushButton_12->setVisible(false);


    }

}




void GUI::page_generator(int n){
    sizeChecker=n;
    num=+(5*n);
    ui->textEdit_7->setVisible(false);

    int S1=docsContainingSearchTerm.size();



        if (((S1==1)&&(n==0))||((S1==6)&&(n==1))||((S1==11)&&(n==2))||((S1==16)&&(n==3))||((S1==21)&&(n==4))||((S1==26)&&(n==5))||((S1==31)&&(n==6))||((S1==36)&&(n==7))||((S1==41)&&(n==8)))
        {
            ui->label->setText("<a href=Title>"+L1[num]+"</a>");
            ui->textEdit->setText(body[num]);
            ui->label_2->setVisible(false);
            ui->label_3->setVisible(false);
            ui->label_4->setVisible(false);
            ui->label_5->setVisible(false);
            ui->textEdit_2->setVisible(false);
            ui->textEdit_3->setVisible(false);
            ui->textEdit_4->setVisible(false);
        }


        else if (((S1==2)&&(n==0))||((S1==7)&&(n==1))||((S1==12)&&(n==2))||((S1==17)&&(n==3))||((S1==22)&&(n==4))||((S1==27)&&(n==5))||((S1==32)&&(n==6))||((S1==37)&&(n==7))||((S1==42)&&(n==8)))

        {
            ui->label->setText("<a href=Title>"+L1[num]+"</a>");
            ui->label_2->setText("<a href=Title>"+L1[num+1]+"</a>");
            ui->textEdit->setText(body[num]);
            ui->textEdit_2->setText(body[num+1]);
            ui->label_3->setVisible(false);
            ui->label_4->setVisible(false);
            ui->label_5->setVisible(false);
            ui->textEdit_3->setVisible(false);
            ui->textEdit_4->setVisible(false);
        }


        else if (((S1==3)&&(n==0))||((S1==8)&&(n==1))||((S1==13)&&(n==2))||((S1==18)&&(n==3))||((S1==23)&&(n==4))||((S1==28)&&(n==5))||((S1==33)&&(n==6))||((S1==38)&&(n==7))||((S1==43)&&(n==8)))

        {
            ui->label->setText("<a href=Title>"+L1[num]+"</a>");
            ui->label_2->setText("<a href=Title>"+L1[num+1]+"</a>");
            ui->label_3->setText("<a href=Title>"+L1[num+2]+"</a>");
            ui->textEdit->setText(body[num]);
            ui->textEdit_2->setText(body[num+1]);
            ui->textEdit_3->setText(body[num+2]);
            ui->label_4->setVisible(false);
            ui->label_5->setVisible(false);
            ui->textEdit_4->setVisible(false);
        }

        else if (((S1==4)&&(n==0))||((S1==9)&&(n==1))||((S1==14)&&(n==2))||((S1==19)&&(n==3))||((S1==24)&&(n==4))||((S1==29)&&(n==5))||((S1==34)&&(n==6))||((S1==39)&&(n==7))||((S1==44)&&(n==8)))

        {
            ui->label->setText("<a href=Title>"+L1[num]+"</a>");
            ui->label_2->setText("<a href=Title>"+L1[num+1]+"</a>");
            ui->label_3->setText("<a href=Title>"+L1[num+2]+"</a>");
            ui->label_4->setText("<a href=Title>"+L1[num+3]+"</a>");
            ui->textEdit->setText(body[num]);
            ui->textEdit_2->setText(body[num+1]);
            ui->textEdit_3->setText(body[num+2]);
            ui->textEdit_4->setText(body[num+3]);
            ui->label_5->setVisible(false);
        }

    else
        {
            ui->label->setVisible(true);
            ui->textEdit->setVisible(true);
            ui->label_2->setVisible(true);
            ui->label_3->setVisible(true);
            ui->label_4->setVisible(true);
            ui->label_5->setVisible(true);
            ui->textEdit_2->setVisible(true);
            ui->textEdit_3->setVisible(true);
            ui->textEdit_4->setVisible(true);
            ui->label->setText("<a href=Title>"+L1[num]+"</a>");
            ui->label_2->setText("<a href=Title>"+L1[num+1]+"</a>");
            ui->label_3->setText("<a href=Title>"+L1[num+2]+"</a>");
            ui->label_4->setText("<a href=Title>"+L1[num+3]+"</a>");
            ui->label_5->setText("<a href=Title>"+L1[num+4]+"</a>");
            ui->textEdit->setText(body[num]);
            ui->textEdit_2->setText(body[num+1]);
            ui->textEdit_3->setText(body[num+2]);
            ui->textEdit_4->setText(body[num+3]);

        }


}


void GUI::on_pushButton_5_clicked()
{
    page_generator(3);


}


void GUI::on_pushButton_7_clicked()
{
    page_generator(4);

}


void GUI::on_pushButton_8_clicked()
{
    page_generator(5);

}


void GUI::on_pushButton_9_clicked()
{
    page_generator(6);

}


void GUI::on_pushButton_10_clicked()
{
    page_generator(7);
}


void GUI::on_pushButton_11_clicked()
{
    page_generator(8);
}


void GUI::on_pushButton_13_clicked()
{
    ui->label->setVisible(false);
    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    ui->label_5->setVisible(false);
    ui->textEdit->setVisible(false);
    ui->textEdit_2->setVisible(false);
    ui->textEdit_3->setVisible(false);
    ui->textEdit_4->setVisible(false);
    ui->textEdit_6->setVisible(false);
    ui->pushButton->setVisible(false);
    ui->textEdit_7->setVisible(true);
}


void GUI::on_textEdit_7_copyAvailable(bool b)
{

}

