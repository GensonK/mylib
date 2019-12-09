//
// Created by twak on 14/10/2019.
//

#ifndef RESPONSIVELABEL_H
#define RESPONSIVELABEL_H


#include <QLabel>
#include <QString>
#include <map>

using namespace std;


// Please add to, but DO NOT modify the constants in this file.

// label names that are displayed
const QString
kHomeLink = "home",
kBackButton = "back",
kShoppingBasket = "basket",
kSignIn = "sign-in",
kNavTabs = "navigation tabs",
kFooter = "fat footer",
kAdvert = "advert",
kSearchButton = "search",
kSearchResult = "result2",
kSearchResult1 = "result1",//to add result
kSearchText = "search query",
kSearchForward = ">",
kSearchBackward = "<",
kSearchOptions = "search options",
kViewDetailButt = "view button2",
kViewDetailButt1 = "view button1";// extra function: button to view more details about the result

// every label name has a colour
const map<QString, QString> kColours = {
        make_pair(kHomeLink,       "#ffaaff"),
        make_pair(kBackButton,     "#ffffaa"),
        make_pair(kShoppingBasket, "#ffaaaa"),
        make_pair(kSignIn,         "#aaffaa"),
        make_pair(kNavTabs,        "#ffa9d3"),
        make_pair(kFooter,         "#66ffaa"),
        make_pair(kAdvert,         "#ffaa66"),
        make_pair(kSearchButton,   "#aaffff"),

        make_pair(kSearchResult1,   "#99ddff"),
		make_pair(kSearchResult,   "#99ddff"),
		make_pair(kSearchText,     "#aaaaff"),
        make_pair(kSearchForward,  "#5caeff"),
        make_pair(kSearchBackward, "#5caeff"),
        make_pair(kSearchOptions,  "#9dceff"),
		make_pair(kViewDetailButt1,  "#9dccff"),
		make_pair(kViewDetailButt,  "#9dccff")
    };

class ResponsiveLabel : public QLabel {
public:
    ResponsiveLabel(QString name) ;
    ResponsiveLabel(QString name, QString colour) ;
};


#endif // RESPONSIVELABEL_H
