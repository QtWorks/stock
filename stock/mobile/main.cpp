
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2018 Igor Mironchik

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// Qt include.
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QIcon>
#include <QTranslator>
#include <QLocale>
#include <QStandardPaths>
#include <QDir>
#include <QQmlContext>

// Stock include.
#include "qml_cpp_signals.hpp"


static const QString c_configFoler = QLatin1String( "Stock" );


int main( int argc, char ** argv )
{
	QGuiApplication app( argc, argv );

	QIcon appIcon( ":/img/icon_256x256.png" );
	appIcon.addFile( ":/img/icon_128x128.png" );
	appIcon.addFile( ":/img/icon_64x64.png" );
	app.setWindowIcon( appIcon );

	QTranslator appTranslator;
	appTranslator.load( "./tr/stock_" + QLocale::system().name() );
	app.installTranslator( &appTranslator );

	const auto configsPath = QStandardPaths::standardLocations(
		QStandardPaths::ConfigLocation ).first();

	QDir dir( configsPath );

	if( !dir.exists( c_configFoler ) )
		dir.mkdir( c_configFoler );

	const auto cfgFileName = configsPath + QLatin1String( "/" ) + c_configFoler +
		QLatin1String( "/stock.cfg" );

	bool passwordSet = false;
	QString password;

	if( QFileInfo::exists( cfgFileName ) )
	{

	}

	Stock::QmlCppSignals sigs( cfgFileName );

	QQmlApplicationEngine engine;
	engine.rootContext()->setContextProperty( "passwordSet", passwordSet );
	engine.rootContext()->setContextProperty( "password", password );
	engine.rootContext()->setContextProperty( "qmlCppSignals", &sigs );
	engine.load( QUrl( "qrc:/qml/main.qml" ) );

	if( engine.rootObjects().isEmpty() )
		return -1;

	return app.exec();
}
