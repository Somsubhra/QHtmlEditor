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


#ifndef QHtmlEditor_H
#define QHtmlEditor_H

#include <KXmlGuiWindow>
#include <QWebView>
#include <KTextEdit>

class QHtmlEditor : public KXmlGuiWindow
{
    Q_OBJECT
public:
    QHtmlEditor(QWidget *parent=0);
    virtual ~QHtmlEditor();
    void openFile(const QString &inputFileName);


private:
    void setupActions();
    QWebView* webView;
    QTextEdit* textArea;
    QString fileName;

private slots:
    void newFile();
    void openFile();
    void saveFile();
    void saveFileAs();
    void saveFileAs(const QString &outputFileName);
    void displayOutput();

};

#endif // QHtmlEditor_H
