#include "../include/Editor.hpp"

Editor::Editor():QWidget()
{
 apply.setText(tr("Apply"));
 ok.setText(tr("Ok"));
 cancel.setText(tr("Cancel"));
 alab.setText(tr("Answer A: "));
 blab.setText(tr("Answer B: "));
 clab.setText(tr("Answer C: "));
 dlab.setText(tr("Answer D: "));
 rlab.setText(tr("Richtige Antwort: "));
 g.addWidget(&alab);
 g.addWidget(&A);
 g.addWidget(&blab);
 g.addWidget(&B);
 g.addWidget(&clab);
 g.addWidget(&C);
 g.addWidget(&dlab);
 g.addWidget(&D);
 g.addWidget(&rlab);
 g.addWidget(&R);
 g.addWidget(&ok);
 g.addWidget(&cancel);
 g.addWidget(&apply);
 setLayout(&g);
 //resize(500,500);
}

Editor::~Editor()
{
    //dtor
}
