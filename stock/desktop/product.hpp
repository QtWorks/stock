
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

#ifndef STOCK_PRODUCT_HPP_INCLUDED
#define STOCK_PRODUCT_HPP_INCLUDED

// Qt include.
#include <QDialog>
#include <QScopedPointer>


namespace Stock {

//
// ProductDlg
//

class ProductDlgPrivate;

//! Dialog with settings of product.
class ProductDlg Q_DECL_FINAL
	:	public QDialog
{
	Q_OBJECT

public:
	ProductDlg( const QString & code,
		const QString & place,
		quint64 count,
		const QString & desc,
		const QStringList & codes,
		const QStringList & places,
		bool isNewProduct,
		QWidget * parent );
	virtual ~ProductDlg();

	//! \return Code.
	QString code() const;
	//! \return Place.
	QString place() const;
	//! \return Amount.
	quint64 count() const;
	//! \return Description.
	QString desc() const;

private:
	Q_DISABLE_COPY( ProductDlg )

	QScopedPointer< ProductDlgPrivate > d;
}; // class ProductDlg

} /* namespace Stock */

#endif // STOCK_PRODUCT_HPP_INCLUDED