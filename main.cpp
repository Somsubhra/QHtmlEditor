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
#include<KApplication>
#include <KAboutData>
#include <KCmdLineArgs>
#include <KUrl>

int main(int argc, char* argv[]) {
    KAboutData aboutData("QHtmlEditor","QHtmlEditor",
                         ki18n("QHtmlEditor"),"1.0",
                         ki18n("HTML Editor"),
                         KAboutData::License_GPL,
                         ki18n("Copyright(c) 2012 Somsubhra")
                        );

    KCmdLineArgs::init(argc, argv, &aboutData);

    KCmdLineOptions options;

    options.add("+[file]", ki18n("HTML Document to open"));

    KCmdLineArgs::addCmdLineOptions(options);

    KApplication app;

    QHtmlEditor* window = new QHtmlEditor();

    window->show();

    KCmdLineArgs *args = KCmdLineArgs::parsedArgs();

    if(args->count()) {
        window->openFile(args->url(0).url());
    }

    return app.exec();
}
