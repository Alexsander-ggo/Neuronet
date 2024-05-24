#include "Form.h"

#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication application(argc, argv);
    Form form;
    form.show();
    return application.exec();
    return 0;
}
