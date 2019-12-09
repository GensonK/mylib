//
// Created by twak on 07/10/2019.
//

#include "responsive_layout.h"
#include "responsive_label.h"
#include <iostream>



using namespace std;

// you should probably make extensive changes to this function


void ResponsiveLayout::setGeometry(const QRect &r /* our layout should always fit inside r */ ) {

    QLayout::setGeometry(r);

    // for all the Widgets added in ResponsiveWindow.cpp
    for (int i = 0; i < list_.size(); i++) {

        QLayoutItem *o = list_.at(i);
		
        try {
            // cast the widget to one of our responsive labels
            ResponsiveLabel *label = static_cast<ResponsiveLabel *>(o->widget());

			if (label == NULL) // null: cast failed on pointer
				cout << "warning, unknown widget class in layout" << endl;
			else if (label->text() == kNavTabs) // headers go at the top
				label->setGeometry(0 + r.x(), 0 + r.y(), r.width(), 0.2*r.height());//relative position and size for base menu
			else if (label->text() == kBackButton)
				label->setGeometry(0.008* r.width(), 0.04* r.height(), 0.24*r.width(), 0.12*r.height());//relative position and size for base menu
			else if (label->text() == kShoppingBasket)
				label->setGeometry(0.256* r.width(), 0.04* r.height(), 0.24*r.width(), 0.12*r.height());//relative position and size for base menu
			else if (label->text() == kSignIn)
				label->setGeometry(0.504* r.width(), 0.04* r.height(), 0.24*r.width(), 0.12*r.height());//relative position and size for base menu
			else if (label->text() == kHomeLink)
				label->setGeometry(0.752* r.width(), 0.04* r.height(), 0.24*r.width(), 0.12*r.height());//relative position and size for base menu

			else if (label->text() == kAdvert && r.width() > 540 && r.height() > 540)//only when size > 540*540 then advertise and  footer appear
				label->setGeometry(0, 0.21 *r.height(), 0.25*r.width(), 0.5*r.height());
			else if (label->text() == kFooter && r.width() > 540 && r.height() > 540)
				label->setGeometry(0, 0.8*r.height(), r.width(), 0.2*r.height());

			else if (label->text() == kSearchText)
				if (r.width() > 540 && r.height() > 540)
					label->setGeometry(0.26*r.width(), 0.21*r.height(), 0.6*r.width(), 0.1*r.height());
				else
					label->setGeometry(0.1*r.width(), 0.21*r.height(), 0.6*r.width(), 0.1*r.height());

			else if (label->text() == kSearchOptions)
				if (r.width() > 540 && r.height() > 540)
					label->setGeometry(0.26*r.width(), 0.32*r.height(), 0.6*r.width(), 0.1*r.height());
				else
					label->setGeometry(0.1*r.width(), 0.32*r.height(), 0.6*r.width(), 0.1*r.height());
			else if (label->text() == kSearchButton)
				if (r.width() > 540 && r.height() > 540)
					label->setGeometry(0.87*r.width(), 0.21*r.height(), 0.13*r.width(), 0.21*r.height());
				else
					label->setGeometry(0.74*r.width(), 0.21*r.height(), 0.13*r.width(), 0.21*r.height());
			else if (label->text() == kSearchResult1)
				if (r.width() < 540 || r.height() < 540)
					label->setGeometry(0.1*r.width(), 0.5*r.height(), 0.5*r.width(), 0.12*r.height());
				else
					label->setGeometry(0.26*r.width(), 0.5 *r.height(), 0.5*r.width(), 0.12*r.height());
			else if (label->text() == kSearchResult)
				if (r.width() < 540 || r.height() < 540)
					label->setGeometry(0.1*r.width(), 0.621*r.height(), 0.5*r.width(), 0.12*r.height());
				else
					label->setGeometry(0.26*r.width(), 0.621 *r.height(), 0.5*r.width(), 0.12*r.height());
			else if (label->text() == kViewDetailButt1)
				if (r.width() < 540 || r.height() < 540)
					label->setGeometry(0.7*r.width(), 0.5 *r.height(), 0.17*r.width(), 0.12*r.height());
				else
					label->setGeometry(0.86*r.width(), 0.5 *r.height(), 0.14*r.width(), 0.12*r.height());
			else if (label->text() == kViewDetailButt)
				if (r.width() < 540 || r.height() < 540)
					label->setGeometry(0.7*r.width(), 0.621 *r.height(), 0.17*r.width(), 0.12*r.height());
				else
					label->setGeometry(0.86*r.width(), 0.621 *r.height(), 0.14*r.width(), 0.12*r.height());
			else if (label->text() == kSearchForward)        //forward and backward button are set as absolute size
				if (r.width() < 540 || r.height() < 540)
					label->setGeometry(0.7*r.width(), 0.9*r.height(), 20, 20);
				else
					label->setGeometry(0.76*r.width(), 0.8*r.height()-20, 20, 20);
			else if (label->text() == kSearchBackward)
				if (r.width() < 540 || r.height() < 540)
					label->setGeometry(0.2*r.width(), 0.9*r.height(), 20, 20);
				else
					label->setGeometry(0.36*r.width() , 0.8*r.height() - 20, 20, 20);
			else // otherwise: disappear label by moving out of bounds
				label->setGeometry(-1, -1, 0, 0);

	
        }
        catch (bad_cast) {
            // bad_case: cast failed on reference...
            cout << "warning, unknown widget class in layout" << endl;
        }
    }
}

// following methods provide a trivial list-based implementation of the QLayout class
int ResponsiveLayout::count() const {
    return list_.size();
}

QLayoutItem *ResponsiveLayout::itemAt(int idx) const {
    return list_.value(idx);
}

QLayoutItem *ResponsiveLayout::takeAt(int idx) {
    return idx >= 0 && idx < list_.size() ? list_.takeAt(idx) : 0;
}

void ResponsiveLayout::addItem(QLayoutItem *item) {
    list_.append(item);
}

QSize ResponsiveLayout::sizeHint() const {
    return minimumSize();
}

QSize ResponsiveLayout::minimumSize() const {//minimum size of layout
    return QSize(320,320);
}
QSize ResponsiveLayout::maxmumSize() const {//maxmum size of layout
	return QSize(1920, 1080);
}

ResponsiveLayout::~ResponsiveLayout() {
    QLayoutItem *item;
    while ((item = takeAt(0)))
        delete item;
}
