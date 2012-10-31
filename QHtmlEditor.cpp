/**
*Copyright(c) 2012 Somsubhra
*
*This program is distributed under the terms of the GPL v2.
*
*		    GNU GENERAL PUBLIC LICENSE
*		       Version 2, June 1991
*
*Copyright (C) 1989, 1991 Free Software Foundation, Inc.
*               51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
*Everyone is permitted to copy and distribute verbatim copies
*of this license document, but changing it is not allowed.
*/




/**
 * @author Somsubhra
 */

#include "QHtmlEditor.h"

#include <KApplication>
#include <KAction>
#include <KLocale>
#include <KActionCollection>
#include <KStandardAction>
#include <KFileDialog>
#include <KMessageBox>
#include <KIO/NetAccess>
#include <KSaveFile>
#include <QTextStream>
#include <QHBoxLayout>
#include <QWidget>

QHtmlEditor::QHtmlEditor(QWidget* parent):KXmlGuiWindow(parent), fileName(QString())
{
    QString txt = "<html><h1><font color='#364571'>Welcome to QHtmlEditor</font></h1><hr><p>Welcome to QHtmlEditor which is a browser integrated HTML editor where you can see the layout and design as you type. The integrated browser supports HTML5, CSS and Javascript. Type the HTML, CSS and Javascripts on the left panel and the output appears on the right panel instantly. To start creating immediately, remove this data by clicking Clear or pressing Ctrl+W.</p></body></html>";

    textArea = new QTextEdit;
    webView = new QWebView;

    textArea->setPlainText(txt);
    webView->setHtml(txt);

    QHBoxLayout* h_box = new QHBoxLayout;

    h_box->addWidget(textArea);
    h_box->addWidget(webView);

    connect(textArea, SIGNAL(textChanged()), SLOT(displayOutput()));
    QWidget* central_widget = new QWidget;

    central_widget->setLayout(h_box);

    setCentralWidget(central_widget);
    setupActions();

}

void QHtmlEditor::displayOutput()
{
    QString html = textArea->toPlainText();
    webView->setHtml(html);

}

void QHtmlEditor::setupActions()
{

    KAction *clearAction = new KAction(this);
    clearAction->setText(i18n("Clear"));
    clearAction->setIcon(KIcon("document-new"));
    clearAction->setShortcut(Qt::CTRL + Qt::Key_W);
    actionCollection()->addAction("clear", clearAction);

    connect(clearAction, SIGNAL(triggered(bool)),textArea, SLOT(clear()));

    KStandardAction::quit(kapp, SLOT(quit()), actionCollection());

    KStandardAction::open(this, SLOT(openFile()), actionCollection());

    KStandardAction::save(this, SLOT(saveFile()), actionCollection());

    KStandardAction::saveAs(this, SLOT(saveFileAs()), actionCollection());

    KStandardAction::openNew(this, SLOT(newFile()), actionCollection());


    setupGUI(Default,"qhtmleditorui.rc");
}

void QHtmlEditor::newFile()
{
    fileName.clear();
    textArea->clear();

}

void QHtmlEditor::openFile(const QString& inputFileName)
{

    QString tmpFile;
    if(KIO::NetAccess::download(inputFileName, tmpFile, this)) {
        QFile file(tmpFile);
        file.open(QIODevice::ReadOnly);

        textArea->setPlainText(QTextStream(&file).readAll());
        fileName = inputFileName;

        KIO::NetAccess::removeTempFile(tmpFile);
    }

    else {
        KMessageBox::error(this, KIO::NetAccess::lastErrorString());
    }
}

void QHtmlEditor::openFile()
{

    openFile(KFileDialog::getOpenFileName());
}

void QHtmlEditor::saveFile()
{

    if(!fileName.isEmpty()) {
        saveFileAs(fileName);
    }
    else {
        saveFileAs();
    }
}

void QHtmlEditor::saveFileAs()
{
    saveFileAs(KFileDialog::getSaveFileName());
}

void QHtmlEditor::saveFileAs(const QString& outputFileName)
{

    KSaveFile file(outputFileName);

    file.open();

    QByteArray outputByteArray;
    outputByteArray.append(textArea->toPlainText());
    file.write(outputByteArray);
    file.finalize();
    file.close();

    fileName = outputFileName;
}


QHtmlEditor::~QHtmlEditor()
{}

#include "QHtmlEditor.moc"
