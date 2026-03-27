#include "Lab10_11_Farmacie.h"
#include <QtWidgets/QApplication>
#include "gui.h"
#include "teste.h"
#include "guiReteta.h"
#include "service.h"
#include "reteta.h"
#include "repo.h"

int main(int argc, char* argv[])
{
    Teste teste;
    teste.toateTestele();
    RepoFile repo("medicamente.txt");
    ServiceMedicamente srv(repo);
    Reteta recp;
    QApplication a(argc, argv);
    //GuiReteta w2(recp, srv);
    Gui w1(recp, srv);
    w1.show();
    //w2.show();
    return a.exec();
}
