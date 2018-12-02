#ifndef QHCHUFF_H
#define QHCHUFF_H

#include <QMainWindow>

namespace Ui {
    class Qhchuff;
}

class Qhchuff : public QMainWindow {
    Q_OBJECT
public:
    Qhchuff(QWidget *parent = 0);
    ~Qhchuff();
    int compress(char* filename);
    int uncompress(char* filemane);
protected:
    void changeEvent(QEvent *e);

private:
    Ui::Qhchuff *ui;

private slots:

    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
};

#endif // QHCHUFF_H
