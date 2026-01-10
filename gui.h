#ifndef GUI_H
#define GUI_H
#include <vector>
#include <QMainWindow>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui {
class GUI;
}
QT_END_NAMESPACE

class GUI : public QMainWindow
{
    Q_OBJECT

public:
    GUI(QWidget *parent = nullptr);
    QString dirPath= "E:\\Documents\\4th semester\\DS\\Project Files";
    vector<int> docsContainingSearchTerm;
    string directoryPath = "E:\\Documents\\4th semester\\DS\\Project Files";
    QStringList filePaths,fileNames;
    QStringList L1,L2;
    QStringList FileData,body;
    int sizeChecker;
    bool home;
    int num=0;

    ~GUI();

private slots:
    void on_pushButton_clicked();

    void on_label_linkActivated(const QString &link);

    void on_verticalScrollBar_rangeChanged(int min, int max);

    void on_verticalScrollBar_actionTriggered(int action);

    void on_verticalScrollBar_customContextMenuRequested(const QPoint &pos);

    void on_verticalScrollBar_valueChanged(int value);

    void on_label_2_linkActivated(const QString &link);

    void on_label_3_linkActivated(const QString &link);

    void on_label_4_linkActivated(const QString &link);

    void on_label_5_linkActivated(const QString &link);

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_7_clicked();
    void home_page();

    void on_pushButton_6_clicked();

    void on_pushButton_8_clicked();
    void page_generator(int n);

    void on_pushButton_5_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();



    void on_pushButton_13_clicked();

    void on_textEdit_7_copyAvailable(bool b);

private:
    Ui::GUI *ui;


};
#endif // GUI_H
